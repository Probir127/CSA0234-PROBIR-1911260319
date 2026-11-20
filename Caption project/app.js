
const el=id=>document.getElementById(id);
async function api(parts){
 if(parts.some(v=>/[\t\r\n|]/.test(v)))throw Error('Remove tabs, line breaks and | from fields.');
 if(parts.some(v=>new TextEncoder().encode(v).length>159))throw Error('Fields must be at most 159 UTF-8 bytes.');
 let response;try{response=await fetch('/api?'+encodeURIComponent(parts.join('\t')),{method:'POST',cache:'no-store',signal:AbortSignal.timeout(15000)})}catch(e){throw Error('Cannot reach the C server. Start it with ./start.sh, then reload this page.')}
 const text=await response.text();if(!response.ok)throw Error('Server returned HTTP '+response.status);
 if(!text.endsWith('END\n'))throw Error('Unexpected server response. Restart the server with ./start.sh.');
 const result=text.replace(/END\n$/,'').trim();if(result.startsWith('ERROR'))throw Error(result.slice(6));return result;
}
let records=[];
async function list(){const text=await api(['LIST']);if(text.startsWith('ERROR'))throw Error(text);records=text==='No books found.'?[]:text.split('\n').map(line=>{const [id,title,author,...status]=line.split(' | ');return {id:Number(id),title,author,status:status.join(' | ')}});if(el('total')){el('total').textContent=records.filter(b=>b.status!=='Removed').length;el('available').textContent=records.filter(b=>b.status==='Available').length;el('reserved').textContent=records.filter(b=>b.status.startsWith('Reserved for:')).length;el('out-of-service').textContent=records.filter(b=>b.status==='Damaged'||b.status==='Lost').length;el('borrowed').textContent=records.filter(b=>b.status.startsWith('Borrowed by:')).length}if(el('books'))render();if(el('overview')){el('overview').replaceChildren();for(const b of records.filter(b=>b.status!=='Removed').slice(-6).reverse()){const tr=document.createElement('tr');for(const value of [b.id,b.title,b.status]){const td=document.createElement('td');td.textContent=value;tr.append(td)}el('overview').append(tr)}if(!records.length){const tr=document.createElement('tr'),td=document.createElement('td');td.colSpan=3;td.textContent='Your shelves are ready. Add your first book to get started.';tr.append(td);el('overview').append(tr)}}}
function visible(){const q=el('query').value.toLowerCase();return records.filter(b=>(b.title.toLowerCase().includes(q)||b.author.toLowerCase().includes(q))&&(el('filter').value==='all'&&b.status!=='Removed'||(el('filter').value==='available'&&b.status==='Available'||el('filter').value==='borrowed'&&b.status.startsWith('Borrowed by:')||el('filter').value==='reserved'&&b.status.startsWith('Reserved for: ')||el('filter').value==='damaged'&&b.status==='Damaged'||el('filter').value==='lost'&&b.status==='Lost'||el('filter').value==='removed'&&b.status==='Removed'))).sort((a,b)=>el('sort').value==='id'?a.id-b.id:a[el('sort').value].localeCompare(b[el('sort').value]))}
function render(){el('books').replaceChildren();const rows=visible();el('result-count').textContent=rows.length+' of '+records.length+' books';for(const book of rows){const tr=document.createElement('tr');for(const value of [book.id,book.title,book.author,book.status]){const td=document.createElement('td');td.textContent=value;if(value===book.status){td.textContent='';const badge=document.createElement('span');badge.className='status'+(book.status==='Available'?'':book.status==='Damaged'?' damaged':book.status==='Lost'?' lost':book.status==='Removed'?' removed':book.status.startsWith('Reserved for:')?' reserved':' loan');badge.textContent=value;td.append(badge)}tr.append(td)}const td=document.createElement('td'),button=document.createElement('button');button.textContent=['Damaged','Lost','Removed'].includes(book.status)?'Manage stock':book.status.startsWith('Borrowed by:')?'View loan':book.status.startsWith('Reserved for: ')?'Issue to member':'Borrow';button.onclick=()=>{location.href=['Damaged','Lost','Removed'].includes(book.status)?'/stock':book.status.startsWith('Borrowed by:')?'/loans?book='+book.id:'/loans?id='+book.id};td.append(button);tr.append(td);el('books').append(tr)}if(!rows.length){const tr=document.createElement('tr'),td=document.createElement('td');td.colSpan=5;td.textContent='No matching books. Add a book or adjust your filters.';tr.append(td);el('books').append(tr)}}
if(el('query')){el('query').oninput=render;el('filter').onchange=render;el('sort').onchange=render;el('refresh').onclick=()=>run(()=>list());}
if(el('export'))el('export').onclick=()=>{const quote=v=>'"'+String(v).replaceAll('"','""')+'"';const csv=[['ID','Title','Author','Status'],...visible().map(b=>[b.id,b.title,b.author,b.status])].map(row=>row.map(v=>quote(/^[=+@\-]/.test(String(v))?"'"+v:v)).join(',')).join('\r\n');const url=URL.createObjectURL(new Blob([csv],{type:'text/csv;charset=utf-8'}));const a=document.createElement('a');a.href=url;a.download='library-collection.csv';a.click();setTimeout(()=>URL.revokeObjectURL(url),1000)};
async function run(fn){try{await fn()}catch(e){el('message').textContent=e.message}}
if(el('search')){el('search').onsubmit=e=>{e.preventDefault();render()};el('all').onclick=()=>{el('query').value='';el('filter').value='all';render()};
}
if(el('add'))el('add').onsubmit=e=>{e.preventDefault();run(async()=>{const result=await api(['ADD',el('title').value,el('author').value]);el('message').textContent=result;if(result.startsWith('OK'))e.target.reset();await list()})};
if(el('loan'))el('loan').onsubmit=e=>{e.preventDefault();run(async()=>{el('message').textContent=await api([el('action').value,el('bookid').value,el('borrower').value]);await list()})};run(()=>list());

