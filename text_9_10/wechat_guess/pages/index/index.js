const MODE_NAMES = { classic: '经典', level: '闯关', time: '竞速', vs: '对战', daily: '每日' };

const DIFFS = [
  { name: '简单 (1-50, 7次)', max: 50, guesses: 7 },
  { name: '普通 (1-100, 5次)', max: 100, guesses: 5 },
  { name: '困难 (1-200, 4次)', max: 200, guesses: 4 },
  { name: '自定义' }
];

const THEMES = [
  { id: 0, name: '深海蓝', bgTop: '#1e3c72', bgBottom: '#2a5298', accent: '#38ef7d' },
  { id: 1, name: '极夜紫', bgTop: '#41295a', bgBottom: '#2f0743', accent: '#b388eb' },
  { id: 2, name: '森林绿', bgTop: '#134e5e', bgBottom: '#4e9c6e', accent: '#7fe3c1' },
  { id: 3, name: '暖阳橙', bgTop: '#c0392b', bgBottom: '#f7bb97', accent: '#ffd166' }
];

const ACHIEVEMENTS = [
  { id: 'first', name: '初出茅庐', desc: '获得第一场胜利', icon: '🏆' },
  { id: 'wins10', name: '稳操胜券', desc: '累计胜利 10 局', icon: '⭐' },
  { id: 'total50', name: '百炼成钢', desc: '累计完赛 50 局', icon: '💎' },
  { id: 'speed', name: '闪电手', desc: '5 秒内猜中一局', icon: '⚡' },
  { id: 'racing', name: '竞速达人', desc: '竞速单局猜对 5 题', icon: '🚀' },
  { id: 'level5', name: '闯关先锋', desc: '闯关达到第 5 关', icon: '🏔️' },
  { id: 'streak', name: '连胜传说', desc: '连续胜利 5 局', icon: '🔥' },
  { id: 'custom', name: '自定义大师', desc: '用自定义难度获胜', icon: '🎯' }
];

const TIME_LIMIT = 60;

function getLevelCfg(n) {
  if (n <= 5) return { max: 10 * n, guesses: 6 };
  if (n <= 10) return { max: 50 + 25 * (n - 5), guesses: 7 };
  return { max: 200, guesses: 8 };
}

function pad(n) {
  return n < 10 ? '0' + n : '' + n;
}

function nowStr() {
  const d = new Date();
  return (d.getMonth() + 1) + '/' + d.getDate() + ' ' + pad(d.getHours()) + ':' + pad(d.getMinutes());
}

function dayKey() {
  const d = new Date();
  return '' + d.getFullYear() + (d.getMonth() + 1) + d.getDate();
}

function dayNumber() {
  const s = dayKey();
  let h = 0;
  for (let i = 0; i < s.length; i++) h = (h * 31 + s.charCodeAt(i)) % 997;
  return (h % 100) + 1;
}

