"""Integration checks for the C programs; Python is only used to run tests."""
import concurrent.futures
from pathlib import Path
import socket
import subprocess
import tempfile
import time
import unittest

ROOT = Path(__file__).resolve().parent

class LibraryTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=ROOT)
        self.addCleanup(self.temp.cleanup)
        with socket.socket() as s:
            s.bind(('127.0.0.1', 0))
            self.port = s.getsockname()[1]
        self.start()
        self.addCleanup(self.stop)

    def start(self):
        self.process = subprocess.Popen([str(ROOT / 'server'), str(self.port),
            '127.0.0.1', str(Path(self.temp.name) / 'books.tsv')],
            stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
        for _ in range(100):
            try:
                with socket.create_connection(('127.0.0.1', self.port), timeout=.2):
                    return
            except OSError:
                if self.process.poll() is not None:
                    raise RuntimeError(self.process.stderr.read().decode())
                time.sleep(.02)
        raise RuntimeError('Server did not start')

    def stop(self):
        if self.process.poll() is None:
            self.process.terminate()
            self.process.wait(timeout=5)
        self.process.stderr.close()

    def request(self, command):
        with socket.create_connection(('127.0.0.1', self.port), timeout=3) as s:
            s.sendall((command + '\n').encode())
            with s.makefile('r') as f:
                result = []
                for line in f:
                    if line == 'END\n':
                        return ''.join(result)
                    result.append(line)
                raise AssertionError('Missing response terminator')

    def test_workflow_persistence_and_client(self):
        self.assertIn('No books', self.request('LIST'))
        self.assertIn('OK', self.request('ADD\tThe C Programming Language\tKernighan and Ritchie'))
        self.assertIn('1 | The C', self.request('SEARCH\tKernighan'))
        self.assertIn('ERROR', self.request('BORROW\t999\tAlice'))
        self.assertIn('OK', self.request('BORROW\t1\tAlice'))
        self.assertIn('ERROR', self.request('BORROW\t1\tBob'))
        self.assertIn('ERROR', self.request('RETURN\t1\tBob'))
        self.stop()
        self.start()
        self.assertIn('Borrowed by: Alice', self.request('LIST'))
        self.assertIn('OK', self.request('RETURN\t1\tAlice'))
        self.assertIn('Available', self.request('LIST'))
        result = subprocess.run([str(ROOT / 'client'), '127.0.0.1', str(self.port)],
            input='1\n0\n', text=True, capture_output=True, timeout=5)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('The C Programming Language', result.stdout)
        self.assertIn('ERROR', self.request('ADD\t\tAuthor'))
        self.assertIn('ERROR', self.request('UNKNOWN'))

    def test_existing_borrower_is_managed(self):
        self.stop()
        Path(self.temp.name, 'books.tsv').write_text('1\tExisting title\tAuthor\tshohom\n')
        self.start()
        self.assertIn('shohom', self.request('MEMBERS'))
        loan = self.request('LOANS').splitlines()[0].split(' | ')
        self.assertEqual(loan[1:3], ['1', '1'])
        self.assertEqual(loan[3:6], ['0', '0', '0'])
        self.assertIn('OK', self.request('CHECKIN\t1'))
        self.stop()
        self.start()
        self.assertIn('Available', self.request('LIST'))
        self.assertGreater(int(self.request('LOANS').splitlines()[0].split(' | ')[5]), 0)
        self.assertEqual(len(self.request('LOANS').splitlines()), 1)

    def test_stock_management_and_persistence(self):
        self.assertIn('OK 3 copies added', self.request('STOCK_ADD\tA Title\tAn Author\t3'))
        lines = self.request('LIST').splitlines()
        self.assertEqual([int(line.split(' | ')[0]) for line in lines], [1, 2, 3])
        self.assertIn('ERROR', self.request('STOCK_ADD\tA Title\tAn Author\t51'))
        self.assertEqual(len(self.request('LIST').splitlines()), 3)
        self.assertIn('OK', self.request('STOCK_SET\t1\tDAMAGED'))
        self.assertIn('OK', self.request('STOCK_SET\t2\tLOST'))
        self.assertIn('Damaged', self.request('LIST'))
        self.assertIn('Lost', self.request('LIST'))
        self.request('MEMBER_ADD\tReader\treader@example.com')
        self.assertIn('ERROR', self.request('CHECKOUT\t1\t1\t14'))
        self.assertIn('ERROR', self.request('HOLD\t2\t1'))
        self.assertIn('OK', self.request('STOCK_SET\t3\tREMOVED'))
        self.assertIn('Removed', self.request('LIST'))
        self.assertIn('ERROR', self.request('CHECKOUT\t3\t1\t14'))
        self.assertIn('ERROR', self.request('HOLD\t3\t1'))
        self.assertIn('OK', self.request('STOCK_SET\t3\tACTIVE'))
        self.assertIn('OK', self.request('CHECKOUT\t3\t1\t14'))
        self.assertIn('ERROR', self.request('STOCK_SET\t3\tREMOVED'))
        self.request('CHECKIN\t1')
        self.assertIn('OK', self.request('HOLD\t3\t1'))
        self.assertIn('ERROR', self.request('STOCK_SET\t3\tREMOVED'))
        self.request('CANCEL_HOLD\t1')
        self.assertIn('OK', self.request('STOCK_SET\t3\tREMOVED'))
        self.stop(); self.start()
        self.assertIn('Damaged', self.request('LIST'))
        self.assertIn('Lost', self.request('LIST'))
        self.assertIn('Removed', self.request('LIST'))
        self.assertEqual(len(self.request('LIST').splitlines()), 3)
        self.assertIn('OK', self.request('STOCK_SET\t1\tACTIVE'))
        self.assertIn('OK', self.request('STOCK_SET\t3\tACTIVE'))
        self.assertIn('Available', self.request('SEARCH\tA Title'))

    def test_reservations_and_renewals(self):
        self.assertIn('OK', self.request('MEMBER_ADD\tAlice\talice@example.com'))
        self.assertIn('OK', self.request('MEMBER_ADD\tBob\tbob@example.com'))
        self.request('ADD\tReserved copy\tAuthor')
        self.assertIn('OK', self.request('CHECKOUT\t1\t1\t14'))
        self.assertIn('OK', self.request('HOLD\t1\t2'))
        self.assertIn('ERROR', self.request('HOLD\t1\t2'))
        self.assertIn('ERROR', self.request('RENEW\t1\t14'))
        self.assertIn('OK', self.request('CHECKIN\t1'))
        self.assertIn('Reserved for: Bob', self.request('LIST'))
        self.assertIn('ERROR', self.request('BORROW\t1\tAlice'))
        self.assertIn('ERROR', self.request('CHECKOUT\t1\t1\t14'))
        self.stop(); self.start()
        self.assertIn('Reserved for: Bob', self.request('LIST'))
        self.assertIn('OK', self.request('CHECKOUT\t1\t2\t14'))
        self.assertIn('1 | 1 | 2 |', self.request('HOLDS'))
        self.assertIn('OK', self.request('RENEW\t2\t14'))
        self.assertIn('OK', self.request('RENEW\t2\t14'))
        self.assertIn('ERROR', self.request('RENEW\t2\t14'))
        self.stop(); self.start()
        self.assertTrue(self.request('LOANS').splitlines()[0].endswith(' | 2'))
        self.request('ADD\tSecond copy\tAuthor')
        self.assertIn('OK', self.request('HOLD\t2\t1'))
        self.assertIn('OK', self.request('CANCEL_HOLD\t2'))
        self.assertIn('Available', self.request('SEARCH\tSecond copy'))
        self.assertIn('ERROR', self.request('CANCEL_HOLD\t2'))

    def test_browser_workflow(self):
        import http.client
        from urllib.parse import quote
        def api(*parts):
            c = http.client.HTTPConnection('127.0.0.1', self.port, timeout=5)
            c.request('POST', '/api?' + quote('\t'.join(parts), safe=''))
            r = c.getresponse()
            self.assertEqual(r.status, 200)
            text = r.read().decode()
            c.close()
            self.assertTrue(text.endswith('END\n'))
            return text
        self.assertIn('OK', api('MEMBER_ADD', 'Browser Member', 'browser@example.com'))
        self.assertIn('OK', api('ADD', 'Web title', 'Web author'))
        self.assertIn('OK 2 copies added', api('STOCK_ADD', 'Web stock', 'Author', '2'))
        self.assertIn('OK', api('STOCK_SET', '2', 'DAMAGED'))
        self.assertIn('Damaged', api('LIST'))
        self.assertIn('OK', api('STOCK_SET', '3', 'REMOVED'))
        self.assertIn('Removed', api('LIST'))
        self.assertIn('OK', api('STOCK_SET', '3', 'ACTIVE'))
        self.assertIn('OK', api('CHECKOUT', '1', '1', '14'))
        self.assertIn('Browser Member', api('LIST'))
        self.assertIn('1 | 1 | 1 |', api('LOANS'))
        self.assertIn('OK', api('MEMBER_ADD', 'Waiting Member', 'waiting@example.com'))
        self.assertIn('OK', api('HOLD', '1', '2'))
        self.assertIn('ERROR', api('RENEW', '1', '14'))
        self.assertIn('1 | 1 | 2 |', api('HOLDS'))
        self.assertIn('OK', api('CHECKIN', '1'))
        self.assertIn('Reserved for: Waiting Member', api('LIST'))
        self.assertIn('ERROR', api('CHECKOUT', '1', '1', '14'))
        self.assertIn('OK', api('CHECKOUT', '1', '2', '14'))
        self.assertIn('OK', api('RENEW', '2', '14'))
        self.assertIn('OK', api('CHECKIN', '2'))
        self.assertIn('Available', api('LIST'))
        self.assertIn('ERROR', api('CHECKIN', '1'))
        for path, content_type in [('/app.js?v=8','application/javascript'),('/style.css?v=8','text/css')]:
            c = http.client.HTTPConnection('127.0.0.1', self.port, timeout=5)
            c.request('GET', path)
            r = c.getresponse()
            self.assertEqual(r.status, 200)
            self.assertIn(content_type, r.getheader('Content-Type'))
            self.assertEqual(r.getheader('Cache-Control'), 'no-store')
            self.assertTrue(r.read())
            c.close()

    def test_registered_circulation(self):
        self.assertIn('OK', self.request('MEMBER_ADD\tAlice\talice@example.com'))
        self.assertIn('ERROR', self.request('MEMBER_ADD\tOther\talice@example.com'))
        self.assertIn('ERROR', self.request('CHECKOUT\t1\t1\t14'))
        for i in range(6):
            self.request('ADD\tBook '+str(i)+'\tAuthor')
        self.assertIn('ERROR', self.request('CHECKOUT\t1\t999\t14'))
        self.assertIn('ERROR', self.request('CHECKOUT\t1\t1\t61'))
        for i in range(1, 6):
            self.assertIn('OK', self.request('CHECKOUT\t'+str(i)+'\t1\t14'))
        self.assertIn('ERROR', self.request('CHECKOUT\t6\t1\t14'))
        self.assertIn('ERROR', self.request('RETURN\t1\tAlice'))
        loan = self.request('LOANS').splitlines()[-1].split(' | ')
        self.assertEqual(int(loan[4])-int(loan[3]), 14*86400)
        self.stop()
        self.start()
        self.assertIn('alice@example.com', self.request('MEMBERS'))
        self.assertEqual(len(self.request('LOANS').splitlines()), 5)
        self.assertIn('OK', self.request('CHECKIN\t1'))
        self.assertIn('ERROR', self.request('CHECKIN\t1'))
        self.assertIn('OK', self.request('CHECKOUT\t6\t1\t7'))
        self.assertIn('OK', self.request('EDIT\t1\tCorrected title\tNew author'))
        self.assertIn('Corrected title', self.request('LIST'))
        self.stop()
        self.start()
        returned = self.request('LOANS').splitlines()[-1].split(' | ')
        self.assertGreater(int(returned[5]), 0)

    def test_http_pages_and_api(self):
        import http.client
        for path, expected in [('/', 'Dashboard'), ('/books', 'Book collection'),
                               ('/add', 'Add a book'), ('/loans', 'Borrow & return'),
                               ('/style.css', 'nav'), ('/app.js', 'fetch'), ('/holds', 'Reservations'), ('/stock', 'Stock management')]:
            c = http.client.HTTPConnection('127.0.0.1', self.port, timeout=3)
            c.request('GET', path)
            r = c.getresponse()
            self.assertEqual(r.status, 200)
            self.assertIn(expected, r.read().decode())
            c.close()
        c = http.client.HTTPConnection('127.0.0.1', self.port, timeout=3)
        c.request('GET', '/unknown')
        self.assertEqual(c.getresponse().status, 404)
        c.close()
        c = http.client.HTTPConnection('127.0.0.1', self.port, timeout=3)
        c.request('POST', '/api?ADD%09Web%20Book%09Author')
        r = c.getresponse()
        self.assertIn('OK Book added', r.read().decode())
        c.close()
        self.assertIn('Web Book', self.request('LIST'))

    def test_concurrent_borrow_and_stream_frames(self):
        self.request('ADD\tOne copy\tAuthor')
        with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
            results = list(pool.map(self.request, ['BORROW\t1\tAlice', 'BORROW\t1\tBob']))
        self.assertEqual(sum('OK' in r for r in results), 1)
        with socket.create_connection(('127.0.0.1', self.port), timeout=3) as s:
            s.sendall(b'LI')
            s.sendall(b'ST\nSEARCH\tOne\n')
            with s.makefile('r') as f:
                for _ in range(2):
                    self.assertIn('One copy', f.readline())
                    self.assertEqual(f.readline(), 'END\n')

if __name__ == '__main__':
    unittest.main(verbosity=2)