if(el('loan')){const p=new URLSearchParams(location.search);el('bookid').value=p.get('id')||'';el('action').value=p.get('action')==='RETURN'?'RETURN':'BORROW';el('borrower').value=p.get('borrower')||'';}

// Membership and circulation use server-issued IDs and persisted loan records.
async function rows(command){const text=await api([command]);if(text.startsWith('ERROR'))throw Error(text);return text?text.split('\n').map(x=>x.split(' | ')):[]}
function cellRow(target,values){const tr=document.createElement('tr');for(const v of values){const td=document.createElement('td');td.textContent=v;tr.append(td)}target.append(tr);return tr}
async function directory(){const people=await rows('MEMBERS');el('directory').replaceChildren();for(const person of people)cellRow(el('directory'),person);if(!people.length)cellRow(el('directory'),['No members registered yet.'])}
if(el('register-member')){el('register-member').onsubmit=e=>{e.preventDefault();run(async()=>{const result=await api(['MEMBER_ADD',el('member-name').value.trim(),el('member-email').value.trim().toLowerCase()]);el('message').textContent=result;if(result.startsWith('OK'))e.target.reset();await directory()})};run(directory)}
let loanData=[],memberData=[],bookData=[],holdData=[];
function loanView(){el('loan-register').replaceChildren();const mode=el('loan-filter').value,now=Date.now()/1000;const date=n=>Number(n)>0?new Date(Number(n)*1000).toLocaleDateString():'Not recorded';let shown=0;for(const l of loanData){const returned=Number(l[5])>0,overdue=!returned&&Number(l[4])>0&&Number(l[4])<now;if(mode==='active'&&returned||mode==='overdue'&&!overdue||mode==='returned'&&!returned)continue;shown++;const b=bookData.find(b=>b[0]===l[1]),m=memberData.find(m=>m[0]===l[2]);const tr=cellRow(el('loan-register'),['#'+l[0],b?b[1]:l[1],m?m[1]:l[2],date(l[3]),date(l[4]),returned?'Returned '+date(l[5]):overdue?'Overdue':'On loan',l[6]||'0']);const td=document.createElement('td');td.className='action-group';if(!returned){const renew=document.createElement('button');renew.className='secondary';renew.textContent='Renew';renew.disabled=Number(l[3])===0||Number(l[6])>=2;renew.title=renew.disabled?'This loan cannot be renewed':'Extend due date by 14 days';renew.onclick=()=>run(async()=>{renew.disabled=true;try{el('message').textContent=await api(['RENEW',l[0],'14']);await circulation()}finally{renew.disabled=false}});td.append(renew);const button=document.createElement('button');button.textContent='Return book';button.onclick=()=>run(async()=>{button.disabled=true;try{el('message').textContent=await api(['CHECKIN',l[0]]);await circulation()}finally{button.disabled=false}});td.append(button)}tr.append(td)}if(!shown)cellRow(el('loan-register'),['No loans match this view.'])}
async function circulation(){[loanData,memberData,bookData,holdData]=await Promise.all([rows('LOANS'),rows('MEMBERS'),rows('LIST'),rows('HOLDS')]);bookData=bookData.filter(b=>b.length>=4);for(const [id,data,label] of [['member',memberData,p=>p[0]+' · '+p[1]],['copy',bookData.filter(b=>b[3]==='Available'||b[3].startsWith('Reserved for: ')),p=>p[0]+' · '+p[1]]]){el(id).replaceChildren();const empty=document.createElement('option');empty.value='';empty.textContent=id==='member'?'Select a registered member':'Select an available copy';el(id).append(empty);for(const item of data){const o=document.createElement('option');o.value=item[0];o.textContent=label(item);el(id).append(o)}}el('copy').onchange=()=>{const h=holdData.find(h=>h[1]===el('copy').value&&h[4]==='0');if(h)el('member').value=h[2]};if(el('no-members'))el('no-members').hidden=memberData.length>0;const p=new URLSearchParams(location.search);if(p.get('id')){el('copy').value=p.get('id');el('copy').onchange()}loanView()}
if(el('checkout')){el('loan-filter').onchange=loanView;el('checkout').onsubmit=e=>{e.preventDefault();run(async()=>{const b=e.target.querySelector('button');b.disabled=true;try{el('message').textContent=await api(['CHECKOUT',el('copy').value,el('member').value,el('days').value]);await circulation()}finally{b.disabled=false}})};run(circulation)}