Page({
  data: {
    mode: 'classic',
    MODE_NAMES,
    tabs: [
      { id: 'classic', name: '经典' },
      { id: 'level', name: '闯关' },
      { id: 'time', name: '竞速' },
      { id: 'vs', name: '对战' }
    ],
    diffs: DIFFS,
    diffIndex: 1,
    themes: THEMES,
    themeIndex: 0,
    theme: THEMES[0],
    soundOn: true,
    vibrateOn: true,
    nick: '',
    vsWins: 0,

    customMax: 100,
    customGuess: 5,
    useCustom: false,

    propHint: 3,
    propShield: 2,
    propTime: 1,
    propDouble: 1,
    shieldActive: false,

    level: 1,
    levelBest: 0,
    timeBest: 0,
    score: 0,
    counts: 0,

    vsText: '',
    vsTurn: '',
    dailyBestText: '-',
    dailyToday: false,

    hintText: '请输入你猜的数字 (1-100):',
    inputVal: '',
    inputDisabled: true,
    guessDisabled: true,
    remainText: '-',
    timeText: '0.0s',
    status: '请选择模式后点击开始',
    statusClass: '',
    running: false,
    history: [],

    overlay: '',
    rankList: [],
    bestText: '暂无纪录',
    achvList: [],
    logList: [],
    stats: { total: 0, wins: 0, timeSum: 0, guessSum: 0, bestLevel: 0 },
    posterSrc: ''
  },

  onLoad() {
    this.audioCtx = wx.createInnerAudioContext();
    this.audioCtx.loop = false;
    this.diffBest = [
      Number(wx.getStorageSync('guess_best_classic_0') || 0),
      Number(wx.getStorageSync('guess_best_classic_1') || 0),
      Number(wx.getStorageSync('guess_best_classic_2') || 0),
      Number(wx.getStorageSync('guess_best_classic_3') || 0)
    ];
    this.loadSetting();
    this.loadStats();
    this.loadLevelBest();
    this.loadTimeBest();
    this.loadRank();
    this.loadLog();
    this.loadAchievements();
    this.loadDaily();
    this.refreshBest();
    if (!wx.getStorageSync('guess_guide')) {
      this.setData({ overlay: 'guide' });
    }
  },

  onUnload() {
    this.stopAll();
    if (this.audioCtx) {
      this.audioCtx.destroy();
      this.audioCtx = null;
    }
  },

  onShareAppMessage() {
    return {
      title: this.running
        ? ('我玩猜数字「' + MODE_NAMES[this.data.mode] + '」得了 ' + this.data.score + ' 分，你来挑战一下!')
        : '猜数字小游戏，来挑战我的高分吧!',
      path: '/pages/index/index'
    };
  },

  loadSetting() {
    const s = wx.getStorageSync('guess_setting');
    const nick = wx.getStorageSync('guess_nick') || '';
    if (s) {
      const cur = { soundOn: true, vibrateOn: true, themeIndex: this.data.themeIndex, ...s };
      const th = THEMES[cur.themeIndex] || THEMES[0];
      this.setData({ soundOn: cur.soundOn, vibrateOn: cur.vibrateOn, themeIndex: th.id, theme: th, nick: nick });
      return;
    }
    const th = THEMES[Number(wx.getStorageSync('guess_theme') || 0)] || THEMES[0];
    this.setData({ themeIndex: th.id, theme: th, nick: nick });
  },

  saveSetting() {
    wx.setStorageSync('guess_setting', {
      soundOn: this.data.soundOn,
      vibrateOn: this.data.vibrateOn,
      themeIndex: this.data.themeIndex
    });
  },

  loadStats() {
    const st = wx.getStorageSync('guess_stats');
    const s = st || { total: 0, wins: 0, timeSum: 0, guessSum: 0, bestLevel: 0, consec: 0, bestStreak: 0 };
    s.total = Number(s.total) || 0; s.wins = Number(s.wins) || 0;
    s.timeSum = Number(s.timeSum) || 0; s.guessSum = Number(s.guessSum) || 0;
    s.bestLevel = Number(s.bestLevel) || 0;
    s.consec = Number(s.consec) || 0; s.bestStreak = Number(s.bestStreak) || 0;
    this.addStats = s;
    this.setData({ stats: this.buildStats(s) });
  },

  buildStats(s) {
    return {
      total: s.total,
      wins: s.wins,
      bestLevel: s.bestLevel,
      bestStreak: s.bestStreak,
      consecShow: s.consec,
      winRate: s.total ? Math.round(s.wins * 100 / s.total) + '%' : '-',
      avgTime: s.wins ? (s.timeSum / s.wins).toFixed(1) + 's' : '-',
      avgGuess: s.wins ? (s.guessSum / s.wins).toFixed(1) : '-'
    };
  },

  recordStats(win, secs, guessCount) {
    const s = this.addStats;
    s.total += 1;
    if (win) {
      s.wins += 1;
      s.timeSum += secs;
      s.guessSum += guessCount;
      s.consec += 1;
      if (s.consec > s.bestStreak) s.bestStreak = s.consec;
    } else {
      s.consec = 0;
    }
    if (this.data.mode === 'level') this.updateBestLevel();
    wx.setStorageSync('guess_stats', s);
    this.setData({ stats: this.buildStats(s) });
    this.updateAchievements();
  },

  loadLevelBest() {
    this.levelBest = Number(wx.getStorageSync('guess_best_level') || 0);
    this.setData({ levelBest: this.levelBest });
  },

  loadTimeBest() {
    this.timeBest = Number(wx.getStorageSync('guess_best_time') || 0);
    this.setData({ timeBest: this.timeBest });
  },

  updateBestLevel() {
    if (this.data.mode !== 'level' || !this.level) return;
    const reach = this.level - 1;
    if (reach > this.levelBest) {
      this.levelBest = reach;
      wx.setStorageSync('guess_best_level', this.levelBest);
      this.setData({ levelBest: this.levelBest });
    }
  },

  loadRank() {
    const list = wx.getStorageSync('guess_rank') || [];
    this.setData({ rankList: list.slice(0, 10) });
  },

  submitRank(secs) {
    const score = this.data.score;
    if (score <= 0) return;
    const modeName = MODE_NAMES[this.data.mode];
    const diffName = this.data.mode === 'level'
      ? '第' + (this.level - 1) + '关'
      : (this.data.mode === 'time' ? '1-' + this.maxVal + '区间'
        : (this.data.mode === 'vs' ? '1-' + this.maxVal + '对战'
          : (this.data.mode === 'daily' ? '今日挑战' : this.diffName)));
    const entry = {
      id: Date.now() + '' + Math.floor(Math.random() * 1e6),
      nick: this.data.nick || '匿名玩家',
      score: this.data.score,
      mode: modeName,
      diff: diffName,
      time: secs.toFixed(1) + 's',
      date: nowStr()
    };
    const list = wx.getStorageSync('guess_rank') || [];
    list.push(entry);
    list.sort((a, b) => b.score - a.score);
    const top = list.slice(0, 10);
    wx.setStorageSync('guess_rank', top);
    this.setData({ rankList: top });
  },

  getDiffCfg() {
    const idx = this.data.diffIndex;
    if (idx < 3) {
      this.diffName = DIFFS[idx].name;
      return { max: DIFFS[idx].max, guesses: DIFFS[idx].guesses };
    }
    const omax = parseInt(this.data.customMax, 10);
    const oguess = parseInt(this.data.customGuess, 10);
    this.diffName = '自定义 (1-' + omax + ', ' + oguess + '次)';
    return { max: omax, guesses: oguess };
  },

  refreshBest() {
    const idx = this.data.diffIndex;
    const best = idx < 3 ? this.diffBest[idx] : (Number(wx.getStorageSync('guess_best_classic_3') || 0));
    const text = this.data.mode === 'classic'
      ? (best ? '本难度最高分: ' + best : '本难度暂无纪录')
      : (this.data.mode === 'level' ? '闯关最佳: ' + this.levelBest + ' 关'
        : (this.data.mode === 'time' ? '竞速最佳: ' + this.timeBest + ' 分'
          : (this.data.mode === 'vs' ? 'VS 胜场: ' + (this.vsWins || 0) + ' 场' : '今日最佳: ' + this.dailyBestText)));
    this.setData({ bestText: text });
  },

  onModeTap(e) {
    if (this.running) {
      wx.showToast({ title: '请先结束当前游戏', icon: 'none' });
      return;
    }
    const mode = e.currentTarget.dataset.mode;
    this.setData({ mode: mode, history: [], score: 0, counts: 0, timeText: '0.0s', remainText: '-' });
    this.resetAll();
    this.refreshBest();
  },

  onDiffChange(e) {
    const idx = Number(e.detail.value);
    if (idx === 3) {
      this.setData({ diffIndex: 3, useCustom: true });
      return;
    }
    this.setData({ diffIndex: idx, useCustom: false, status: '请选择模式后点击开始', statusClass: '' });
    this.refreshBest();
  },

  onCustomMax(e) {
    this.setData({ customMax: e.detail.value });
  },

  onCustomGuess(e) {
    this.setData({ customGuess: e.detail.value });
  },

  onInput(e) {
    this.setData({ inputVal: e.detail.value });
  },

  applyCustom(e) {
    const m = parseInt(this.data.customMax, 10);
    const g = parseInt(this.data.customGuess, 10);
    if (!m || m < 5 || m > 5000) {
      wx.showToast({ title: '范围请输入 5-5000', icon: 'none' });
      return;
    }
    if (!g || g < 2 || g > 20) {
      wx.showToast({ title: '次数请输入 2-20', icon: 'none' });
      return;
    }
    this.diffBest[3] = Number(wx.getStorageSync('guess_best_classic_3') || 0);
    this.setData({ useCustom: false, status: '自定义难度已应用, 点击开始', statusClass: 'tip' });
    this.refreshBest();
  },

  resetProps() {
    this.propHint = 3;
    this.propShield = 2;
    this.propTime = 1;
    this.propDouble = 1;
    this.scoreFactor = 1;
    this.shieldActive = false;
    this.tmpSpeed = false;
    this.tmpRacing = false;
    this.tmpCustom = false;
    this.setData({ propHint: 3, propShield: 2, propTime: 1, propDouble: 1, shieldActive: false });
  },

  startGame() {
    const m = this.data.mode;
    this.resetProps();
    if (m === 'classic') {
      const cfg = this.getDiffCfg();
      if (isNaN(cfg.max) || cfg.max < 1 || isNaN(cfg.guesses)) {
        wx.showToast({ title: '请先设置自定义难度', icon: 'none' });
        return;
      }
      this.maxVal = cfg.max;
      this.maxGuess = cfg.guesses;
      this.secret = Math.floor(Math.random() * this.maxVal) + 1;
      this.count = 0;
      this.low = 1;
      this.high = this.maxVal;
      this.hintShown = false;
      this.setData({ score: 0, counts: 0, history: [], vsText: '', vsTurn: '', hintText: '请输入你猜的数字 (1-' + this.maxVal + '):' });
      this.setState('游戏开始! 请在 ' + this.maxGuess + ' 次内猜出数字');
      this.beginRun(true, this.maxVal);
    } else if (m === 'level') {
      this.level = 1;
      this.totalScore = 0;
      this.startLevel();
    } else if (m === 'time') {
      this.totalScore = 0;
      this.counts = 0;
      this.maxVal = 100;
      this.secret = Math.floor(Math.random() * this.maxVal) + 1;
      this.low = 1;
      this.high = this.maxVal;
      this.timeLeft = TIME_LIMIT;
      this.timeBonusSec = 0;
      this.setData({ score: 0, counts: 0, history: [], vsText: '', vsTurn: '', hintText: '请输入你猜的数字 (1-' + this.maxVal + '):' });
      this.setState('竞速开始! 请在 60 秒内猜对越多越好');
      this.beginRun(true, 100);
    } else if (m === 'vs') {
      this.maxVal = 100;
      this.maxGuess = 7;
      this.secret = Math.floor(Math.random() * this.maxVal) + 1;
      this.low = 1;
      this.high = this.maxVal;
      this.playerLeft = 7;
      this.aiLeft = 7;
      this.aiCount = 0;
      this.vsMove = 0;
      this.count = 0;
      this.setData({ score: 0, counts: 0, history: [], vsText: '', vsTurn: '轮到你', hintText: '请输入你猜的数字 (1-' + this.maxVal + '):' });
      this.setState('对战开始! 你和 AI 轮流猜, 谁先猜中 1-' + this.maxVal + ' 内的数字');
      this.beginRun(true, 100);
    }
  },

  startDaily() {
    this.setData({ overlay: '', mode: 'daily' });
    this.resetProps();
    this.maxVal = 100;
    this.maxGuess = 5;
    this.secret = dayNumber();
    this.count = 0;
    this.low = 1;
    this.high = this.maxVal;
    this.hintShown = false;
    this.diffName = '今日挑战 (固定: 1-100, 5次)';
    this.setData({ score: 0, counts: 0, history: [], vsText: '', vsTurn: '', hintText: '请输入你猜的数字 (1-100):' });
    this.setState('今日挑战开始! 数字是固定的, 5 次机会');
    this.beginRun(true, 100);
    this.refreshBest();
  },

  startLevel() {
    const cfg = getLevelCfg(this.level);
    this.maxVal = cfg.max;
    this.maxGuess = cfg.guesses;
    this.secret = Math.floor(Math.random() * this.maxVal) + 1;
    this.count = 0;
    this.low = 1;
    this.high = this.maxVal;
    this.hintShown = false;
    this.setData({
      level: this.level,
      history: [],
      vsText: '',
      vsTurn: '',
      hintText: '请输入你猜的数字 (1-' + this.maxVal + '):'
    });
    this.setState('第 ' + this.level + ' 关: 1-' + this.maxVal + ' 共 ' + this.maxGuess + ' 次机会');
    this.beginRun(true, this.maxVal);
  },

  beginRun(resetScore, maxVal) {
    if (resetScore) this.setData({ score: 0 });
    this.running = true;
    this.setData({ running: true });
    this.clearTimer();
    this.startT = Date.now();
    if (this.data.mode === 'time') {
      this.timeLeft = TIME_LIMIT + (this.timeBonusSec || 0);
      this.setData({ timeText: this.timeLeft + 's' });
      this.timerId = setInterval(() => this.tickTime(), 100);
    } else {
      this.setData({ timeText: '0.0s' });
      this.timerId = setInterval(() => this.updateTime(), 200);
    }
    this.setData({
      inputDisabled: false,
      guessDisabled: false,
      inputVal: '',
      remainText: this.maxGuess ? String(this.maxGuess) : '-'
    });
    if (this.data.mode === 'vs') this.updateRemain();
  },

  timeTotalMs() {
    return (TIME_LIMIT + (this.timeBonusSec || 0)) * 1000;
  },

  tickTime() {
    if (!this.running) return;
    const left = Math.ceil((this.timeTotalMs() - (Date.now() - this.startT)) / 1000);
    if (left > 0) {
      this.timeLeft = left;
      this.setData({ timeText: left + 's' });
      return;
    }
    this.timeLeft = 0;
    this.setData({ timeText: '0s' });
    const secs = (Date.now() - this.startT) / 1000;
    const score = this.data.score + this.counts * 10;
    this.endGame(secs);
    this.setData({ score: score, status: '时间到! 猜对 ' + this.counts + ' 题, 得分 ' + score, statusClass: 'good' });
    this.tmpRacing = (this.counts || 0) >= 5;
    this.checkTimeBest(score);
    this.submitRank(secs);
    if (this.data.score > 0) {
      this.recordLog('完成', MODE_NAMES.time, '1-' + this.maxVal, score, secs, this.counts);
    }
    this.recordStats(this.data.score > 0, secs, this.counts);
  },

  updateTime() {
    if (!this.running) return;
    const s = ((Date.now() - this.startT) / 1000).toFixed(1);
    this.setData({ timeText: s + 's' });
  },

  updateRemain() {
    if (this.data.mode === 'vs') {
      this.setData({ remainText: '你 ' + this.playerLeft + ' / AI ' + this.aiLeft });
      return;
    }
    const r = this.maxGuess ? Math.max(this.maxGuess - (this.count || 0), 0) : 0;
    this.setData({ remainText: r > 0 ? String(r) : '0' });
  },

  checkTimeBest(score) {
    if (score > this.timeBest) {
      this.timeBest = score;
      wx.setStorageSync('guess_best_time', score);
      this.setData({ timeBest: score });
    }
  },

  playSound(kind) {
    if (!this.data.soundOn || !this.audioCtx) return;
    const src = kind === 'ok' ? '/assets/sound/success.wav'
      : kind === 'bad' ? '/assets/sound/fail.wav'
        : '/assets/sound/tick.wav';
    this.audioCtx.src = src;
    this.audioCtx.play();
  },

  vibrate(kind) {
    if (!this.data.vibrateOn) return;
    if (kind === 'ok') {
      wx.vibrateShort({ type: 'medium', fail: () => wx.vibrateShort({}) });
    } else {
      wx.vibrateShort({ type: 'light', fail: () => wx.vibrateShort({}) });
    }
  },

  useHint() {
    if (!this.running) {
      wx.showToast({ title: '请先开始游戏', icon: 'none' });
      return;
    }
    if (this.propHint <= 0) {
      wx.showToast({ title: '提示卡已用完', icon: 'none' });
      return;
    }
    this.propHint--;
    this.setData({ propHint: this.propHint });
    this.setState('提示: 答案在 ' + this.low + ' - ' + this.high + ' 之间', 'tip');
    this.playSound('tick');
  },

  useShield() {
    if (!this.running) {
      wx.showToast({ title: '请先开始游戏', icon: 'none' });
      return;
    }
    if (this.data.mode !== 'classic' && this.data.mode !== 'level' && this.data.mode !== 'daily') {
      wx.showToast({ title: '当前模式无法使用免死', icon: 'none' });
      return;
    }
    if (this.propShield <= 0) {
      wx.showToast({ title: '免死金牌已用完', icon: 'none' });
      return;
    }
    if (this.shieldActive) {
      wx.showToast({ title: '免死已在待命状态', icon: 'none' });
      return;
    }
    this.propShield--;
    this.shieldActive = true;
    this.setData({ propShield: this.propShield, shieldActive: true });
    this.setState('免死金牌已激活! 下次猜错不扣次数', 'tip');
  },

  useTime() {
    if (!this.running) {
      wx.showToast({ title: '请先开始游戏', icon: 'none' });
      return;
    }
    if (this.data.mode !== 'time') {
      wx.showToast({ title: '仅在竞速模式可用', icon: 'none' });
      return;
    }
    if (this.propTime <= 0) {
      wx.showToast({ title: '加时卡已用完', icon: 'none' });
      return;
    }
    this.propTime--;
    this.timeBonusSec = (this.timeBonusSec || 0) + 15;
    this.timeLeft = Math.ceil((this.timeTotalMs() - (Date.now() - this.startT)) / 1000);
    this.setData({ propTime: this.propTime, timeText: this.timeLeft + 's' });
    this.setState('加时生效! +15 秒', 'good');
    this.playSound('ok');
  },

  useDouble() {
    if (!this.running) {
      wx.showToast({ title: '请先开始游戏', icon: 'none' });
      return;
    }
    if (this.data.mode === 'time' || this.data.mode === 'vs') {
      wx.showToast({ title: '当前模式无法使用翻倍', icon: 'none' });
      return;
    }
    if (this.propDouble <= 0) {
      wx.showToast({ title: '翻倍卡已用完', icon: 'none' });
      return;
    }
    this.propDouble--;
    this.scoreFactor = 2;
    this.setData({ propDouble: this.propDouble });
    this.setState('翻倍卡生效! 本局得分 ×2', 'good');
    this.playSound('ok');
  },

  doGuess() {
    if (!this.running) return;
    const v = parseInt(this.data.inputVal, 10);
    if (isNaN(v) || v < 1 || v > this.maxVal) {
      this.playSound('bad');
      this.vibrate('wrong');
      this.setData({ status: '请输入 1-' + this.maxVal + ' 之间的数字!', statusClass: 'bad' });
      return;
    }

    if (this.data.mode === 'vs') {
      this.vsGuess(v);
      return;
    }

    this.count++;
    const remain = this.maxGuess ? this.maxGuess - this.count : 0;
    const remainTip = this.data.mode === 'time' ? '' : ' 还剩 ' + remain + ' 次机会';
    this.setData({ inputVal: '' });

    if (v > this.secret) {
      if (v < this.high) this.high = v - 1;
      this.playSound('tick');
      this.vibrate('wrong');
      if (this.shieldActive && this.data.mode !== 'time') {
        this.shieldActive = false;
        this.count--;
        this.setData({ shieldActive: false });
        this.setState('猜大了! 免死金牌格挡, 次数不变', 'down');
      } else {
        this.setState('猜大了!' + remainTip, 'up');
      }
      this.addHistory(this.count, v, '猜大了', 'up');
    } else if (v < this.secret) {
      if (v > this.low) this.low = v + 1;
      this.playSound('tick');
      this.vibrate('wrong');
      if (this.shieldActive && this.data.mode !== 'time') {
        this.shieldActive = false;
        this.count--;
        this.setData({ shieldActive: false });
        this.setState('猜小了! 免死金牌格挡, 次数不变', 'up');
      } else {
        this.setState('猜小了!' + remainTip, 'down');
      }
      this.addHistory(this.count, v, '猜小了', 'down');
    } else {
      this.playSound('ok');
      this.vibrate('ok');
      this.onCorrect(v, remain);
      return;
    }

    if (this.data.mode !== 'time') {
      if (this.maxGuess - this.count === 2 && !this.hintShown) {
        this.hintShown = true;
        this.setState('提示: 答案在 ' + this.low + ' - ' + this.high + ' 之间, 还有 2 次机会', 'tip');
      }
      if (this.count >= this.maxGuess) {
        this.onFailCouplet();
        return;
      }
      this.updateRemain();
    }
  },

  vsGuess(v) {
    if (this.playerLeft <= 0) {
      wx.showToast({ title: '你已用完机会', icon: 'none' });
      return;
    }
    this.setData({ inputVal: '' });
    this.vsMove = (this.vsMove || 0) + 1;
    if (v === this.secret) {
      this.playSound('ok');
      this.vibrate('ok');
      this.vsPlayerGuess = (this.vsPlayerGuess || 0) + 1;
      this.finishVs('player');
      return;
    }
    this.vsPlayerGuess = (this.vsPlayerGuess || 0) + 1;
    if (v > this.secret) {
      if (v < this.high) this.high = v - 1;
      this.setState('你猜大了! 剩余 ' + this.playerLeft + ' 次', 'up');
      this.addHistory(this.vsMove, v, '你·大了', 'up');
    } else {
      if (v > this.low) this.low = v + 1;
      this.setState('你猜小了! 剩余 ' + this.playerLeft + ' 次', 'down');
      this.addHistory(this.vsMove, v, '你·小了', 'down');
    }
    this.playerLeft--;
    this.updateRemain();
    this.vsTurn();
  },

  vsTurn() {
    if (!this.running) return;
    this.setData({ vsTurn: 'AI 回合' });
    this.aiCount++;
    const g = this.aiPick();
    if (g === this.secret) {
      this.playSound('bad');
      this.vibrate('wrong');
      this.addHistory(this.aiCount, g, 'AI·对了', 'ok');
      this.finishVs('ai');
      return;
    }
    if (g > this.secret) {
      if (g < this.high) this.high = g - 1;
      this.addHistory(this.aiCount, g, 'AI·大了', 'up');
    } else {
      if (g > this.low) this.low = g + 1;
      this.addHistory(this.aiCount, g, 'AI·小了', 'down');
    }
    this.aiLeft--;
    if (this.aiLeft <= 0) {
      if (this.playerLeft <= 0) {
        this.finishVs('tie');
      } else {
        this.setData({ vsTurn: 'AI 用完了机会, 轮到你' });
        this.setState('AI 已经用尽机会! 现在只剩你了', 'good');
        this.updateRemain();
      }
      return;
    }
    this.setData({ vsTurn: '轮到你' });
    this.setState('AI 猜了 ' + g + ': ' + (g > this.secret ? '猜大了' : '猜小了') + ' (AI 剩 ' + this.aiLeft + ' 次)', 'tip');
    this.updateRemain();
  },

  aiPick() {
    const span = this.high - this.low;
    const mid = Math.round((this.low + this.high) / 2);
    if (Math.random() < 0.18) {
      return this.low + Math.floor(Math.random() * (span + 1));
    }
    const jitter = Math.round((Math.random() - 0.5) * span * 0.3);
    return Math.max(this.low, Math.min(this.high, mid + jitter));
  },

  finishVs(who) {
    const secs = (Date.now() - this.startT) / 1000;
    const guessNum = this.vsPlayerGuess || 1;
    let score = 0;
    let outcome = '败';
    if (who === 'player') {
      this.vsWins = (this.vsWins || 0) + 1;
      score = (this.playerLeft + 1) * 50;
      this.setData({ score: score, vsWins: this.vsWins, status: '你赢了! 得分 ' + score, statusClass: 'good' });
      outcome = '胜';
    } else if (who === 'tie') {
      score = 200;
      this.setData({ score: score, status: '平局! 双方都用完机会', statusClass: 'tip' });
      outcome = '平';
    } else {
      this.playSound('bad');
      this.vibrate('wrong');
      this.setData({ score: 0, status: 'AI 猜中了! 继续加油', statusClass: 'bad' });
    }
    this.endGame(secs);
    this.refreshBest();
    this.recordStats(who === 'player', secs, guessNum);
    this.recordLog(outcome, MODE_NAMES.vs, '1-100', this.data.score, secs, guessNum);
    if (score > 0) this.submitRank(secs);
  },

  onCorrect(v, remain) {
    const secs = (Date.now() - this.startT) / 1000;

    if (this.data.mode === 'time') {
      this.addHistory(this.count, v, '正确', 'ok');
      this.counts = (this.data.counts || 0) + 1;
      const score = this.data.score + 100;
      const left = Math.ceil((this.timeTotalMs() - (Date.now() - this.startT)) / 1000);
      this.setData({
        score: score,
        counts: this.counts,
        status: '答对 +100 分! 剩余 ' + Math.max(left, 0) + ' 秒 (' + this.counts + ' 题)',
        statusClass: 'good'
      });
      if (left <= 0) return;
      this.secret = Math.floor(Math.random() * this.maxVal) + 1;
      this.low = 1;
      this.high = this.maxVal;
      this.count = 0;
      this.setData({ hintText: '请输入你猜的数字 (1-' + this.maxVal + '):' });
      return;
    }

    if (this.data.mode === 'level') {
      let gain = (remain + 1) * 100 + this.level * 50;
      gain = Math.round(gain * (this.scoreFactor || 1));
      this.totalScore += gain;
      this.level++;
      this.setData({ score: this.totalScore });
      if (this.level > this.levelBest) {
        this.levelBest = this.level;
        wx.setStorageSync('guess_best_level', this.levelBest);
        this.setData({ levelBest: this.levelBest });
      }
      const cfg = getLevelCfg(this.level);
      this.maxVal = cfg.max;
      this.maxGuess = cfg.guesses;
      this.secret = Math.floor(Math.random() * this.maxVal) + 1;
      this.count = 0;
      this.low = 1;
      this.high = this.maxVal;
      this.hintShown = false;
      this.setData({
        level: this.level,
        history: [],
        score: this.totalScore,
        status: '第 ' + (this.level - 1) + ' 关通过! +' + gain + '分, 进入第 ' + this.level + ' 关 (' + cfg.max + '以内, ' + cfg.guesses + '次)',
        statusClass: 'good'
      });
      this.updateRemain();
      wx.showToast({ title: '进入第 ' + this.level + ' 关', icon: 'success' });
      return;
    }

    if (this.data.mode === 'daily') {
      this.dailyWin(v, secs, remain);
      return;
    }

    const factor = this.scoreFactor || 1;
    const sc = Math.max(((remain + 1) * 100 - Math.floor(secs)) * factor, 0);
    this.endGame(secs);
    let isRecord = false;
    if (sc > (this.diffBest[this.data.diffIndex] || 0)) {
      this.diffBest[this.data.diffIndex] = sc;
      wx.setStorageSync('guess_best_classic_' + this.data.diffIndex, sc);
      isRecord = true;
    }
    this.tmpSpeed = secs < 5;
    if (this.data.diffIndex === 3) this.tmpCustom = true;
    this.setData({
      score: sc,
      status: '恭喜你, 猜对了! 用时 ' + secs.toFixed(1) + ' 秒, 得分 ' + sc + (isRecord ? ' - 新纪录!' : ''),
      statusClass: 'good'
    });
    this.addHistory(this.count, v, '猜对了', 'ok');
    this.refreshBest();
    this.recordLog('胜', MODE_NAMES.classic, this.diffName, sc, secs, this.count);
    this.recordStats(true, secs, this.count);
    this.submitRank(secs);
  },

  dailyWin(v, secs, remain) {
    const factor = this.scoreFactor || 1;
    const sc = Math.max(((remain + 1) * 100 - Math.floor(secs)) * factor, 0);
    this.endGame(secs);
    this.tmpSpeed = secs < 5;
    const key = dayKey();
    const cur = wx.getStorageSync('guess_daily') || {};
    let isRecord = false;
    if ((!cur.date || cur.date !== key) || sc > (cur.best || 0)) {
      wx.setStorageSync('guess_daily', { date: key, best: sc });
      isRecord = true;
    }
    this.setData({
      score: sc,
      status: '今日挑战成功! 得分 ' + sc + (isRecord ? ' - 今日新高!' : ''),
      statusClass: 'good'
    });
    this.addHistory(this.count, v, '猜对了', 'ok');
    this.dailyBestText = sc;
    this.setData({ dailyBestText: String(sc), dailyToday: true });
    this.refreshBest();
    this.recordLog('胜', MODE_NAMES.daily, '1-100 5次', sc, secs, this.count);
    this.recordStats(true, secs, this.count);
    this.submitRank(secs);
  },

  onFailCouplet() {
    this.endGame();
    const m = this.data.mode;
    this.setData({
      status: this.maxGuess + '次都没猜对! 正确答案是: ' + this.secret,
      statusClass: 'bad'
    });
    this.playSound('bad');
    this.vibrate('wrong');
    if (m === 'level') {
      const reach = this.level - 1;
      if (reach > this.levelBest) {
        this.levelBest = reach;
        wx.setStorageSync('guess_best_level', this.levelBest);
        this.setData({ levelBest: this.levelBest });
      }
    }
    const secs = (Date.now() - this.startT) / 1000;
    this.recordLog('败', MODE_NAMES[m] || m, this.logDiffLabel(), this.data.score, secs, this.count);
    this.recordStats(false, secs, this.count);
    if (m === 'level' || m === 'daily') {
      this.submitRank(secs);
    }
  },

  logDiffLabel() {
    if (this.data.mode === 'daily') return '1-100 5次';
    return this.diffName || '1-' + this.maxVal;
  },

  endGame(secs) {
    this.running = false;
    this.clearTimer();
    this.setData({ running: false, guessDisabled: true, inputDisabled: true, remainText: '0' });
  },

  exitGame() {
    if (this.running) {
      wx.showModal({
        title: '退出游戏',
        content: '确定要退出当前游戏吗?',
        success: (res) => {
          if (res.confirm) this.resetAll();
        }
      });
      return;
    }
    this.resetAll();
  },

  resetAll() {
    this.stopAll();
    this.recordStatsOnExit();
    this.setData({
      inputVal: '',
      inputDisabled: true,
      guessDisabled: true,
      remainText: '-',
      timeText: '0.0s',
      history: [],
      vsTurn: '',
      status: '已退出, 切换模式或难度后点开始',
      statusClass: ''
    });
    this.refreshBest();
  },

  recordStatsOnExit() {
    if (!this.running || !this.startT) return;
    const secs = (Date.now() - this.startT) / 1000;
    this.recordStats(false, secs, this.count || this.playerLeft || 0);
    this.running = false;
  },

  stopAll() {
    this.running = false;
    this.clearTimer();
    this.setData({ running: false });
  },

  clearTimer() {
    if (this.timerId) {
      clearInterval(this.timerId);
      this.timerId = null;
    }
  },

  setState(msg, cls) {
    this.setData({ status: msg, statusClass: cls || '' });
  },

  addHistory(n, v, text, cls) {
    const history = this.data.history.slice();
    history.push({ n: n, v: v, text: text, cls: cls });
    this.setData({ history: history });
  },

  recordLog(outcome, modeName, diff, score, secs, used) {
    const list = wx.getStorageSync('guess_log') || [];
    list.unshift({
      id: Date.now() + '' + Math.floor(Math.random() * 1e6),
      outcome: outcome,
      mode: modeName || '',
      diff: diff || '',
      score: score || 0,
      time: (secs || 0).toFixed(1) + 's',
      used: used || 0,
      date: nowStr()
    });
    const top = list.slice(0, 30);
    wx.setStorageSync('guess_log', top);
    this.setData({ logList: top });
  },

  loadLog() {
    this.setData({ logList: wx.getStorageSync('guess_log') || [] });
  },

  loadAchievements() {
    const unlocked = wx.getStorageSync('guess_achv') || [];
    this.achv = unlocked;
    this.setData({ achvList: ACHIEVEMENTS.map((a) => ({
      id: a.id, name: a.name, desc: a.desc, icon: a.icon,
      unlocked: unlocked.indexOf(a.id) !== -1
    })) });
  },

  updateAchievements() {
    const s = this.addStats;
    const conds = {
      first: s.wins >= 1,
      wins10: s.wins >= 10,
      total50: s.total >= 50,
      speed: !!this.tmpSpeed,
      racing: !!this.tmpRacing,
      level5: s.bestLevel >= 5,
      streak: (s.bestStreak || 0) >= 5,
      custom: !!this.tmpCustom
    };
    const unlocked = this.achv || [];
    let changed = false;
    ACHIEVEMENTS.forEach((a) => {
      if (conds[a.id] && unlocked.indexOf(a.id) === -1) {
        unlocked.push(a.id);
        changed = true;
      }
    });
    if (changed) {
      wx.setStorageSync('guess_achv', unlocked);
      this.achv = unlocked;
    }
    this.setData({ achvList: ACHIEVEMENTS.map((a) => ({
      id: a.id, name: a.name, desc: a.desc, icon: a.icon,
      unlocked: unlocked.indexOf(a.id) !== -1
    })) });
  },

  loadDaily() {
    const cur = wx.getStorageSync('guess_daily') || {};
    if (cur.date === dayKey()) {
      this.dailyBestText = cur.best || 0;
      this.setData({ dailyBestText: String(cur.best || 0), dailyToday: true });
    } else {
      this.dailyBestText = '-';
      this.setData({ dailyBestText: '-', dailyToday: false });
    }
  },

  openOverlay(e) {
    const t = e.currentTarget.dataset.type;
    if (this.running && (t === 'setting' || t === 'poster')) {
      wx.showToast({ title: '请先结束当前游戏', icon: 'none' });
      return;
    }
    if (t === 'rank' || t === 'stats') this.loadRank();
    if (t === 'log') this.loadLog();
    if (t === 'achv') this.loadAchievements();
    this.setData({ overlay: t, posterSrc: '' });
    if (t === 'poster') {
      if (!this.data.score) {
        this.setData({ overlay: '' });
        wx.showToast({ title: '先完成一局再生成海报', icon: 'none' });
        return;
      }
      setTimeout(() => this.drawPoster(), 150);
    }
  },

  closeOverlay() {
    this.saveSetting();
    this.setData({ overlay: '' });
  },

  onNickInput(e) {
    this.setData({ nick: e.detail.value });
  },

  saveNick() {
    const v = (this.data.nick || '').trim().slice(0, 8);
    wx.setStorageSync('guess_nick', v);
    this.setData({ nick: v });
    wx.showToast({ title: '昵称已保存', icon: 'success' });
  },

  finishGuide() {
    wx.setStorageSync('guess_guide', true);
    this.setData({ overlay: '' });
  },

  onThemeTap(e) {
    const idx = Number(e.currentTarget.dataset.idx);
    this.setData({ themeIndex: idx, theme: THEMES[idx] });
    this.saveSetting();
  },

  onSoundChange(e) {
    this.setData({ soundOn: e.detail.value });
    this.saveSetting();
  },

  onVibrateChange(e) {
    this.setData({ vibrateOn: e.detail.value });
    this.saveSetting();
  },

  clearRank() {
    wx.showModal({
      title: '清空排行榜',
      content: '确定要清空本地排行榜吗?',
      success: (res) => {
        if (res.confirm) {
          wx.removeStorageSync('guess_rank');
          this.setData({ rankList: [] });
        }
      }
    });
  },

  clearLog() {
    wx.showModal({
      title: '清空对局记录',
      content: '确定要清空本地对局记录吗?',
      success: (res) => {
        if (res.confirm) {
          wx.removeStorageSync('guess_log');
          this.setData({ logList: [] });
        }
      }
    });
  },

  drawPoster() {
    const ctx = wx.createCanvasContext('posterCanvas', this);
    const modeName = MODE_NAMES[this.data.mode] || MODE_NAMES.classic;
    const sc = this.data.score;
    const t = this.data.timeText;
    const nick = this.data.nick || '匿名玩家';
    const date = nowStr();
    const W = 600;
    const H = 900;
    const g = ctx.createLinearGradient(0, 0, 0, H);
    g.addColorStop(0, '#1e3c72');
    g.addColorStop(1, '#2a5298');
    ctx.setFillStyle(g);
    ctx.fillRect(0, 0, W, H);

    ctx.setFillStyle('#ffd166');
    ctx.setTextAlign('center');
    ctx.setFontSize(72);
    ctx.fillText('猜 数 字', W / 2, 200);

    ctx.setFillStyle('#ffffff');
    ctx.setFontSize(40);
    ctx.fillText('模式: ' + modeName, W / 2, 290);

    ctx.setFillStyle('#38ef7d');
    ctx.setFontSize(150);
    ctx.fillText(String(sc), W / 2, 460);

    ctx.setFillStyle('#ffffff');
    ctx.setFontSize(32);
    ctx.fillText('得 分', W / 2, 520);

    ctx.setFillStyle('#cde3ff');
    ctx.setFontSize(30);
    ctx.fillText('用时 ' + t + '    ' + date, W / 2, 640);
    ctx.fillText('玩家: ' + nick, W / 2, 700);

    ctx.setFillStyle('#b9d4ff');
    ctx.setFontSize(26);
    ctx.fillText('快来挑战我的高分吧!', W / 2, 800);

    ctx.draw(false, () => {
      wx.canvasToTempFilePath({
        canvasId: 'posterCanvas',
        width: W,
        height: H,
        destWidth: W * 2,
        destHeight: H * 2,
        success: (res) => {
          this.posterPath = res.tempFilePath;
          this.setData({ posterSrc: res.tempFilePath });
        },
        fail: () => wx.showToast({ title: '海报生成失败', icon: 'none' })
      }, this);
    });
  },

  savePoster() {
    if (!this.posterPath) {
      wx.showToast({ title: '海报尚未生成', icon: 'none' });
      return;
    }
    wx.saveImageToPhotosAlbum({
      filePath: this.posterPath,
      success: () => wx.showToast({ title: '已保存到相册', icon: 'success' }),
      fail: (err) => {
        if (err.errMsg && err.errMsg.indexOf('auth') !== -1) {
          wx.showModal({
            title: '需要相册权限',
            content: '请在设置中允许保存图片到相册',
            success: (res) => {
              if (res.confirm) wx.openSetting();
            }
          });
        } else {
          wx.showToast({ title: '保存失败', icon: 'none' });
        }
      }
    });
  }
});