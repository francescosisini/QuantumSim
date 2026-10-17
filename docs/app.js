'use strict';

/* QuantumSim website — lightweight, dependency-free client features.
 * The mini lab below is an independent two-qubit ideal statevector visualizer.
 * It is intentionally distinct from the actual QuantumSim C engine.
 */
const BASE = 'https://github.com/francescosisini/QuantumSim/blob/master/Esercizi/';
const exercises = [
  [1,'Inizializzazione di un qubit','Prepara un qubit nello stato |0⟩ e introduce la struttura dati usata dal simulatore.','stati','es_1_initialize_qubit_state.c'],
  [2,'Visualizzare lo stato |0⟩','Stampa le ampiezze del qubit inizializzato in |0⟩, senza effettuare una misura.','stati','es_2_print_qubit_state_0.c'],
  [3,'Visualizzare lo stato |1⟩','Imposta |1⟩ e ne osserva la rappresentazione nella base computazionale.','stati','es_3_print_qubit_state_1.c'],
  [4,'Hadamard sullo stato |0⟩','Crea una sovrapposizione equiprobabile e osserva ampiezze e misura.','porte','es_4_apply_hadamard_to_state_0.c'],
  [5,'Hadamard sullo stato |1⟩','Ottiene una sovrapposizione con una diversa fase relativa e la confronta con H|0⟩.','porte','es_5_apply_hadamard_to_state_1.c'],
  [6,'Pauli X, Y, Z su |0⟩','Confronta come le tre porte trasformano lo stato iniziale |0⟩.','porte','es_6_apply_pauli_xyz_to_state_0.c'],
  [7,'Pauli X, Y, Z su |1⟩','Ripete le trasformazioni partendo da |1⟩, osservando stati e fasi.','porte','es_7_apply_pauli_xyz_to_state_1.c'],
  [8,'Porte S, T e T† su |0⟩','Verifica che le trasformazioni di fase lasciano invariato |0⟩.','porte','es_8_apply_s_t_tdag_to_state_0.c'],
  [9,'Porte S, T e T† su |1⟩','Osserva le fasi introdotte dalle porte S, T e T† sullo stato |1⟩.','porte','es_9_apply_s_t_tdag_to_state_1.c'],
  [10,'Un sistema di due qubit','Inizializza e stampa i quattro stati base |00⟩, |01⟩, |10⟩ e |11⟩.','due','es_10_initialize_two_qubits_state.c'],
  [11,'La porta CNOT','Applica la porta controllata agli stati base e ne verifica la condizione di attivazione.','due','es_11_apply_cnot_to_base_states.c'],
  [12,'Il primo stato di Bell','Usa Hadamard e CNOT per ottenere uno stato entangled di due qubit.','due','es_12_first_bell_state.c'],
  [13,'Misurare uno stato di Bell','Ripete la misura del sistema entangled e osserva la correlazione tra i qubit.','due','es_13_measure_first_bell_state.c'],
  [14,'CZ sugli stati base','Osserva come CZ modifica la fase di |11⟩ lasciando invariati gli altri stati base.','due','es_14_apply_cz_to_base_states.c'],
  [15,'CZ e sovrapposizione','Applica CZ a una sovrapposizione uniforme e osserva il cambiamento di fase.','due','es_15_apply_cz_to_superposition_state.c'],
  [16,'L’interferenza rivela la fase','La sequenza H–CZ–H rende osservabile una differenza di fase relativa.','due','es_16_cz_phase_inference.c'],
  [17,'La porta CCZ','Su tre qubit in sovrapposizione, inverte la fase della sola componente |111⟩.','tre','es_17_apply_ccz_to_superposition_state.c'],
  [18,'La porta Toffoli','Confronta l’effetto del NOT a doppio controllo sugli stati |010⟩ e |111⟩.','tre','es_18_apply_toffoli_to_base_states.c']
];
const categoryLabels = {stati:'STATI',porte:'PORTE',due:'DUE QUBIT',tre:'TRE QUBIT'};

const grid = document.getElementById('exerciseGrid');
const empty = document.getElementById('exerciseEmpty');
const search = document.getElementById('exerciseSearch');
const filterButtons = [...document.querySelectorAll('.filter-button')];
let activeFilter = 'all';