if(el('books')){const section=document.createElement('section');section.innerHTML='<h2>Edit book record</h2><form id="edit-book"><label for="edit-id">Book ID</label><input id="edit-id" type="number" min="1" required><label for="edit-title">Corrected title</label><input id="edit-title" maxlength="158" required><label for="edit-author">Corrected author</label><input id="edit-author" maxlength="158" required><button>Save book details</button></form>';document.querySelector('main').append(section);el('edit-id').oninput=()=>{const b=records.find(b=>b.id===Number(el('edit-id').value));if(b){el('edit-title').value=b.title;el('edit-author').value=b.author}};el('edit-book').onsubmit=e=>{e.preventDefault();run(async()=>{el('message').textContent=await api(['EDIT',el('edit-id').value,el('edit-title').value.trim(),el('edit-author').value.trim()]);await list()})}}

if(el('quick-member'))el('quick-member').onsubmit=e=>{e.preventDefault();run(async()=>{const result=await api(['MEMBER_ADD',el('quick-name').value.trim(),el('quick-email').value.trim().toLowerCase()]);el('message').textContent=result;e.target.reset();await circulation();const newest=memberData[memberData.length-1];if(newest)el('member').value=newest[0]})};

async function loadHolds(){const [bs,ms,hs]=await Promise.all([rows('LIST'),rows('MEMBERS'),rows('HOLDS')]);const books=bs.filter(b=>b.length>=4);const reservable=books.filter(b=>b[3]!=='Damaged'&&b[3]!=='Lost'&&b[3]!=='Removed');const members=ms.filter(m=>m.length>=3);holdData=hs;
 for(const [id,data,placeholder] of [['hold-copy',reservable,'Select a copy'],['hold-member',members,'Select a member']]){const select=el(id);select.replaceChildren();const first=document.createElement('option');first.value='';first.textContent=placeholder;select.append(first);for(const item of data){const option=document.createElement('option');option.value=item[0];option.textContent=item[0]+' · '+item[1];select.append(option)}}
 const target=el('hold-register');target.replaceChildren();for(const h of hs){const b=books.find(b=>b[0]===h[1]),m=members.find(m=>m[0]===h[2]);const state=h[4]==='0'?'Queued':h[4]==='1'?'Filled':'Cancelled';const tr=cellRow(target,[h[0],b?b[1]:h[1],m?m[1]:h[2],new Date(Number(h[3])*1000).toLocaleDateString(),state]);const td=document.createElement('td');if(state==='Queued'){const button=document.createElement('button');button.textContent='Cancel';button.onclick=()=>run(async()=>{button.disabled=true;try{el('message').textContent=await api(['CANCEL_HOLD',h[0]]);await loadHolds()}finally{button.disabled=false}});td.append(button)}tr.append(td)}if(!hs.length)cellRow(target,['No reservations yet.'])}
if(el('hold-form')){el('hold-form').onsubmit=e=>{e.preventDefault();run(async()=>{el('message').textContent=await api(['HOLD',el('hold-copy').value,el('hold-member').value]);await loadHolds()})};run(loadHolds)}

