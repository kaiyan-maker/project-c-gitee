const diffs = [
  { name: '简单 (1-50, 7次)', max: 50, guesses: 7 },
  { name: '普通 (1-100, 5次)', max: 100, guesses: 5 },
  { name: '困难 (1-200, 4次)', max: 200, guesses: 4 }
];

Page({
  data: {
    diffs: diffs,
    diffIndex: 1,
    hintText: '请输入你猜的数字 (1-100):',
    inputVal: '',
    inputDisabled: true,
    guessDisabled: true,
    remainText: '-',
    timeText: '0.0s',
    score: 0,
    best: 0,
    status: '请选择难度后点击开始',
    statusClass: '',
    history: []
  },

  onLoad() {
    const best = Number(wx.getStorageSync('guess_best') || 0);
    this.setData({ best: best });
  },

  onUnload() {
    this.clearTimer();
  },

  clearTimer() {
    if (this.timerId) {
      clearInterval(this.timerId);
      this.timerId = null;
    }
  },

  onDiffChange(e) {
    this.setData({ diffIndex: Number(e.detail.value) });
  },

  onInput(e) {
    this.setData({ inputVal: e.detail.value });
  },

  startGame() {
    const cfg = diffs[this.data.diffIndex];
    this.secret = Math.floor(Math.random() * cfg.max) + 1;
    this.maxVal = cfg.max;
    this.maxGuess = cfg.guesses;
    this.count = 0;
    this.low = 1;
    this.high = cfg.max;
    this.hintShown = false;
    this.startT = Date.now();
    this.running = true;

    this.clearTimer();
    this.timerId = setInterval(() => this.updateTime(), 200);

    this.setData({
      hintText: '请输入你猜的数字 (1-' + cfg.max + '):',
      inputVal: '',
      inputDisabled: false,
      guessDisabled: false,
      score: 0,
      history: [],
      status: '游戏开始! 请在 ' + cfg.guesses + ' 次内猜出数字',
      statusClass: ''
    });
    this.updateRemain();
    this.updateTime();
  },

  updateRemain() {
    const r = Math.max(this.maxGuess - (this.count || 0), 0);
    this.setData({ remainText: r > 0 ? String(r) : '0' });
  },

  updateTime() {
    if (!this.running) return;
    const s = ((Date.now() - this.startT) / 1000).toFixed(1);
    this.setData({ timeText: s + 's' });
  },

  addHistory(n, v, text, cls) {
    const history = this.data.history;
    history.push({ n: n, v: v, text: text, cls: cls });
    this.setData({ history: history });
  },

  endGame() {
    this.running = false;
    this.clearTimer();
    this.setData({ guessDisabled: true, inputDisabled: true });
  },

  doGuess() {
    if (!this.running) return;
    const v = parseInt(this.data.inputVal, 10);
    if (isNaN(v) || v < 1 || v > this.maxVal) {
      this.setData({ status: '请输入 1-' + this.maxVal + ' 之间的数字!', statusClass: 'bad' });
      return;
    }
    this.count++;
    const remain = this.maxGuess - this.count;
    this.setData({ inputVal: '' });

    if (v > this.secret) {
      if (v < this.high) this.high = v - 1;
      this.setData({ status: '猜大了! 还剩 ' + remain + ' 次机会', statusClass: 'up' });
      this.addHistory(this.count, v, '猜大了', 'up');
    } else if (v < this.secret) {
      if (v > this.low) this.low = v + 1;
      this.setData({ status: '猜小了! 还剩 ' + remain + ' 次机会', statusClass: 'down' });
      this.addHistory(this.count, v, '猜小了', 'down');
    } else {
      this.endGame();
      const secs = (Date.now() - this.startT) / 1000;
      let sc = (remain + 1) * 100 - Math.floor(secs);
      if (sc < 0) sc = 0;
      let isRecord = false;
      if (sc > this.data.best) {
        wx.setStorageSync('guess_best', sc);
        this.setData({ best: sc });
        isRecord = true;
      }
      this.setData({
        score: sc,
        status: '恭喜你, 猜对了! 用时 ' + secs.toFixed(1) + ' 秒, 得分 ' + sc + (isRecord ? ' - 新纪录!' : ''),
        statusClass: 'good'
      });
      this.addHistory(this.count, v, '猜对了', 'ok');
      return;
    }

    if (this.maxGuess - this.count === 2 && !this.hintShown) {
      this.hintShown = true;
      this.setData({
        status: '提示: 答案在 ' + this.low + ' - ' + this.high + ' 之间, 还有 2 次机会',
        statusClass: 'tip'
      });
    }

    if (this.count >= this.maxGuess) {
      this.endGame();
      this.setData({
        status: this.maxGuess + '次都没猜对! 正确答案是: ' + this.secret,
        statusClass: 'bad'
      });
    }

    this.updateRemain();
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
    this.running = false;
    this.clearTimer();
    this.count = 0;
    this.setData({
      inputVal: '',
      inputDisabled: true,
      guessDisabled: true,
      remainText: '-',
      timeText: '0.0s',
      history: [],
      status: '已退出, 选择难度后点开始',
      statusClass: ''
    });
  }
});