function escapeHTML(v) { return String(v).replace(/[&<>"']/g, x => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[x])); }
function renderExercises() {
  if(!grid) return;
  const q = (search?.value || '').trim().toLocaleLowerCase('it');
  const visible = exercises.filter(([id,title,description,category,file]) =>
    (activeFilter === 'all' || activeFilter === category) &&
    [id,title,description,categoryLabels[category],file].join(' ').toLocaleLowerCase('it').includes(q)
  );
  grid.innerHTML = visible.map(([id,title,description,category,file]) => `
    <article class="exercise-card">
      <div class="exercise-top"><span class="exercise-num">EX / ${String(id).padStart(2,'0')}</span><span class="exercise-category">${categoryLabels[category]}</span></div>
      <h4>${escapeHTML(title)}</h4><p>${escapeHTML(description)}</p>
      <div class="exercise-links"><a href="${BASE}${encodeURIComponent(file)}" target="_blank" rel="noopener noreferrer" aria-label="Apri il codice dell'esercizio ${id} su GitHub">Vedi il codice ↗</a><button class="copy-exercise" type="button" data-exercise="${escapeHTML(file)}" aria-label="Copia il comando di compilazione dell'esercizio ${id}">⧉ Copia make</button></div>
    </article>`).join('');
  empty.hidden = visible.length !== 0;
}
filterButtons.forEach(btn => btn.addEventListener('click', () => {
  activeFilter = btn.dataset.filter;
  filterButtons.forEach(b => {const isActive=b===btn; b.classList.toggle('is-selected',isActive); b.setAttribute('aria-pressed', String(isActive));});
  renderExercises();
}));
search?.addEventListener('input',renderExercises);
renderExercises();

let toastTimeout;
function siteToast(message) {
  const el=document.getElementById('siteToast');
  if(!el) return;
  el.textContent=message; el.classList.add('is-visible');
  clearTimeout(toastTimeout);
  toastTimeout=setTimeout(()=>el.classList.remove('is-visible'),2400);
}
async function copyText(value) {
  try {
    if(navigator.clipboard && window.isSecureContext) await navigator.clipboard.writeText(value);
    else {
      const field=document.createElement('textarea');field.value=value;field.setAttribute('readonly','');field.style.position='fixed';field.style.opacity='0';
      document.body.append(field);field.select();
      if(!document.execCommand('copy')) throw new Error('Copy not available');
      field.remove();
    }
    siteToast('Comando copiato negli appunti ✓');
  } catch(_err) { siteToast('Seleziona il testo e copialo manualmente.'); }
}
document.addEventListener('click', e => {
  const exercise = e.target.closest('[data-exercise]');
  if(exercise) copyText(`make -B CIRCUIT_FILE=Esercizi/${exercise.dataset.exercise}\n./QuantumSim`);
  const generic = e.target.closest('[data-copy]');
  if(generic) copyText(generic.dataset.copy);
});

const navToggle = document.querySelector('.nav-toggle');
const navLinks = document.getElementById('main-nav');
navToggle?.addEventListener('click',() => {
  const opened = navToggle.getAttribute('aria-expanded') !== 'true';
  navToggle.setAttribute('aria-expanded',String(opened));
  navToggle.setAttribute('aria-label',opened?'Chiudi il menu':'Apri il menu');
  navLinks?.classList.toggle('is-open',opened);
});
navLinks?.querySelectorAll('a').forEach(a=>a.addEventListener('click',()=>{
  navLinks.classList.remove('is-open');navToggle?.setAttribute('aria-expanded','false');navToggle?.setAttribute('aria-label','Apri il menu');
}));

const osHelp = {
 linux: 'Su Ubuntu/Debian puoi installare gli strumenti necessari con <code>sudo apt install git build-essential</code>.',
 mac: 'Su macOS installa gli strumenti a riga di comando con <code>xcode-select --install</code>, poi verifica Git e il compilatore.',
 windows: 'Su Windows 10/11 usa WSL: in PowerShell come amministratore esegui <code>wsl --install</code>, riavvia e installa Git/GCC nell’ambiente Linux.'
};
const osHint=document.getElementById('osHint');
document.querySelectorAll('.os-tab').forEach(btn=>btn.addEventListener('click',()=>{
  document.querySelectorAll('.os-tab').forEach(b=>{const selected=b===btn;b.classList.toggle('active-os',selected);b.setAttribute('aria-pressed',String(selected));});
  if(osHint) osHint.innerHTML=osHelp[btn.dataset.os];
}));

/* Exact ideal single- and two-qubit quantum operations (independent JS demo). */
let state, operations, measured;
const gates = {
 H0:{label:'H(q₀)',c:'applyHadamard(state, 0);'},H1:{label:'H(q₁)',c:'applyHadamard(state, 1);'},
 X0:{label:'X(q₀)',c:'applyX(state, 0);'},X1:{label:'X(q₁)',c:'applyX(state, 1);'},
 Z0:{label:'Z(q₀)',c:'applyZ(state, 0);'},Z1:{label:'Z(q₁)',c:'applyZ(state, 1);'},
 CNOT:{label:'CNOT',c:'applyCNOT(state, 0, 1);'},CZ:{label:'CZ',c:'applyCZ(state, 0, 1);'}
};
const SQRT2=Math.SQRT1_2;
function resetState(){state=[[1,0],[0,0],[0,0],[0,0]];operations=[];measured=false;updateLab('Stato iniziale <strong>|00⟩</strong> pronto.');}
function applySingle(gate,bit){
  const mask=1<<bit;
  for(let index=0;index<4;index++){
    if(index & mask) continue;
    const partner=index|mask;
    const a=state[index].slice(),b=state[partner].slice();
    if(gate==='H'){
      state[index]=[(a[0]+b[0])*SQRT2,(a[1]+b[1])*SQRT2];
      state[partner]=[(a[0]-b[0])*SQRT2,(a[1]-b[1])*SQRT2];
    } else if(gate==='X'){
      state[index]=b;state[partner]=a;
    } else if(gate==='Z'){
      state[partner]=[-b[0],-b[1]];
    }
  }
}
function applyGate(name){
  if(!gates[name]) return;
  if(name==='CNOT'){
    // q0 is the least-significant bit, controls the flip of q1.
    [state[1],state[3]]=[state[3],state[1]];
  } else if(name==='CZ'){
    state[3]=state[3].map(v=>-v);
  } else {
    applySingle(name[0], Number(name[1]));
  }
  operations.push(name);measured=false;
  updateLab(`Porta <strong>${gates[name].label}</strong> applicata. Osserva lo stato aggiornato.`);
}
function probs(){return state.map(a=>a[0]*a[0]+a[1]*a[1]);}
function ketLabel(i){return `|${(i>>1)&1}${i&1}⟩`;}
function measure(){
  const p=probs(); let r=Math.random(), index=3;
  for(let i=0;i<4;i++){ r-=p[i];if(r<=0){index=i;break;} }
  state=state.map((_,i)=>i===index?[1,0]:[0,0]);
  operations.push('MEASURE'); measured=true;
  updateLab(`Misura simulata: risultato <strong>${ketLabel(index)}</strong>. Lo stato è collassato.`);
}
function formatNumber(v){return (Math.abs(v)<0.0000001?0:v).toFixed(3);}
function buildCode(){
  const c=[
    '#include <stdio.h>',
    '#include "../src/quantum_sim.h"',
    '',
    'void circuit(void) {',
    '    QubitState *state = initializeState(2);'
  ];
  operations.forEach(g=>{
    if(g==='MEASURE'){c.push('    measure(state, 0);');c.push('    measure(state, 1);');}
    else c.push(`    ${gates[g].c}`);
  });
  c.push('    printState(state);','    freeState(state);','}');
  return c.join('\n');
}
function updateLab(message){
  const toast=document.getElementById('labToast');
  if(toast) toast.innerHTML=message;
  const probList=document.getElementById('probList');
  if(probList){
    const p=probs();
    probList.innerHTML=p.map((v,i)=>{
      const pct=Math.max(0,Math.min(100,v*100));
      return `<div class="prob-row"><span>${ketLabel(i)}</span><div class="prob-track" role="progressbar" aria-label="Probabilità dello stato ${ketLabel(i)}" aria-valuemin="0" aria-valuemax="100" aria-valuenow="${pct.toFixed(1)}"><div class="prob-fill" style="width:${pct}%"></div></div><strong>${pct<.05?'0':pct.toFixed(pct===100?0:1)}%</strong></div>`;
    }).join('');
  }
  const amps=document.getElementById('amplitudes');
  if(amps){amps.innerHTML=state.map((a,i)=>`<div class="amplitude"><b>${ketLabel(i)}</b> &nbsp; ${formatNumber(a[0])} ${a[1]<0?'−':'+'} ${formatNumber(Math.abs(a[1]))}i</div>`).join('');}
  const stepCount=document.getElementById('labStepCount');
  if(stepCount) stepCount.textContent=`${operations.length} OPERAZION${operations.length===1?'E':'I'}`;
  const circuitSteps=document.getElementById('circuitSteps');
  if(circuitSteps){
    const visible=operations.slice(-11);
    circuitSteps.innerHTML=visible.length
      ? `<span class="circuit-pill">|00⟩</span>${visible.map(g=>`<span class="circuit-arrow">→</span><span class="circuit-pill ${g==='CNOT'||g==='CZ'||g==='MEASURE'?'alt':''}">${g==='MEASURE'?'M':gates[g].label}</span>`).join('')}`
      : '<span class="empty-circuit">|00⟩ &nbsp; ─── &nbsp; scegli una porta per iniziare</span>';
  }
  const short=document.getElementById('circuitShort');
  if(short)short.textContent=measured?'MISURATO':`|ψ⟩ (${operations.length} gate)`;
  const code=document.querySelector('#generatedCode code');
  if(code) code.textContent=buildCode();
}
document.querySelectorAll('[data-gate]').forEach(btn=>btn.addEventListener('click',()=>applyGate(btn.dataset.gate)));
document.getElementById('measureBtn')?.addEventListener('click',measure);
document.getElementById('resetBtn')?.addEventListener('click',resetState);
document.getElementById('copyCircuit')?.addEventListener('click',()=>copyText(buildCode()));
resetState();

if('IntersectionObserver' in window){
  const observer=new IntersectionObserver((entries,obs)=>{
    entries.forEach(entry=>{if(entry.isIntersecting){entry.target.classList.add('in-view');obs.unobserve(entry.target);}});
  },{threshold:.09,rootMargin:'0px 0px 24px 0px'});
  document.querySelectorAll('.reveal').forEach(el=>observer.observe(el));
} else document.querySelectorAll('.reveal').forEach(el=>el.classList.add('in-view'));