// Inventory view: server remains the authority for stock changes.
let inventory = [];
function stockKind(status) {
  if (status === 'Damaged' || status === 'Lost' || status === 'Removed' || status === 'Available') return status;
  return status.startsWith('Borrowed by:') ? 'Borrowed' : 'Reserved';
}
function renderStock() {
  const counts = {Available:0, Borrowed:0, Reserved:0, Damaged:0, Lost:0, Removed:0};
  for (const copy of inventory) counts[stockKind(copy[3])]++;
  el('stock-total').textContent = inventory.length-counts.Removed;
  for (const [key,id] of [['Available','stock-shelf'],['Borrowed','stock-loan'],['Reserved','stock-reserved'],['Damaged','stock-damaged'],['Lost','stock-lost'],['Removed','stock-removed']]) el(id).textContent=counts[key];
  const titles = new Map();
  for (const copy of inventory) {
    if (stockKind(copy[3])==='Removed') continue;
    const key=JSON.stringify([copy[1],copy[2]]);
    if (!titles.has(key)) titles.set(key,{title:copy[1],author:copy[2],total:0,Available:0,Borrowed:0,Reserved:0,Damaged:0,Lost:0});
    const item=titles.get(key); item.total++; item[stockKind(copy[3])]++;
  }
  el('stock-titles').replaceChildren();
  for (const item of titles.values()) cellRow(el('stock-titles'),[item.title,item.author,item.total,item.Available,item.Borrowed,item.Reserved,item.Damaged,item.Lost]);
  if (!titles.size) cellRow(el('stock-titles'),['No books in stock yet.']);
  const query=el('stock-query').value.toLowerCase(), filter=el('stock-filter').value;
  const shown=inventory.filter(c=>(filter==='all'||stockKind(c[3])===filter)&&([c[0],c[1],c[2]].some(v=>String(v).toLowerCase().includes(query))));
  el('stock-count').textContent=shown.length+' of '+inventory.length+' copy records';
  el('stock-copies').replaceChildren();
  for (const copy of shown) {
    const tr=cellRow(el('stock-copies'),[copy[0],copy[1],copy[2],copy[3]]);
    const td=document.createElement('td');td.className='stock-action';
    const kind=stockKind(copy[3]);
    if (kind==='Borrowed'||kind==='Reserved') {
      const link=document.createElement('a');link.href=kind==='Borrowed'?'/loans':'/holds';link.textContent=kind==='Borrowed'?'Manage loan':'Manage reservation';td.append(link);
    } else if (kind==='Removed') {
      const button=document.createElement('button');button.textContent='Restore copy';button.className='secondary';
      button.onclick=()=>run(async()=>{button.disabled=true;try{el('message').textContent=await api(['STOCK_SET',copy[0],'ACTIVE']);await loadStock()}finally{button.disabled=false}});
      td.append(button);
    } else {
      const select=document.createElement('select');select.setAttribute('aria-label','Status for copy '+copy[0]);
      for (const [value,label] of [['ACTIVE','On shelf'],['DAMAGED','Damaged'],['LOST','Lost']]) {
        const option=document.createElement('option');option.value=value;option.textContent=label;select.append(option);
      }
      select.value=kind==='Available'?'ACTIVE':kind.toUpperCase();
      const button=document.createElement('button');button.textContent='Save';
      button.onclick=()=>run(async()=>{button.disabled=true;try{el('message').textContent=await api(['STOCK_SET',copy[0],select.value]);await loadStock()}finally{button.disabled=false}});
      td.append(select,button);
      const remove=document.createElement('button');remove.type='button';remove.className='danger';remove.textContent='Remove copy';
      remove.onclick=()=>run(async()=>{remove.disabled=true;try{el('message').textContent=await api(['STOCK_SET',copy[0],'REMOVED']);await loadStock()}finally{remove.disabled=false}});
      td.append(remove);
    }
    tr.append(td);
  }
  if (!shown.length) cellRow(el('stock-copies'),['No copies match these filters.']);
}
async function loadStock() {
  inventory=(await rows('LIST')).filter(row=>row.length>=4);
  renderStock();
}
if(el('stock-add')) {
  el('stock-query').oninput=renderStock;
  el('stock-filter').onchange=renderStock;
  el('stock-refresh').onclick=()=>run(loadStock);
  el('stock-add').onsubmit=e=>{e.preventDefault();run(async()=>{
    const button=e.target.querySelector('button');button.disabled=true;
    try {el('message').textContent=await api(['STOCK_ADD',el('stock-title').value.trim(),el('stock-author').value.trim(),el('stock-quantity').value]);await loadStock();e.target.reset()}
    finally {button.disabled=false}
  })};
  run(loadStock);
}
