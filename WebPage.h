#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="tr" class="dark">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
<meta name="theme-color" content="#03182b">
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<link rel="manifest" href="/manifest.json">
<link rel="apple-touch-icon" href="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='none' stroke='%230ea5e9' stroke-width='2' stroke-linecap='round' stroke-linejoin='round'%3E%3Cpath d='M19 17h2c.6 0 1-.4 1-1v-3c0-.9-.7-1.7-1.5-1.9C18.7 10.6 16 10 16 10s-1.3-1.4-2.2-2.3c-.5-.4-1.1-.7-1.8-.7H5c-.6 0-1.1.4-1.4.9l-1.4 2.9A3.7 3.7 0 0 0 2 12v4c0 .6.4 1 1 1h2'%3E%3C/path%3E%3Ccircle cx='7' cy='17' r='2'%3E%3C/circle%3E%3Cpath d='M9 17h6'%3E%3C/path%3E%3Ccircle cx='17' cy='17' r='2'%3E%3C/circle%3E%3C/svg%3E">
<title>Karavan OS</title>
<!-- Google Fonts with swap for offline fallback -->
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap" rel="stylesheet" media="print" onload="this.media='all'">
<!-- Local SD Card Tailwind JS Engine -->
<script src="/js/tailwindcss.js"></script>
<script>
  if (window.tailwind) {
    tailwind.config = {
      darkMode: 'class',
      theme: {
        extend: {
          fontFamily: { sans: ['Inter', 'system-ui', 'sans-serif'], mono: ['monospace'] }
        }
      }
    };
  }
</script>
<script>
  // Load Chart.js async (Local SD Card)
  var cjsScript = document.createElement('script');
  cjsScript.src = '/js/chart.umd.min.js';
  cjsScript.onerror = function() { window.Chart = null; console.warn("Chart.js failed to load from SD"); };
  document.head.appendChild(cjsScript);
  
  // Load PapaParse async (Local SD Card)
  var papaScript = document.createElement('script');
  papaScript.src = '/js/papaparse.min.js';
  papaScript.onerror = function() { window.Papa = null; console.warn("PapaParse failed to load from SD"); };
  document.head.appendChild(papaScript);
