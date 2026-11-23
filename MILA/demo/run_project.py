#!/usr/bin/env python3
"""Local browser runner for the actual compiled MILA C programs (no packages)."""
import argparse
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
ACTIVITIES = [
    {"id": "01_pogil_arrays", "name": "POGIL", "topic": "Array sum and mean",
     "example": "5 1 2 3 4 5", "format": "Count (1–100), followed by that many integers.",
     "meaning": "The loop visits every element once and accumulates the sum. Floating-point division gives the mean."},
    {"id": "02_jigsaw_statistics", "name": "Jigsaw", "topic": "Modular statistics",
     "example": "5 12 7 19 7 5", "format": "Count (1–100), followed by that many integers.",
     "meaning": "Separate functions read the data, find extrema, and calculate the total."},
    {"id": "03_scale_up_inventory", "name": "SCALE-UP", "topic": "Inventory valuation",
     "example": "3\n2 1250\n3 499\n0 999", "format": "Item count, then quantity and unit price in cents for each item. Quantity: 0–10000; price: 0–1000000.",
     "meaning": "Structures hold each item. Integer cents keep the total exact: 2500 + 1497 = 3997."},
    {"id": "04_pltbl_prime", "name": "PLTBL", "topic": "Prime checking",
     "example": "97", "format": "One signed integer. Try 97 (prime) or 49 (composite).",
     "meaning": "Try divisors up to the square root. The expression d <= n / d avoids squaring the divisor."},
    {"id": "05_critical_bounds", "name": "Critical Pedagogy", "topic": "Safe array bounds",
     "example": "3 10 -2 5", "format": "Count (0–100), followed by that many integers. Try 101 to see validation.",
     "meaning": "The program validates the count before indexing the array and initializes its wide accumulator."},
    {"id": "06_quiz", "name": "Game-Based Learning", "topic": "C concept quiz",
     "example": "1 2 3 1 2", "format": "Five choices, each 1–3, in the question order below.",
     "meaning": "One point per correct answer. Feedback identifies the correct choice for each question."},
    {"id": "07_role_play_swap", "name": "Role Play", "topic": "Values and pointers",
     "example": "10 20", "format": "Two signed integers to exchange.",
     "meaning": "The first call swaps local copies. The second call writes through pointers to change the caller's objects."},
    {"id": "08_flipped_search", "name": "Flipped Classroom", "topic": "Binary search",
     "example": "5\n2 4 6 8 10\n8", "format": "Count (0–100), sorted integers, then target. A match returns a zero-based index; -1 means absent.",
     "meaning": "Search repeatedly halves the candidate interval. The C program checks that input is sorted first."},
]
PROGRAMS = {item["id"] for item in ACTIVITIES}