</script>
<style>
  /* SD Card Checkbox Fix */
  .peer:checked + div > svg { opacity: 1 !important; }
  .peer:checked + div { background-color: #2563eb !important; border-color: #3b82f6 !important; }

  * { box-sizing: border-box; outline: none !important; -webkit-tap-highlight-color: transparent !important; }
  body { font-family: 'Inter', system-ui, sans-serif; background-color: #020617; color: #f1f5f9; overflow-x: hidden; }

  /*  Glass Cards  */
  .glass-card {
    background: rgba(15, 23, 42, 0.60);
    backdrop-filter: blur(24px);
    -webkit-backdrop-filter: blur(24px);
    border: 1px solid rgba(255, 255, 255, 0.05);
    box-shadow: 0 4px 24px -4px rgba(0,0,0,0.6), inset 0 1px 0 rgba(255,255,255,0.02);
  }
  
  /* Ambient card glows */
  . { background: radial-gradient(circle at top right, rgba(34, 211, 238, 0.08) 0%, transparent 60%); }
  . { background: radial-gradient(circle at top right, rgba(251, 113, 133, 0.08) 0%, transparent 60%); }
  . { background: radial-gradient(circle at top right, rgba(52, 211, 153, 0.08) 0%, transparent 60%); }
  . { background: radial-gradient(circle at top right, rgba(45, 212, 191, 0.08) 0%, transparent 60%); }
  . { background: radial-gradient(circle at top left, rgba(251, 146, 60, 0.08) 0%, transparent 70%); }
  . { background: radial-gradient(circle at top left, rgba(250, 204, 21, 0.06) 0%, transparent 70%); }
  
  /* Text Gradients */
  .text-gradient-cyan { background: linear-gradient(to right, #67e8f9, #06b6d4); -webkit-background-clip: text; -webkit-text-fill-color: transparent; }
  .text-gradient-rose { background: linear-gradient(to right, #fda4af, #f43f5e); -webkit-background-clip: text; -webkit-text-fill-color: transparent; }
  .text-gradient-blue { background: linear-gradient(to right, #93c5fd, #3b82f6); -webkit-background-clip: text; -webkit-text-fill-color: transparent; }
  .text-gradient-green { background: linear-gradient(to right, #86efac, #10b981); -webkit-background-clip: text; -webkit-text-fill-color: transparent; }
  .text-gradient-amber { background: linear-gradient(to right, #fde047, #f59e0b); -webkit-background-clip: text; -webkit-text-fill-color: transparent; }
  
  /* Hover effects removed as requested, keeping subtle border highlight on active states if needed */

  /*  Pulse Animation  */
  .pulse-red { animation: pulseRed 1.4s infinite; border-color: #ef4444 !important; }
  @keyframes pulseRed {
    0%   { box-shadow: 0 0 0 0   rgba(239,68,68,0.5); }
    70%  { box-shadow: 0 0 0 12px rgba(239,68,68,0); }
    100% { box-shadow: 0 0 0 0   rgba(239,68,68,0); }
  }

  /*  Button Press  */
  .btn-press { transition: transform 0.1s ease, opacity 0.1s ease; }
  .btn-press:active { transform: scale(0.96); opacity: 0.85; }

  /*  Toggle Switch  */
  .switch { position:relative; display:inline-block; width:46px; height:24px; }
  .switch input { opacity:0; width:0; height:0; }
  .slider { position:absolute; cursor:pointer; top:0; left:0; right:0; bottom:0; background:#1e293b; border:1px solid #334155; transition:.3s; border-radius:34px; }
  .slider:before { position:absolute; content:""; height:16px; width:16px; left:3px; bottom:3px; background:#64748b; transition:.3s; border-radius:50%; }
  input:checked + .slider { background:#0e7490; border-color:#06b6d4; box-shadow: 0 0 8px rgba(6,182,212,0.4); }
  input:checked + .slider:before { transform:translateX(22px); background:#fff; }

  /* Flowing sparkline line animation */
  @keyframes sparkFlow {
    to { stroke-dashoffset: -20; }
  }
  .animate-spark-flow {
    animation: sparkFlow 8s linear infinite;
  }

  /* Gradient Slider Thumb */
  input[type=range]#cal-g, input[type=range]#cal-t {
    -webkit-appearance: none;
    appearance: none;
    width: 100%;
    background: transparent;
    cursor: pointer;
  }
  input[type=range]#cal-g::-webkit-slider-thumb, input[type=range]#cal-t::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 20px;
    height: 20px;
    border-radius: 50%;
    background: #fff;
    border: 2px solid rgba(255,255,255,0.9);
    box-shadow: 0 0 8px rgba(0,0,0,0.5), 0 0 0 3px rgba(255,255,255,0.15);
    cursor: pointer;
    transition: transform 0.15s ease;
  }
  input[type=range]#cal-g::-webkit-slider-thumb:hover, input[type=range]#cal-t::-webkit-slider-thumb:hover {
    transform: scale(1.2);
  }
  input[type=range]#cal-g::-moz-range-thumb, input[type=range]#cal-t::-moz-range-thumb {
    width: 20px;
    height: 20px;
    border-radius: 50%;
    background: #fff;
    border: 2px solid rgba(255,255,255,0.9);
    box-shadow: 0 0 8px rgba(0,0,0,0.5);
    cursor: pointer;
  }

  /*  Scrollbar  */
  .custom-scrollbar {
    scrollbar-width: thin;
    scrollbar-color: rgba(71,85,105,0.3) transparent;
  }
  .custom-scrollbar::-webkit-scrollbar { width:4px; height:5px; }
  .custom-scrollbar::-webkit-scrollbar-track { background:transparent; }
  .custom-scrollbar::-webkit-scrollbar-thumb { background:rgba(71,85,105,0.35); border-radius:999px; }
  .custom-scrollbar::-webkit-scrollbar-thumb:hover { background:rgba(6,182,212,0.6); }

  /*  Stat Badge  */
  .stat-badge { display:flex; flex-direction:column; align-items:center; justify-content:center; gap:2px;
    background:rgba(15,23,42,0.5); border:1px solid rgba(255,255,255,0.05); border-radius:14px; padding:8px 10px; }

  /*  Card Label  */
  .card-label { font-size:10px; font-weight:600; letter-spacing:.12em; text-transform:uppercase; color:#64748b; }

  /*  Number Display  */
  .value-xl  { font-size:3rem;   font-weight:300; line-height:1; letter-spacing:-.02em; color:#f8fafc; }
  .value-lg  { font-size:2.25rem; font-weight:300; line-height:1; letter-spacing:-.02em; color:#f8fafc; }
  .value-md  { font-size:1.5rem;  font-weight:400; line-height:1; color:#f8fafc; }

  /*  Ambient BG blobs  */
  .blob { position:fixed; border-radius:50%; filter:blur(90px); pointer-events:none; z-index:0; opacity:.55; }

  

    .btn-settings:hover {
    background: rgba(255, 255, 255, 0.08);
    color: #f1f5f9;
    border-color: rgba(255, 255, 255, 0.15);
  }
  .btn-settings:active {
    transform: scale(0.92);
  }

    @keyframes flow-down {
      0% { transform: translateY(-2px); opacity: 0; }
      20% { opacity: 1; }
      80% { opacity: 1; }
      100% { transform: translateY(6px); opacity: 0; }
    }
    .animate-flow path:nth-child(1) { animation: flow-down 1.2s infinite linear; }
    .animate-flow path:nth-child(2) { animation: flow-down 1.2s infinite linear 0.4s; }
    .animate-flow path:nth-child(3) { animation: flow-down 1.2s infinite linear 0.8s; }
  
    @keyframes pump-ring-pulse {
      0% { box-shadow: 0 0 0 0 rgba(45,212,191,0.5); border-color: rgba(45,212,191,0.5); }
      70% { box-shadow: 0 0 0 15px rgba(45,212,191,0); border-color: rgba(45,212,191,0); }
      100% { box-shadow: 0 0 0 0 rgba(45,212,191,0); border-color: rgba(45,212,191,0); }
    }
    .anim-pump-active {
      animation: pump-ring-pulse 1.5s infinite;
      background-color: rgba(45,212,191,0.1) !important;
    }

    @keyframes flow-minimal {
      0% { transform: translateY(12px); opacity: 0; }
      20% { opacity: 1; }
      80% { opacity: 1; }
      100% { transform: translateY(-12px); opacity: 0; }
    }
    .animate-flow-minimal {
      animation: flow-minimal 2s cubic-bezier(0.4, 0, 0.2, 1) infinite;
    }
    @media (min-width: 768px) {
      @keyframes flow-minimal {
        0% { transform: translateX(30px); opacity: 0; }
        20% { opacity: 1; }
        80% { opacity: 1; }
        100% { transform: translateX(-30px); opacity: 0; }
      }
    }
    .animate-flow-dynamic {
      animation: flow-anim 2s linear infinite;
    }
    .flow-icon {
      transform: rotate(90deg);
    }
    @media (min-width: 768px) {
      @keyframes flow-minimal {
      0% { transform: translateY(12px); opacity: 0; }
      20% { opacity: 1; }
      80% { opacity: 1; }
      100% { transform: translateY(-12px); opacity: 0; }
    }
    .animate-flow-minimal {
      animation: flow-minimal 2s cubic-bezier(0.4, 0, 0.2, 1) infinite;
    }
    @media (min-width: 768px) {
      @keyframes flow-minimal {
        0% { transform: translateX(30px); opacity: 0; }
        20% { opacity: 1; }
        80% { opacity: 1; }
        100% { transform: translateX(-30px); opacity: 0; }
      }
    }
      .flow-icon {
        transform: rotate(0deg);
      }
    }

    @keyframes slide-down {
      from { transform: translateY(-100%); opacity: 0; }
      to { transform: translateY(0); opacity: 1; }
    }
    .animate-slide-down {
      animation: slide-down 0.4s cubic-bezier(0.16, 1, 0.3, 1) forwards;
    }
    
    @keyframes splashProgress {
      0% { transform: scaleX(0); }
      100% { transform: scaleX(1); }
    }
    .animate-splash-progress {
      animation: splashProgress 1.2s cubic-bezier(0.4, 0, 0.2, 1) forwards;
    }
</style>
</head>
<body class="min-h-screen p-3 md:p-6 flex flex-col items-center relative z-10">

  <!-- SPLASH SCREEN -->
  <div id="splashScreen" class="fixed inset-0 z-[100] bg-[#020617] flex flex-col items-center justify-center transition-opacity duration-700">
    <div class="relative flex flex-col items-center justify-center">
      <!-- Glow behind logo -->
      <div class="absolute w-32 h-32 bg-cyan-500/20 rounded-full blur-2xl animate-pulse"></div>
      
      <!-- Animated Icon (Caravan/System) -->
      <div class="w-16 h-16 bg-slate-800/80 rounded-2xl flex items-center justify-center border border-slate-700/50 shadow-2xl relative z-10 mb-6 animate-bounce">
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-8 h-8 text-cyan-400">
          <path stroke-linecap="round" stroke-linejoin="round" d="M8.25 18.75a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m3 0h6m-9 0H3.375a1.125 1.125 0 01-1.125-1.125V14.25m17.25 4.5a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m3 0h1.125c.621 0 1.129-.504 1.09-1.124a17.902 17.902 0 00-3.213-9.193 2.056 2.056 0 00-1.58-.86H14.25M16.5 18.75h-2.25m0-11.177v-.958c0-.568-.422-1.048-.987-1.106a48.554 48.554 0 00-10.026 0 1.106 1.106 0 00-.987 1.106v7.635m12-6.677v6.677m0 4.5v-4.5m0 0h-12" />
        </svg>
      </div>
      
      <h1 class="text-3xl font-black text-white tracking-widest relative z-10 drop-shadow-md">HOTO<span class="text-cyan-400">MOBİL</span></h1>
      <p class="text-slate-400 text-[10px] font-mono uppercase tracking-[0.3em] mt-3 relative z-10">INITIALIZING...</p>
      
      <!-- Progress Bar -->
      <div class="w-48 h-1 bg-slate-800 rounded-full mt-8 overflow-hidden relative z-10">
        <div class="h-full bg-cyan-400 w-full origin-left animate-splash-progress"></div>
      </div>
    </div>
  </div>

  <!-- Ambient Glow Blobs -->
  <div class="blob w-[600px] h-[600px] bg-cyan-500/20 -top-60 -left-60"></div>
  <div class="blob w-[500px] h-[500px] bg-violet-600/15 -bottom-60 -right-60"></div>
  <div class="blob w-[300px] h-[300px] bg-teal-600/10 top-1/2 left-1/2 -translate-x-1/2 -translate-y-1/2"></div>

  <!--  HEADER  -->
  <header class="w-full max-w-6xl flex justify-between items-center mb-6 md:mb-8 gap-4 relative z-10">
    <div class="flex items-center gap-3.5">
      <!-- Caravan icon -->
      <div class="p-2.5 rounded-2xl bg-cyan-500/10 border border-cyan-500/20">
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-7 h-7 text-cyan-400">
          <path stroke-linecap="round" stroke-linejoin="round" d="M8.25 18.75a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m3 0h6m-9 0H3.375a1.125 1.125 0 01-1.125-1.125V14.25m17.25 4.5a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m3 0h1.125c.621 0 1.129-.504 1.09-1.124a17.902 17.902 0 00-3.213-9.193 2.056 2.056 0 00-1.58-.86H14.25M16.5 18.75h-2.25m0-11.177v-.958c0-.568-.422-1.048-.987-1.106a48.554 48.554 0 00-10.026 0 1.106 1.106 0 00-.987 1.106v7.635m12-6.677v6.677m0 4.5v-4.5m0 0h-12" />
        </svg>
      </div>
      <!-- Brand Logo Replica -->
      <div class="flex items-end leading-none relative pb-1">
        <div class="relative flex flex-col items-center">
          <span class="text-xl sm:text-2xl font-black text-slate-100 tracking-[0.03em] uppercase select-none">HOTO</span>
          <svg class="absolute -bottom-[3px] w-[88%] h-1.5 text-cyan-400 drop-shadow-[0_0_6px_rgba(34,211,238,0.7)]" viewBox="0 0 40 6" fill="none">
            <path d="M 1.5,0.5 Q 20,5.5 38.5,0.5" stroke="currentColor" stroke-width="2.5" stroke-linecap="round"/>
          </svg>
        </div>
        <span class="text-xl sm:text-2xl font-black text-cyan-400 drop-shadow-[0_0_10px_rgba(34,211,238,0.6)] tracking-[0.03em] uppercase select-none ml-1">MOBİL</span>
      </div>
    </div>
    <div class="flex gap-4 items-center">
      <!-- Kalp Atışı İndikatörü -->
      <div id="heartbeat-dot" class="w-2.5 h-2.5 rounded-full bg-slate-700 shadow-[0_0_8px_rgba(0,0,0,0)] transition-all duration-300" title="Veri Akışı"></div>

      <!-- Hamburger Menu Button -->
      <button onclick="openSidebar()" class="btn-press flex items-center justify-center p-2.5 rounded-2xl bg-slate-800/40 hover:bg-slate-700/40 border border-slate-700/50 text-slate-300 hover:text-white transition-all">
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-6 h-6"><path stroke-linecap="round" stroke-linejoin="round" d="M3.75 6.75h16.5M3.75 12h16.5m-16.5 5.25h16.5" /></svg>
      </button>
    </div>
  </header>

  <!-- ALERT CONTAINER -->
  <div id="alert-container" class="w-full max-w-6xl relative z-50 transition-all empty:hidden"></div>

  <!--  MAIN DASHBOARD WRAPPER  -->
  <main id="dashboard-view" class="w-full max-w-6xl grid grid-cols-1 md:grid-cols-3 gap-4 md:gap-5 relative z-10">

            <!--  ENERJİ YÖNETİMİ KARTI (Sade ve Uyumlu Tasarım)  -->
    <div class="glass-card card-energy rounded-[28px] p-5 flex flex-col gap-4 relative md:col-span-2 overflow-hidden" style="display: none; border:1px solid rgba(255,255,255,0.05);">
      
      <!-- Header -->
      <div class="flex justify-between items-center z-10 mb-2">
        <div class="flex items-center gap-2">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 text-amber-400"><path stroke-linecap="round" stroke-linejoin="round" d="M3.75 13.5l10.5-11.25L12 10.5h8.25L9.75 21.75 12 13.5H3.75z" /></svg>
          <span class="card-label m-0 text-amber-100">Enerji Yönetimi</span>
        </div>
        <div class="flex items-center gap-2">
          <button id="btn-refresh-mppt" onclick="fetchMpptData()" class="px-2 py-1 bg-cyan-500/20 hover:bg-cyan-500/30 text-cyan-400 rounded-lg text-[9px] font-bold uppercase tracking-wider transition-all border border-cyan-500/30 flex items-center gap-1 cursor-pointer">
            <svg id="mppt-refresh-icon" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-3 h-3"><path stroke-linecap="round" stroke-linejoin="round" d="M16.023 9.348h4.992v-.001M2.985 19.644v-4.992m0 0h4.992m-4.993 0l3.181 3.183a8.25 8.25 0 0013.803-3.7M4.031 9.865a8.25 8.25 0 0113.803-3.7l3.181 3.182m0-4.991v4.99" /></svg>
            <span id="mppt-refresh-text">Yenile</span>
          </button>
          <span class="w-1.5 h-1.5 rounded-full bg-green-400 animate-pulse ml-1" id="mppt-status-dot"></span>
          <span class="text-[9px] font-bold text-slate-400 tracking-widest uppercase hidden sm:block" id="batt-status">Şarj Bekleniyor</span>
        </div>
      </div>

      <!-- 2 Sütunlu Sade Yapı -->
      <div class="grid grid-cols-2 gap-2 z-10">
        
        <!-- AKÜ (Sol) -->
        <div class="flex flex-col items-center justify-center p-3">
          <div class="relative w-28 h-28 flex items-center justify-center mb-3">
            <svg class="absolute w-full h-full -rotate-90" viewBox="0 0 100 100">
              <circle cx="50" cy="50" r="42" fill="none" stroke="rgba(30,41,59,0.5)" stroke-width="6"/>
              <circle cx="50" cy="50" r="42" fill="none" stroke="currentColor"
                class="text-cyan-400 transition-all duration-1000 ease-out" stroke-width="6"
                stroke-dasharray="263.9" stroke-dashoffset="132" stroke-linecap="round" id="battery-circle"/>
            </svg>
            <div class="absolute flex flex-col items-center">
              <span class="text-[9px] text-slate-500 font-bold uppercase tracking-widest mb-0.5">LiFePO4</span>
              <span class="text-3xl font-black text-white" id="batt-pct-text">0%</span>
            </div>
          </div>
          <div class="flex items-baseline gap-1">
            <span class="text-xl font-bold text-cyan-400" id="val-v">0.00</span>
            <span class="text-xs text-cyan-400/60 font-bold">V</span>
          </div>
          <div class="flex items-center gap-1 mt-1 opacity-80">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-3 h-3 text-cyan-300"><path stroke-linecap="round" stroke-linejoin="round" d="M3.75 13.5l10.5-11.25L12 10.5h8.25L9.75 21.75 12 13.5H3.75z" /></svg>
            <span class="text-[10px] text-slate-300 font-bold uppercase tracking-wider">Şarj: <span id="val-batt-c" class="text-cyan-300">0.0A</span></span>
          </div>
        </div>

        <!-- SOLAR (Sağ) -->
        <div class="flex flex-col justify-center items-center p-3 relative border-l border-slate-800/50">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6 text-orange-400 mb-1 opacity-80">
            <path stroke-linecap="round" stroke-linejoin="round" d="M12 3v2.25m6.364.386l-1.591 1.591M21 12h-2.25m-.386 6.364l-1.591-1.591M12 18.75V21m-4.773-4.227l-1.591 1.591M5.25 12H3m4.227-4.773L5.636 5.636M15.75 12a3.75 3.75 0 11-7.5 0 3.75 3.75 0 017.5 0z" />
          </svg>
          <span class="text-[9px] text-slate-500 font-bold uppercase tracking-widest mb-3">Güneş Paneli</span>
          
          <div class="flex items-baseline gap-1 mb-4">
            <span class="text-5xl font-black text-orange-400" id="val-mpw" style="letter-spacing: -1px;">0.0</span>
            <span class="text-lg text-orange-400/60 font-bold">W</span>
          </div>

          <div class="flex gap-5 opacity-80">
            <div class="flex flex-col items-center">
              <span class="text-[8px] text-slate-500 uppercase tracking-widest">Voltaj</span>
              <div class="flex items-baseline gap-0.5 mt-0.5">
                <span class="font-mono text-sm font-bold text-slate-200" id="val-mpv">0.0</span>
                <span class="text-[8px] text-orange-400 font-bold">V</span>
              </div>
            </div>
            <div class="flex flex-col items-center">
              <span class="text-[8px] text-slate-500 uppercase tracking-widest">Akım</span>
              <div class="flex items-baseline gap-0.5 mt-0.5">
                <span class="font-mono text-sm font-bold text-slate-200" id="val-mpc">0.0</span>
                <span class="text-[8px] text-blue-400 font-bold">A</span>
              </div>
            </div>
          </div>
        </div>

      </div>
    </div>
    
    <!--  İKLİMLENDİRME KARTI  -->
    <div class="glass-card card-env rounded-[32px] p-5 flex flex-col gap-4 relative overflow-hidden md:col-span-1">
      <div class="absolute -top-10 -right-10 w-48 h-48 bg-gradient-to-br from-rose-500/20 to-violet-500/20 rounded-full blur-[40px] pointer-events-none"></div>

      <!-- Header -->
      <div class="flex justify-between items-center z-10">
        <div class="flex items-center gap-2">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 text-rose-400"><path stroke-linecap="round" stroke-linejoin="round" d="M2.25 12l8.954-8.955c.44-.439 1.152-.439 1.591 0L21.75 12M4.5 9.75v10.125c0 .621.504 1.125 1.125 1.125H9.75v-4.875c0-.621.504-1.125 1.125-1.125h2.25c.621 0 1.125.504 1.125 1.125V21h4.125c.621 0 1.125-.504 1.125-1.125V9.75M8.25 21h8.25" /></svg>
          <span class="card-label m-0 text-rose-100">İklimlendirme</span>
        </div>
        <button onclick="openEnvSettingsModal()" class="p-1.5 bg-slate-800/50 hover:bg-slate-700/50 rounded-xl border border-slate-700/50 text-slate-400 hover:text-white transition-colors">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M9.594 3.94c.09-.542.56-.94 1.11-.94h2.593c.55 0 1.02.398 1.11.94l.213 1.281c.063.374.313.686.645.87.074.04.147.083.22.127.324.196.72.257 1.075.124l1.217-.456a1.125 1.125 0 011.37.49l1.296 2.247a1.125 1.125 0 01-.26 1.431l-1.003.827c-.293.24-.438.613-.431.992a6.759 6.759 0 010 .255c-.007.378.138.75.43.99l1.005.828c.424.35.534.954.26 1.43l-1.298 2.247a1.125 1.125 0 01-1.369.491l-1.217-.456c-.355-.133-.75-.072-1.076.124a6.57 6.57 0 01-.22.128c-.331.183-.581.495-.644.869l-.213 1.28c-.09.543-.56.941-1.11.941h-2.594c-.55 0-1.02-.398-1.11-.94l-.213-1.281c-.062-.374-.312-.686-.644-.87a6.52 6.52 0 01-.22-.127c-.325-.196-.72-.257-1.076-.124l-1.217.456a1.125 1.125 0 01-1.369-.49l-1.297-2.247a1.125 1.125 0 01.26-1.431l1.004-.827c.292-.24.437-.613.43-.992a6.932 6.932 0 010-.255c.007-.378-.138-.75-.43-.99l-1.004-.828a1.125 1.125 0 01-.26-1.43l1.297-2.247a1.125 1.125 0 011.37-.491l1.216.456c.356.133.751.072 1.076-.124.072-.044.146-.087.22-.128.332-.183.582-.495.644-.869l.214-1.281z" /><path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" /></svg>
        </button>
      </div>

      <!-- İçerik: Sıcaklık + Hava -->
      <div class="flex items-center justify-between z-10 mt-1">
        <div class="flex flex-col">
          <div class="flex items-start">
            <span class="text-[64px] font-black text-transparent bg-clip-text bg-gradient-to-b from-white to-rose-200 drop-shadow-md leading-none" id="val-t" style="letter-spacing: -3px;">0.0</span>
            <span class="text-2xl text-rose-400 font-bold ml-1 mt-2">°C</span>
          </div>
          <span class="text-xs font-medium text-rose-200/70 pl-1 mt-1" id="val-feels">Hissedilen: -- °C</span>
        </div>
        <!-- Hava Durumu -->
        <div class="flex flex-col items-center gap-1.5">
          <div id="wf-big-icon" class="w-12 h-12 transition-all duration-500" style="filter: drop-shadow(0 0 10px rgba(251,113,133,0.4));">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.3" stroke="currentColor" class="w-full h-full text-rose-400"><path stroke-linecap="round" stroke-linejoin="round" d="M2.25 15a4.5 4.5 0 004.5 4.5H18a3.75 3.75 0 001.332-7.257 3 3 0 00-3.758-3.848 5.25 5.25 0 00-10.233 2.33A4.502 4.502 0 002.25 15z" /></svg>
          </div>
          <span class="text-[10px] font-bold text-rose-300 tracking-widest uppercase text-center leading-tight" id="wf-text">Hava<br>Durgun</span>
        </div>
      </div>

      <!-- Orta: Isı Trend Grafiği -->
      <div class="w-full relative z-10 p-2">
        <div class="flex items-center gap-2 mb-2">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-4 h-4 text-rose-500"><path stroke-linecap="round" stroke-linejoin="round" d="M2.25 18L9 11.25l4.306 4.307a11.95 11.95 0 015.814-5.519l2.74-1.22m0 0l-5.94-2.28m5.94 2.28l-2.28 5.941" /></svg>
          <span class="text-[9px] text-slate-400 font-bold uppercase tracking-widest">Sıcaklık Trendi (12 Saat)</span>
        </div>
        <div class="relative w-full h-10 group cursor-crosshair flex items-center justify-center" id="spark-container">
          <!-- Subtle Dotted Background Grid -->
          <svg id="sparkline-t" viewBox="0 0 100 24" class="w-full h-full overflow-visible" preserveAspectRatio="none">
            <line x1="0" y1="4" x2="100" y2="4" stroke="rgba(255,255,255,0.03)" stroke-dasharray="1 3" stroke-width="0.5" />
            <line x1="0" y1="12" x2="100" y2="12" stroke="rgba(255,255,255,0.03)" stroke-dasharray="1 3" stroke-width="0.5" />
            <line x1="0" y1="20" x2="100" y2="20" stroke="rgba(255,255,255,0.03)" stroke-dasharray="1 3" stroke-width="0.5" />
            
            <!-- Faint moving mock wave line when waiting for data -->
            <path id="spark-mock-line" d="M 0,14 C 20,4 30,20 50,12 C 70,4 80,18 100,10" fill="none" stroke="rgba(251,113,133,0.18)" stroke-width="1.2" stroke-dasharray="2 3" class="animate-spark-flow transition-opacity duration-300" />

            <!-- Real solid history line (hidden initially until real data arrives) -->
            <polyline id="spark-line-t" points="0,12 100,12" fill="none" stroke="url(#line-gradient)" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="opacity-0 transition-opacity duration-300"/>
            <defs>
              <linearGradient id="line-gradient" x1="0" y1="0" x2="1" y2="0">
                <stop offset="0%" stop-color="#fb7185" stop-opacity="0.15" />
                <stop offset="100%" stop-color="#fb7185" stop-opacity="1" />
              </linearGradient>
            </defs>
          </svg>
          
          <!-- Live pulse dot (hidden initially) -->
          <div id="spark-dot-html" class="absolute w-2 h-2 rounded-full bg-rose-500 shadow-[0_0_8px_rgba(244,63,94,1)] opacity-0 transition-opacity duration-300" style="top: 50%; right: 0; transform: translate(50%, -50%);"></div>
          <div id="trend-tooltip" class="absolute hidden flex-col items-center gap-0.5 bg-slate-900/95 text-white text-[10px] px-2 py-1.5 rounded-lg shadow-xl whitespace-nowrap pointer-events-none z-50 transform -translate-x-1/2 -translate-y-full -top-1 border border-slate-700/50 backdrop-blur-md"></div>
        </div>
      </div>

      <!-- Alt: 2x2 Sensör Grid -->
      <div class="grid grid-cols-2 gap-2 z-10 mt-1">

        <!-- Nem -->
        <div class="p-2 flex items-center gap-2.5 relative">
          <div class="p-1.5 rounded-xl shrink-0" style="background:rgba(59,130,246,0.1);">
            <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" class="w-5 h-5 text-blue-400"><path d="M12 2.25c-5.385 4.362-9 8.653-9 13.125a9 9 0 1018 0c0-4.472-3.615-8.763-9-13.125z" /></svg>
          </div>
          <div class="flex flex-col">
            <span class="text-[8px] text-slate-500 font-bold uppercase tracking-widest leading-none">Nem</span>
            <div class="flex items-baseline gap-0.5 mt-0.5">
              <span class="text-base font-black text-slate-100" id="val-h">0.0</span>
              <span class="text-[9px] text-blue-400 font-bold">%</span>
            </div>
          </div>
        </div>

        <!-- Basınç -->
        <div class="p-2 flex items-center gap-2.5 relative">
          <div class="p-1.5 rounded-xl shrink-0" style="background:rgba(139,92,246,0.1);">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 text-violet-400"><circle cx="12" cy="12" r="9"/><path stroke-linecap="round" stroke-linejoin="round" d="M12 12l2.5-2.5M12 7.5v1M7.5 12h1M15.5 12h1M12 15.5v1"/></svg>
          </div>
          <div class="flex flex-col">
            <span class="text-[8px] text-slate-500 font-bold uppercase tracking-widest leading-none">Basınç</span>
            <div class="flex items-baseline gap-0.5 mt-0.5">
              <span class="text-base font-black text-slate-100" id="val-p">--</span>
              <span class="text-[9px] text-violet-400 font-bold">hPa</span>
            </div>
            <span class="inline-block w-fit px-1.5 py-0.5 text-center text-[8px] font-bold rounded uppercase mt-1" id="val-p-trend" style="color:#a78bfa; background:rgba(139,92,246,0.15);">Stabil</span>
          </div>
        </div>

        <!-- Rakım -->
        <div class="p-2 flex items-center gap-2.5 relative">
          <div class="p-1.5 rounded-xl shrink-0" style="background:rgba(20,184,166,0.1);">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 text-teal-400">
              <path stroke-linecap="round" stroke-linejoin="round" d="M3 20l5-8 3 4 4-7 6 11H3z"/>
              <path stroke-linecap="round" stroke-linejoin="round" d="M15.5 7.5a1.5 1.5 0 100-3 1.5 1.5 0 000 3z" fill="currentColor" fill-opacity="0.3"/>
            </svg>
          </div>
          <div class="flex flex-col">
            <span class="text-[8px] text-slate-500 font-bold uppercase tracking-widest leading-none">Rakım</span>
            <div class="flex items-baseline gap-0.5 mt-0.5">
              <span class="text-base font-black text-slate-100" id="val-alt">--</span>
              <span class="text-[9px] text-teal-400 font-bold">m</span>
            </div>
            <span class="text-[8px] text-slate-600 mt-0.5">±10m hata payı</span>
          </div>
        </div>

        <!-- Gaz / Duman -->
        <div id="gas-icon-bg" class="rounded-2xl p-2 border border-transparent flex items-center gap-2.5 relative transition-colors duration-500">
          <div class="p-1.5 rounded-xl shrink-0 transition-colors duration-500" id="gas-bg-svg-wrapper" style="background:rgba(34,197,94,0.1);">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 text-green-400 transition-colors duration-500" id="gas-bg-svg"><path stroke-linecap="round" stroke-linejoin="round" d="M2.25 15a4.5 4.5 0 004.5 4.5H18a3.75 3.75 0 001.332-7.257 3 3 0 00-3.758-3.848 5.25 5.25 0 00-10.233 2.33A4.502 4.502 0 002.25 15z" /></svg>
          </div>
          <div class="flex flex-col">
            <span class="text-[8px] text-slate-500 font-bold uppercase tracking-widest leading-none">Gaz/Duman</span>
            <div class="flex items-baseline gap-0.5 mt-0.5">
              <span class="text-base font-black text-slate-100" id="val-g">0</span>
              <span class="text-[9px] text-green-400 font-bold transition-colors duration-500" id="text-gas-unit">ppm</span>
            </div>
            <span class="inline-block w-fit px-1.5 py-0.5 text-center text-[8px] font-bold rounded uppercase mt-1 tracking-wider transition-colors duration-500" id="text-gas-status" style="color:#4ade80; background:rgba(74,222,128,0.1);">NORMAL</span>
          </div>
        </div>

      </div>
    </div>
    <!--  ARAÇ DENGE SİSTEMİ KARTI  -->
    <div class="glass-card card-tilt rounded-[32px] p-5 flex flex-col gap-3 relative md:col-span-1">
      <!-- Header -->
      <div class="flex justify-between items-center z-10">
        <div class="flex items-center gap-2">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 text-cyan-400"><path stroke-linecap="round" stroke-linejoin="round" d="M12 3v17.25m0 0c-1.472 0-2.882.265-4.185.75M12 20.25c1.472 0 2.882.265 4.185.75M18.75 4.97A48.416 48.416 0 0012 4.5c-2.291 0-4.545.16-6.75.47m13.5 0c1.01.143 2.01.317 3 .52m-3-.52l2.62 10.726c.122.499-.106 1.028-.589 1.202a5.988 5.988 0 01-2.031.352 5.988 5.988 0 01-2.031-.352c-.483-.174-.711-.703-.59-1.202L18.75 4.971zm-16.5.52c.99-.203 1.99-.377 3-.52m0 0l2.62 10.726c.122.499-.106 1.028-.589 1.202a5.989 5.989 0 01-2.031.352 5.989 5.989 0 01-2.031-.352c-.483-.174-.711-.703-.59-1.202L5.25 4.971z" /></svg>
          <span class="card-label m-0 text-cyan-100">Karavan Terazisi</span>
        </div>
        <div class="flex items-center gap-2">
          <button onclick="toggleTerazi()" class="p-1.5 bg-indigo-500/20 hover:bg-indigo-500/40 rounded-xl border border-indigo-500/30 text-indigo-300 hover:text-white transition-colors" title="Büyük Terazi Görünümü">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M3.75 3.75v4.5m0-4.5h4.5m-4.5 0L9 9M3.75 20.25v-4.5m0 4.5h4.5m-4.5 0L9 15M20.25 3.75h-4.5m4.5 0v4.5m0-4.5L15 9m5.25 11.25h-4.5m4.5 0v-4.5m0 4.5L15 15" /></svg>
          </button>
          <button onclick="openTiltSettingsModal()" class="p-1.5 bg-slate-800/50 hover:bg-slate-700/50 rounded-xl border border-slate-700/50 text-slate-400 hover:text-white transition-colors" title="Ayarlar">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M9.594 3.94c.09-.542.56-.94 1.11-.94h2.593c.55 0 1.02.398 1.11.94l.213 1.281c.063.374.313.686.645.87.074.04.147.083.22.127.324.196.72.257 1.075.124l1.217-.456a1.125 1.125 0 011.37.49l1.296 2.247a1.125 1.125 0 01-.26 1.431l-1.003.827c-.293.24-.438.613-.431.992a6.759 6.759 0 010 .255c-.007.378.138.75.43.99l1.005.828c.424.35.534.954.26 1.43l-1.298 2.247a1.125 1.125 0 01-1.369.491l-1.217-.456c-.355-.133-.75-.072-1.076.124a6.57 6.57 0 01-.22.128c-.331.183-.581.495-.644.869l-.213 1.28c-.09.543-.56.941-1.11.941h-2.594c-.55 0-1.02-.398-1.11-.94l-.213-1.281c-.062-.374-.312-.686-.644-.87a6.52 6.52 0 01-.22-.127c-.325-.196-.72-.257-1.076-.124l-1.217.456a1.125 1.125 0 01-1.369-.49l-1.297-2.247a1.125 1.125 0 01.26-1.431l1.004-.827c.292-.24.437-.613.43-.992a6.932 6.932 0 010-.255c.007-.378-.138-.75-.43-.99l-1.004-.828a1.125 1.125 0 01-.26-1.43l1.297-2.247a1.125 1.125 0 011.37-.491l1.216.456c.356.133.751.072 1.076-.124.072-.044.146-.087.22-.128.332-.183.582-.495.644-.869l.214-1.281z" /><path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" /></svg>
          </button>
        </div>
      </div>

      <!-- Modern 2D Silhouette Level with Platform & Arrows -->
      <div class="flex flex-col gap-3 my-auto">
        <!-- Pitch (Y axis) - Ön/Arka -->
        <div class="flex-1 flex flex-col items-center bg-slate-900/40 rounded-2xl p-2 border border-slate-700/40 relative overflow-hidden">
          <span class="text-[9px] text-slate-500 uppercase tracking-widest font-bold mb-1 z-10">Arka / Ön</span>
          <div class="h-[70px] w-full relative flex items-center justify-center mt-1">
            <!-- Sabit yatay referans çizgisi (düz zemin) -->
            <div class="absolute w-[85%] h-[1px] border-t border-dashed border-slate-600/60 top-[62%]"></div>
            
            <!-- Sol ok (Ön aşağı) -->
            <div class="absolute left-0 top-1/2 -translate-y-1/2 flex flex-col items-center z-20" id="arrow-pitch-left">
              <svg viewBox="0 0 16 24" class="w-3 h-4 text-slate-700 transition-colors duration-300"><path d="M8 4v16M8 20l-5-5M8 20l5-5" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>
            </div>
            <!-- Sağ ok (Arka aşağı) -->
            <div class="absolute right-0 top-1/2 -translate-y-1/2 flex flex-col items-center z-20" id="arrow-pitch-right">
              <svg viewBox="0 0 16 24" class="w-3 h-4 text-slate-700 transition-colors duration-300"><path d="M8 4v16M8 20l-5-5M8 20l5-5" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>
            </div>

            <!-- Eğik platform çizgisi (döner) -->
            <div class="absolute w-[75%] h-[2px] bg-cyan-500/40 rounded-full top-[62%] transition-transform duration-300" id="platform-pitch"></div>
            
            <!-- Karavan silüeti -->
            <svg id="svg-pitch" viewBox="0 0 100 60" class="w-[75%] h-full overflow-visible transition-transform duration-300 origin-[50%_65%] text-cyan-400">
              <path d="M 15,40 V 12 H 70 C 75,12 85,12 85,18 V 23 H 72 L 82,33 H 92 C 95,33 96,36 96,40 Z" fill="currentColor" fill-opacity="0.15" stroke="currentColor" stroke-width="2" stroke-linejoin="round"/>
              <circle cx="30" cy="40" r="6" fill="#0f172a" stroke="currentColor" stroke-width="2"/>
              <circle cx="78" cy="40" r="6" fill="#0f172a" stroke="currentColor" stroke-width="2"/>
              <rect x="45" y="18" width="10" height="18" rx="1" fill="none" stroke="currentColor" stroke-width="1.5"/>
              <rect x="22" y="18" width="16" height="8" rx="1" fill="currentColor" fill-opacity="0.2" stroke="currentColor" stroke-width="1.5"/>
              <path d="M 72,15 H 77 Q 80,15 80,18 V 19 H 72 Z" fill="currentColor" fill-opacity="0.2" stroke="currentColor" stroke-width="1.5"/>
              <path d="M 72,25 L 78,31 H 72 Z" fill="currentColor" fill-opacity="0.2" stroke="currentColor" stroke-width="1.5"/>
            </svg>
          </div>
          <div class="font-mono text-base font-bold text-white mt-1" id="val-y">+0.0°</div>
        </div>

        <!-- Roll (X axis) - Sağ/Sol -->
        <div class="flex-1 flex flex-col items-center bg-slate-900/40 rounded-2xl p-2 border border-slate-700/40 relative overflow-hidden">
          <span class="text-[9px] text-slate-500 uppercase tracking-widest font-bold mb-1 z-10">Sol / Sağ</span>
          <div class="h-[70px] w-full relative flex items-center justify-center mt-1">
            <!-- Sabit yatay referans çizgisi -->
            <div class="absolute w-[85%] h-[1px] border-t border-dashed border-slate-600/60 top-[62%]"></div>
            
            <!-- Sol ok -->
            <div class="absolute left-0 top-1/2 -translate-y-1/2 flex flex-col items-center z-20" id="arrow-roll-left">
              <svg viewBox="0 0 16 24" class="w-3 h-4 text-slate-700 transition-colors duration-300"><path d="M8 4v16M8 20l-5-5M8 20l5-5" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>
            </div>
            <!-- Sağ ok -->
            <div class="absolute right-0 top-1/2 -translate-y-1/2 flex flex-col items-center z-20" id="arrow-roll-right">
              <svg viewBox="0 0 16 24" class="w-3 h-4 text-slate-700 transition-colors duration-300"><path d="M8 4v16M8 20l-5-5M8 20l5-5" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>
            </div>

            <!-- Eğik platform çizgisi -->
            <div class="absolute w-[75%] h-[2px] bg-teal-500/40 rounded-full top-[62%] transition-transform duration-300" id="platform-roll"></div>
            
            <!-- Karavan silüeti -->
            <svg id="svg-roll" viewBox="0 0 100 60" class="w-[75%] h-full overflow-visible transition-transform duration-300 origin-[50%_65%] text-teal-400">
              <path d="M 30,40 V 14 Q 30,10 35,10 H 65 Q 70,10 70,14 V 40 Z" fill="currentColor" fill-opacity="0.15" stroke="currentColor" stroke-width="2" stroke-linejoin="round"/>
              <circle cx="34" cy="40" r="6" fill="#0f172a" stroke="currentColor" stroke-width="2"/>
              <circle cx="66" cy="40" r="6" fill="#0f172a" stroke="currentColor" stroke-width="2"/>
              <rect x="40" y="16" width="20" height="8" rx="1" fill="currentColor" fill-opacity="0.2" stroke="currentColor" stroke-width="1.5"/>
              <rect x="32" y="32" width="6" height="3" rx="1" fill="#ef4444" opacity="0.8"/>
              <rect x="62" y="32" width="6" height="3" rx="1" fill="#ef4444" opacity="0.8"/>
              <path d="M 30,22 H 26 V 28 H 30" fill="none" stroke="currentColor" stroke-width="1.5"/>
              <path d="M 70,22 H 74 V 28 H 70" fill="none" stroke="currentColor" stroke-width="1.5"/>
            </svg>
          </div>
          <div class="font-mono text-base font-bold text-white mt-1" id="val-x">+0.0°</div>
        </div>
      </div>

      <div class="flex items-center justify-between bg-slate-900/40 rounded-xl p-2.5 border border-slate-700/30 mt-auto">
        <span class="card-label">Durum</span>
        <span class="text-[11px] font-bold tracking-widest text-teal-400 drop-shadow-[0_0_8px_rgba(45,212,191,0.5)]" id="level-status">DÜZGÜN</span>
      </div>
      
    </div>

    <!--  KONTROL PANELİ KARTI  -->
    <div class="glass-card card-ctrl rounded-[32px] p-5 flex flex-col gap-4 relative overflow-hidden md:col-span-1">
      <!-- Header -->
      <div class="flex justify-start items-center gap-2 relative z-10 mb-2">
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 text-indigo-400"><path stroke-linecap="round" stroke-linejoin="round" d="M10.5 6h9.75M10.5 6a1.5 1.5 0 11-3 0m3 0a1.5 1.5 0 10-3 0M3.75 6H7.5m3 12h9.75m-9.75 0a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m-3.75 0H7.5m9-6h3.75m-3.75 0a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m-9.75 0h9.75" /></svg>
        <span class="card-label m-0 text-indigo-100">Kontrol Paneli</span>
      </div>

      <div class="flex flex-col gap-4 relative z-10">
        <!-- İnverter 220V Kontrol Grubu -->
        <div class="flex flex-col gap-2">
          <button id="btn-inv" onclick="toggleInv()" class="btn-press relative overflow-hidden flex items-center justify-between p-3 rounded-[24px] bg-slate-800/40 hover:bg-slate-700/40 border border-slate-700/50 transition-all select-none text-left">
            
            <div class="flex items-center gap-4">
              <!-- Icon -->
              <div id="icon-bg-inv" class="relative p-2 transition-all shrink-0">
                <svg id="icon-inv" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" class="w-8 h-8 transition-colors relative z-10 text-slate-400">
                  <path d="M9 2v4M15 2v4" stroke-linecap="round" stroke-linejoin="round"/>
                  <path d="M6 8a2 2 0 0 1 2-2h8a2 2 0 0 1 2 2v4a6 6 0 0 1-12 0V8z" stroke-linecap="round" stroke-linejoin="round"/>
                  <path d="M13 8.5l-3 3.5h3.5l-2 3.5" stroke-linecap="round" stroke-linejoin="round"/>
                  <path d="M10 16v1a1 1 0 0 0 1 1h2a1 1 0 0 0 1-1v-1" stroke-linecap="round" stroke-linejoin="round"/>
                  <path d="M12 18v4" stroke-linecap="round" stroke-linejoin="round"/>
                </svg>
              </div>
              
              <!-- Text Content -->
              <div class="text-left relative z-10">
                <div class="text-[17px] font-bold text-white tracking-wide">İnverter 220V</div>
                <div class="text-[11px] text-slate-400 mt-0.5 font-medium">Sistem Durumu: <span id="text-inv-sub" class="text-slate-500 font-bold transition-colors">Kapalı</span></div>
              </div>
            </div>
            
            <!-- State Indicator Dot (Right) -->
            <div id="icon-power-inv" class="mr-4 w-2.5 h-2.5 rounded-full bg-current text-slate-600 shadow-[0_0_5px_currentColor] shrink-0 transition-all opacity-40"></div>
          </button>
        </div>

        <!-- Gri Su Tankı Button -->
        <button id="btn-pump" class="btn-press relative overflow-hidden flex items-center justify-between p-3 rounded-[24px] bg-slate-800/40 hover:bg-slate-700/40 border border-slate-700/50 transition-all select-none text-left">
          <div class="flex items-center gap-4 flex-1">
            <!-- Icon -->
            <div id="icon-bg-pump" class="relative p-2 transition-all shrink-0">
              <svg id="icon-pump" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.5" class="w-8 h-8 text-teal-200/90 transition-colors relative z-10 overflow-visible">
                <path stroke-linecap="round" stroke-linejoin="round" d="M12 2.25c-5.385 4.362-9 8.685-9 12.825A9 9 0 1021 15.075c0-4.14-3.615-8.463-9-12.825z" />
                <g id="water-flow" class="opacity-0 transition-opacity duration-300">
                  <path d="M12 11v6 M9 13v3 M15 13v3" stroke-linecap="round" stroke-width="2" class="text-teal-400" />
                </g>
              </svg>
            </div>
            
            <!-- Text Content -->
            <div class="py-1 relative z-10">
              <div class="text-[17px] font-bold text-white tracking-wide">Gri Su Tankı</div>
              <div class="text-[11px] text-teal-400/80 mt-1 font-bold tracking-widest uppercase" id="text-pump-sub">BASILI TUT &rarr; BOŞALT</div>
            </div>
          </div>
          
          <div id="dot-pump" class="mr-4 w-2.5 h-2.5 rounded-full bg-current text-slate-600 shadow-[0_0_5px_currentColor] shrink-0 transition-all opacity-40"></div>
        </button>
      </div>
    </div>

    <!--  FOOTER (Version, Date & Clock)  -->
    <footer class="w-full mt-8 mb-2 flex flex-col sm:flex-row justify-between items-center gap-3 px-2 py-2 relative z-10 opacity-70">
      <!-- Left side: Software Version -->
      <div class="flex items-center gap-2">
        <span class="w-1.5 h-1.5 rounded-full bg-cyan-400 animate-pulse shadow-[0_0_8px_rgba(34,211,238,0.6)]"></span>
        <span class="text-[10px] sm:text-xs text-slate-400 font-medium tracking-widest uppercase">HOTOMOBİL <span class="text-cyan-400 font-bold ml-1">v2.1</span></span>
      </div>
      <!-- Right side: Date and Clock -->
      <div id="footer-time-wrapper" class="flex items-center gap-3 text-slate-400 font-mono text-[10px] sm:text-xs font-semibold select-none tracking-wider">
        <!-- Date display -->
        <span id="footer-date-text" class="border-r border-slate-800 pr-3 text-slate-500">--.--.----</span>
        <!-- Time display -->
        <div id="footer-time-container" class="flex items-center gap-1.5 text-cyan-400 font-bold">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-3.5 h-3.5"><path stroke-linecap="round" stroke-linejoin="round" d="M12 6v6h4.5m4.5 0a9 9 0 11-18 0 9 9 0 0118 0z" /></svg>
          <span id="footer-time-text">--:--:--</span>
        </div>
      </div>
    </footer>

  </main>

  <!--  TERAZİ (BUBBLE LEVEL) VIEW  -->
  <main id="terazi-view" class="w-full max-w-6xl relative z-10 hidden flex-col items-center min-h-[60vh] gap-8 mt-10">
    
    <div class="w-full max-w-sm flex justify-start -mb-2">
       <button onclick="toggleTerazi()" class="flex items-center gap-2 px-4 py-2 rounded-xl bg-slate-800/60 hover:bg-slate-700/80 border border-slate-700/50 text-slate-300 hover:text-white transition-all text-sm font-bold shadow-md">
         <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M9 15L3 9m0 0l6-6M3 9h12a6 6 0 010 12h-3" /></svg>
         Geri Dön
       </button>
    </div>

    <div class="text-center">
      <h2 class="text-3xl font-black text-white tracking-widest uppercase drop-shadow-md">Karavan Terazisi</h2>
      <p class="text-slate-400 mt-2 text-sm max-w-md mx-auto">Karavanınızı yatay olarak dengelemek için su damlasını ortadaki yeşil hedef alanına getirin.</p>
    </div>
    
    <div class="relative w-72 h-72 rounded-full border-[12px] border-slate-800 bg-slate-900 shadow-[inset_0_0_60px_rgba(0,0,0,1),0_20px_40px_rgba(0,0,0,0.5)] flex items-center justify-center overflow-hidden">
       <!-- Grid Background -->
       <div class="absolute inset-0 opacity-20 bg-[linear-gradient(rgba(255,255,255,0.2)_1px,transparent_1px),linear-gradient(90deg,rgba(255,255,255,0.2)_1px,transparent_1px)] bg-[size:20px_20px] rounded-full pointer-events-none"></div>
       
       <!-- Crosshairs SVG for super precise look -->
       <svg class="absolute inset-0 w-full h-full text-slate-500/60" viewBox="0 0 100 100">
         <line x1="50" y1="0" x2="50" y2="100" stroke="currentColor" stroke-width="0.3" />
         <line x1="0" y1="50" x2="100" y2="50" stroke="currentColor" stroke-width="0.3" />
         <!-- Degree ticks (top, bottom, left, right) -->
         <line x1="50" y1="0" x2="50" y2="5" stroke="currentColor" stroke-width="1.5" />
         <line x1="50" y1="95" x2="50" y2="100" stroke="currentColor" stroke-width="1.5" />
         <line x1="0" y1="50" x2="5" y2="50" stroke="currentColor" stroke-width="1.5" />
         <line x1="95" y1="50" x2="100" y2="50" stroke="currentColor" stroke-width="1.5" />
       </svg>

       <!-- Outer Safe Zone -->
       <div class="absolute w-36 h-36 rounded-full border border-amber-500/30 border-dashed pointer-events-none"></div>
       
       <!-- Perfect Zone - The Bullseye -->
       <div class="absolute w-14 h-14 rounded-full border-2 border-emerald-400 shadow-[0_0_20px_rgba(52,211,153,0.4)] bg-emerald-500/10 flex items-center justify-center pointer-events-none">
         <div class="w-1.5 h-1.5 bg-emerald-400 rounded-full shadow-[0_0_5px_rgba(52,211,153,0.8)]"></div>
       </div>

       <!-- The Bubble -->
       <div id="bubble-dot" class="absolute w-12 h-12 rounded-full border-[2.5px] border-cyan-400 bg-cyan-500/20 backdrop-blur-[2px] shadow-[inset_0_0_15px_rgba(34,211,238,0.5),0_0_25px_rgba(34,211,238,0.6)] transition-all duration-200 ease-out flex items-center justify-center z-10">
          <div class="w-2.5 h-2.5 rounded-full bg-cyan-100 shadow-[0_0_10px_rgba(255,255,255,1)]"></div>
       </div>
    </div>
    
    <div class="grid grid-cols-2 gap-4 w-full max-w-sm mt-4">
       <div class="glass-card rounded-2xl p-4 flex flex-col items-center justify-center text-center">
         <span class="text-[10px] font-bold text-slate-500 uppercase tracking-widest mb-1">X Ekseni (Sağ-Sol)</span>
         <span id="terazi-x" class="text-3xl font-black text-cyan-400">0.0°</span>
       </div>
       <div class="glass-card rounded-2xl p-4 flex flex-col items-center justify-center text-center">
         <span class="text-[10px] font-bold text-slate-500 uppercase tracking-widest mb-1">Y Ekseni (Ön-Arka)</span>
         <span id="terazi-y" class="text-3xl font-black text-indigo-400">0.0°</span>
       </div>
    </div>
  </main>



  <!--  SYSTEM LOG MODAL  -->
  <div id="sysLogModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div class="w-full md:max-w-2xl bg-slate-900 border-t md:border border-slate-700 md:rounded-3xl shadow-2xl h-[60vh] md:h-[70vh] flex flex-col transform transition-transform duration-150 translate-y-full md:my-auto" id="logModalContent">
      
      <!-- Header -->
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-slate-800 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-slate-300"><path stroke-linecap="round" stroke-linejoin="round" d="M8.25 6.75h12M8.25 12h12m-12 5.25h12M3.75 6.75h.007v.008H3.75V6.75zm.375 0a.375.375 0 11-.75 0 .375.375 0 01.75 0zM3.75 12h.007v.008H3.75V12zm.375 0a.375.375 0 11-.75 0 .375.375 0 01.75 0zm-.375 5.25h.007v.008H3.75v-.008zm.375 0a.375.375 0 11-.75 0 .375.375 0 01.75 0z" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">Sistem Logları</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Olay Geçmişi & İşlemler</p>
          </div>
        </div>
        <button onclick="closeLogModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>

      <!-- Filter Tabs -->
      <div class="flex items-center gap-2 p-3 border-b border-slate-800/50 bg-slate-900/50 overflow-x-auto custom-scrollbar shrink-0">
        <button onclick="setLogFilter('all')" id="btnFilter-all" class="px-3 py-1.5 rounded-lg bg-slate-700 text-white font-bold text-[11px] uppercase tracking-wider transition-colors shrink-0">Tümü</button>
        <button onclick="setLogFilter('info')" id="btnFilter-info" class="px-3 py-1.5 rounded-lg bg-slate-800 text-slate-400 hover:text-white font-bold text-[11px] uppercase tracking-wider transition-colors shrink-0">Bilgi</button>
        <button onclick="setLogFilter('warn')" id="btnFilter-warn" class="px-3 py-1.5 rounded-lg bg-slate-800 text-slate-400 hover:text-white font-bold text-[11px] uppercase tracking-wider transition-colors shrink-0">Uyarı</button>
        <button onclick="setLogFilter('error')" id="btnFilter-error" class="px-3 py-1.5 rounded-lg bg-slate-800 text-slate-400 hover:text-white font-bold text-[11px] uppercase tracking-wider transition-colors shrink-0">Hata</button>
      </div>

      <!-- Log Output Area -->
      <div class="flex-1 overflow-y-auto p-3 custom-scrollbar space-y-2 bg-slate-950/20" id="logOutput">
      </div>
      
      <div class="p-3 border-t border-slate-800 flex justify-between items-center bg-slate-900/50 md:rounded-b-3xl">
        <span class="text-[10px] text-slate-500" id="logCount">Toplam: 0 kayıt</span>
        <button onclick="clearLogs()" class="text-[10px] text-slate-400 hover:text-rose-400 uppercase tracking-wider font-bold transition-colors">Temizle</button>
      </div>
    </div>
  </div>

  <!--  CHART MODAL  -->
  <div id="chartModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div class="w-full max-w-6xl bg-slate-900 border border-slate-700 rounded-3xl shadow-2xl flex flex-col relative my-auto max-h-[95vh] overflow-hidden">
      <!-- Standard Header -->
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-cyan-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-cyan-400"><path stroke-linecap="round" stroke-linejoin="round" d="M3 13.125C3 12.504 3.504 12 4.125 12h2.25c.621 0 1.125.504 1.125 1.125v6.75C7.5 20.496 6.996 21 6.375 21h-2.25A1.125 1.125 0 013 19.875v-6.75zM9.75 8.625c0-.621.504-1.125 1.125-1.125h2.25c.621 0 1.125.504 1.125 1.125v11.25c0 .621-.504 1.125-1.125 1.125h-2.25a1.125 1.125 0 01-1.125-1.125V8.625zM16.5 4.125c0-.621.504-1.125 1.125-1.125h2.25C20.496 3 21 3.504 21 4.125v15.75c0 .621-.504 1.125-1.125 1.125h-2.25a1.125 1.125 0 01-1.125-1.125V4.125z" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">Geçmiş Veriler</h3>
            <div class="flex items-center gap-2 mt-0.5">
              <span class="text-[10px] text-slate-500 uppercase tracking-wider" id="chart-sub-label">Sensör Analizleri</span>
              <span class="w-1 h-1 rounded-full bg-slate-700"></span>
              <span class="text-[10px] text-slate-500 uppercase tracking-wider" id="chart-points-label">-- Nokta</span>
            </div>
          </div>
        </div>
        <button onclick="closeChartModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all shrink-0">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>

      <div class="p-5 flex flex-col flex-1 overflow-y-auto custom-scrollbar">
        <!-- Tabs & Range Selector Group -->
        <div class="flex flex-col md:flex-row gap-3 items-stretch md:items-center w-full lg:w-auto">
          <!-- Time Range Selector -->
          <div class="flex bg-slate-950/80 p-1 rounded-2xl border border-slate-800/60 gap-1 text-[10px] self-start md:self-auto shrink-0">
            <button id="range-24h" onclick="changeChartRange(96)" class="px-3 py-1.5 rounded-xl font-bold transition-all bg-cyan-500/20 text-cyan-400">24 Saat</button>
            <button id="range-7d" onclick="changeChartRange(672)" class="px-3 py-1.5 rounded-xl font-bold transition-all text-slate-400 hover:text-white">7 Gün</button>
            <button id="range-30d" onclick="changeChartRange(2880)" class="px-3 py-1.5 rounded-xl font-bold transition-all text-slate-400 hover:text-white">30 Gün</button>
          </div>
          <!-- Chart Tabs (2x2 Grid on Mobile, Flex Row on Desktop) -->
          <div class="grid grid-cols-3 md:flex bg-slate-950/80 p-1 rounded-2xl md:rounded-3xl border border-slate-800/60 gap-1.5 w-full md:w-auto">
            <button id="tab-env" onclick="switchChartTab('env')" class="px-1 min-[375px]:px-1.5 py-1.5 md:px-4 md:py-1.5 rounded-xl md:rounded-full text-[9px] min-[375px]:text-[10px] md:text-xs font-semibold tracking-tighter md:tracking-wide transition-all duration-300 bg-cyan-500/20 text-cyan-400 text-center">Sıcaklık &amp; Nem</button>
            <button id="tab-gas" onclick="switchChartTab('gas')" class="px-1 min-[375px]:px-1.5 py-1.5 md:px-4 md:py-1.5 rounded-xl md:rounded-full text-[9px] min-[375px]:text-[10px] md:text-xs font-semibold tracking-tighter md:tracking-wide transition-all duration-300 text-slate-400 hover:text-white text-center">Gaz (PPM)</button>
            <button id="tab-press" onclick="switchChartTab('press')" class="px-1 min-[375px]:px-1.5 py-1.5 md:px-4 md:py-1.5 rounded-xl md:rounded-full text-[9px] min-[375px]:text-[10px] md:text-xs font-semibold tracking-tighter md:tracking-wide transition-all duration-300 text-slate-400 hover:text-white text-center">Hava Basıncı</button>
          </div>
        </div>
      </div>

      <!-- Stats Row -->
      <div class="grid grid-cols-3 gap-3 mb-5">
        <div class="stat-badge">
          <div class="card-label mb-1" id="stat-label-min">Minimum</div>
          <div class="text-sm font-semibold text-cyan-400" id="stat-val-min">--</div>
        </div>
        <div class="stat-badge">
          <div class="card-label mb-1" id="stat-label-max">Maksimum</div>
          <div class="text-sm font-semibold text-rose-400" id="stat-val-max">--</div>
        </div>
        <div class="stat-badge">
          <div class="card-label mb-1" id="stat-label-avg">Ortalama</div>
          <div class="text-sm font-semibold text-amber-400" id="stat-val-avg">--</div>
        </div>
      </div>

      <!-- Chart -->
      <div class="bg-slate-950/50 rounded-2xl border border-slate-800/50 p-3 w-full h-[42vh] relative flex items-center justify-center overflow-hidden">
        
        <div id="chartLoading" class="absolute flex flex-col items-center gap-2 text-slate-400 transition-opacity z-20">
          <svg class="animate-spin h-7 w-7 text-cyan-400" fill="none" viewBox="0 0 24 24"><circle class="opacity-25" cx="12" cy="12" r="10" stroke="currentColor" stroke-width="4"></circle><path class="opacity-75" fill="currentColor" d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"></path></svg>
          <span class="text-xs">Yükleniyor...</span>
        </div>

        <!-- Empty State -->
        <div id="chartEmpty" class="absolute flex flex-col items-center gap-3 text-slate-500 opacity-0 pointer-events-none transition-opacity duration-300 z-10">
          <div class="p-4 bg-slate-900 rounded-full border border-slate-800 shadow-inner">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-8 h-8 text-slate-600"><path stroke-linecap="round" stroke-linejoin="round" d="M19.5 14.25v-2.625a3.375 3.375 0 00-3.375-3.375h-1.5A1.125 1.125 0 0113.5 7.125v-1.5a3.375 3.375 0 00-3.375-3.375H8.25m3.75 9v6m3-3H9m1.5-12H5.625c-.621 0-1.125.504-1.125 1.125v17.25c0 .621.504 1.125 1.125 1.125h12.75c.621 0 1.125-.504 1.125-1.125V11.25a9 9 0 00-9-9z" /></svg>
          </div>
          <div class="text-center">
            <span class="block text-sm font-bold text-slate-400 tracking-wide mb-1">Veri Bekleniyor</span>
            <span class="text-[10px] uppercase tracking-widest opacity-60">Kayıt Bulunamadı</span>
          </div>
        </div>

        <div id="chartContainer" class="w-full h-full overflow-x-auto custom-scrollbar opacity-0 transition-opacity duration-300 z-0">
          <div class="min-w-[900px] lg:min-w-0 h-full">
            <canvas id="historyChart" class="w-full h-full"></canvas>
          </div>
        </div>
      </div>
      <div class="flex justify-center items-center gap-2 mt-3 text-[11px] text-slate-500 lg:hidden">
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-3.5 h-3.5 animate-pulse"><path stroke-linecap="round" stroke-linejoin="round" d="M7.5 21L3 16.5m0 0L7.5 12M3 16.5h13.5m0-13.5L21 7.5m0 0L16.5 12M21 7.5H7.5" /></svg>
        <span>Kaydırarak gözatın</span>
      </div>
    </div>
  </div>

  
  <!--  ENV SETTINGS MODAL  -->
  <div id="envSettingsModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div class="w-full max-w-sm bg-slate-900 border border-slate-700 rounded-3xl shadow-2xl overflow-hidden flex flex-col max-h-[85vh] transform transition-transform duration-150 scale-95 opacity-0 my-auto" id="envSettingsContent">
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-indigo-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-indigo-400"><path stroke-linecap="round" stroke-linejoin="round" d="M12 3v2.25m6.364.386l-1.591 1.591M21 12h-2.25m-.386 6.364l-1.591-1.591M12 18.75V21m-4.773-4.227l-1.591 1.591M5.25 12H3m4.227-4.773L5.636 5.636M15.75 12a3.75 3.75 0 11-7.5 0 3.75 3.75 0 017.5 0z" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">İç Ortam Ayarları</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">İklimlendirme ve Gaz Sensörü</p>
          </div>
        </div>
        <button onclick="closeEnvSettingsModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>
      <div class="p-5 space-y-6 overflow-y-auto custom-scrollbar flex-1">
        <!-- Sıcaklık Ofseti -->
        <div>
          <div class="flex items-center gap-2.5 mb-2.5">
            <div class="p-1.5 bg-rose-500/10 rounded-xl">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-4 h-4 text-rose-400"><path stroke-linecap="round" stroke-linejoin="round" d="M15.362 5.214A8.252 8.252 0 0112 21 8.25 8.25 0 016.038 7.048 8.287 8.287 0 009 9.6a8.983 8.983 0 013.361-6.867 8.21 8.21 0 003 2.48z" /><path stroke-linecap="round" stroke-linejoin="round" d="M12 18a3.75 3.75 0 00.495-7.467 5.99 5.99 0 00-1.925 3.546 5.974 5.974 0 01-2.133-1A3.75 3.75 0 0012 18z" /></svg>
            </div>
            <span class="text-[11px] text-slate-300 uppercase tracking-widest font-bold">Sıcaklık Ofseti</span>
          </div>
          <div class="rounded-2xl p-4" style="background:rgba(255,255,255,0.03);">
            <!-- Zero-Centered Temperature Slider -->
            <div class="flex justify-between items-center mb-3">
              <!-- Mevcut Ofset + Info Tooltip Container -->
              <div class="flex items-center gap-1.5 relative group" tabindex="0">
                <span class="text-[10px] text-slate-400 font-bold uppercase tracking-wider">Mevcut Ofset</span>
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-3.5 h-3.5 text-slate-400 hover:text-white cursor-help transition-colors">
                  <path stroke-linecap="round" stroke-linejoin="round" d="M11.25 11.25l.041-.02a.75.75 0 111.083 1.083l-.041.02H11.25zM12 21.75a9.75 9.75 0 100-19.5 9.75 9.75 0 000 19.5zM12 8.25h.008v.008H12V8.25z" />
                </svg>
                <!-- Tooltip -->
                <div class="absolute bottom-full left-0 mb-2 w-56 p-2.5 bg-slate-950/95 border border-slate-700/80 text-[10px] text-slate-300 font-medium rounded-xl shadow-2xl opacity-0 pointer-events-none group-hover:opacity-100 group-focus-within:opacity-100 transition-opacity z-[100] text-left leading-normal">
                  Sensörün gösterdiği sıcaklığı düzeltmek için offset değeri. Negatif değer düşürür, pozitif yükseltir.
                  <!-- Arrow -->
                  <div class="absolute top-full left-4 border-[5px] border-transparent border-t-slate-950"></div>
                </div>
              </div>
              <div class="bg-slate-900 px-3 py-1.5 rounded-xl border border-slate-700/60 flex items-center gap-0.5">
                <span class="text-[17px] font-black text-rose-400 tabular-nums leading-none" id="t-offset-display">0.0</span>
                <span class="text-xs text-slate-500 font-bold self-end pb-0.5">°C</span>
              </div>
            </div>
            <div class="relative w-full h-8 flex items-center mb-1">
              <!-- Visual Gradient Track -->
              <div class="w-full h-2 rounded-full pointer-events-none relative" style="background:linear-gradient(to right, #3b82f6, #334155, #f43f5e);">
                <!-- Center zero tick indicator -->
                <div class="absolute left-1/2 top-1/2 -translate-x-1/2 -translate-y-1/2 w-[3px] h-4 bg-slate-400 rounded-full border border-slate-900 shadow"></div>
              </div>
              <!-- Real slider input -->
              <input type="range" id="cal-t" min="-10.0" max="10.0" step="0.1" value="0.0"
                oninput="onTempSlider(this.value)"
                class="absolute inset-x-0 w-full h-8 appearance-none cursor-pointer"
                style="background:transparent; margin:0; outline:none;"
              >
            </div>
            <div class="flex justify-between text-[9px] font-bold tracking-wide px-0.5 mt-1.5 text-slate-500">
              <span class="text-blue-400">-10.0°C (SOĞUK)</span>
              <span>0.0°C</span>
              <span class="text-rose-400">+10.0°C (SICAK)</span>
            </div>
            <!-- Durum -->
            <div class="flex items-center gap-1.5 mt-3 pt-3 border-t border-slate-800/60">
              <div class="w-1.5 h-1.5 rounded-full bg-slate-600 transition-colors duration-300" id="t-save-dot"></div>
              <span class="text-[9px] text-slate-500 font-medium" id="t-save-status">Değiştirince otomatik kaydedilir</span>
            </div>
          </div>
        </div>

        <!-- Gaz/Duman -->
        <div class="pt-5 border-t border-slate-800">
          <div class="flex items-center gap-2.5 mb-4">
            <div class="p-1.5 bg-green-500/10 rounded-xl">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-4 h-4 text-green-400"><path stroke-linecap="round" stroke-linejoin="round" d="M2.25 15a4.5 4.5 0 004.5 4.5H18a3.75 3.75 0 001.332-7.257 3 3 0 00-3.758-3.848 5.25 5.25 0 00-10.233 2.33A4.502 4.502 0 002.25 15z" /></svg>
            </div>
            <span class="text-[11px] text-slate-300 uppercase tracking-widest font-bold">MQ-2 Gaz Sensörü</span>
          </div>
          <div class="space-y-3">
            <div class="flex justify-between items-center p-3 rounded-2xl mb-3" style="background:rgba(255,255,255,0.03);">
              <div class="flex items-center gap-2.5">
                <div class="w-2 h-2 rounded-full bg-green-400 animate-pulse" id="g-en-dot"></div>
                <span class="text-sm text-white font-semibold">Sensör Durumu</span>
              </div>
              <div class="flex items-center gap-3">
                <span id="g-en-text" class="text-[10px] font-bold tracking-wider text-green-400">AÇIK</span>
                <style>#cal-g-en:checked + .slider { background:#16a34a !important; border-color:#22c55e !important; box-shadow: 0 0 8px rgba(34,197,94,0.4) !important; }</style>
                <label class="switch transform scale-90 m-0"><input type="checkbox" id="cal-g-en" checked onchange="updateGasEnText(this.checked); sendCal('gen', event)"><span class="slider"></span></label>
              </div>
            </div>
            <div id="gas-thresh-section" class="rounded-2xl p-4 transition-all duration-300" style="background:rgba(255,255,255,0.03);">
              <div class="flex justify-between items-center mb-4">
                <span class="text-[11px] text-slate-300 uppercase tracking-widest font-bold">Alarm Eşiği</span>
                <div class="flex items-center gap-1 bg-slate-900 px-3 py-1.5 rounded-xl border border-slate-700/60">
                  <span class="text-lg font-black text-cyan-400 tabular-nums leading-none" id="g-thresh-val">2000</span>
                  <span class="text-[9px] text-slate-500 font-bold ml-1 self-end pb-0.5">PPM</span>
                </div>
              </div>
              <div class="relative w-full h-8 flex items-center mb-1">
                <div class="w-full h-2 rounded-full pointer-events-none" style="background:linear-gradient(to right,#22c55e,#facc15,#f97316,#ef4444);"></div>
                <input type="range" id="cal-g" min="0" max="4000" value="2000"
                  oninput="onGasSlider(this.value)"
                  class="absolute inset-x-0 w-full h-8 appearance-none cursor-pointer"
                  style="background:transparent; margin:0; outline:none;"
                >
              </div>
              <div class="flex justify-between text-[9px] font-bold tracking-wide px-0.5 mt-2">
                <span class="text-green-500">GÜVENLİ</span>
                <span class="text-yellow-500">DÜŞÜK</span>
                <span class="text-orange-500">YÜKSEK</span>
                <span class="text-red-500">TEHLİKELİ</span>
              </div>
              <div class="flex items-center gap-1.5 mt-3 pt-3 border-t border-slate-800/60">
                <div class="w-1.5 h-1.5 rounded-full bg-slate-600 transition-colors duration-300" id="g-save-dot"></div>
                <span class="text-[9px] text-slate-500 font-medium" id="g-save-status">Değiştirince otomatik kaydedilir</span>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!--  TILT SETTINGS MODAL  -->
  <div id="tiltSettingsModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div class="w-full max-w-sm bg-slate-900 border border-slate-700 rounded-3xl shadow-2xl overflow-hidden flex flex-col transform transition-transform duration-150 scale-95 opacity-0 my-auto" id="tiltSettingsContent">
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-teal-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-teal-400"><path stroke-linecap="round" stroke-linejoin="round" d="M3.75 3v11.25A2.25 2.25 0 006 16.5h2.25M3.75 3h-1.5m1.5 0h16.5m0 0h1.5m-1.5 0v11.25A2.25 2.25 0 0118 16.5h-2.25m-7.5 0h7.5m-7.5 0l-1 3m8.5-3l1 3m0 0l.5 1.5m-.5-1.5h-9.5m0 0l-.5 1.5m.5-1.5H9" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">Karavan Terazisi</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Park ve Denge Ayarları</p>
          </div>
        </div>
        <button onclick="closeTiltSettingsModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>
      <div class="p-5 text-center">
        <div class="p-3 bg-teal-500/10 rounded-2xl border border-teal-500/20 inline-block mb-4">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-8 h-8 text-teal-400"><path stroke-linecap="round" stroke-linejoin="round" d="M8.25 18.75a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m3 0h6m-9 0H3.375a1.125 1.125 0 01-1.125-1.125V14.25m17.25 4.5a1.5 1.5 0 01-3 0m3 0a1.5 1.5 0 00-3 0m3 0h1.125c.621 0 1.129-.504 1.09-1.124a17.902 17.902 0 00-3.213-9.193 2.056 2.056 0 00-1.58-.86H14.25M16.5 18.75h-2.25m0-11.177v-.958c0-.568-.422-1.048-.987-1.106a48.554 48.554 0 00-10.026 0 1.106 1.106 0 00-.987 1.106v7.635m12-6.677v6.677m0 4.5v-4.5m0 0h-12" /></svg>
        </div>
        <p class="text-xs text-slate-400 mb-6 leading-relaxed">Araç <span class="text-white font-bold">tam düz zemindeyken</span> kalibre etmek (mevcut konumu 0° merkezi yapmak) için kullanılır.</p>
        <button onclick="sendCal('tilt', event); closeTiltSettingsModal();" class="btn-press w-full py-3 bg-teal-500/10 text-teal-400 border border-teal-500/40 rounded-xl hover:bg-teal-500 hover:text-black transition-all text-sm font-bold tracking-wider">0° Dara Al (Sıfırla)</button>
      </div>
    </div>
  </div>

  <!--  SYSTEM STATUS MODAL  -->
  <div id="sysStatusModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div class="w-full max-w-sm bg-slate-900 border border-slate-700 rounded-3xl shadow-2xl overflow-hidden flex flex-col transform transition-transform duration-150 scale-95 opacity-0 my-auto" id="sysStatusContent">
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-green-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-green-400"><path stroke-linecap="round" stroke-linejoin="round" d="M9 12.75L11.25 15 15 9.75M21 12a9 9 0 11-18 0 9 9 0 0118 0z" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">Donanım Durumu</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Sensör Bağlantı Kontrolü</p>
          </div>
        </div>
        <button onclick="closeSysStatusModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>

      <div class="p-5 flex flex-col gap-3">
        <!-- Vertical List Items -->
        <div class="flex items-center gap-3 p-3 bg-slate-800/30 rounded-2xl border border-slate-700/40">
          <div id="stat-bme" class="w-2 h-2 rounded-full bg-slate-600 shadow-[0_0_5px_currentColor] shrink-0"></div>
          <div class="flex flex-col">
            <span class="text-[10px] text-slate-200 font-bold tracking-wider uppercase">İklimlendirme Modülü</span>
            <span class="text-[9px] text-slate-500">BME280 Sensör</span>
          </div>
        </div>
        
        <div class="flex items-center gap-3 p-3 bg-slate-800/30 rounded-2xl border border-slate-700/40">
          <div id="stat-adxl" class="w-2 h-2 rounded-full bg-slate-600 shadow-[0_0_5px_currentColor] shrink-0"></div>
          <div class="flex flex-col">
            <span class="text-[10px] text-slate-200 font-bold tracking-wider uppercase">Karavan Denge</span>
            <span class="text-[9px] text-slate-500">ADXL345 Sensör</span>
          </div>
        </div>

        <div class="flex items-center gap-3 p-3 bg-slate-800/30 rounded-2xl border border-slate-700/40">
          <div id="stat-sd" class="w-2 h-2 rounded-full bg-slate-600 shadow-[0_0_5px_currentColor] shrink-0"></div>
          <div class="flex flex-col">
            <span class="text-[10px] text-slate-200 font-bold tracking-wider uppercase">Kayıt Modülü</span>
            <span class="text-[9px] text-slate-500">SD Kart (SPI)</span>
          </div>
        </div>

        <div class="flex items-center gap-3 p-3 bg-slate-800/30 rounded-2xl border border-slate-700/40">
          <div id="stat-rtc" class="w-2 h-2 rounded-full bg-slate-600 shadow-[0_0_5px_currentColor] shrink-0"></div>
          <div class="flex flex-col">
            <span class="text-[10px] text-slate-200 font-bold tracking-wider uppercase">Sistem Saati</span>
            <span class="text-[9px] text-slate-500">DS3231 Zamanlayıcı</span>
          </div>
        </div>

        <div class="flex items-center gap-3 p-3 bg-slate-800/30 rounded-2xl border border-slate-700/40">
          <div id="stat-mq2" class="w-2 h-2 rounded-full bg-slate-600 shadow-[0_0_5px_currentColor] shrink-0"></div>
          <div class="flex flex-col">
            <span class="text-[10px] text-slate-200 font-bold tracking-wider uppercase">Gaz & Duman Alarmı</span>
            <span class="text-[9px] text-slate-500">MQ-2 Güvenlik Sensörü</span>
          </div>
        </div>
        

      </div>
    </div>
  </div>

  <!--  SD CARD MODAL  -->
  <div id="sdCardModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div class="w-full max-w-sm bg-slate-900 border border-slate-700 rounded-3xl shadow-2xl overflow-hidden flex flex-col transform transition-transform duration-150 scale-95 opacity-0 my-auto" id="sdCardContent">
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-blue-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-blue-400"><path stroke-linecap="round" stroke-linejoin="round" d="M19.5 8.25l-4.5-4.5H6A2.25 2.25 0 003.75 6v12A2.25 2.25 0 006 20.25h12A2.25 2.25 0 0020.25 18V8.25z" /><path stroke-linecap="round" stroke-linejoin="round" d="M8.25 7.5v3m3-3v3m3-3v3" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">SD Kart Yönetimi</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Depolama & Log İşlemleri</p>
          </div>
        </div>
        <button onclick="closeSdCardModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>

      <div class="p-5 flex flex-col gap-4">
        
        <div class="flex flex-col gap-3 p-4 bg-slate-800/50 rounded-2xl border border-slate-700/50">
          <div class="flex justify-between items-center">
            <span class="text-[11px] text-slate-300 font-bold tracking-wider uppercase">Güncel Depolama</span>
            <span id="sd-cap-text" class="text-[10px] font-mono font-bold text-blue-400">-- / -- MB</span>
          </div>
          <div class="w-full bg-slate-900 rounded-full h-2 overflow-hidden">
            <div id="sd-cap-bar" class="bg-blue-500 h-2 rounded-full transition-all duration-700" style="width: 0%"></div>
          </div>
        </div>
        
        <div class="border-t border-slate-800 pt-4 flex flex-col gap-3">
          <p class="text-[10px] text-slate-400 leading-relaxed text-center mb-1">Tüm karavan kayıtlarınızı indirebilir veya silebilirsiniz.</p>
          <div class="flex gap-2">
            <button onclick="window.location.href='/indir'" class="flex-1 py-3 rounded-xl bg-blue-500/10 hover:bg-blue-500/20 text-blue-400 border border-blue-500/20 text-[11px] font-bold transition-colors">İndir (CSV)</button>
            <button onclick="clearSdLog()" class="flex-1 py-3 rounded-xl bg-rose-500/10 hover:bg-rose-500/20 text-rose-400 border border-rose-500/20 text-[11px] font-bold transition-colors">Temizle</button>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!--  WIFI SETTINGS MODAL  -->
  <div id="wifiSettingsModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div class="w-full max-w-sm bg-slate-900 border border-slate-700 rounded-3xl shadow-2xl overflow-hidden flex flex-col transform transition-transform duration-150 scale-95 opacity-0 my-auto" id="wifiSettingsContent">
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-cyan-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-cyan-400"><path stroke-linecap="round" stroke-linejoin="round" d="M8.288 15.038a5.25 5.25 0 017.424 0M5.106 11.856c3.807-3.808 9.98-3.808 13.788 0M1.924 8.674c5.565-5.565 14.587-5.565 20.152 0M12.53 18.22l-.53.53-.53-.53a.75.75 0 011.06 0z" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">WiFi Ayarları</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Ağ Adı ve Şifre Yönetimi</p>
          </div>
        </div>
        <button onclick="closeWifiSettingsModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>
      <div class="p-4 flex flex-col gap-4 overflow-y-auto max-h-[75vh] w-full">
        <!-- AP & mDNS Bölümü -->
        <div class="bg-slate-800/50 p-3 rounded-2xl border border-slate-700/50 flex flex-col gap-3">
          <div class="flex items-center gap-2 mb-1">
             <div class="w-1.5 h-1.5 rounded-full bg-emerald-400"></div>
             <h4 class="text-[11px] font-bold text-emerald-400 uppercase tracking-wider">Karavan Ağı (Yerel)</h4>
          </div>
          
          <div class="grid grid-cols-2 gap-3">
            <div>
              <label class="text-[10px] text-slate-400 font-bold mb-1 block">Ağ Adı (SSID)</label>
              <input type="text" id="wifi-ap-ssid-inp" placeholder="Karavan" class="w-full bg-slate-950 border border-slate-700 rounded-lg px-3 py-2 text-white text-[13px] focus:outline-none focus:border-emerald-500 transition-colors">
            </div>
            <div>
              <label class="text-[10px] text-slate-400 font-bold mb-1 block">Ağ Şifresi</label>
              <input type="text" id="wifi-ap-pass-inp" placeholder="En az 8" class="w-full bg-slate-950 border border-slate-700 rounded-lg px-3 py-2 text-white text-[13px] focus:outline-none focus:border-emerald-500 transition-colors">
            </div>
          </div>
          
          <div>
            <label class="text-[10px] text-slate-400 font-bold mb-1 block">Web Adresi (.local)</label>
            <div class="flex items-center">
              <span class="bg-slate-800 border border-slate-700 border-r-0 rounded-l-lg px-2 py-2 text-slate-400 text-[13px]">http://</span>
              <input type="text" id="wifi-mdns-inp" placeholder="karavan" class="w-full bg-slate-950 border border-slate-700 rounded-none px-2 py-2 text-white text-[13px] focus:outline-none focus:border-emerald-500 transition-colors">
              <span class="bg-slate-800 border border-slate-700 border-l-0 rounded-r-lg px-2 py-2 text-slate-400 text-[13px]">.local</span>
            </div>
          </div>

          <button onclick="saveWifiSettings()" class="w-full py-2.5 bg-emerald-500/10 hover:bg-emerald-500/20 text-emerald-400 font-bold tracking-wide rounded-lg border border-emerald-500/30 transition-all text-xs shadow-lg mt-1">Kaydet ve Yeniden Başlat</button>
        </div>

        <!-- Dış Ağ Bölümü -->
        <div class="bg-slate-800/50 p-3 rounded-2xl border border-slate-700/50 flex flex-col gap-2">
          <div class="flex justify-between items-center mb-1">
            <div class="flex items-center gap-2">
              <div class="w-1.5 h-1.5 rounded-full bg-indigo-400"></div>
              <h4 class="text-[11px] font-bold text-indigo-400 uppercase tracking-wider">Dış İnternet (İstasyon)</h4>
            </div>
          </div>
          <div class="bg-slate-900/50 p-3 rounded-xl border border-slate-700/50 flex flex-col gap-2">
             <div class="flex items-center gap-3">
               <div id="ext-wifi-dot" class="w-2.5 h-2.5 rounded-full bg-rose-500 animate-pulse shadow-[0_0_8px_rgba(244,63,94,0.6)] shrink-0"></div>
               <div class="flex flex-col w-full overflow-hidden">
                 <span id="ext-wifi-name" class="text-[12px] text-rose-400 font-bold truncate">Bağlı Değil</span>
                 <span id="ext-wifi-ip" class="text-[10px] text-slate-500">IP Yok</span>
               </div>
             </div>
             <div id="ext-wifi-buttons-container" class="grid grid-cols-1 gap-2 mt-2">
               <button onclick="openWifiScannerModal(); closeWifiSettingsModal();" class="w-full py-2 bg-indigo-500/10 hover:bg-indigo-500/20 text-indigo-400 font-bold tracking-wide rounded-lg border border-indigo-500/30 transition-all text-xs flex items-center justify-center gap-1.5">
                  <svg xmlns="http://www.w3.org/2000/svg" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M5 12.55a11 11 0 0 1 14.08 0"></path><path d="M1.42 9a16 16 0 0 1 21.16 0"></path><path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>
                  Ağ Ara
               </button>
               <button id="btn-disconnect-ext" onclick="disconnectExtWifi()" class="hidden w-full py-2 bg-rose-500/10 hover:bg-rose-500/20 text-rose-400 font-bold tracking-wide rounded-lg border border-rose-500/30 transition-all text-xs flex items-center justify-center gap-1.5">
                  <svg xmlns="http://www.w3.org/2000/svg" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M18.36 6.64a9 9 0 1 1-12.73 0"></path><line x1="12" y1="2" x2="12" y2="12"></line></svg>
                  Bağlantıyı Kes
               </button>
             </div>
          </div>
        </div>
      </div>
    </div>
  </div>

  <!-- OTA Modal -->
  <div id="otaModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden">
    <div id="otaContent" class="bg-slate-900 border border-slate-700/60 rounded-3xl p-5 w-full max-w-sm shadow-2xl transform scale-95 opacity-0 transition-all duration-300 relative overflow-hidden flex flex-col my-auto">
      <div class="absolute -top-10 -right-10 w-24 h-24 bg-violet-500/10 rounded-full blur-2xl pointer-events-none"></div>
      
      <div class="flex justify-between items-start mb-5 relative z-10">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-violet-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-violet-400"><path stroke-linecap="round" stroke-linejoin="round" d="M3 16.5v2.25A2.25 2.25 0 005.25 21h13.5A2.25 2.25 0 0021 18.75V16.5m-13.5-9L12 3m0 0l4.5 4.5M12 3v13.5" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">Yazılım Güncelleme</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Sistem (OTA) Güncellemesi</p>
          </div>
        </div>
        <button onclick="closeOtaModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>

      <div class="bg-slate-800/50 p-4 rounded-2xl border border-slate-700/50 flex flex-col gap-3 relative z-10">
        <p class="text-xs text-slate-300 leading-relaxed">
          Yeni bir KaravanOS yazılım sürümü (firmware.bin) yüklemek için dosyayı seçip güncelleyebilirsiniz. İşlem sonrası cihazınız <span class="text-violet-400 font-bold">otomatik olarak yeniden başlayacaktır</span>.
        </p>
        <div class="flex flex-col gap-3 mt-2">
          <input type="file" id="ota-file-input" accept=".bin" class="block w-full text-xs text-slate-400 file:mr-3 file:py-2 file:px-4 file:rounded-xl file:border-0 file:text-xs file:font-bold file:bg-violet-500/20 file:text-violet-300 hover:file:bg-violet-500/30 transition-all cursor-pointer bg-slate-900 rounded-xl border border-slate-700">
          <button onclick="uploadFirmware()" id="ota-upload-btn" class="w-full py-3 bg-violet-600 hover:bg-violet-500 text-white font-bold tracking-wide rounded-xl border border-violet-500/30 transition-all text-sm shadow-lg">Güncellemeyi Başlat</button>
        </div>
        
        <div id="ota-progress-container" class="hidden flex-col gap-2 mt-2">
          <div class="flex justify-between text-xs font-bold text-slate-300">
            <span id="ota-status-text">Yükleniyor...</span>
            <span id="ota-percent">0%</span>
          </div>
          <div class="w-full bg-slate-900 rounded-full h-2 border border-slate-700/50 overflow-hidden">
            <div id="ota-progress-bar" class="bg-violet-500 h-2 rounded-full transition-all duration-300" style="width: 0%"></div>
          </div>
        </div>
      </div>
    </div>
  </div>

  </div>

  <!-- SD Card Modal -->
  <div id="sdModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden opacity-0 pointer-events-none">
    <div id="sdModalContent" class="bg-slate-900 border border-slate-700/60 rounded-3xl p-5 w-full max-w-sm shadow-2xl transform scale-95 transition-all duration-300 relative overflow-hidden flex flex-col max-h-[85vh] my-auto">
      <div class="absolute -top-10 -right-10 w-24 h-24 bg-blue-500/10 rounded-full blur-2xl pointer-events-none"></div>
      
      <div class="flex justify-between items-start mb-5 relative z-10 border-b border-slate-800 pb-4">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-blue-500/10 rounded-xl">
             <svg xmlns="http://www.w3.org/2000/svg" class="h-5 w-5 text-blue-400" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19.5 8.25l-4.5-4.5H6A2.25 2.25 0 003.75 6v12A2.25 2.25 0 006 20.25h12A2.25 2.25 0 0020.25 18V8.25z" /><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M8.25 7.5v3m3-3v3m3-3v3" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">SD Kart Yönetimi</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Dosya Görüntüleme & Silme</p>
          </div>
        </div>
        <button onclick="closeSdModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all">
          <svg class="w-4 h-4" fill="none" stroke="currentColor" viewBox="0 0 24 24" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12"></path></svg>
        </button>
      </div>

      <!-- Storage Bar -->
      <div class="mb-4 bg-slate-800/40 rounded-xl p-3 border border-slate-700/50 relative z-10">
        <div class="flex justify-between items-center text-xs text-slate-300 mb-1.5">
          <span class="font-semibold">Depolama</span>
          <span id="sdStorageText" class="text-[10px] text-slate-400">Hesaplaniyor...</span>
        </div>
        <div class="w-full bg-slate-900 rounded-full h-1.5 border border-slate-800">
          <div id="sdStorageBar" class="bg-blue-500 h-1.5 rounded-full transition-all duration-500" style="width: 0%"></div>
        </div>
      </div>

      <!-- Actions (Bulk Delete & Upload) -->
      <div class="flex justify-between items-center mb-3 relative z-10">
        <div class="flex items-center gap-2">
          <label class="relative flex items-center cursor-pointer group">
            <input type="checkbox" id="sdSelectAll" onclick="toggleSdSelectAll()" class="peer sr-only">
            <div class="w-5 h-5 rounded-lg border border-slate-600 bg-slate-800/80 peer-checked:bg-blue-600 peer-checked:border-blue-500 transition-all flex items-center justify-center group-hover:border-blue-500/50 shadow-inner">
              <svg class="w-3.5 h-3.5 text-white opacity-0 peer-checked:opacity-100 transition-opacity drop-shadow-md" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="3"><path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7" /></svg>
            </div>
            <span class="ml-2 text-xs font-medium text-slate-300 group-hover:text-white transition-colors">Tümünü Seç</span>
          </label>
          <button id="sdBulkDeleteBtn" onclick="deleteSelectedSdFiles()" class="ml-2 hidden p-1.5 bg-rose-500/20 text-rose-400 hover:bg-rose-500/40 rounded-lg transition-colors text-xs font-semibold px-2">Seçilenleri Sil</button>
        </div>
        <div>
          <input type="file" id="sdUploadInput" class="hidden" onchange="uploadSdFile(this)">
          <button onclick="document.getElementById('sdUploadInput').click()" id="sdUploadBtn" class="p-1.5 px-3 bg-blue-600 hover:bg-blue-500 text-white rounded-lg transition-colors text-xs font-bold shadow-lg shadow-blue-500/20 flex items-center gap-1.5">
            <svg class="w-3.5 h-3.5" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2.5" d="M4 16v1a3 3 0 003 3h10a3 3 0 003-3v-1m-4-8l-4-4m0 0L8 8m4-4v12"></path></svg>
            Yükle
          </button>
        </div>
      </div>

      <div class="relative z-10 flex flex-col gap-2 overflow-y-auto pr-1 custom-scrollbar" id="sdFileList" style="max-height: 40vh;">
        <div class="text-center text-slate-500 text-sm py-4">Yükleniyor...</div>
      </div>
    </div>
  </div>

  <!-- WiFi Scanner Modal -->
  <div id="wifiScannerModal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all hidden opacity-0">
    <div id="wifiScannerContent" class="bg-slate-900 border border-slate-700/60 rounded-3xl p-5 w-full max-w-sm shadow-2xl transform scale-95 transition-all duration-300 relative overflow-hidden flex flex-col max-h-[85vh] my-auto">
      <div class="absolute -top-10 -right-10 w-24 h-24 bg-blue-500/10 rounded-full blur-2xl pointer-events-none"></div>
      
      <div class="flex justify-between items-center mb-5 relative z-10">
        <div class="flex items-center gap-2">
          <svg xmlns="http://www.w3.org/2000/svg" class="text-blue-400" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M5 12.55a11 11 0 0 1 14.08 0"></path><path d="M1.42 9a16 16 0 0 1 21.16 0"></path><path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>
          <h3 class="text-[14px] font-bold text-slate-200">Çevredeki Ağlar</h3>
        </div>
        <button onclick="closeWifiScannerModal(); openWifiSettingsModal();" class="text-slate-400 hover:text-white p-2 rounded-xl bg-slate-800/50 hover:bg-slate-700 transition-colors">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>

      <button onclick="scanWifi()" id="btn-scan-wifi" class="w-full relative group flex items-center justify-center gap-2 py-3 bg-gradient-to-r from-blue-600/20 to-indigo-600/20 hover:from-blue-500/30 hover:to-indigo-500/30 text-blue-300 hover:text-white font-bold tracking-wide rounded-xl border border-blue-500/30 transition-all duration-300 text-xs shadow-[0_0_15px_rgba(59,130,246,0.1)] hover:shadow-[0_0_20px_rgba(59,130,246,0.2)] overflow-hidden shrink-0">
        <svg id="scan-wifi-icon" xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" class="group-hover:animate-pulse"><path d="M5 12.55a11 11 0 0 1 14.08 0"></path><path d="M1.42 9a16 16 0 0 1 21.16 0"></path><path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>
        <svg id="scan-spinner-icon" class="animate-spin hidden" xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="12" y1="2" x2="12" y2="6"></line><line x1="12" y1="18" x2="12" y2="22"></line><line x1="4.93" y1="4.93" x2="7.76" y2="7.76"></line><line x1="16.24" y1="16.24" x2="19.07" y2="19.07"></line><line x1="2" y1="12" x2="6" y2="12"></line><line x1="18" y1="12" x2="22" y2="12"></line><line x1="4.93" y1="19.07" x2="7.76" y2="16.24"></line><line x1="16.24" y1="7.76" x2="19.07" y2="4.93"></line></svg>
        <span id="scan-wifi-text">Ağları Tara</span>
      </button>

      <div id="wifi-list" class="mt-4 flex flex-col gap-2.5 hidden overflow-y-auto pr-1 flex-1 min-h-[150px] relative z-10 custom-scrollbar">
      </div>

      <div id="wifi-password-container" class="mt-4 hidden bg-slate-950/80 p-4 rounded-xl border border-blue-500/30 shadow-inner relative z-10 transition-all shrink-0">
        <label id="selected-wifi-lbl" class="text-[11px] text-blue-400 font-bold mb-2.5 block uppercase tracking-wider truncate w-full">Ağ Seçildi</label>
        <div class="relative mb-3 flex items-center">
          <svg xmlns="http://www.w3.org/2000/svg" class="absolute left-3 top-1/2 -translate-y-1/2 text-slate-500 z-10" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="11" width="18" height="11" rx="2" ry="2"></rect><path d="M7 11V7a5 5 0 0 1 10 0v4"></path></svg>
          <input type="password" id="ext-wifi-pass-inp" placeholder="WiFi Şifresi" class="w-full bg-slate-900 border border-slate-700 rounded-lg pl-9 pr-10 py-2.5 text-white text-[13px] focus:outline-none focus:border-blue-500/60 focus:ring-1 focus:ring-blue-500/30 transition-all relative">
          <button onclick="toggleWifiPass()" type="button" class="absolute right-2 p-1 text-slate-400 hover:text-white transition-colors z-10" title="Şifreyi Göster">
            <svg id="wifi-pass-eye" xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M2 12s3-7 10-7 10 7 10 7-3 7-10 7-10-7-10-7Z"></path><circle cx="12" cy="12" r="3"></circle></svg>
          </button>
        </div>
        <button onclick="connectExtWifi()" id="btn-connect-ext" class="w-full flex items-center justify-center gap-2 py-2.5 bg-blue-600 hover:bg-blue-500 text-white font-bold rounded-lg transition-all duration-300 text-xs shadow-[0_0_10px_rgba(37,99,235,0.4)] hover:shadow-[0_0_15px_rgba(37,99,235,0.6)]">
          Bağlan
          <svg xmlns="http://www.w3.org/2000/svg" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><line x1="5" y1="12" x2="19" y2="12"></line><polyline points="12 5 19 12 12 19"></polyline></svg>
        </button>
      </div>
    </div>
  </div>

  <!--  SCRIPT  -->
  <script>
    //  Simulation State 
    var sim_v = 13.4, sim_t = 24.5, sim_h = 45.0, sim_p = 1013.0;
    var sim_x = 0.5, sim_y = -0.2, sim_g = 500;
    var sim_mp_v = 14.1, sim_mp_c = 5.2;
    var sim_alarm_thresh = 2000, sim_alarm_en = true;
    var invState = false;
    var pumpState = false;
    var sim_inv_timer = 0;
    var ws;

    //  Battery Bar 
    function updateBatteryBar(v, currentWatt, socPct) {
      let pct = socPct !== undefined ? socPct : 0;
      pct = Math.max(0, Math.min(100, pct));

      // Dairesel gösterge (r=42, çevre=263.9)
      let bCircle = document.getElementById('battery-circle');
      if (bCircle) {
        let offset = 263.9 - ((pct / 100) * 263.9);
        bCircle.style.strokeDashoffset = offset;
        if (pct <= 20) {
          bCircle.style.color = '#ef4444';
          bCircle.style.filter = 'drop-shadow(0 0 6px rgba(239,68,68,0.5))';
        } else if (pct <= 50) {
          bCircle.style.color = '#f59e0b';
          bCircle.style.filter = 'drop-shadow(0 0 6px rgba(245,158,11,0.5))';
        } else {
          bCircle.style.color = '#2dd4bf'; // teal-400
          bCircle.style.filter = 'drop-shadow(0 0 6px rgba(45,212,191,0.4))';
        }
      }
      
      // Yüzde metni
      let pctText = document.getElementById('batt-pct-text');
      if(pctText) pctText.innerText = Math.round(pct) + '%';

      // Şarj durumu yazısı
      let bStat = document.getElementById('batt-status');
      let mpptDot = document.getElementById('mppt-status-dot');
      if(bStat) {
        if(currentWatt > 5) {
          bStat.innerText = 'Şarj Oluyor';
          bStat.style.color = '#4ade80';
          if(mpptDot) mpptDot.style.background = '#4ade80';
        }
        else if(pct > 95) {
          bStat.innerText = 'Tam Dolu';
          bStat.style.color = '#38bdf8';
          if(mpptDot) mpptDot.style.background = '#38bdf8';
        }
        else {
          bStat.innerText = 'Bekleniyor';
          bStat.style.color = '#94a3b8';
          if(mpptDot) mpptDot.style.background = '#94a3b8';
        }
      }
    }

    //  Tilt Visualizer 
    function updateBubble(x, y) {
      let svgPitch = document.getElementById('svg-pitch');
      let svgRoll = document.getElementById('svg-roll');
      let platPitch = document.getElementById('platform-pitch');
      let platRoll = document.getElementById('platform-roll');
      let valXEl = document.getElementById('val-x');
      let valYEl = document.getElementById('val-y');
      
      // Karavan ve platform birlikte döner
      if(svgPitch) svgPitch.style.transform = `rotate(${y}deg)`;
      if(svgRoll) svgRoll.style.transform = `rotate(${x}deg)`;
      if(platPitch) platPitch.style.transform = `rotate(${y}deg)`;
      if(platRoll) platRoll.style.transform = `rotate(${x}deg)`;

      // Renk Dinamikleri (Yeşil -> Düz, Sarı -> Hafif Eğik, Kırmızı -> Çok Eğik)
      function getColor(val) {
        let a = Math.abs(val);
        if (a < 1.0) return { text: '#4ade80', bg: 'rgba(74, 222, 128, 0.4)' }; // Green
        if (a < 3.0) return { text: '#fbbf24', bg: 'rgba(251, 191, 36, 0.4)' }; // Amber
        return { text: '#f43f5e', bg: 'rgba(244, 63, 94, 0.4)' }; // Rose/Red
      }

      let cX = getColor(x);
      let cY = getColor(y);

      if(valXEl) valXEl.style.color = cX.text;
      if(svgRoll) svgRoll.style.color = cX.text;
      if(platRoll) platRoll.style.backgroundColor = cX.bg;

      if(valYEl) valYEl.style.color = cY.text;
      if(svgPitch) svgPitch.style.color = cY.text;
      if(platPitch) platPitch.style.backgroundColor = cY.bg;

      // Okları renklendir: hangi yöne yatıksa o taraf parlasın
      let arrowPL = document.getElementById('arrow-pitch-left');
      let arrowPR = document.getElementById('arrow-pitch-right');
      let arrowRL = document.getElementById('arrow-roll-left');
      let arrowRR = document.getElementById('arrow-roll-right');
      
      let threshold = 1.0; // Ufak bir eğimde bile sarı ok çıksın
      let activeColor = 'color: #fbbf24'; // amber
      let critColor = 'color: #f43f5e';   // red
      let idleColor = 'color: #334155';   // slate-700

      // Pitch arrows (Y: pozitif = arka yüksek/ön düşük  sol ok aktif)
      if(arrowPL && arrowPR) {
        if(y > threshold) {
          arrowPL.querySelector('svg').style.cssText = (y >= 3.0 ? critColor : activeColor);
          arrowPR.querySelector('svg').style.cssText = idleColor;
        } else if(y < -threshold) {
          arrowPR.querySelector('svg').style.cssText = (y <= -3.0 ? critColor : activeColor);
          arrowPL.querySelector('svg').style.cssText = idleColor;
        } else {
          arrowPL.querySelector('svg').style.cssText = idleColor;
          arrowPR.querySelector('svg').style.cssText = idleColor;
        }
      }
      // Roll arrows (X: pozitif = sağ düşük  sağ ok aktif)
      if(arrowRL && arrowRR) {
        if(x > threshold) {
          arrowRR.querySelector('svg').style.cssText = (x >= 3.0 ? critColor : activeColor);
          arrowRL.querySelector('svg').style.cssText = idleColor;
        } else if(x < -threshold) {
          arrowRL.querySelector('svg').style.cssText = (x <= -3.0 ? critColor : activeColor);
          arrowRR.querySelector('svg').style.cssText = idleColor;
        } else {
          arrowRL.querySelector('svg').style.cssText = idleColor;
          arrowRR.querySelector('svg').style.cssText = idleColor;
        }
      }

      // Update level status
      let totalTilt = Math.sqrt(x * x + y * y);
      let statusEl = document.getElementById('level-status');
      if (!statusEl) return;
      
      if (totalTilt < 1.0) {
        statusEl.innerText = 'MÜKEMMEL DENGE'; statusEl.className = 'text-[11px] font-bold tracking-widest text-green-400 drop-shadow-[0_0_8px_rgba(74,222,128,0.5)]';
      } else if (totalTilt < 3.0) {
        statusEl.innerText = 'HAFİF EĞİK'; statusEl.className = 'text-[11px] font-bold tracking-widest text-amber-400 drop-shadow-[0_0_8px_rgba(251,191,36,0.5)]';
      } else {
        statusEl.innerText = 'DİKKAT! ÇOK EĞİK'; statusEl.className = 'text-[11px] font-bold tracking-widest text-rose-400 drop-shadow-[0_0_8px_rgba(244,63,94,0.5)] animate-pulse';
      }
    }

    
    //  Component Settings Modals 
    function openEnvSettingsModal() {
      let m = document.getElementById('envSettingsModal');
      let c = document.getElementById('envSettingsContent');
      m.classList.remove('hidden');
      setTimeout(() => {
        c.classList.remove('scale-95', 'opacity-0');
        c.classList.add('scale-100', 'opacity-100');
      }, 10);
    }
    function closeEnvSettingsModal() {
      let m = document.getElementById('envSettingsModal');
      let c = document.getElementById('envSettingsContent');
      c.classList.remove('scale-100', 'opacity-100');
      c.classList.add('scale-95', 'opacity-0');
      setTimeout(() => {
        m.classList.add('hidden');
      }, 150);
    }

    function openTiltSettingsModal() {
      let m = document.getElementById('tiltSettingsModal');
      let c = document.getElementById('tiltSettingsContent');
      m.classList.remove('hidden');
      setTimeout(() => {
        c.classList.remove('scale-95', 'opacity-0');
        c.classList.add('scale-100', 'opacity-100');
      }, 10);
    }
    function closeTiltSettingsModal() {
      let m = document.getElementById('tiltSettingsModal');
      let c = document.getElementById('tiltSettingsContent');
      c.classList.remove('scale-100', 'opacity-100');
      c.classList.add('scale-95', 'opacity-0');
      setTimeout(() => {
        m.classList.add('hidden');
      }, 150);
    }
    //  WebSocket / Mock 
    function initWebSocket() {
      let sbStatus = document.getElementById('sidebar-status-text');
      if (window.location.protocol === 'file:' || window.location.hostname === '' || window.location.hostname === 'localhost') {
        console.log('Mock Simulator Active');
        if (sbStatus) { sbStatus.innerText = 'Simülatör'; sbStatus.className = 'text-cyan-400'; }
        setInterval(function () {
          sim_v  += (Math.random() - 0.5) * 0.05;
          sim_t  += (Math.random() - 0.5) * 0.1;
          sim_h  += (Math.random() - 0.5) * 0.2;
          // Eğimi belirgin sinüs dalgası ile simüle et (demo için)
          var tiltTime = Date.now() / 1000;
          sim_x = Math.sin(tiltTime * 0.3) * 10 + (Math.random() - 0.5) * 1;
          sim_y = Math.cos(tiltTime * 0.2) * 8 + (Math.random() - 0.5) * 1;
          sim_g  += Math.floor((Math.random() - 0.5) * 18);
          sim_mp_v += (Math.random() - 0.5) * 0.1;
          sim_mp_c += (Math.random() - 0.5) * 0.2;
          sim_p   += (Math.random() - 0.5) * 0.3;

          sim_v = Math.max(11.0, Math.min(14.4, sim_v));
          sim_g = Math.max(0, sim_g);

          if (sim_inv_timer > 0) {
            sim_inv_timer--;
            if (sim_inv_timer <= 0) {
              sim_inv_timer = 0;
              invState = false;
              addLog('İnverter Sistemi kapatıldı (Simülasyon zamanlayıcı bitti).', 'warn');
            }
          }

          // Simülasyonda Hava Tahmini (Deadband: ±1.5)
          if (!window._simPressBuf) window._simPressBuf = [];
          window._simPressBuf.push(sim_p);
          if (window._simPressBuf.length > 18) window._simPressBuf.shift();
          let sim_wf = 2; // Default Stabil
          if (window._simPressBuf.length >= 2) {
              let p_delta = sim_p - window._simPressBuf[0];
              if (p_delta <= -2.5) sim_wf = 0;
              else if (p_delta < -1.5) sim_wf = 1;
              else if (p_delta > 1.5) sim_wf = 3;
          }
          
          processData({
            v: sim_v, t: sim_t, h: sim_h, x: sim_x, y: sim_y,
            g: Math.floor(sim_g),
            al: sim_alarm_en && (sim_g > sim_alarm_thresh),
            inv: invState, inv_timer: sim_inv_timer, mp_v: sim_mp_v, mp_c: Math.max(0, sim_mp_c), p: sim_p, wf: sim_wf,
            st_b: true, st_a: true, st_s: true, st_r: true, st_v: true, st_g: true,
            epoch: Math.floor(Date.now() / 1000)
          });
        }, 1000);
      } else {
        ws = new WebSocket('ws://' + window.location.hostname + '/ws');
        ws.onopen = function () {
          if (sbStatus) { sbStatus.innerText = 'Çevrimiçi'; sbStatus.className = 'text-green-400'; }
          // Cihazın (RTC) yerel saatte çalışması için timezone farkını (dakika cinsinden) hesaba katarak gönderiyoruz
          let localEpoch = Math.floor((Date.now() - (new Date().getTimezoneOffset() * 60000)) / 1000);
          sendWs({ cmd: 'sync_time', val: localEpoch });
        };
        ws.onmessage = function (e) { processData(JSON.parse(e.data)); };
        ws.onclose = function () { 
          if (sbStatus) { sbStatus.innerText = 'Çevrimdışı'; sbStatus.className = 'text-[11px] font-bold px-3 py-1.5 bg-rose-500/10 border border-rose-500/20 rounded-xl text-rose-400 flex items-center shadow-[0_0_15px_rgba(244,63,94,0.15)] animate-pulse'; }
          setTimeout(initWebSocket, 2000); 
        };
      }
    }

    // Arayüzün WebSocket tarafından sürekli ezilmesini önlemek için son senkronize edilen değerleri tutuyoruz
    let lastSynced = { t_off: null, g_thr: null, g_en: null };
    let lastDomValues = {};

    function updateDOM(id, value, isHtml = false, isClass = false) {
       let el = document.getElementById(id);
       if(!el) return;
       let key = id + (isHtml ? '_h' : (isClass ? '_c' : '_t'));
       if(lastDomValues[key] !== value) {
          lastDomValues[key] = value;
          if(isClass) el.className = value;
          else if(isHtml) el.innerHTML = value;
          else el.innerText = value;
       }
    }

    function triggerHeartbeat() {
       let hb = document.getElementById('heartbeat-dot');
       if(hb) {
          hb.className = "w-2.5 h-2.5 rounded-full bg-cyan-400 shadow-[0_0_12px_rgba(34,211,238,0.8)] transition-none";
          setTimeout(() => {
             hb.className = "w-2.5 h-2.5 rounded-full bg-slate-700 shadow-[0_0_8px_rgba(0,0,0,0)] transition-all duration-500";
          }, 50);
       }
    }


    function renderWifiList(nets) {
      let listEl = document.getElementById('wifi-list');
      if(!listEl) return;
      listEl.innerHTML = '';
      if(nets && nets.length > 0) {
        nets.forEach(n => {
          let signalIcon = `<svg xmlns="http://www.w3.org/2000/svg" width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M5 12.55a11 11 0 0 1 14.08 0"></path><path d="M1.42 9a16 16 0 0 1 21.16 0"></path><path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path><line x1="12" y1="20" x2="12.01" y2="20"></line></svg>`;
          let color = n.q > -60 ? "text-green-400 bg-green-500/10 border-green-500/20" : n.q > -80 ? "text-yellow-400 bg-yellow-500/10 border-yellow-500/20" : "text-rose-400 bg-rose-500/10 border-rose-500/20";
          let html = `
          <div onclick="selectWifi('${n.s}')" class="group flex justify-between items-center bg-slate-800/40 hover:bg-blue-500/20 border border-slate-700/50 hover:border-blue-500/40 p-3 rounded-xl cursor-pointer transition-all duration-300 transform hover:-translate-y-0.5 hover:shadow-lg">
            <div class="flex items-center gap-3 w-full overflow-hidden">
              <div class="p-2 rounded-lg bg-slate-900/60 text-slate-400 group-hover:text-blue-400 transition-colors shrink-0">
                ${signalIcon}
              </div>
              <span class="text-[13px] font-bold text-slate-300 group-hover:text-white transition-colors tracking-wide truncate block max-w-[140px] md:max-w-[180px]">${n.s}</span>
            </div>
            <span class="text-[10px] font-bold px-2.5 py-1 rounded-lg ${color} shadow-sm backdrop-blur-sm border shrink-0 ml-2">${n.q} dBm</span>
          </div>`;
          listEl.insertAdjacentHTML('beforeend', html);
        });
      } else {
        listEl.innerHTML = '<div class="text-[11px] text-slate-500 text-center py-4 bg-slate-900/40 rounded-xl border border-slate-800/50">Çevrede ağ bulunamadı.</div>';
      }
      let btnTxt = document.getElementById('scan-wifi-text');
      if(btnTxt) btnTxt.innerText = "Yeniden Tara";
      let scanIcon = document.getElementById('scan-wifi-icon');
      let spinnerIcon = document.getElementById('scan-spinner-icon');
      if(scanIcon) scanIcon.classList.remove('hidden');
      if(spinnerIcon) spinnerIcon.classList.add('hidden');
      listEl.classList.remove('hidden');
    }

    //  Process Incoming Data 
    function processData(data) {
      triggerHeartbeat();
      if (data.syslog !== undefined) {
        if (window.showAlert) {
          let title = data.type === 'report' ? 'GÜN SONU KAMP RAPORU' : 'BİLDİRİM';
          window.showAlert(data.type === 'report' ? 'alert-report' : 'alert-info', title, data.msg, data.type || 'info');
        }
        addLog(data.msg, data.type === 'report' ? 'info' : (data.type || 'info'));
        return;
      }
      if (data.type === 'scan_res') {
        if(window.scanInterval) clearInterval(window.scanInterval);
        renderWifiList(data.nets);
        return;
      }
      
      // Footer Clock & Date update
      let footerDate = document.getElementById('footer-date-text');
      let footerTimeText = document.getElementById('footer-time-text');
      let footerTimeContainer = document.getElementById('footer-time-container');
      
      if (footerTimeContainer) {
        if (data.st_r) {
          // Connected: Cyan theme
          footerTimeContainer.className = "flex items-center gap-1.5 text-cyan-400 font-bold";
          if (footerDate) footerDate.className = "border-r border-slate-800 pr-3 text-slate-500";
          
          if (data.epoch) {
            let dt = new Date(data.epoch * 1000);
            if (footerDate) {
              let day = dt.getDate().toString().padStart(2, '0');
              let month = (dt.getMonth() + 1).toString().padStart(2, '0');
              let year = dt.getFullYear();
              footerDate.innerText = `${day}.${month}.${year}`;
            }
            if (footerTimeText) {
              footerTimeText.innerText = dt.toLocaleTimeString('tr-TR', { hour: '2-digit', minute: '2-digit', second: '2-digit' });
            }
          }
        } else {
          // Disconnected: Red/Orange warning theme
          footerTimeContainer.className = "flex items-center gap-1.5 text-rose-400 font-bold animate-pulse";
          updateDOM('footer-time-container', "flex items-center gap-1.5 text-rose-400 font-bold animate-pulse", false, true);
          updateDOM('footer-date-text', "border-r border-slate-800 pr-3 text-rose-500/50", false, true);
          updateDOM('footer-date-text', "SAAT MODÜLÜ YOK");
          updateDOM('footer-time-text', "BAĞLANTI HATASI");
        }
      }

      // Fallback for missing sensor data (null/undefined)
      let v = data.v || 0;
      let mp_v = data.mp_v || 0;
      let mp_c = data.mp_c || 0;
      let mp_w = data.mp_w || 0;
      let soc = data.soc || 0;
      let t = data.t || 0;
      let h = data.h || 0;
      let g = data.g || 0;
      // Sensör montaj yönüne göre eksenler tersine çevrildi
      let ax = -(data.x || 0);
      let ay = -(data.y || 0);

      // Terazi (Bubble Level) Güncellemesi
      let bx = ax * 12; // Hassasiyet çarpanı
      let by = ay * 12;
      let r = Math.sqrt(bx*bx + by*by);
      if(r > 115) { bx = (bx/r)*115; by = (by/r)*115; } // Dışarı taşmayı engelle
      
      let bubble = document.getElementById('bubble-dot');
      if (bubble) bubble.style.transform = `translate(${bx}px, ${by}px)`;
      updateDOM('terazi-x', ax.toFixed(1) + '°');
      updateDOM('terazi-y', ay.toFixed(1) + '°');

      updateDOM('val-v', v.toFixed(2));
      updateDOM('batt-pct-text', soc + '%');

      let mpptW = mp_w;
      updateBatteryBar(v, mpptW, soc);
      updateDOM('val-mpv', mp_v.toFixed(1));
      updateDOM('val-mpc', mp_c.toFixed(1));
      updateDOM('val-mpw', mpptW.toString());

      if (mpptW > 0 || mp_c > 0) {
        updateDOM('batt-status', 'Şarj Ediliyor');
        updateDOM('batt-status', 'text-[9px] font-bold text-green-400 tracking-widest uppercase', false, true);
        updateDOM('mppt-status-dot', 'w-1.5 h-1.5 rounded-full bg-green-400 animate-pulse', false, true);
      } else {
        updateDOM('batt-status', 'Akü Kullanılıyor');
        updateDOM('batt-status', 'text-[9px] font-bold text-orange-400 tracking-widest uppercase', false, true);
        updateDOM('mppt-status-dot', 'w-1.5 h-1.5 rounded-full bg-orange-400', false, true);
      }

      let batt_c = data.batt_c || 0;
      updateDOM('val-batt-c', batt_c.toFixed(1) + 'A');

      updateDOM('val-t', t.toFixed(1));
      updateDOM('val-h', h.toFixed(1));

      //  Hissedilen Sıcaklık (Heat Index, Steadman formülü) 
      let HI = t;
      if (t >= 27 && h >= 40) {
        HI = -8.78469475556 + 1.61139411 * t + 2.33854883889 * h
           - 0.14611605 * t * h - 0.012308094 * t * t
           - 0.016424828 * h * h + 0.002211732 * t * t * h
           + 0.00072546 * t * h * h - 0.000003582 * t * t * h * h;
      }
      updateDOM('val-feels', 'Hissedilen: ' + HI.toFixed(1) + ' °C');

      //  Basınç ve Hava Tahmini 
      if (data.p !== undefined) {
        let p = parseFloat(data.p);
        updateDOM('val-p', p.toFixed(0));

        //  Rakım Hesaplama (Uluslararası Barometre Formülü) 
        if (p > 0) {
          let alt = 44330 * (1 - Math.pow(p / 1013.25, 0.1903));
          updateDOM('val-alt', Math.round(alt).toString());
        }

        // Weather Forecast (0: Fırtına, 1: Yağmur, 2: Durgun, 3: Açık)
        if (data.wf !== undefined) {
          let wf = data.wf;
          let wfBigIcon = document.getElementById('wf-big-icon');
          let wfText    = document.getElementById('wf-text');
          let pTrendEl  = document.getElementById('val-p-trend');

          const wfColors  = ['text-red-400','text-slate-400','text-rose-400','text-yellow-400'];
          const wfGlows   = [
            'drop-shadow(0 0 10px rgba(239,68,68,0.6))',
            'drop-shadow(0 0 10px rgba(148,163,184,0.4))',
            'drop-shadow(0 0 10px rgba(251,113,133,0.4))',
            'drop-shadow(0 0 10px rgba(250,204,21,0.5))'
          ];
          const wfPaths = [
            'M3.75 13.5l10.5-11.25L12 10.5h8.25L9.75 21.75 12 13.5H3.75z',
            'M12 21v-4m-4 4v-4m8 4v-4m-4-9a5.25 5.25 0 00-10.233 2.33A4.502 4.502 0 002.25 15h16.5a4.5 4.5 0 001.332-8.757 3 3 0 00-3.758-3.848z',
            'M2.25 15a4.5 4.5 0 004.5 4.5H18a3.75 3.75 0 001.332-7.257 3 3 0 00-3.758-3.848 5.25 5.25 0 00-10.233 2.33A4.502 4.502 0 002.25 15z',
            'M12 3v2.25m6.364.386l-1.591 1.591M21 12h-2.25m-.386 6.364l-1.591-1.591M12 18.75V21m-4.773-4.227l-1.591 1.591M5.25 12H3m4.227-4.773L5.636 5.636M15.75 12a3.75 3.75 0 11-7.5 0 3.75 3.75 0 017.5 0z'
          ];
          const wfLabels = ['Fırtına\nBekleniyor','Hava\nBozacak','Hava\nDurgun','Hava\nAçacak'];
          const pTrendTxt = ['Hızlı Düşüş','Düşüyor','Stabil','Yükseliyor'];
          const pTrendClr = ['#f87171','#94a3b8','#a78bfa','#facc15'];
          const pTrendBg  = ['rgba(248,113,113,0.15)','rgba(148,163,184,0.15)','rgba(139,92,246,0.15)','rgba(250,204,21,0.15)'];

          if (wfBigIcon) {
            wfBigIcon.innerHTML = `<svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.3" stroke="currentColor" class="w-full h-full ${wfColors[wf]}"><path stroke-linecap="round" stroke-linejoin="round" d="${wfPaths[wf]}" /></svg>`;
            wfBigIcon.style.filter = wfGlows[wf];
          }
          if (wfText) {
            wfText.innerHTML = wfLabels[wf].replace('\n','<br>');
            wfText.style.color = wfColors[wf].replace('text-','').replace('-400','') === 'slate'
              ? '#94a3b8' : wfColors[wf].includes('red') ? '#f87171'
              : wfColors[wf].includes('rose') ? '#fda4af'
              : '#fde047';
          }
          if (pTrendEl) {
            pTrendEl.innerText = pTrendTxt[wf];
            pTrendEl.style.color = pTrendClr[wf];
            pTrendEl.style.background = pTrendBg[wf];
          }
        }
      } // end if (data.p !== undefined)

      //  Sparkline Trend Grafiği (Ring Buffer C++'dan) 
      let sparkLine = document.getElementById('spark-line-t');
      let sparkMockLine = document.getElementById('spark-mock-line');
      let sparkDotHtml = document.getElementById('spark-dot-html');

      // data.t_hist varsa (cihazdan geliyorsa) onu kullan, yoksa simülasyon fallback
      let histArr = [];
      let hasRealHistory = data.t_hist && data.t_hist.length > 1;
      
      if (hasRealHistory) {
        histArr = data.t_hist;
        if (sparkMockLine) sparkMockLine.classList.add('opacity-0');
        if (sparkLine) sparkLine.classList.remove('opacity-0');
        if (sparkDotHtml) sparkDotHtml.classList.remove('opacity-0');
      } else {
        // Cihaz henüz 10 dakikayı doldurmadığı için veya yeni açıldığı için yeterli geçmiş yok.
        // Şimdilik güncel sıcaklık ile düz bir çizgi (başlangıç durumu) gösterelim.
        let ct = data.t || 0;
        histArr = [ct, ct];
        if (sparkMockLine) sparkMockLine.classList.remove('opacity-0');
        if (sparkLine) sparkLine.classList.add('opacity-0');
        if (sparkDotHtml) sparkDotHtml.classList.add('opacity-0');
      }
      window._sparkHist = histArr;

      if (sparkLine && histArr.length > 1) {
        let minT = Math.min(...histArr);
        let maxT = Math.max(...histArr);
        let range = maxT - minT || 1; // 0'a bölme hatası önlemi
        let pts = histArr.map((v, i) => {
          let x = (i / (histArr.length - 1)) * 100;
          let y = 20 - ((v - minT) / range) * 16;
          return x.toFixed(1) + ',' + y.toFixed(1);
        });
        sparkLine.setAttribute('points', pts.join(' '));
        // Son nokta
        let lastPt = pts[pts.length - 1].split(',');
        let sparkDotHtml = document.getElementById('spark-dot-html');
        if (sparkDotHtml) {
          // Y koordinatı viewBox (24) üzerinden yüzdeye çevrilir
          let yPercent = (parseFloat(lastPt[1]) / 24.0) * 100;
          sparkDotHtml.style.top = yPercent + '%';
        }
      }

      let xSign = ax >= 0 ? '+' : '';
      let ySign = ay >= 0 ? '+' : '';
      document.getElementById('val-x').innerText = xSign + ax.toFixed(1);
      document.getElementById('val-y').innerText = ySign + ay.toFixed(1);
      updateBubble(ax, ay);

      document.getElementById('val-g').innerText = g;
      let textGas = document.getElementById('text-gas-status');
      let gasIconBg = document.getElementById('gas-icon-bg');
      let gasSvgWrapper = document.getElementById('gas-bg-svg-wrapper');
      let gasUnit = document.getElementById('text-gas-unit');

      if (window.gasAlarmActive === undefined) window.gasAlarmActive = false;

      if (data.al !== window.gasAlarmActive) {
        if (data.al) {
          addLog('Gaz/Duman alarmı TETİKLENDİ!', 'error');
          if(window.showAlert) window.showAlert('alert-gas', 'DİKKAT: GAZ/DUMAN ALARMI', 'Karavan içinde yüksek oranda zararlı gaz veya duman tespit edildi! Ortamı derhal havalandırın.', 'alarm');
        } else {
          addLog('Gaz/Duman seviyesi normale döndü.', 'success');
          if(window.hideAlert) window.hideAlert('alert-gas');
        }
        window.gasAlarmActive = data.al;
      }
      
      if (data.al) {
        textGas.innerText = 'TEHLİKE';
        textGas.style.color = '#ef4444';
        textGas.style.background = 'rgba(239,68,68,0.15)';
        
        gasIconBg.style.background = 'rgba(239,68,68,0.15)';
        gasIconBg.style.borderColor = 'rgba(239,68,68,0.3)';
        gasSvgWrapper.style.color = 'rgba(239,68,68,0.2)';
        gasUnit.style.color = '#ef4444';
      } else {
        textGas.innerText = 'NORMAL';
        textGas.style.color = '#4ade80';
        textGas.style.background = 'rgba(74,222,128,0.1)';
        
        gasIconBg.style.background = '';
        gasIconBg.style.borderColor = '';
        gasSvgWrapper.style.color = '';
        gasUnit.style.color = '#4ade80';
      }

      if (data.inv !== invState) {
        if (data.inv) addLog('İnverter Sistemi 220V açıldı.', 'info');
        else addLog('İnverter Sistemi kapatıldı.', 'warn');
        invState = data.inv;
      }
      
      let btnInv = document.getElementById('btn-inv');
      let textInvSub = document.getElementById('text-inv-sub');
      let iconInv = document.getElementById('icon-inv');
      let iconBgInv = document.getElementById('icon-bg-inv');
      let dotInv = document.getElementById('dot-inv');
      let glowInv = document.getElementById('');

      let iconPowerInv = document.getElementById('icon-power-inv');
      
      if (invState) {
        btnInv.style.borderColor = 'rgba(249,115,22,0.2)';
        btnInv.style.background = 'rgba(249,115,22,0.1)';
        if (data.inv_timer > 0) {
          let m = Math.floor(data.inv_timer / 60);
          let s = data.inv_timer % 60;
          let timeStr = (m < 10 ? '0' : '') + m + ':' + (s < 10 ? '0' : '') + s;
          textInvSub.innerHTML = `AÇIK (<span class="pulse-orange inline-block">${timeStr}</span>)`;
          textInvSub.style.color = '#f97316';
        } else {
          textInvSub.innerText = 'AÇIK';
          textInvSub.style.color = '#f97316';
        }
        iconInv.style.color = '#f97316';
        // iconBgInv.style.background = 'rgba(249,115,22,0.15)';
        // iconBgInv.style.borderColor = 'rgba(249,115,22,0.15)';
        if(iconPowerInv) {
          iconPowerInv.style.color = '#f97316';
          iconPowerInv.style.opacity = '1';
        }
      } else {
        btnInv.style.borderColor = '';
        btnInv.style.background = '';
        textInvSub.innerText = 'Kapalı';
        textInvSub.style.color = '';
        iconInv.style.color = '';
        iconBgInv.style.background = '';
        iconBgInv.style.borderColor = '';
        if(iconPowerInv) {
          iconPowerInv.style.color = '';
          iconPowerInv.style.opacity = '';
        }
      }
      
      // Sistem Durumu Güncellemesi
      if(data.st_b !== undefined) document.getElementById('stat-bme').className = data.st_b ? 'w-2.5 h-2.5 rounded-full bg-green-400' : 'w-2.5 h-2.5 rounded-full bg-red-500 animate-pulse';
      if(data.st_a !== undefined) document.getElementById('stat-adxl').className = data.st_a ? 'w-2.5 h-2.5 rounded-full bg-green-400' : 'w-2.5 h-2.5 rounded-full bg-red-500 animate-pulse';
      if(data.st_s !== undefined) {
        let sdDot = document.getElementById('stat-sd');
        if (sdDot) sdDot.className = data.st_s ? 'w-2.5 h-2.5 rounded-full bg-green-400' : 'w-2.5 h-2.5 rounded-full bg-red-500 animate-pulse';
        let sdText = document.getElementById('sd-cap-text');
        let sdBar = document.getElementById('sd-cap-bar');
        if (data.st_s && data.sd_t !== undefined && data.sd_u !== undefined) {
          if (sdText) sdText.innerText = data.sd_u.toFixed(1) + ' / ' + data.sd_t.toFixed(1) + ' MB';
          if (sdBar) sdBar.style.width = ((data.sd_u / data.sd_t) * 100) + '%';
        } else {
          if (sdText) sdText.innerText = "Kart Bulunamadı";
          if (sdBar) sdBar.style.width = "0%";
        }
      }
      if(data.st_r !== undefined) document.getElementById('stat-rtc').className = data.st_r ? 'w-2.5 h-2.5 rounded-full bg-green-400' : 'w-2.5 h-2.5 rounded-full bg-red-500 animate-pulse';
      if(data.st_g !== undefined) document.getElementById('stat-mq2').className = data.st_g ? 'w-2.5 h-2.5 rounded-full bg-green-400' : 'w-2.5 h-2.5 rounded-full bg-red-500 animate-pulse';
      
      // UI Ayarları Senkronizasyonu (Sadece ESP32 tarafında gerçekten değişmişse güncelle)
      let wifiModal = document.getElementById('wifiSettingsModal');
      let isWifiModalOpen = wifiModal && !wifiModal.classList.contains('hidden');
      
      // Sadece wifi modalı kapalıysa (veya kullanıcı işlem yapmıyorsa) güncelle, böylece yazarken veri ezilmez!
      if(!isWifiModalOpen) {
        if(data.ap_s !== undefined) {
          let el = document.getElementById('wifi-ap-ssid-inp');
          if(el) el.value = data.ap_s;
        }
        if(data.ap_p !== undefined) {
          let el = document.getElementById('wifi-ap-pass-inp');
          if(el) el.value = data.ap_p;
        }
        if(data.mdns !== undefined) {
          let el = document.getElementById('wifi-mdns-inp');
          if(el) el.value = data.mdns;
        }
      }
      // Dış ağ detayları artık Karavan Portal üzerinden yönetiliyor.
      if(data.ext_ip !== undefined) {
        let extName = document.getElementById('ext-wifi-name');
        let extIp = document.getElementById('ext-wifi-ip');
        let extDot = document.getElementById('ext-wifi-dot');
        let btnContainer = document.getElementById('ext-wifi-buttons-container');
        let disconnectBtn = document.getElementById('btn-disconnect-ext');
        
        if(data.ext_ip.length > 0) {
          if(extName) {
            extName.innerText = (data.ext_ssid && data.ext_ssid.length > 0) ? "Bağlı: " + data.ext_ssid : "Bağlı";
            extName.className = "text-[12px] text-green-400 font-bold truncate";
          }
          if(extIp) extIp.innerText = "IP: " + data.ext_ip;
          if(extDot) extDot.className = "w-2.5 h-2.5 rounded-full bg-green-500 shadow-[0_0_8px_rgba(34,197,94,0.6)] shrink-0";
          
          if(btnContainer) btnContainer.className = "grid grid-cols-2 gap-2 mt-2";
          if(disconnectBtn) disconnectBtn.classList.remove('hidden');
        } else {
          if(extName) {
            extName.innerText = "Bağlı Değil";
            extName.className = "text-[12px] text-rose-400 font-bold truncate";
          }
          if(extIp) extIp.innerText = "IP Yok";
          if(extDot) extDot.className = "w-2.5 h-2.5 rounded-full bg-rose-500 animate-pulse shadow-[0_0_8px_rgba(244,63,94,0.6)] shrink-0";
          
          if(btnContainer) btnContainer.className = "grid grid-cols-1 gap-2 mt-2";
          if(disconnectBtn) disconnectBtn.classList.add('hidden');
        }
      }
      if(data.t_off !== undefined && data.t_off !== lastSynced.t_off) {
        let tval = parseFloat(data.t_off);
        let tinp = document.getElementById('cal-t');
        let tdisp = document.getElementById('t-offset-display');
        if(tinp) tinp.value = tval.toFixed(1);
        if(tdisp) tdisp.innerText = (tval >= 0 ? '+' : '') + tval.toFixed(1);
        lastSynced.t_off = data.t_off;
      }
      if(data.g_thr !== undefined && data.g_thr !== lastSynced.g_thr) {
        document.getElementById('cal-g').value = data.g_thr;
        document.getElementById('g-thresh-val').innerText = data.g_thr;
        lastSynced.g_thr = data.g_thr;
      }
      if(data.g_en !== undefined && data.g_en !== lastSynced.g_en) {
        document.getElementById('cal-g-en').checked = data.g_en;
        if(typeof updateGasEnText === 'function') updateGasEnText(data.g_en);
        lastSynced.g_en = data.g_en;
      }
      if(data.pm !== undefined) {
        if(data.pm !== pumpState) {
          pumpState = data.pm;
          let pFlow = document.getElementById('pump-flow');
          if(pumpState) {
            if(pFlow) { pFlow.style.opacity = '1'; pFlow.classList.add('animate-flow'); }
          } else {
            if(pFlow) { pFlow.style.opacity = '0'; pFlow.classList.remove('animate-flow'); }
          }
        }
      }
      
    }

    //  Controls 
    function fetchMpptData() {
      let btn = document.getElementById('btn-refresh-mppt');
      let icon = document.getElementById('mppt-refresh-icon');
      let text = document.getElementById('mppt-refresh-text');
      
      if(btn) {
        btn.disabled = true;
        btn.classList.add('opacity-50', 'cursor-not-allowed');
        if(icon) icon.classList.add('animate-spin');
        if(text) text.innerText = 'Bağlanıyor...';
      }
      
      sendWs({ cmd: 'fetch_mppt' });
      
      // Auto-reset button after 6 seconds (timeout)
      setTimeout(() => {
        if(btn) {
          btn.disabled = false;
          btn.classList.remove('opacity-50', 'cursor-not-allowed');
          if(icon) icon.classList.remove('animate-spin');
          if(text) text.innerText = 'Yenile';
        }
      }, 6000);
    }

    function sendWs(obj) {
      if (ws && ws.readyState === WebSocket.OPEN) ws.send(JSON.stringify(obj));
    }

    function showInvModal() {
      let modal = document.getElementById('inv-modal');
      let content = document.getElementById('inv-modal-content');
      modal.classList.remove('opacity-0', 'pointer-events-none');
      content.classList.remove('scale-95');
      content.classList.add('scale-100');
    }

    function hideInvModal() {
      let modal = document.getElementById('inv-modal');
      let content = document.getElementById('inv-modal-content');
      modal.classList.add('opacity-0', 'pointer-events-none');
      content.classList.remove('scale-100');
      content.classList.add('scale-95');
    }

    function startInvWithTimer(minutes) {
      hideInvModal();
      if (ws && ws.readyState === WebSocket.OPEN) {
        if (minutes === -1) {
          sendWs({ cmd: 'inv', val: true });
          addLog('İnverter Sistemi süresiz açıldı.', 'info');
        } else {
          sendWs({ cmd: 'inv_timer', val: minutes });
          addLog(`İnverter Sistemi ${minutes} dakika süreli açıldı.`, 'info');
        }
      } else {
        // Simülasyon (Preview) Modu
        invState = true;
        let timerVal = minutes === -1 ? 0 : minutes * 60;
        // Simülasyonda Hava Tahmini (Deadband: ±1.5)
          if (!window._simPressBuf) window._simPressBuf = [];
          window._simPressBuf.push(sim_p);
          if (window._simPressBuf.length > 18) window._simPressBuf.shift();
          let sim_wf = 2; // Default Stabil
          if (window._simPressBuf.length >= 2) {
              let p_delta = sim_p - window._simPressBuf[0];
              if (p_delta <= -2.5) sim_wf = 0;
              else if (p_delta < -1.5) sim_wf = 1;
              else if (p_delta > 1.5) sim_wf = 3;
          }
          processData({
            v: sim_v, t: sim_t, h: sim_h, x: sim_x, y: sim_y,
            g: Math.floor(sim_g),
            al: sim_alarm_en && (sim_g > sim_alarm_thresh),
            inv: invState, inv_timer: sim_inv_timer, mp_v: sim_mp_v, mp_c: Math.max(0, sim_mp_c), p: sim_p, wf: sim_wf
          });
          if (minutes === -1) addLog('İnverter Sistemi süresiz açıldı (Simülasyon).', 'info');
          else addLog(`İnverter Sistemi ${minutes} dakika süreli açıldı (Simülasyon).`, 'info');
      }
    }

    // UI Toggles
    function toggleTerazi() {
      let dash = document.getElementById('dashboard-view');
      let ter = document.getElementById('terazi-view');
      if(ter.classList.contains('hidden')) {
         dash.classList.add('hidden');
         ter.classList.remove('hidden');
         ter.classList.add('flex');
      } else {
         ter.classList.add('hidden');
         ter.classList.remove('flex');
         dash.classList.remove('hidden');
      }
    }

    function toggleInv() {
      if (invState) {
        // Açıksa direkt kapat
        if (ws && ws.readyState === WebSocket.OPEN) {
          sendWs({ cmd: 'inv', val: false });
        } else {
          invState = false;
          // Simülasyonda Hava Tahmini (Deadband: ±1.5)
          if (!window._simPressBuf) window._simPressBuf = [];
          window._simPressBuf.push(sim_p);
          if (window._simPressBuf.length > 18) window._simPressBuf.shift();
          let sim_wf = 2; // Default Stabil
          if (window._simPressBuf.length >= 2) {
              let p_delta = sim_p - window._simPressBuf[0];
              if (p_delta <= -2.5) sim_wf = 0;
              else if (p_delta < -1.5) sim_wf = 1;
              else if (p_delta > 1.5) sim_wf = 3;
          }
          
          processData({
            v: sim_v, t: sim_t, h: sim_h, x: sim_x, y: sim_y,
            g: Math.floor(sim_g),
            al: sim_alarm_en && (sim_g > sim_alarm_thresh),
            inv: invState, inv_timer: sim_inv_timer, mp_v: sim_mp_v, mp_c: Math.max(0, sim_mp_c), p: sim_p, wf: sim_wf
          });
          addLog('İnverter Sistemi kapatıldı (Simülasyon).', 'warn');
        }
      } else {
        // Kapalıysa modalı göster
        showInvModal();
      }
    }

    var pumpBtn = document.getElementById('btn-pump');
    var pumpActive = false;

    function setPump(state) {
      if (pumpActive === state) return;
      pumpActive = state;
      sendWs({ cmd: 'pump', val: state });
      
      let wFlow = document.getElementById('water-flow');
      let btnPump = document.getElementById('btn-pump');
      let dotPump = document.getElementById('dot-pump');
      let textPumpSub = document.getElementById('text-pump-sub');
      
      if (state) {
        addLog('Gri Su Tankı çalıştırılıyor...', 'info');
        if(btnPump) {
          btnPump.style.borderColor = 'rgba(45,212,191,0.2)';
          btnPump.style.background = 'rgba(45,212,191,0.1)';
        }
        if(wFlow) {
            wFlow.style.opacity = '1';
            wFlow.classList.add('animate-flow');
        }
        if(dotPump) {
            dotPump.style.color = '#2dd4bf';
            dotPump.style.opacity = '1';
        }
        if(textPumpSub) {
            textPumpSub.innerText = 'BOŞALTILIYOR...';
            textPumpSub.style.color = '#2dd4bf';
        }
      } else {
        addLog('Gri Su Tankı durduruldu.', 'warn');
        if(btnPump) {
          btnPump.style.borderColor = '';
          btnPump.style.background = '';
        }
        if(wFlow) {
            wFlow.style.opacity = '0';
            wFlow.classList.remove('animate-flow');
        }
        if(dotPump) {
            dotPump.style.color = '';
            dotPump.style.opacity = '';
        }
        if(textPumpSub) {
            textPumpSub.innerText = 'Basılı Tut';
            textPumpSub.style.color = '';
        }
      }
    }

    if(pumpBtn) {
        pumpBtn.addEventListener('mousedown', () => setPump(true));
        pumpBtn.addEventListener('mouseup', () => setPump(false));
        pumpBtn.addEventListener('mouseleave', () => setPump(false));
        pumpBtn.addEventListener('touchstart', e => { e.preventDefault(); setPump(true); }, {passive: false});
        pumpBtn.addEventListener('touchend', e => { e.preventDefault(); setPump(false); }, {passive: false});
    }

    // Sparkline Hover Tooltip
    let sparkContainer = document.getElementById('spark-container');
    let trendTooltip = document.getElementById('trend-tooltip');
    if (sparkContainer && trendTooltip) {
      sparkContainer.addEventListener('mousemove', (e) => {
        let hist = window._sparkHist;
        if(!hist || hist.length < 2) return;
        let rect = sparkContainer.getBoundingClientRect();
        let xPercent = (e.clientX - rect.left) / rect.width;
        xPercent = Math.max(0, Math.min(1, xPercent));
        
        let index = Math.round(xPercent * (hist.length - 1));
        let val = hist[index];
        
        // Hesapla: Her nokta 10 dakika (12 saat = 72 nokta)
        let diffPoints = (hist.length - 1) - index;
        let diffMins = diffPoints * 10;
        let timeStr = diffMins === 0 ? "Şu an" : 
                      (diffMins < 60 ? `${diffMins} dk önce` : 
                      `${Math.floor(diffMins/60)} sa ${diffMins%60} dk önce`);

        trendTooltip.innerHTML = `<span class="font-bold text-white text-xs">${val.toFixed(1)}°C</span><span class="text-[8.5px] text-slate-400 font-medium">${timeStr}</span>`;
        trendTooltip.style.left = (xPercent * 100) + '%';
        trendTooltip.classList.remove('hidden');
        trendTooltip.classList.add('flex');
      });
      sparkContainer.addEventListener('mouseleave', () => {
        trendTooltip.classList.add('hidden');
        trendTooltip.classList.remove('flex');
      });
    }

    function sendMute() {
      sendWs({ cmd: 'mute' });
      let btn = document.getElementById('btn-mute');
      btn.innerText = ' SUSTURULDU';
      btn.classList.remove('animate-pulse');
      btn.style.opacity = '0.5';
    }

    //  Settings Modal 
    function openSettingsModal() {
      const modal = document.getElementById('sysSettingsModal');
      const content = document.getElementById('settingsModalContent');
      modal.classList.remove('hidden');
      setTimeout(() => {
        content.classList.remove('translate-y-full');
      }, 10);
    }
    function closeSettingsModal() {
      const modal = document.getElementById('sysSettingsModal');
      const content = document.getElementById('settingsModalContent');
      content.classList.add('translate-y-full');
      setTimeout(() => {
        modal.classList.add('hidden');
      }, 300);
    }

    //  Log System 
    let sysLogsArray = JSON.parse(localStorage.getItem('karavanSysLogs') || '[]');
    let currentLogFilter = 'all';

    function setLogFilter(filter) {
      currentLogFilter = filter;
      ['all', 'info', 'warn', 'error'].forEach(f => {
        let btn = document.getElementById('btnFilter-' + f);
        if(!btn) return;
        if(f === filter) {
          btn.classList.remove('bg-slate-800', 'text-slate-400');
          btn.classList.add('bg-slate-700', 'text-white');
        } else {
          btn.classList.add('bg-slate-800', 'text-slate-400');
          btn.classList.remove('bg-slate-700', 'text-white');
        }
      });
      renderLogs();
    }

    function renderLogs() {
      const logOut = document.getElementById('logOutput');
      const logCountEl = document.getElementById('logCount');
      if (!logOut) return;
      logOut.innerHTML = '';

      let filteredLogs = sysLogsArray;
      if (currentLogFilter !== 'all') {
        filteredLogs = sysLogsArray.filter(l => l.type === currentLogFilter || (currentLogFilter==='info' && l.type==='success'));
      }

      if (filteredLogs.length === 0) {
        logOut.innerHTML = '<div class="flex flex-col items-center justify-center py-12 text-center"><svg class="w-8 h-8 text-slate-700 mb-3" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5" d="M9 12h6m-6 4h6m2 5H7a2 2 0 01-2-2V5a2 2 0 012-2h5.586a1 1 0 01.707.293l5.414 5.414a1 1 0 01.293.707V19a2 2 0 01-2 2z"/></svg><span class="text-slate-600 text-xs">Kayıt bulunamadı</span></div>';
      }

      filteredLogs.forEach(log => {
        let accentColor, labelText, iconSvg;

        if (log.type === 'error') {
          accentColor = '#f43f5e'; labelText = 'HATA';
          iconSvg = `<svg class="w-3 h-3" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12"/></svg>`;
        } else if (log.type === 'warn') {
          accentColor = '#f59e0b'; labelText = 'UYARI';
          iconSvg = `<svg class="w-3 h-3" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M12 9v3m0 4h.01M10.29 3.86L1.82 18a2 2 0 001.71 3h16.94a2 2 0 001.71-3L13.71 3.86a2 2 0 00-3.42 0z"/></svg>`;
        } else if (log.type === 'success') {
          accentColor = '#10b981'; labelText = 'BAŞARILI';
          iconSvg = `<svg class="w-3 h-3" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7"/></svg>`;
        } else {
          accentColor = '#38bdf8'; labelText = 'BİLGİ';
          iconSvg = `<svg class="w-3 h-3" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M13 16h-1v-4h-1m1-4h.01M12 21a9 9 0 100-18 9 9 0 000 18z"/></svg>`;
        }

        const logHtml = `
        <div class="flex items-stretch group cursor-default">
          <div class="w-[2.5px] rounded-full shrink-0 my-[3px] ml-1" style="background:${accentColor};"></div>
          <div class="flex-1 flex items-center gap-2.5 px-3 py-2.5 min-w-0 group-hover:bg-white/[0.02] rounded-r-lg transition-colors duration-100">
            <div class="shrink-0 w-[18px] h-[18px] rounded-full flex items-center justify-center" style="background:${accentColor}18; color:${accentColor};">
              ${iconSvg}
            </div>
            <span class="text-[9.5px] font-bold tracking-widest shrink-0 w-12" style="color:${accentColor};">${labelText}</span>
            <span class="flex-1 text-slate-300 text-[12px] leading-snug min-w-0 truncate">${log.msg}</span>
            <span class="shrink-0 text-[9px] text-slate-600 font-mono tabular-nums">${log.time}</span>
          </div>
        </div>`;
        logOut.insertAdjacentHTML('beforeend', logHtml);
      });
      if(logCountEl) logCountEl.innerText = `${filteredLogs.length} / ${sysLogsArray.length} kayıt`;
    }

    
    setTimeout(renderLogs, 100);

    function addLog(msg, type = 'info') {
      const time = new Date().toLocaleTimeString('tr-TR', { hour12: false });
      sysLogsArray.unshift({ time, msg, type });
      if (sysLogsArray.length > 50) sysLogsArray.pop();
      localStorage.setItem('karavanSysLogs', JSON.stringify(sysLogsArray));
      renderLogs();
    }
    
    function clearLogs() {
      sysLogsArray = [];
      localStorage.removeItem('karavanSysLogs');
      renderLogs();
    }
    
    function clearSdLog() {
      if (confirm('SD Kart üzerindeki tüm geçmiş sensör logları silinecek. Emin misiniz?')) {
        sendWs({ cmd: "clear_log" });
        addLog('SD Kart logları başarıyla temizlendi.', 'success');
        alert('Loglar temizlendi ve yeni başlık atıldı!');
      }
    }
    
    function openLogModal() {
      const modal = document.getElementById('sysLogModal');
      const content = document.getElementById('logModalContent');
      modal.classList.remove('hidden');
      setTimeout(() => {
        content.classList.remove('translate-y-full');
      }, 10);
    }
    function closeLogModal() {
      const modal = document.getElementById('sysLogModal');
      const content = document.getElementById('logModalContent');
      content.classList.add('translate-y-full');
      setTimeout(() => {
        modal.classList.add('hidden');
      }, 150);
    }
    
    // Add initial log

    function openSysStatusModal() {
      let modal = document.getElementById('sysStatusModal');
      modal.classList.remove('hidden');
      setTimeout(() => {
        let c = document.getElementById('sysStatusContent');
        c.classList.remove('scale-95','opacity-0');
        c.classList.add('scale-100','opacity-100');
      }, 10);
    }
    function closeSysStatusModal() {
      let c = document.getElementById('sysStatusContent');
      c.classList.remove('scale-100','opacity-100');
      c.classList.add('scale-95','opacity-0');
      setTimeout(() => document.getElementById('sysStatusModal').classList.add('hidden'), 150);
    }

    function openSdCardModal() {
      let modal = document.getElementById('sdCardModal');
      modal.classList.remove('hidden');
      setTimeout(() => {
        let c = document.getElementById('sdCardContent');
        c.classList.remove('scale-95','opacity-0');
        c.classList.add('scale-100','opacity-100');
      }, 10);
    }

    function closeSdCardModal() {
      let c = document.getElementById('sdCardContent');
      c.classList.remove('scale-100','opacity-100');
      c.classList.add('scale-95','opacity-0');
      setTimeout(() => document.getElementById('sdCardModal').classList.add('hidden'), 150);
    }

    function toggleWifiPass() {
      let inp = document.getElementById('ext-wifi-pass-inp');
      let eye = document.getElementById('wifi-pass-eye');
      if (!inp || !eye) return;
      if (inp.type === "password") {
        inp.type = "text";
        eye.innerHTML = '<path d="M9.88 9.88a3 3 0 1 0 4.24 4.24"></path><path d="M10.73 5.08A10.43 10.43 0 0 1 12 5c7 0 10 7 10 7a13.16 13.16 0 0 1-1.67 2.68"></path><path d="M6.61 6.61A13.526 13.526 0 0 0 2 12s3 7 10 7a9.74 9.74 0 0 0 5.39-1.61"></path><line x1="2" y1="2" x2="22" y2="22"></line>';
      } else {
        inp.type = "password";
        eye.innerHTML = '<path d="M2 12s3-7 10-7 10 7 10 7-3 7-10 7-10-7-10-7Z"></path><circle cx="12" cy="12" r="3"></circle>';
      }
    }

    function openWifiScannerModal() {
      let modal = document.getElementById('wifiScannerModal');
      let content = document.getElementById('wifiScannerContent');
      if(modal && content) {
        modal.classList.remove('hidden');
        setTimeout(() => {
          modal.classList.remove('opacity-0');
          content.classList.remove('scale-95');
        }, 10);
        scanWifi();
      }
    }

    function closeWifiScannerModal() {
      let modal = document.getElementById('wifiScannerModal');
      let content = document.getElementById('wifiScannerContent');
      if(modal && content) {
        content.classList.add('scale-95');
        modal.classList.add('opacity-0');
        setTimeout(() => { modal.classList.add('hidden'); }, 300);
      }
    }

    function openWifiSettingsModal() {
      let modal = document.getElementById('wifiSettingsModal');
      let content = document.getElementById('wifiSettingsContent');
      if(modal && content) {
        modal.classList.remove('hidden');
        setTimeout(() => {
          content.classList.remove('scale-95', 'opacity-0');
          content.classList.add('scale-100', 'opacity-100');
        }, 10);
      }
    }
    
    function openOtaModal() {
      let modal = document.getElementById('otaModal');
      let content = document.getElementById('otaContent');
      if(modal && content) {
        modal.classList.remove('hidden');
        setTimeout(() => {
          content.classList.remove('scale-95', 'opacity-0');
          content.classList.add('scale-100', 'opacity-100');
        }, 10);
      }
    }
    
    function closeOtaModal() {
      let modal = document.getElementById('otaModal');
      let content = document.getElementById('otaContent');
      if(modal && content) {
        content.classList.remove('scale-100', 'opacity-100');
        content.classList.add('scale-95', 'opacity-0');
        setTimeout(() => { modal.classList.add('hidden'); }, 300);
      }
    }

    function closeWifiSettingsModal() {
      let modal = document.getElementById('wifiSettingsModal');
      let content = document.getElementById('wifiSettingsContent');
      if(modal && content) {
        content.classList.remove('scale-100', 'opacity-100');
        content.classList.add('scale-95', 'opacity-0');
        setTimeout(() => modal.classList.add('hidden'), 150);
      }
    }

    let selectedExtWifi = "";
    function scanWifi() {
      document.getElementById('scan-wifi-text').innerText = "Ağlar Aranıyor...";
      let scanIcon = document.getElementById('scan-wifi-icon');
      let spinnerIcon = document.getElementById('scan-spinner-icon');
      if(scanIcon) scanIcon.classList.add('hidden');
      if(spinnerIcon) spinnerIcon.classList.remove('hidden');
      
      document.getElementById('wifi-list').classList.add('hidden');
      document.getElementById('wifi-password-container').classList.add('hidden');
      sendWs({ cmd: "scan_wifi" });
      
      // ESP32 ağ taraması yaparken anteni meşgul ettiği için anlık veri kayıpları olabilir.
      // Eğer yayın bize ulaşmazsa, 3 saniyede bir ESP32'den sonuçları iste.
      if(window.scanInterval) clearInterval(window.scanInterval);
      window.scanInterval = setInterval(() => {
          let btnTxt = document.getElementById('scan-wifi-text');
          if (btnTxt && btnTxt.innerText.includes("Aranıyor")) {
              sendWs({ cmd: "get_scan" });
          } else {
              clearInterval(window.scanInterval);
          }
      }, 3000);
    }
    
    function selectWifi(ssid) {
      selectedExtWifi = ssid;
      document.getElementById('selected-wifi-lbl').innerText = "Ağ: " + ssid;
      document.getElementById('wifi-password-container').classList.remove('hidden');
      document.getElementById('ext-wifi-pass-inp').value = "";
      document.getElementById('ext-wifi-pass-inp').focus();
    }
    
    function connectExtWifi() {
      let pass = document.getElementById('ext-wifi-pass-inp').value.trim();
      let btn = document.getElementById('btn-connect-ext');
      btn.innerText = "Bağlanıyor...";
      sendWs({ cmd: "connect_ext", ssid: selectedExtWifi, pass: pass });
      setTimeout(() => {
         btn.innerText = "Ağa Bağlan";
         document.getElementById('wifi-password-container').classList.add('hidden');
         document.getElementById('wifi-list').classList.add('hidden');
         document.getElementById('scan-wifi-text').innerText = "Ağ Değiştir (Çevreyi Tara)";
         let scanIcon = document.getElementById('scan-wifi-icon');
         let spinnerIcon = document.getElementById('scan-spinner-icon');
         if(scanIcon) scanIcon.classList.remove('hidden');
         if(spinnerIcon) spinnerIcon.classList.add('hidden');
         alert("Bağlantı isteği arka planda başlatıldı. Kontrol paneli kapanmayacak, 10-15 saniye içinde WiFi durumunuz güncellenecektir.");
      }, 1500);
    }

    function disconnectExtWifi() {
      if(confirm("Dış internet bağlantısını kesmek istediğinize emin misiniz?")) {
        document.getElementById('ext-wifi-name').innerText = "Kesiliyor...";
        document.getElementById('ext-wifi-ip').innerText = "Lütfen bekleyin...";
        sendWs({ cmd: "disconnect_ext" });
      }
    }

    let isUploadingOta = false;
    window.addEventListener('beforeunload', function (e) {
      if (isUploadingOta) {
        e.preventDefault();
        e.returnValue = 'Yazılım güncellemesi devam ediyor! Sayfadan ayrılırsanız işlem iptal olabilir.';
        return e.returnValue;
      }
    });

    function uploadFirmware() {
      let input = document.getElementById('ota-file-input');
      if (input.files.length === 0) {
        alert("Lütfen bir .bin dosyası seçin.");
        return;
      }
      let file = input.files[0];
      if (!file.name.endsWith(".bin")) {
        alert("Sadece .bin uzantılı dosyalar yüklenebilir.");
        return;
      }
      
      if(!confirm("Cihaz güncellenecek. Bu işlem sırasında cihazı KESİNLİKLE KAPATMAYIN. Devam edilsin mi?")) return;

      isUploadingOta = true;
      let btn = document.getElementById('ota-upload-btn');
      btn.disabled = true;
      btn.classList.add('opacity-50', 'cursor-not-allowed');
      
      let pContainer = document.getElementById('ota-progress-container');
      let pBar = document.getElementById('ota-progress-bar');
      let pPct = document.getElementById('ota-percent');
      let pTxt = document.getElementById('ota-status-text');
      
      pContainer.classList.remove('hidden');
      pContainer.classList.add('flex');
      
      let formData = new FormData();
      formData.append("update", file, file.name);
      
      let request = new XMLHttpRequest();
      request.open("POST", "/update");
      
      request.upload.addEventListener("progress", function(e) {
        let pct = (e.loaded / e.total) * 100;
        pBar.style.width = pct + "%";
        pPct.innerText = Math.round(pct) + "%";
      });
      
      request.addEventListener("load", function(e) {
        isUploadingOta = false;
        if (request.status === 200 && request.responseText === "OK") {
          pTxt.innerText = "Başarılı! Yeniden başlatılıyor...";
          pTxt.classList.replace('text-slate-300', 'text-green-400');
          pBar.classList.replace('bg-violet-500', 'bg-green-500');
          setTimeout(() => { window.location.reload(); }, 3000);
        } else {
          pTxt.innerText = "Hata: " + request.responseText;
          pTxt.classList.replace('text-slate-300', 'text-rose-400');
          pBar.classList.replace('bg-violet-500', 'bg-rose-500');
          btn.disabled = false;
          btn.classList.remove('opacity-50', 'cursor-not-allowed');
        }
      });
      
      request.addEventListener("error", function(e) {
        isUploadingOta = false;
        pTxt.innerText = "Ağ Hatası!";
        pTxt.classList.replace('text-slate-300', 'text-rose-400');
        btn.disabled = false;
        btn.classList.remove('opacity-50', 'cursor-not-allowed');
      });
      
      request.send(formData);
    }

    function saveWifiSettings() {
      let ap_s = document.getElementById('wifi-ap-ssid-inp').value.trim();
      let ap_p = document.getElementById('wifi-ap-pass-inp').value.trim();
      let mdns = document.getElementById('wifi-mdns-inp').value.trim();
      
      if(ap_s.length < 1) { alert("Lütfen geçerli bir Karavan Ağ Adı girin."); return; }
      if(ap_p.length > 0 && ap_p.length < 8) { alert("Karavan Şifresi en az 8 karakter olmalıdır."); return; }
      if(mdns.length < 1) { mdns = "karavan"; } // default fallback
      
      if(confirm('Yeni ağ ayarları kaydedilip cihaz yeniden başlatılacak. Onaylıyor musunuz?')) {
        sendWs({ cmd: "set_wifi", ssid: ap_s, pass: ap_p, mdns: mdns });
        
        let current_mdns = window.location.hostname.replace('.local', '');
        if (mdns !== current_mdns && window.location.hostname.includes('.local')) {
            alert("Cihaz yeniden başlatılıyor... Yeni adresinize (http://" + mdns + ".local) yönlendirileceksiniz. Lütfen Karavan ağına bağlı kaldığınızdan emin olun.");
            setTimeout(() => { window.location.href = "http://" + mdns + ".local"; }, 6000);
        } else {
            alert("Cihaz yeniden başlatılıyor... Lütfen ağınıza tekrar bağlanın. Sayfa 6 saniye içinde yenilenecek.");
            setTimeout(() => { window.location.reload(); }, 6000);
        }
        closeWifiSettingsModal();
      }
    }

    // ─── Sidebar Controls ───
    function openSidebar() {
      let d = document.getElementById('sidebarDrawer');
      let c = document.getElementById('sidebarContent');
      d.classList.remove('hidden');
      setTimeout(() => {
        d.classList.remove('opacity-0');
        d.classList.add('opacity-100');
        c.classList.remove('translate-x-full');
        c.classList.add('translate-x-0');
      }, 50);
    }
    function closeSidebar() {
      let d = document.getElementById('sidebarDrawer');
      let c = document.getElementById('sidebarContent');
      d.classList.remove('opacity-100');
      d.classList.add('opacity-0');
      c.classList.remove('translate-x-0');
      c.classList.add('translate-x-full');
      setTimeout(() => d.classList.add('hidden'), 150);
    }

    // ─── sendCal (Senkronize) ───
    function updateGasEnText(isOn) {
      let span = document.getElementById('g-en-text');
      let threshSec = document.getElementById('gas-thresh-section');
      if(span) {
        span.innerText = isOn ? 'AÇIK' : 'KAPALI';
        span.className = isOn ? 'text-[10px] font-bold tracking-wider text-green-400' : 'text-[10px] font-bold tracking-wider text-slate-500';
      }
      if(threshSec) {
        if(isOn) {
          threshSec.classList.remove('hidden');
        } else {
          threshSec.classList.add('hidden');
        }
      }
    }

    // Sıcaklık Ofseti — Otomatik Kayıt (Debounce)
    let _tempDebounce = null;
    function onTempSlider(val) {
      let tval = parseFloat(val);
      let disp = document.getElementById('t-offset-display');
      if (disp) disp.innerText = (tval >= 0 ? '+' : '') + tval.toFixed(1);
      
      let dot = document.getElementById('t-save-dot');
      let status = document.getElementById('t-save-status');
      if(dot) dot.style.background = '#facc15';
      if(status) { status.innerText = 'Kaydediliyor...'; status.style.color = '#facc15'; }
      
      clearTimeout(_tempDebounce);
      _tempDebounce = setTimeout(() => {
        sendWs({ cmd: 'cal', type: 't', val: tval });
        if(dot) dot.style.background = '#22c55e';
        if(status) { status.innerText = 'Kaydedildi \u2713'; status.style.color = '#22c55e'; }
        setTimeout(() => {
          if(dot) dot.style.background = '#475569';
          if(status) { status.innerText = 'De\u011fi\u015ftirince otomatik kaydedilir'; status.style.color = ''; }
        }, 1800);
      }, 600);
    }

    // Gaz Eşiği — Otomatik Kayıt (Debounce)
    let _gasDebounce = null;
    function onGasSlider(val) {
      document.getElementById('g-thresh-val').innerText = val;
      let dot = document.getElementById('g-save-dot');
      let status = document.getElementById('g-save-status');
      if(dot) { dot.style.background = '#facc15'; }
      if(status) { status.innerText = 'Kaydediliyor...'; status.style.color = '#facc15'; }
      clearTimeout(_gasDebounce);
      _gasDebounce = setTimeout(() => {
        sendWs({ cmd: 'cal', type: 'g', val: parseInt(val) });
        if(dot) { dot.style.background = '#22c55e'; }
        if(status) { status.innerText = 'Kaydedildi \u2713'; status.style.color = '#22c55e'; }
        setTimeout(() => {
          if(dot) { dot.style.background = '#475569'; }
          if(status) { status.innerText = 'De\u011fi\u015ftirince otomatik kaydedilir'; status.style.color = ''; }
        }, 1800);
      }, 600);
    }

    function sendCal(type, event) {
      var payload = { cmd: 'cal', type: type };
      if (type === 'g') {
        let val = parseInt(document.getElementById('cal-g').value);
        payload.val = val;
      } else if (type === 'gen') {
        let on = document.getElementById('cal-g-en').checked;
        payload.val = on ? 1 : 0;
      } else if (type === 't') {
        let val = parseFloat(document.getElementById('cal-t').value || 0);
        payload.val = val;
      }
      sendWs(payload);
      let btn = event.target;
      if (!btn.classList.contains('switch') && btn.tagName === 'BUTTON') {
        let old = btn.innerText;
        btn.innerText = 'KAYDEDILDI';
        btn.style.background = '#22d3ee'; // cyan-400
        btn.style.color = '#000';
        setTimeout(() => { btn.innerText = old; btn.style.background = ''; btn.style.color = ''; }, 1500);
      }
    }

    //  Chart Modal 
    let historyChartInstance = null;
    // SD Kart Yöneticisi Fonksiyonları
    function openSdCardModal() {
      let m = document.getElementById('sdModal');
      let c = document.getElementById('sdModalContent');
      if(m) m.classList.remove('hidden');
      setTimeout(() => {
        if(m) m.classList.remove('opacity-0', 'pointer-events-none');
        if(c) c.classList.remove('scale-95');
        if(c) c.classList.add('scale-100');
      }, 10);
      loadSdFiles();
    }

    function closeSdModal() {
      let m = document.getElementById('sdModal');
      let c = document.getElementById('sdModalContent');
      if(m) m.classList.add('opacity-0', 'pointer-events-none');
      if(c) c.classList.remove('scale-100');
      if(c) c.classList.add('scale-95');
      setTimeout(() => { if(m) m.classList.add('hidden'); }, 150);
    }

    function loadSdFiles() {
      let list = document.getElementById('sdFileList');
      if(!list) return;
      list.innerHTML = '<div class="text-center text-slate-500 text-sm py-4">Dosyalar Yükleniyor...</div>';
      
      if (window.location.protocol === 'file:' || window.location.hostname === '' || window.location.hostname === 'localhost') {
         setTimeout(() => {
             renderSdFiles({
                 total: 16000000000, 
                 used: 2500000000, 
                 files: [{name: "log.csv", size: 10245}, {name: "config.json", size: 512}]
             });
         }, 500);
         return;
      }

      fetch('/api/sd/list?t=' + Date.now())
        .then(r => r.json())
        .then(data => renderSdFiles(data))
        .catch(e => { list.innerHTML = `<div class="text-center text-rose-500 text-sm py-4">Hata: ${e.message}</div>`; });
    }

    function renderSdFiles(data) {
      let list = document.getElementById('sdFileList');
      let files = data.files || data; 
      
      // Update Storage Bar
      if(data.totalMB) {
          let tMb = data.totalMB;
          let uMb = data.usedMB;
          let pct = Math.min(100, Math.round((uMb / tMb) * 100));
          document.getElementById('sdStorageText').innerText = `${uMb} MB / ${tMb} MB`;
          document.getElementById('sdStorageBar').style.width = pct + '%';
      }
      
      let root = { dirs: {}, files: [], f: null };
      
      files.forEach(f => {
        let n = f.name.startsWith('/') ? f.name.substring(1) : f.name;
        let parts = n.split('/');
        let isDir = (f.isDir === true || f.isDir === 'true');
        let current = root;
        
        for(let i = 0; i < parts.length - 1; i++) {
           if(!current.dirs[parts[i]]) {
               current.dirs[parts[i]] = { dirs:{}, files:[], f: {name: parts.slice(0, i+1).join('/'), isDir: true, size: 0} };
           }
           current = current.dirs[parts[i]];
        }
        
        let last = parts[parts.length - 1];
        if(isDir) {
           if(!current.dirs[last]) current.dirs[last] = { dirs:{}, files:[], f: f };
           else current.dirs[last].f = f;
        } else {
           f.displayName = last;
           current.files.push(f);
        }
      });
      
      function renderTree(node, level = 0) {
         let html = '';
         let pl = level * 1.5;
         let lineLeft = level > 0 ? (level * 1.5) - 0.75 : 0;
         
         for(let dname in node.dirs) {
             let dNode = node.dirs[dname];
             let f = dNode.f;
             let n = f.name.startsWith('/') ? f.name : '/' + f.name;
             let id = 'dir-' + Math.random().toString(36).substr(2, 9);
             
             html += `
             <div class="flex flex-col relative w-full">
               ${level > 0 ? `<div class="absolute top-0 bottom-0 border-l border-slate-700/50" style="left: ${lineLeft}rem"></div>` : ''}
               <div class="flex items-center justify-between py-1.5 px-2 hover:bg-slate-800/60 rounded-md cursor-pointer transition-colors" style="padding-left: ${pl + 0.5}rem" onclick="toggleDir('${id}')">
                 <div class="flex items-center gap-2 truncate pr-4">
                   <svg id="icon-${id}" class="w-3.5 h-3.5 text-slate-500 transition-transform -rotate-90 shrink-0" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 9l-7 7-7-7" /></svg>
                   <svg class="h-4 w-4 text-amber-400 shrink-0" fill="currentColor" viewBox="0 0 20 20"><path d="M2 6a2 2 0 012-2h4l2 2h6a2 2 0 012 2v8a2 2 0 01-2 2H4a2 2 0 01-2-2V6z"/></svg>
                   <span class="text-sm font-medium text-slate-200 truncate select-none">${dname}</span>
                 </div>
                 <div class="flex items-center gap-2 shrink-0 opacity-0 hover:opacity-100 transition-opacity">
                   <button onclick="event.stopPropagation(); deleteSdFile('${n}')" class="text-rose-400 hover:text-rose-300 p-1" title="Sil"><svg class="h-4 w-4" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16" /></svg></button>
                 </div>
               </div>
               <div id="${id}" class="hidden flex-col w-full">
                 ${renderTree(dNode, level + 1)}
               </div>
             </div>
             `;
         }
         
         node.files.forEach(f => {
             let sizeKb = (f.size / 1024).toFixed(1) + ' KB';
             let n = f.name.startsWith('/') ? f.name : '/' + f.name;
             
             html += `
             <div class="flex flex-col relative w-full group">
               ${level > 0 ? `<div class="absolute top-0 bottom-0 border-l border-slate-700/50" style="left: ${lineLeft}rem"></div>` : ''}
               <div class="flex items-center justify-between py-1.5 px-2 hover:bg-slate-800/40 rounded-md transition-colors w-full" style="padding-left: ${pl + 1.25}rem">
                 <div class="flex items-center gap-2 truncate pr-4 w-full">
                   <label class="relative flex items-center cursor-pointer shrink-0">
                     <input type="checkbox" value="${n}" class="sd-file-chk peer sr-only" onclick="checkSdSelection()">
                     <div class="w-4 h-4 rounded border border-slate-600 bg-slate-800/80 peer-checked:bg-blue-600 peer-checked:border-blue-500 flex items-center justify-center transition-colors">
                       <svg class="w-3 h-3 text-white opacity-0 peer-checked:opacity-100" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="3"><path stroke-linecap="round" stroke-linejoin="round" d="M5 13l4 4L19 7" /></svg>
                     </div>
                   </label>
                   <svg class="h-4 w-4 text-slate-400 shrink-0" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M7 21h10a2 2 0 002-2V9.414a1 1 0 00-.293-.707l-5.414-5.414A1 1 0 0012.586 3H7a2 2 0 00-2 2v14a2 2 0 002 2z" /></svg>
                   <span class="text-sm text-slate-300 truncate select-none">${f.displayName}</span>
                 </div>
                 <div class="flex items-center gap-3 shrink-0 opacity-0 group-hover:opacity-100 transition-opacity">
                   <span class="text-[10px] text-slate-500">${sizeKb}</span>
                   <a href="/api/sd/download?f=${encodeURIComponent(n)}" class="text-blue-400 hover:text-blue-300 p-0.5" title="İndir"><svg class="h-4 w-4" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M4 16v1a3 3 0 003 3h10a3 3 0 003-3v-1m-4-4l-4 4m0 0l-4-4m4 4V4" /></svg></a>
                   <button onclick="deleteSdFile('${n}')" class="text-rose-400 hover:text-rose-300 p-0.5" title="Sil"><svg class="h-4 w-4" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16" /></svg></button>
                 </div>
               </div>
             </div>
             `;
         });
         return html;
      }
      
      list.innerHTML = renderTree(root);
    }
    
    window.toggleDir = function(id) {
       let el = document.getElementById(id);
       let icon = document.getElementById('icon-' + id);
       if(el.classList.contains('hidden')) {
          el.classList.remove('hidden');
          el.classList.add('flex');
          if(icon) icon.classList.add('rotate-180');
       } else {
          el.classList.add('hidden');
          el.classList.remove('flex');
          if(icon) icon.classList.remove('rotate-180');
       }
    };
    checkSdSelection();

    function toggleSdSelectAll() {
      let mainChk = document.getElementById('sdSelectAll');
      let checks = document.querySelectorAll('.sd-file-chk');
      checks.forEach(c => c.checked = mainChk.checked);
      checkSdSelection();
    }
    
    function checkSdSelection() {
      let checks = document.querySelectorAll('.sd-file-chk:checked');
      let btn = document.getElementById('sdBulkDeleteBtn');
      if(btn) {
        if(checks.length > 0) btn.classList.remove('hidden');
        else btn.classList.add('hidden');
      }
    }

    async function deleteSelectedSdFiles() {
      let checks = document.querySelectorAll('.sd-file-chk:checked');
      if(checks.length === 0) return;
      if(!confirm(checks.length + ' adet dosyayı silmek istediğinize emin misiniz?')) return;
      
      let btn = document.getElementById('sdBulkDeleteBtn');
      btn.innerText = 'Siliniyor...';
      btn.disabled = true;
      
      for(let i=0; i<checks.length; i++) {
        let fd = new FormData();
        fd.append('f', checks[i].value);
        try {
          await fetch('/api/sd/delete', { method: 'POST', body: fd });
        } catch(e) {}
      }
      
      addLog(checks.length + ' dosya silindi.', 'success');
      btn.innerText = 'Seçilenleri Sil';
      btn.disabled = false;
      document.getElementById('sdSelectAll').checked = false;
      loadSdFiles();
    }

    function deleteSdFile(filename) {
      if (!confirm(filename + ' dosyasını silmek istediğinize emin misiniz?')) return;
      let fd = new FormData();
      fd.append('f', filename);
      fetch('/api/sd/delete', { method: 'POST', body: fd })
        .then(r => { 
           if(r.ok) { 
             addLog(filename + ' silindi.', 'success'); 
             loadSdFiles(); 
           } else {
             throw new Error('Silinemedi'); 
           }
        })
        .catch(e => alert('Hata: ' + e.message));
    }

    function uploadSdFile(input) {
      if(!input.files || input.files.length === 0) return;
      let file = input.files[0];
      if(!confirm(file.name + ' dosyasını SD Karta yüklemek istiyor musunuz?')) {
          input.value = '';
          return;
      }
      
      let btn = document.getElementById('sdUploadBtn');
      let ogText = btn.innerHTML;
      btn.innerHTML = '<span class="animate-pulse">%0 Yükleniyor...</span>';
      btn.disabled = true;

      let fd = new FormData();
      fd.append('file', file, file.name);
      
      let xhr = new XMLHttpRequest();
      xhr.open('POST', '/api/sd/upload', true);
      
      xhr.upload.onprogress = function(e) {
        if (e.lengthComputable) {
          let percent = Math.round((e.loaded / e.total) * 100);
          btn.innerHTML = `<span class="animate-pulse">%${percent} Yükleniyor...</span>`;
        }
      };
      
      xhr.onload = function() {
        if (xhr.status === 200) {
           addLog(file.name + ' başarıyla yüklendi.', 'success');
           loadSdFiles();
        } else {
           alert('Hata: Yükleme başarısız (' + xhr.status + ')');
        }
        btn.innerHTML = ogText;
        btn.disabled = false;
        input.value = '';
      };
      
      xhr.onerror = function() {
        alert('Hata: Ağ hatası oluştu.');
        btn.innerHTML = ogText;
        btn.disabled = false;
        input.value = '';
      };
      
      xhr.send(fd);
    }

    let parsedLogData = [];
    let currentChartTab = 'env';

    function fetchChartData() {
      fetch('/indir?t=' + new Date().getTime())
        .then(r => { if (!r.ok) throw new Error('Log dosyası bulunamadı.'); return r.text(); })
        .then(csv => parseAndRenderChart(csv))
        .catch(e => { 
            let msg = e.message;
            if(msg.includes('Failed to fetch')) msg = 'Bağlantı koptu (WiFi bağlantınızı kontrol edin).';
            document.getElementById('chartLoading').innerHTML = `<span class="text-rose-400 text-sm font-semibold text-center px-4">Hata: ${msg}</span>`; 
        });
    }

    function openChartModal() {
      document.getElementById('chartModal').classList.remove('hidden');
      document.getElementById('chartLoading').classList.remove('opacity-0', 'pointer-events-none');
      let emptyUI = document.getElementById('chartEmpty');
      if (emptyUI) emptyUI.classList.add('opacity-0', 'pointer-events-none');
      let chartUI = document.getElementById('chartContainer');
      if (chartUI) chartUI.classList.add('opacity-0', 'pointer-events-none');

      if (window.location.protocol === 'file:' || window.location.hostname === '' || window.location.hostname === 'localhost') {
        setTimeout(() => {
          let mockCsv = 'Tarih-Saat,Sicaklik(C),Nem(%),Basinc(hPa),Gaz(ppm),Egim-X,Egim-Y,Inverter,Pompa,Alarm\n';
          let nowSec = Math.floor(Date.now() / 1000);
          for (let i = 1100; i >= 0; i--) {
            let rt = nowSec - i * 600;
            let dt = new Date(rt * 1000);
            let dStr = dt.getFullYear() + '-' + String(dt.getMonth()+1).padStart(2,'0') + '-' + String(dt.getDate()).padStart(2,'0') + ' ' + String(dt.getHours()).padStart(2,'0') + ':' + String(dt.getMinutes()).padStart(2,'0') + ':' + String(dt.getSeconds()).padStart(2,'0');
            let mt = (23.0 + Math.sin(i / 20) * 3.5 + (Math.random() - 0.5) * 0.2).toFixed(1);
            let mh = (52.0 + Math.cos(i / 25) * 10.0 + (Math.random() - 0.5) * 0.5).toFixed(1);
            let mg = Math.floor(400 + Math.abs(Math.sin(i / 30)) * 600 + Math.random() * 50);
            let mp = (1011.5 + Math.cos(i / 40) * 12.0 + (Math.random() - 0.5) * 0.5).toFixed(1);
            mockCsv += `${dStr},${mt},${mh},${mp},${mg},0.0,0.0,0,0,0\n`;
          }
          parseAndRenderChart(mockCsv);
        }, 500);
        return;
      }

      fetchChartData();
      if(window.historyChartInterval) clearInterval(window.historyChartInterval);
      window.historyChartInterval = setInterval(fetchChartData, 60000); // Otomatik 1 dakikada bir guncelle
    }

    function closeChartModal() { 
      document.getElementById('chartModal').classList.add('hidden'); 
      if(window.historyChartInterval) clearInterval(window.historyChartInterval);
    }

    let chartRangePoints = 96; // Default to 24 Hours (96 points of 15 min logs)

    function changeChartRange(points) {
      chartRangePoints = points;
      ['range-24h', 'range-7d', 'range-30d'].forEach(id => {
        let b = document.getElementById(id);
        if (b) {
          b.classList.remove('bg-cyan-500/20', 'text-cyan-400');
          b.classList.add('text-slate-400', 'hover:text-white');
        }
      });
      let activeId = points === 96 ? 'range-24h' : points === 672 ? 'range-7d' : 'range-30d';
      let actBtn = document.getElementById(activeId);
      if (actBtn) {
        actBtn.classList.remove('text-slate-400', 'hover:text-white');
        actBtn.classList.add('bg-cyan-500/20', 'text-cyan-400');
      }
      fetchChartData();
    }

    function switchChartTab(tab) {
      if (currentChartTab === tab) return;
      currentChartTab = tab;
      ['tab-env', 'tab-gas', 'tab-press'].forEach(id => {
        let b = document.getElementById(id);
        if (b) {
          b.classList.remove('bg-cyan-500/20', 'text-cyan-400');
          b.classList.add('text-slate-400', 'hover:text-white');
        }
      });
      let activeBtn = document.getElementById('tab-' + tab);
      if (activeBtn) {
        activeBtn.classList.remove('text-slate-400', 'hover:text-white');
        activeBtn.classList.add('bg-cyan-500/20', 'text-cyan-400');
      }
      fetchChartData();
    }

    function parseAndRenderChart(csvText) {
      if (!csvText) return;
      let lines = csvText.trim().split(/\r?\n/);
      if (lines.length < 2) return;
      let headers = lines[0].split(',').map(h => h.trim());
      let parsedData = [];
      for (let i = 1; i < lines.length; i++) {
        let line = lines[i].trim();
        if (!line) continue;
        let values = line.split(',');
        let rowObj = {};
        for (let j = 0; j < headers.length; j++) {
          rowObj[headers[j]] = values[j] ? values[j].trim() : '';
        }
        parsedData.push(rowObj);
      }
      parsedLogData = parsedData;
      renderSelectedChart();
    }

    function renderSelectedChart() {
      let emptyUI = document.getElementById('chartEmpty');
      let chartUI = document.getElementById('chartContainer');
      let loadUI = document.getElementById('chartLoading');
      
      if(loadUI) loadUI.classList.add('opacity-0', 'pointer-events-none');

      if (!parsedLogData || parsedLogData.length === 0) {
        if(emptyUI) emptyUI.classList.remove('opacity-0', 'pointer-events-none');
        if(chartUI) chartUI.classList.add('opacity-0', 'pointer-events-none');
        return;
      }
      
      // Filter points based on selected range
      let data = parsedLogData.length > chartRangePoints ? parsedLogData.slice(-chartRangePoints) : parsedLogData;
      
      if (data.length === 0) {
        if(emptyUI) emptyUI.classList.remove('opacity-0', 'pointer-events-none');
        if(chartUI) chartUI.classList.add('opacity-0', 'pointer-events-none');
        return;
      }
      
      // Grafik kütüphanesi pointRadius:0 ayarında tek noktayı çizgiye dönüştüremediği için gizli kalır. 
      // 1 nokta varsa, düz çizgi görünmesi için başa sahte bir önceki nokta kopyalıyoruz.
      if (data.length === 1) {
        let clonedData = JSON.parse(JSON.stringify(data[0]));
        clonedData['Tarih-Saat'] = 'Ölçüm Başlangıcı'; // Sahte etiket
        data.unshift(clonedData);
      }
      
      if(emptyUI) emptyUI.classList.add('opacity-0', 'pointer-events-none');
      if(chartUI) chartUI.classList.remove('opacity-0', 'pointer-events-none');
      
      // Update sub labels
      let subLbl = document.getElementById('chart-sub-label');
      let ptsLbl = document.getElementById('chart-points-label');
      if(subLbl) {
        subLbl.innerText = currentChartTab === 'env' ? 'Sıcaklık & Nem Analizi' 
          : currentChartTab === 'volt' ? 'Voltaj Analizi' 
          : currentChartTab === 'gas' ? 'Gaz Analizi' 
          : 'Hava Basıncı Analizi';
      }
      

      let labels = [], y1Data = [], y2Data = [];
      let minV1 = Infinity, maxV1 = -Infinity, sumV1 = 0;
      let minV2 = Infinity, maxV2 = -Infinity, sumV2 = 0;

      data.forEach(row => {
        let lblRaw = row['Tarih-Saat'] || row['Uptime(s)'];
        if (lblRaw) lblRaw = lblRaw.trim();
        let lbl = lblRaw || '--';
        
        let tMatch = lblRaw ? lblRaw.match(/^(\d{4})-(\d{2})-(\d{2}) (\d{2}):(\d{2}):(\d{2})/) : null;
        if (tMatch) {
           // Zaman dilimi kaymasını önlemek için string'i doğrudan kesiyoruz (Örn: 2026-06-29 13:07:55 -> 29.06 13:07)
           lbl = `${tMatch[3]}.${tMatch[2]} ${tMatch[4]}:${tMatch[5]}`;
        } else if (lblRaw && lblRaw.includes('-') && lblRaw.includes(':')) {
           let dt = new Date(lblRaw.replace(' ', 'T'));
           if (!isNaN(dt.getTime())) {
             lbl = dt.toLocaleDateString('tr-TR', { month: 'short', day: 'numeric' }) + ' ' + dt.toLocaleTimeString('tr-TR', { hour: '2-digit', minute: '2-digit' });
           }
        } else if (lblRaw && lblRaw.includes('_sn')) {
           let s = parseInt(lblRaw);
           if (!isNaN(s) && s < 864000) {
             let d = Math.floor(s / 86400), h = Math.floor((s % 86400) / 3600), m = Math.floor((s % 3600) / 60);
             lbl = d > 0 ? `${d}g ${h}s` : `${h}:${m.toString().padStart(2, '0')}`;
           }
        }
        labels.push(lbl);

        if (currentChartTab === 'env') {
          let t = parseFloat(row['Sicaklik(C)']), h = parseFloat(row['Nem(%)']);
          y1Data.push(t); y2Data.push(h);
          if (!isNaN(t) && t < minV1) minV1 = t; if (!isNaN(t) && t > maxV1) maxV1 = t; if (!isNaN(t)) sumV1 += t;
          if (!isNaN(h) && h < minV2) minV2 = h; if (!isNaN(h) && h > maxV2) maxV2 = h; if (!isNaN(h)) sumV2 += h;
        } else if (currentChartTab === 'volt') {
          let v = parseFloat(row['Voltaj(V)']);
          y1Data.push(v);
          if (!isNaN(v) && v < minV1) minV1 = v; if (!isNaN(v) && v > maxV1) maxV1 = v; if (!isNaN(v)) sumV1 += v;
        } else if (currentChartTab === 'gas') {
          let g = parseFloat(row['Gaz(ppm)']);
          if (isNaN(g)) g = 400; // default for old logs
          y1Data.push(g);
          if (g < minV1) minV1 = g; if (g > maxV1) maxV1 = g; sumV1 += g;
        } else if (currentChartTab === 'press') {
          let p = parseFloat(row['Basinc(hPa)']);
          if (isNaN(p)) p = 1013.2; // default for old logs
          y1Data.push(p);
          if (p < minV1) minV1 = p; if (p > maxV1) maxV1 = p; sumV1 += p;
        }
      });

      if(ptsLbl) {
        if (y1Data.length > 0) ptsLbl.innerText = data.length + ' Nokta (Son: ' + y1Data[y1Data.length-1].toFixed(1) + ')';
        else ptsLbl.innerText = data.length + ' Nokta';
      }

      let avgV1 = sumV1 / data.length, avgV2 = sumV2 / data.length;

      let ml = document.getElementById('stat-label-min'), mxl = document.getElementById('stat-label-max'), avl = document.getElementById('stat-label-avg');
      let mv = document.getElementById('stat-val-min'), mxv = document.getElementById('stat-val-max'), avv = document.getElementById('stat-val-avg');

      if (currentChartTab === 'env') {
        ml.innerText = 'MIN SIC / NEM'; mxl.innerText = 'MAKS SIC / NEM'; avl.innerText = 'ORT SIC / NEM';
        mv.innerText = `${minV1 === Infinity ? 0 : minV1.toFixed(1)}°C / ${Math.round(minV2 === Infinity ? 0 : minV2)}%`;
        mxv.innerText = `${maxV1 === -Infinity ? 0 : maxV1.toFixed(1)}°C / ${Math.round(maxV2 === -Infinity ? 0 : maxV2)}%`;
        avv.innerText = `${avgV1.toFixed(1)}°C / ${Math.round(avgV2)}%`;
      } else if (currentChartTab === 'volt') {
        ml.innerText = 'MIN AKÜ'; mxl.innerText = 'MAKS AKÜ'; avl.innerText = 'ORT AKÜ';
        mv.innerText = `${minV1 === Infinity ? 0 : minV1.toFixed(2)} V`; mxv.innerText = `${maxV1 === -Infinity ? 0 : maxV1.toFixed(2)} V`; avv.innerText = `${avgV1.toFixed(2)} V`;
      } else if (currentChartTab === 'gas') {
        ml.innerText = 'MIN GAZ'; mxl.innerText = 'MAKS GAZ'; avl.innerText = 'ORT GAZ';
        mv.innerText = `${minV1 === Infinity ? 0 : Math.round(minV1)} ppm`; mxv.innerText = `${maxV1 === -Infinity ? 0 : Math.round(maxV1)} ppm`; avv.innerText = `${Math.round(avgV1)} ppm`;
      } else if (currentChartTab === 'press') {
        ml.innerText = 'MIN BASINÇ'; mxl.innerText = 'MAKS BASINÇ'; avl.innerText = 'ORT BASINÇ';
        mv.innerText = `${minV1 === Infinity ? 0 : minV1.toFixed(1)} hPa`; mxv.innerText = `${maxV1 === -Infinity ? 0 : maxV1.toFixed(1)} hPa`; avv.innerText = `${avgV1.toFixed(1)} hPa`;
      }

      if (historyChartInstance) historyChartInstance.destroy();
      let ctx = document.getElementById('historyChart').getContext('2d');
      Chart.defaults.color = '#64748b';

      let pRad = data.length > 150 ? 0 : 3;
      let datasets = [], scales = {
        x: { grid: { display: false, drawBorder: false }, ticks: { maxRotation: 0, autoSkip: true, maxTicksLimit: window.innerWidth < 768 ? 6 : 12, color: 'rgba(148, 163, 184, 0.7)' } }
      };

      // Create Custom Premium Gradient Fills
      let grad1 = null, grad2 = null;
      try {
        grad1 = ctx.createLinearGradient(0, 0, 0, 300);
        grad2 = ctx.createLinearGradient(0, 0, 0, 300);
      } catch(e) {}

      if (currentChartTab === 'env') {
        if (grad1) { grad1.addColorStop(0, 'rgba(251,113,133,0.4)'); grad1.addColorStop(1, 'rgba(251,113,133,0.0)'); }
        if (grad2) { grad2.addColorStop(0, 'rgba(96,165,250,0.4)'); grad2.addColorStop(1, 'rgba(96,165,250,0.0)'); }
        datasets = [
          { label: 'Sıcaklık (°C)', data: y1Data, borderColor: '#fb7185', backgroundColor: grad1 || 'rgba(251,113,133,0.08)', tension: 0.35, fill: true, yAxisID: 'y', borderWidth: 2, pointRadius: pRad, pointHoverRadius: 6 },
          { label: 'Nem (%)', data: y2Data, borderColor: '#60a5fa', backgroundColor: grad2 || 'rgba(96,165,250,0.05)', tension: 0.35, fill: true, yAxisID: 'y1', borderWidth: 2, pointRadius: pRad, pointHoverRadius: 6 }
        ];
        scales.y  = { type:'linear', position:'left', grace: '5%', border: { display: false }, grid:{ color:'rgba(51,65,85,0.1)', borderDash: [5, 5] }, ticks: { font: { size: 9 }, color: 'rgba(148, 163, 184, 0.5)' } };
        scales.y1 = { type:'linear', position:'right', grace: '5%', border: { display: false }, grid:{ drawOnChartArea:false }, min: 0, max: 100, ticks: { font: { size: 9 }, color: 'rgba(148, 163, 184, 0.5)' } };
      } else if (currentChartTab === 'volt') {
        if (grad1) { grad1.addColorStop(0, 'rgba(34,211,238,0.4)'); grad1.addColorStop(1, 'rgba(34,211,238,0.0)'); }
        datasets = [
          { label: 'Akü Voltajı (V)', data: y1Data, borderColor: '#22d3ee', backgroundColor: grad1 || 'rgba(34,211,238,0.08)', tension: 0.35, fill: true, yAxisID: 'y', borderWidth: 2, pointRadius: pRad, pointHoverRadius: 6 }
        ];
        let gMin = Math.floor(minV1 - 0.5), gMax = Math.ceil(maxV1 + 0.5);
        gMin = Math.max(10, gMin); gMax = Math.min(16, gMax);
        if(isNaN(gMin)) { gMin = 10; gMax = 15; }
        scales.y = { type:'linear', position:'left', grace: '5%', border: { display: false }, grid:{ color:'rgba(51,65,85,0.1)', borderDash: [5, 5] }, min:gMin, max:gMax, ticks: { font: { size: 9 }, color: 'rgba(148, 163, 184, 0.5)' } };
      } else if (currentChartTab === 'gas') {
        if (grad1) { grad1.addColorStop(0, 'rgba(52,211,153,0.4)'); grad1.addColorStop(1, 'rgba(52,211,153,0.0)'); }
        datasets = [
          { label: 'Gaz / Hava Kalitesi (ppm)', data: y1Data, borderColor: '#34d399', backgroundColor: grad1 || 'rgba(52,211,153,0.08)', tension: 0.35, fill: true, yAxisID: 'y', borderWidth: 2, pointRadius: pRad, pointHoverRadius: 6 }
        ];
        let gMax = Math.ceil((maxV1 === -Infinity ? 500 : maxV1) * 1.2);
        scales.y = { type:'linear', position:'left', grace: '5%', border: { display: false }, grid:{ color:'rgba(51,65,85,0.1)', borderDash: [5, 5] }, min:0, max:gMax, ticks: { font: { size: 9 }, color: 'rgba(148, 163, 184, 0.5)' } };
      } else if (currentChartTab === 'press') {
        if (grad1) { grad1.addColorStop(0, 'rgba(167,139,250,0.4)'); grad1.addColorStop(1, 'rgba(167,139,250,0.0)'); }
        datasets = [
          { label: 'Hava Basıncı (hPa)', data: y1Data, borderColor: '#a78bfa', backgroundColor: grad1 || 'rgba(167,139,250,0.08)', tension: 0.35, fill: true, yAxisID: 'y', borderWidth: 2, pointRadius: pRad, pointHoverRadius: 6 }
        ];
        let gMin = Math.floor(minV1 - 2), gMax = Math.ceil(maxV1 + 2);
        if (isNaN(gMin) || gMin < 500) { gMin = 950; gMax = 1050; }
        scales.y = { type:'linear', position:'left', grace: '5%', border: { display: false }, grid:{ color:'rgba(51,65,85,0.1)', borderDash: [5, 5] }, min:gMin, max:gMax, ticks: { font: { size: 9 }, color: 'rgba(148, 163, 184, 0.5)' } };
      }

      historyChartInstance = new Chart(ctx, {
        type: 'line', data: { labels, datasets },
        options: {
          responsive: true, maintainAspectRatio: false,
          interaction: { mode: 'index', intersect: false },
          plugins: { 
            legend: { position: 'top', labels: { boxWidth: 10, boxHeight: 10, font: { size: 10 }, padding: 16 } },
            tooltip: { backgroundColor: 'rgba(15,23,42,0.95)', titleColor: '#cbd5e1', bodyColor: '#fff', borderColor: 'rgba(51,65,85,0.6)', borderWidth: 1, padding: 10, cornerRadius: 8, displayColors: true }
          },
          scales
        }
      });
    }

    window.addEventListener('load', () => {
      initWebSocket();
      setTimeout(() => {
        const splash = document.getElementById('splashScreen');
        if(splash) {
          splash.classList.add('opacity-0', 'pointer-events-none');
          setTimeout(() => splash.remove(), 700);
        }
      }, 1200);
    });

    function closeAllModals() {
      try { closeEnvSettingsModal(); } catch(e){}
      try { closeTiltSettingsModal(); } catch(e){}
      try { closeSettingsModal(); } catch(e){}
      try { closeLogModal(); } catch(e){}
      try { closeSysStatusModal(); } catch(e){}
      try { closeSdCardModal(); } catch(e){}
      try { closeWifiScannerModal(); } catch(e){}
      try { closeOtaModal(); } catch(e){}
      try { closeWifiSettingsModal(); } catch(e){}
      try { closeSdModal(); } catch(e){}
      try { closeChartModal(); } catch(e){}
      try { if(typeof hideInvModal === 'function') hideInvModal(); } catch(e){}
      try { closeSidebar(); } catch(e){}
    }

    window.showAlert = function(id, title, message, type) {
      const container = document.getElementById('alert-container');
      if(!container) return;
      
      if(document.getElementById(id)) return;
      
      const alertEl = document.createElement('div');
      alertEl.id = id;
      alertEl.className = `w-full rounded-[24px] p-4 flex flex-col md:flex-row md:items-center justify-between backdrop-blur-xl relative overflow-hidden transition-all duration-500 gap-4 mb-4 shadow-2xl`;
      
      let colorClass = 'text-sky-400';
      let icon = '<svg class="w-8 h-8" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="1.5"><path stroke-linecap="round" stroke-linejoin="round" d="M13 16h-1v-4h-1m1-4h.01M12 21a9 9 0 100-18 9 9 0 000 18z"/></svg>';
      
      if (type === 'alarm' || type === 'error') {
        colorClass = 'text-rose-400';
        icon = '<svg class="w-8 h-8 animate-bounce text-rose-500" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="1.5"><path stroke-linecap="round" stroke-linejoin="round" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"/></svg>';
        alertEl.classList.add('bg-rose-500/10', 'border', 'border-rose-500/30');
        alertEl.innerHTML = `
          <div class="absolute inset-0 bg-rose-500/5 animate-pulse"></div>
          <div class="flex items-center gap-4 relative z-10">
            <div class="p-3 bg-rose-500/20 rounded-2xl shrink-0 border border-rose-500/30">${icon}</div>
            <div>
              <h2 class="text-base md:text-lg font-black ${colorClass} uppercase tracking-widest">${title}</h2>
              <p class="text-[13px] md:text-sm text-rose-200/80 mt-1 leading-snug">${message}</p>
            </div>
          </div>
        `;
      } else if (type === 'report') {
        colorClass = 'text-amber-400';
        icon = '<svg class="w-8 h-8 text-amber-500" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="1.5"><path stroke-linecap="round" stroke-linejoin="round" d="M9 12h6m-6 4h6m2 5H7a2 2 0 01-2-2V5a2 2 0 012-2h5.586a1 1 0 01.707.293l5.414 5.414a1 1 0 01.293.707V19a2 2 0 01-2 2z"/></svg>';
        alertEl.classList.add('bg-amber-500/10', 'border', 'border-amber-500/30');
        alertEl.innerHTML = `
          <div class="flex items-center gap-4 relative z-10">
            <div class="p-3 bg-amber-500/20 rounded-2xl shrink-0 border border-amber-500/30">${icon}</div>
            <div>
              <h2 class="text-base md:text-lg font-black ${colorClass} uppercase tracking-widest">${title}</h2>
              <p class="text-[13px] md:text-sm text-amber-100/80 mt-1 leading-snug">${message}</p>
            </div>
          </div>
          <button onclick="window.hideAlert('${id}')" class="relative z-10 px-6 py-2.5 md:py-3 w-full md:w-auto bg-amber-500/10 hover:bg-amber-500/30 text-amber-200 text-[11px] md:text-xs font-bold rounded-xl border border-amber-500/30 transition-colors shrink-0 tracking-[0.2em] uppercase">Gizle</button>
        `;
      }
      
      container.appendChild(alertEl);
    };

    window.hideAlert = function(id) {
      const el = document.getElementById(id);
      if (el) el.remove();
    };

    window.addEventListener('keydown', (e) => {
      if (e.key === 'Escape') closeAllModals();
    });

    window.addEventListener('click', (e) => {
      if (e.target && e.target.classList && e.target.classList.contains('fixed') && e.target.classList.contains('inset-0')) {
        closeAllModals();
      }
    });

    // TOAST NOTIFICATION SYSTEM
    function showToast(title, message, type = 'info', id = null, persistent = false) {
      const container = document.getElementById('toast-container');
      if (!container) return;
      
      if (id) {
        let existing = document.getElementById('toast-' + id);
        if (existing) return; // Already showing
      } else {
        id = Date.now().toString() + Math.floor(Math.random()*1000);
      }
      
      let colors = {
        'error':   { bg: 'bg-rose-500/10', border: 'border-rose-500/30', text: 'text-rose-400', icon: '<svg class="w-5 h-5" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M12 9v2m0 4h.01m-6.938 4h13.856c1.54 0 2.502-1.667 1.732-3L13.732 4c-.77-1.333-2.694-1.333-3.464 0L3.34 16c-.77 1.333.192 3 1.732 3z"/></svg>' },
        'success': { bg: 'bg-emerald-500/10', border: 'border-emerald-500/30', text: 'text-emerald-400', icon: '<svg class="w-5 h-5" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M9 12l2 2 4-4m6 2a9 9 0 11-18 0 9 9 0 0118 0z"/></svg>' },
        'warn':    { bg: 'bg-amber-500/10', border: 'border-amber-500/30', text: 'text-amber-400', icon: '<svg class="w-5 h-5" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M12 8v4m0 4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"/></svg>' },
        'info':    { bg: 'bg-sky-500/10', border: 'border-sky-500/30', text: 'text-sky-400', icon: '<svg class="w-5 h-5" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M13 16h-1v-4h-1m1-4h.01M21 12a9 9 0 11-18 0 9 9 0 0118 0z"/></svg>' }
      };
      let c = colors[type] || colors['info'];
      
      let toast = document.createElement('div');
      toast.id = 'toast-' + id;
      toast.className = `w-full bg-[#020617]/95 backdrop-blur-xl border ${c.border} rounded-2xl p-3.5 flex gap-3.5 shadow-[0_15px_40px_-10px_rgba(0,0,0,0.7)] transform translate-x-full opacity-0 transition-all duration-400 pointer-events-auto`;
      toast.innerHTML = `
        <div class="shrink-0 ${c.text} bg-slate-800/80 p-2 rounded-xl border border-slate-700/50 shadow-inner flex items-center justify-center">
          ${c.icon}
        </div>
        <div class="flex-1 min-w-0 flex flex-col justify-center">
          <span class="text-[10px] font-black tracking-widest uppercase ${c.text}">${title}</span>
          <span class="text-slate-200 text-[13px] font-medium mt-0.5 leading-tight break-words">${message}</span>
        </div>
        <button onclick="removeToast('${id}')" class="shrink-0 text-slate-500 hover:text-white p-1.5 rounded-full hover:bg-slate-800 transition-colors self-start -mt-1 -mr-1">
          <svg class="w-4 h-4" fill="none" viewBox="0 0 24 24" stroke="currentColor" stroke-width="2.5"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12"/></svg>
        </button>
      `;
      
      container.appendChild(toast);
      
      // Animate in
      requestAnimationFrame(() => {
        toast.classList.remove('translate-x-full', 'opacity-0');
      });
      
      if (!persistent) {
        setTimeout(() => removeToast(id), 6000);
      }
    }
    
    function removeToast(id) {
      let toast = document.getElementById('toast-' + id);
      if (toast) {
        toast.classList.add('translate-x-full', 'opacity-0');
        setTimeout(() => toast.remove(), 400); // Wait for transition
      }
    }
  </script>

  <!-- İnverter Zamanlayıcı Modal -->
  <div id="inv-modal" class="fixed inset-0 z-[90] bg-slate-950/80 backdrop-blur-sm flex flex-col items-center justify-center p-4 overflow-y-auto transition-all opacity-0 pointer-events-none duration-150">
    <div class="absolute inset-0 bg-transparent" onclick="hideInvModal()"></div>
    <div class="relative w-full max-w-sm bg-slate-900 border border-slate-700 rounded-3xl shadow-2xl overflow-hidden flex flex-col transform scale-95 transition-transform duration-150 my-auto" id="inv-modal-content">
      
      <!-- Standardized Header -->
      <div class="flex justify-between items-center p-4 border-b border-slate-800">
        <div class="flex items-center gap-3">
          <div class="p-2 bg-orange-500/10 rounded-xl">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5 text-orange-400"><path stroke-linecap="round" stroke-linejoin="round" d="M12 6v6h4.5m4.5 0a9 9 0 11-18 0 9 9 0 0118 0z" /></svg>
          </div>
          <div>
            <h3 class="text-white font-bold tracking-wide text-sm">İnverter Yönetimi</h3>
            <p class="text-[10px] text-slate-500 uppercase tracking-wider">Otomatik Kapanma Süresi</p>
          </div>
        </div>
        <button onclick="hideInvModal()" class="text-slate-400 hover:text-white bg-slate-800 hover:bg-slate-700 p-1.5 rounded-full transition-all shrink-0">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-4 h-4"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
        </button>
      </div>

      <div class="p-5 flex flex-col gap-4">
        

        <button onclick="startInvWithTimer(-1)" class="w-full py-3.5 rounded-2xl bg-orange-500/20 border border-orange-500/30 text-orange-400 font-bold hover:bg-orange-500/30 hover:border-orange-500/50 transition-all flex items-center justify-center gap-2 text-sm shadow-[0_0_15px_rgba(249,115,22,0.15)] group">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2" stroke="currentColor" class="w-5 h-5 group-hover:scale-110 transition-transform"><path stroke-linecap="round" stroke-linejoin="round" d="M5.636 5.636a9 9 0 1012.728 0M12 3v9" /></svg>
          Sürekli Açık
        </button>
        
        <div class="grid grid-cols-2 gap-3 mt-1">
          <button onclick="startInvWithTimer(5)" class="py-3 rounded-2xl bg-slate-800/60 border border-slate-700/60 text-slate-300 text-xs font-bold hover:bg-slate-700 hover:text-white hover:border-slate-600 transition-all">5 Dakika</button>
          <button onclick="startInvWithTimer(15)" class="py-3 rounded-2xl bg-slate-800/60 border border-slate-700/60 text-slate-300 text-xs font-bold hover:bg-slate-700 hover:text-white hover:border-slate-600 transition-all">15 Dakika</button>
          <button onclick="startInvWithTimer(30)" class="py-3 rounded-2xl bg-slate-800/60 border border-slate-700/60 text-slate-300 text-xs font-bold hover:bg-slate-700 hover:text-white hover:border-slate-600 transition-all">30 Dakika</button>
          <button onclick="startInvWithTimer(60)" class="py-3 rounded-2xl bg-slate-800/60 border border-slate-700/60 text-slate-300 text-xs font-bold hover:bg-slate-700 hover:text-white hover:border-slate-600 transition-all">1 Saat</button>
          <button onclick="startInvWithTimer(120)" class="py-3 rounded-2xl bg-slate-800/60 border border-slate-700/60 text-slate-300 text-xs font-bold hover:bg-slate-700 hover:text-white hover:border-slate-600 transition-all">2 Saat</button>
          <button onclick="startInvWithTimer(240)" class="py-3 rounded-2xl bg-slate-800/60 border border-slate-700/60 text-slate-300 text-xs font-bold hover:bg-slate-700 hover:text-white hover:border-slate-600 transition-all">4 Saat</button>
        </div>
      </div>
    </div>
  </div>


  <!--  SIDEBAR DRAWER  -->
  <div id="sidebarDrawer" class="hidden fixed inset-0 z-[90] opacity-0 transition-opacity duration-150 flex justify-end">
    <!-- Backdrop overlay -->
    <div class="absolute inset-0 bg-slate-950/60 backdrop-blur-sm" onclick="closeSidebar()"></div>
    <!-- Drawer content -->
    <div id="sidebarContent" class="h-full w-72 bg-slate-900 border-l border-slate-800 shadow-2xl p-6 flex flex-col justify-between transform translate-x-full transition-transform duration-150 z-10 relative">
      
      <!-- Drawer Top -->
      <div>
        <div class="flex items-center justify-between mb-8">
          <span class="text-xs font-bold text-slate-500 uppercase tracking-widest">KONTROL PANELİ</span>
          <button onclick="closeSidebar()" class="text-slate-400 hover:text-white p-1 rounded-lg hover:bg-slate-800 transition-all">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="2.5" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" /></svg>
          </button>
        </div>

        <!-- Vertical Menu List -->
        <div class="space-y-4">
          <!-- Geçmiş Veriler -->
          <button onclick="openChartModal(); closeSidebar();" class="w-full flex items-center gap-4 p-3 rounded-2xl bg-slate-800/30 hover:bg-violet-500/10 border border-slate-700/40 hover:border-violet-500/30 text-slate-300 hover:text-violet-300 transition-all duration-200 group text-left">
            <div class="p-2 bg-violet-500/10 rounded-xl text-violet-400 group-hover:bg-violet-500/20 transition-colors shrink-0">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M3 13.125C3 12.504 3.504 12 4.125 12h2.25c.621 0 1.125.504 1.125 1.125v6.75C7.5 20.496 6.996 21 6.375 21h-2.25A1.125 1.125 0 013 19.875v-6.75zM9.75 8.625c0-.621.504-1.125 1.125-1.125h2.25c.621 0 1.125.504 1.125 1.125v11.25c0 .621-.504 1.125-1.125 1.125h-2.25a1.125 1.125 0 01-1.125-1.125V8.625zM16.5 4.125c0-.621.504-1.125 1.125-1.125h2.25C20.496 3 21 3.504 21 4.125v15.75c0 .621-.504 1.125-1.125 1.125h-2.25a1.125 1.125 0 01-1.125-1.125V4.125z" /></svg>
            </div>
            <div class="flex flex-col">
              <span class="text-sm font-semibold tracking-wide">Geçmiş Veriler</span>
              <span class="text-[10px] text-slate-500 font-medium mt-0.5">Aylık Isı Grafiği</span>
            </div>
          </button>
          
          <!-- Sistem Logları -->
          <button onclick="openLogModal(); closeSidebar();" class="w-full flex items-center gap-4 p-3 rounded-2xl bg-slate-800/30 hover:bg-amber-500/10 border border-slate-700/40 hover:border-amber-500/30 text-slate-300 hover:text-amber-300 transition-all duration-200 group text-left">
            <div class="p-2 bg-amber-500/10 rounded-xl text-amber-400 group-hover:bg-amber-500/20 transition-colors shrink-0">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M3.75 12h16.5m-16.5 3.75h16.5M3.75 19.5h16.5M5.625 4.5h12.75a1.875 1.875 0 010 3.75H5.625a1.875 1.875 0 010-3.75z" /></svg>
            </div>
            <div class="flex flex-col">
              <span class="text-sm font-semibold tracking-wide">Sistem Logları</span>
              <span class="text-[10px] text-slate-500 font-medium mt-0.5">Anlık Olay Günlükleri</span>
            </div>
          </button>
          
          <!-- SD Kart Yönetimi -->
          <button onclick="openSdCardModal(); closeSidebar();" class="w-full flex items-center gap-4 p-3 rounded-2xl bg-slate-800/30 hover:bg-blue-500/10 border border-slate-700/40 hover:border-blue-500/30 text-slate-300 hover:text-blue-300 transition-all duration-200 group text-left">
            <div class="p-2 bg-blue-500/10 rounded-xl text-blue-400 group-hover:bg-blue-500/20 transition-colors shrink-0">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M19.5 8.25l-4.5-4.5H6A2.25 2.25 0 003.75 6v12A2.25 2.25 0 006 20.25h12A2.25 2.25 0 0020.25 18V8.25z" /><path stroke-linecap="round" stroke-linejoin="round" d="M8.25 7.5v3m3-3v3m3-3v3" /></svg>
            </div>
            <div class="flex flex-col">
              <span class="text-sm font-semibold tracking-wide">SD Kart Yönetimi</span>
              <span class="text-[10px] text-slate-500 font-medium mt-0.5">Depolama & Log İndirme</span>
            </div>
          </button>
          
          <!-- Sistem Durumu -->
          <button onclick="openSysStatusModal(); closeSidebar();" class="w-full flex items-center gap-4 p-3 rounded-2xl bg-slate-800/30 hover:bg-emerald-500/10 border border-slate-700/40 hover:border-emerald-500/30 text-slate-300 hover:text-emerald-300 transition-all duration-200 group text-left">
            <div class="p-2 bg-emerald-500/10 rounded-xl text-emerald-400 group-hover:bg-emerald-500/20 transition-colors shrink-0">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M9 12.75L11.25 15 15 9.75M21 12a9 9 0 11-18 0 9 9 0 0118 0z" /></svg>
            </div>
            <div class="flex flex-col">
              <span class="text-sm font-semibold tracking-wide">Sistem Durumu</span>
              <span class="text-[10px] text-slate-500 font-medium mt-0.5">Donanım & Hat Raporu</span>
            </div>
          </button>
          
          <!-- WiFi Ayarları -->
          <button onclick="openWifiSettingsModal(); closeSidebar();" class="w-full flex items-center gap-4 p-3 rounded-2xl bg-slate-800/30 hover:bg-cyan-500/10 border border-slate-700/40 hover:border-cyan-500/30 text-slate-300 hover:text-cyan-300 transition-all duration-200 group text-left">
            <div class="p-2 bg-cyan-500/10 rounded-xl text-cyan-400 group-hover:bg-cyan-500/20 transition-colors shrink-0">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M8.288 15.038a5.25 5.25 0 017.424 0M5.106 11.856c3.807-3.808 9.98-3.808 13.788 0M1.924 8.674c5.565-5.565 14.587-5.565 20.152 0M12.53 18.22l-.53.53-.53-.53a.75.75 0 011.06 0z" /></svg>
            </div>
            <div class="flex flex-col">
              <span class="text-sm font-semibold tracking-wide">WiFi Ayarları</span>
              <span class="text-[10px] text-slate-500 font-medium mt-0.5">Karavan Ağ Adı & Şifresi</span>
            </div>
          </button>
          
          <!-- Sistem Güncelleme (OTA) -->
          <button onclick="openOtaModal(); closeSidebar();" class="w-full flex items-center gap-4 p-3 rounded-2xl bg-slate-800/30 hover:bg-violet-500/10 border border-slate-700/40 hover:border-violet-500/30 text-slate-300 hover:text-violet-300 transition-all duration-200 group text-left">
            <div class="p-2 bg-violet-500/10 rounded-xl text-violet-400 group-hover:bg-violet-500/20 transition-colors shrink-0">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M3 16.5v2.25A2.25 2.25 0 005.25 21h13.5A2.25 2.25 0 0021 18.75V16.5m-13.5-9L12 3m0 0l4.5 4.5M12 3v13.5" /></svg>
            </div>
            <div class="flex flex-col">
              <span class="text-sm font-semibold tracking-wide">Yazılım Güncelleme</span>
              <span class="text-[10px] text-slate-500 font-medium mt-0.5">Sistem (OTA) Güncellemesi</span>
            </div>
          </button>
          
          <!-- Sistemi Yeniden Başlat -->
          <button onclick="if(confirm('Karavan kontrol sistemini yeniden başlatmak istediğinize emin misiniz?')) { sendWs({cmd:'reboot'}); closeSidebar(); }" class="w-full flex items-center gap-4 p-3 rounded-2xl bg-slate-800/30 hover:bg-rose-500/10 border border-slate-700/40 hover:border-rose-500/30 text-slate-300 hover:text-rose-300 transition-all duration-200 group text-left">
            <div class="p-2 bg-rose-500/10 rounded-xl text-rose-400 group-hover:bg-rose-500/20 transition-colors shrink-0">
              <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.8" stroke="currentColor" class="w-5 h-5"><path stroke-linecap="round" stroke-linejoin="round" d="M5.636 5.636a9 9 0 1012.728 0M12 3v9" /></svg>
            </div>
            <div class="flex flex-col">
              <span class="text-sm font-semibold tracking-wide">Yeniden Başlat</span>
              <span class="text-[10px] text-slate-500 font-medium mt-0.5">Sistemi Yeniden Başlatır</span>
            </div>
          </button>
        </div>
      </div>

      <!-- Drawer Bottom -->
      <div class="border-t border-slate-800 pt-4 flex flex-col gap-1.5 text-[9px] text-slate-500 tracking-wider uppercase font-bold">
        <div class="flex justify-between">
          <span>Yazılım</span>
          <span class="text-cyan-400">Hotomobil v2.1</span>
        </div>
        <div class="flex justify-between">
          <span>Durum</span>
          <span id="sidebar-status-text" class="text-green-400">Çevrimiçi</span>
        </div>
      </div>

    </div>
  </div>

</body>
</html>

)rawliteral";

#endif