HTML = r'''<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>MILA — Run the C project</title><style>
:root{font-family:Arial,sans-serif;color:#edf3ff;background:#101827;color-scheme:dark}*{box-sizing:border-box}
body{margin:0}header{padding:26px 38px;border-bottom:1px solid #30415b;display:flex;justify-content:space-between;align-items:center}
.eyebrow{color:#65ddd4;letter-spacing:2px;font-size:12px;font-weight:bold}h1{margin:8px 0 0;font-size:28px}.identity{text-align:right;color:#b4c3d9;font-size:13px;line-height:1.7}
main{max-width:1380px;margin:auto;padding:26px 38px;display:grid;grid-template-columns:270px 1fr;gap:30px}
nav button{display:block;width:100%;text-align:left;margin:0 0 8px;padding:13px 14px;border:1px solid #30415b;border-radius:9px;background:#172438;color:#b8c8df;cursor:pointer}
nav button[aria-pressed=true]{background:#254448;color:#a2fff2;border-color:#65ddd4}nav small{display:block;margin-top:5px;font-size:11px}
section{min-width:0}h2{font-size:25px;margin:1px 0 8px}.topic{color:#b4c3d9;margin:0 0 20px;line-height:1.5;font-size:15px}
label,.label{display:block;color:#c8d5e8;font-size:13px;font-weight:bold;margin-bottom:9px}
textarea{width:100%;height:105px;resize:vertical;padding:14px;border:1px solid #4e6686;border-radius:8px;background:#0b1320;color:#f1f7ff;font:18px/1.5 monospace}
button{font-size:14px}button:focus-visible,textarea:focus-visible{outline:3px solid #85f4e5;outline-offset:3px}.actions{display:flex;gap:12px;margin:13px 0 18px;align-items:center}
.primary{background:#72e6d7;color:#092621;border:0;border-radius:7px;font-weight:bold;padding:12px 22px;cursor:pointer}.secondary{background:none;color:#b9cbe2;border:1px solid #516582;border-radius:7px;padding:11px 18px;cursor:pointer}
.status{color:#aebed5;font-size:13px}.terminal{background:#080f1b;border:1px solid #30415b;border-radius:10px;overflow:hidden}.bar{padding:11px 16px;border-bottom:1px solid #27374f;display:flex;justify-content:space-between;font-size:12px;color:#a9c1db}
pre{font:15px/1.55 monospace;white-space:pre-wrap;overflow-wrap:anywhere;margin:0;padding:17px;min-height:155px;color:#d5f6df}.meaning{padding:16px 0;color:#b4c3d9;font-size:14px;line-height:1.6}.note{font-size:12px;color:#879cb9;line-height:1.6;margin:22px 0}.quiz{font-size:13px;color:#c1d0e4;line-height:1.6;margin:0 0 14px}.map{display:grid;gap:12px}.map p{margin:0;padding:14px;background:#1d2d44;border-radius:8px}.hidden{display:none!important}
@media(max-width:850px){header{padding:18px}.identity{display:none}main{padding:18px;grid-template-columns:1fr}nav{display:flex;overflow:auto;gap:8px}nav button{min-width:160px}.topic{font-size:14px}}
</style></head><body>
<header><div><div class="eyebrow">CSA0234 / LIVE C PROGRAMS</div><h1>MILA activity runner</h1></div><div class="identity">PROBIR SAHA SHOHOM · 1911260319<br>Local input → compiled C executable → actual output</div></header>
<main><aside><nav aria-label="MILA activities" id="activities"></nav><p class="note">This runner sends your input to the existing C programs. It does not calculate or simulate their results.</p></aside>
<section><h2 id="heading"></h2><p class="topic" id="format"></p>
<div id="interactive"><div id="quiz" class="quiz hidden">1. First array index: 1) 0, 2) 1, 3) -1<br>2. Address-of: 1) *, 2) &amp;, 3) %<br>3. Remainder: 1) /, 2) +, 3) %<br>4. Exit loop: 1) break, 2) continue, 3) sizeof<br>5. Binary search: 1) unique keys, 2) sorted input, 3) positive keys</div>
<label for="stdin">Program input (standard input)</label><textarea id="stdin" spellcheck="false"></textarea><div class="actions"><button id="run" class="primary">Run C program</button><button id="example" class="secondary">Load example</button><span class="status" id="status" role="status">Ready</span></div>
<div class="terminal"><div class="bar"><span id="executable"></span><span id="exit">Not run yet</span></div><pre id="output" aria-live="polite">Enter input above, then choose Run C program.</pre></div></div>
<div id="concept" class="map hidden"><p>Arrays → loop traversal → sum, mean, and extrema</p><p>Functions → contracts → modular problem solving</p><p>Pointers → object addresses → caller-visible mutation</p><p>Structures → related fields → inventory valuation</p><p>Sorted input → candidate interval → binary search</p><p>Validation and tests → evidence across all activities</p></div>
<p class="meaning" id="meaning"></p></section></main>
<script>
const activities = __ACTIVITIES__;
const $=id=>document.getElementById(id); let selected=activities[0];let busy=false;
function select(item){if(busy)return;selected=item;$('heading').textContent=item.name+' — '+item.topic;$('format').textContent=item.format;$('meaning').textContent=item.meaning;$('stdin').value=item.example;$('executable').textContent='./build/'+item.id;$('exit').textContent='Not run yet';$('output').textContent='Enter input above, then choose Run C program.';$('status').textContent='Ready';$('quiz').classList.toggle('hidden',item.id!=='06_quiz');$('interactive').classList.remove('hidden');$('concept').classList.add('hidden');for(const b of document.querySelectorAll('nav button'))b.setAttribute('aria-pressed',String(b.dataset.id===item.id));}
for(const item of activities){const b=document.createElement('button');b.dataset.id=item.id;b.textContent=item.name;const small=document.createElement('small');small.textContent=item.topic;b.appendChild(small);b.onclick=()=>select(item);$('activities').appendChild(b);}
const map=document.createElement('button');map.dataset.id='map';map.textContent='Concept Mapping';map.onclick=()=>{if(busy)return;for(const b of document.querySelectorAll('nav button'))b.setAttribute('aria-pressed',String(b===map));$('heading').textContent='Concept Mapping — C relationships';$('format').textContent='Read each arrow as a relationship between concepts.';$('meaning').textContent='See CONCEPT_MAP.md for the full diagram and explanations.';$('interactive').classList.add('hidden');$('concept').classList.remove('hidden');};$('activities').appendChild(map);
$('example').onclick=()=>{if(!busy)$('stdin').value=selected.example;};
$('run').onclick=async()=>{if(busy)return;busy=true;$('run').disabled=true;$('status').textContent='Running compiled C program…';try{const r=await fetch('/run',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify({program:selected.id,input:$('stdin').value})});const data=await r.json();if(!r.ok)throw Error(data.error);$('output').textContent=data.stdout+data.stderr||'(No output)';$('exit').textContent='Exit status '+data.exit_status;$('status').textContent=data.exit_status===0?'Completed successfully':'Input rejected by C program';}catch(e){$('output').textContent=String(e.message);$('status').textContent='Unable to run';$('exit').textContent='Runner error';}finally{busy=false;$('run').disabled=false;}};
select(selected);
</script></body></html>'''


class Handler(BaseHTTPRequestHandler):
    def respond(self, status, data, content_type='application/json'):
        payload = data.encode('utf-8') if isinstance(data, str) else json.dumps(data).encode('utf-8')
        self.send_response(status)
        self.send_header('Content-Type', content_type + '; charset=utf-8')
        self.send_header('Content-Length', str(len(payload)))
        self.send_header('Cache-Control', 'no-store')
        self.send_header('X-Content-Type-Options', 'nosniff')
        self.end_headers()
        self.wfile.write(payload)

    def do_GET(self):
        if self.path == '/':
            self.respond(200, HTML.replace('__ACTIVITIES__', json.dumps(ACTIVITIES)), 'text/html')
        else:
            self.respond(404, {'error': 'Not found'})

    def do_POST(self):
        if self.path != '/run':
            return self.respond(404, {'error': 'Not found'})
        origin = self.headers.get('Origin')
        if origin and origin not in (f'http://127.0.0.1:{self.server.server_port}', f'http://localhost:{self.server.server_port}'):
            return self.respond(403, {'error': 'Origin not allowed'})
        try:
            length = int(self.headers.get('Content-Length', '0'))
            if not 0 < length <= 8192:
                raise ValueError('Request must contain 1–8192 bytes')
            request = json.loads(self.rfile.read(length))
            if not isinstance(request, dict):
                raise ValueError('Expected an object')
            program, input_text = request.get('program'), request.get('input')
            if not isinstance(program, str) or program not in PROGRAMS or not isinstance(input_text, str):
                raise ValueError('Choose a known program and provide text input')
            executable = ROOT / 'build' / program
            if not executable.is_file():
                return self.respond(503, {'error': 'Build the C programs first: run make from MILA/'})
            result = subprocess.run([str(executable)], input=input_text + '\n', text=True,
                                    capture_output=True, timeout=3, cwd=ROOT, check=False)
            self.respond(200, {'stdout': result.stdout, 'stderr': result.stderr, 'exit_status': result.returncode})
        except (ValueError, UnicodeError) as error:
            self.respond(400, {'error': str(error)})
        except subprocess.TimeoutExpired:
            self.respond(408, {'error': 'Program exceeded three seconds'})
        except OSError:
            self.respond(500, {'error': 'Unable to execute the C program; rebuild with make clean and make'})

    def log_message(self, format, *args):
        pass


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=5088)
    args = parser.parse_args()
    if not 1 <= args.port <= 65535:
        parser.error('port must be 1–65535')
    server = ThreadingHTTPServer(('127.0.0.1', args.port), Handler)
    print(f'MILA runner: http://127.0.0.1:{args.port}/', flush=True)
    print('Press Ctrl+C to stop. Run make in MILA/ before using the runner.', flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()
