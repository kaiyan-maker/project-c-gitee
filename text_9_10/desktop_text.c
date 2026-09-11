#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

#define ID_BTN_PLAY    101
#define ID_BTN_EXIT    102
#define ID_BTN_GUESS   103
#define ID_EDIT_INPUT  201
#define ID_COMBO_DIFF  202

#define DEFAULT_REMAIN_MAX 5

static HWND hEditInput, hBtnGuess, hBtnPlay, hBtnExit;
static HWND hStaticHint, hStaticStatus, hStaticTime, hStaticRemain;
static HWND hStaticScore, hStaticBest, hCombo, hList;

static int secretNum = 0;
static int guessCount = 0;
static clock_t startTime = 0;
static int gameRunning = 0;
static int lowBound = 1;
static int highBound = 100;
static int hintShown3 = 0;

static int gameMax = 100;
static int gameMaxGuesses = 5;
static int score = 0;
static int bestScore = 0;
static char bestPath[MAX_PATH] = {0};

typedef struct _Diff
{
    const char *name;
    int max;
    int guesses;
} Diff;

static const Diff g_diffs[] =
{
    { "简单 (1-50, 7次)",   50,  7 },
    { "普通 (1-100, 5次)",  100, 5 },
    { "困难 (1-200, 4次)",  200, 4 },
};

void UpdateStatus(HWND hwnd, const char *msg)
{
    SetWindowTextA(hStaticStatus, msg);
}

void UpdateRemain(void)
{
    char buf[64];
    int remain = gameMaxGuesses - guessCount;
    if (remain < 0) remain = 0;
    sprintf(buf, "剩余次数: %d", remain);
    SetWindowTextA(hStaticRemain, remain > 0 ? buf : "已无机会");
}

void UpdateTime(void)
{
    char buf[64];
    if (gameRunning)
    {
        double elapsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        sprintf(buf, "已用时: %.1f 秒", elapsed);
    }
    else
    {
        strcpy(buf, "已用时: 0.0 秒");
    }
    SetWindowTextA(hStaticTime, buf);
}

void UpdateScore(void)
{
    char buf[64];
    sprintf(buf, "本次得分: %d", score);
    SetWindowTextA(hStaticScore, buf);
}

void UpdateBest(void)
{
    char buf[64];
    sprintf(buf, "历史最高分: %d", bestScore);
    SetWindowTextA(hStaticBest, buf);
}

void GetExeBestPath(char *out)
{
    char exe[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, exe, MAX_PATH);
    char *slash = strrchr(exe, '\\');
    if (slash) slash[1] = 0;
    else exe[0] = 0;
    sprintf(out, "%sguess_best.txt", exe);
}

int LoadBest(void)
{
    int best = 0;
    FILE *f = fopen(bestPath, "r");
    if (f)
    {
        if (fscanf(f, "%d", &best) != 1) best = 0;
        fclose(f);
    }
    return best;
}

void SaveBest(void)
{
    FILE *f = fopen(bestPath, "w");
    if (f)
    {
        fprintf(f, "%d", bestScore);
        fclose(f);
    }
}

void StartGame(HWND hwnd)
{
    int idx = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);
    if (idx == CB_ERR) idx = 1;
    if (idx < 0) idx = 0;
    if (idx > 2) idx = 2;

    gameMax = g_diffs[idx].max;
    gameMaxGuesses = g_diffs[idx].guesses;

    srand((unsigned int)time(NULL));
    secretNum = rand() % gameMax + 1;
    guessCount = 0;
    startTime = clock();
    gameRunning = 1;
    lowBound = 1;
    highBound = gameMax;
    hintShown3 = 0;
    score = 0;

    char buf[128];
    sprintf(buf, "请输入你猜的数字 (1-%d):", gameMax);
    SetWindowTextA(hStaticHint, buf);

    EnableWindow(hBtnGuess, TRUE);
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    SetWindowTextA(hEditInput, "");
    UpdateStatus(hwnd, "游戏已开始! 加油猜出数字吧");
    UpdateRemain();
    UpdateTime();
    UpdateScore();
    UpdateBest();
    SetFocus(hEditInput);
}

void AddHistory(int count, int guess, const char *result)
{
    char item[96];
    sprintf(item, "第%d次: %d -> %s", count, guess, result);
    int index = (int)SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)item);
    SendMessage(hList, LB_SETTOPINDEX, index, 0);
}

void DoGuess(HWND hwnd)
{
    if (!gameRunning) return;

    char buf[160];
    int guess = 0;
    char inputBuf[32] = {0};
    GetWindowTextA(hEditInput, inputBuf, sizeof(inputBuf));
    guess = atoi(inputBuf);

    if (guess < 1 || guess > gameMax)
    {
        sprintf(buf, "请输入 1-%d 之间的数字!", gameMax);
        UpdateStatus(hwnd, buf);
        SetWindowTextA(hEditInput, "");
        SetFocus(hEditInput);
        return;
    }

    guessCount++;
    int remain = gameMaxGuesses - guessCount;

    if (guess > secretNum)
    {
        if (guess < highBound) highBound = guess - 1;
        sprintf(buf, "猜大了! 还剩 %d 次机会", remain);
        UpdateStatus(hwnd, buf);
        AddHistory(guessCount, guess, "猜大了");
    }
    else if (guess < secretNum)
    {
        if (guess > lowBound) lowBound = guess + 1;
        sprintf(buf, "猜小了! 还剩 %d 次机会", remain);
        UpdateStatus(hwnd, buf);
        AddHistory(guessCount, guess, "猜小了");
    }
    else
    {
        double elapsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        score = (remain + 1) * 100 - (int)elapsed;
        if (score < 0) score = 0;
        if (score > bestScore)
        {
            bestScore = score;
            SaveBest();
            sprintf(buf, "恭喜你, 猜对了! 用时 %.1f 秒, 得分 %d (新纪录!)", elapsed, score);
        }
        else
        {
            sprintf(buf, "恭喜你, 猜对了! 用时 %.1f 秒, 得分 %d", elapsed, score);
        }
        UpdateStatus(hwnd, buf);
        AddHistory(guessCount, guess, "猜对了");
        gameRunning = 0;
        EnableWindow(hBtnGuess, FALSE);
    }

    if (gameMaxGuesses - guessCount == 2 && gameRunning && !hintShown3)
    {
        hintShown3 = 1;
        sprintf(buf, "提示: 答案在 %d - %d 之间, 还有 2 次机会", lowBound, highBound);
        UpdateStatus(hwnd, buf);
    }

    if (guessCount >= gameMaxGuesses && gameRunning)
    {
        sprintf(buf, "%d次都没猜对! 答案是: %d", gameMaxGuesses, secretNum);
        UpdateStatus(hwnd, buf);
        gameRunning = 0;
        EnableWindow(hBtnGuess, FALSE);
    }

    UpdateRemain();
    UpdateTime();
    UpdateScore();
    UpdateBest();
    SetWindowTextA(hEditInput, "");
    SetFocus(hEditInput);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        GetExeBestPath(bestPath);
        bestScore = LoadBest();

        CreateWindowA("static", "=== 猜数字小游戏 (桌面版) ===",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            0, 8, 540, 26, hwnd, NULL, NULL, NULL);

        CreateWindowA("static", "难度:",
            WS_CHILD | WS_VISIBLE,
            30, 47, 55, 24, hwnd, NULL, NULL, NULL);

        hCombo = CreateWindowA("combobox", NULL,
            WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
            90, 44, 180, 220, hwnd, (HMENU)ID_COMBO_DIFF, NULL, NULL);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_diffs[0].name);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_diffs[1].name);
        SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_diffs[2].name);
        SendMessage(hCombo, CB_SETCURSEL, (WPARAM)1, 0);
        SendMessage(hCombo, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hBtnPlay = CreateWindowA("button", "开始游戏",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            290, 45, 100, 32, hwnd, (HMENU)ID_BTN_PLAY, NULL, NULL);
        SendMessage(hBtnPlay, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hBtnExit = CreateWindowA("button", "退出游戏",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            410, 45, 100, 32, hwnd, (HMENU)ID_BTN_EXIT, NULL, NULL);
        SendMessage(hBtnExit, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hStaticHint = CreateWindowA("static", "请输入你猜的数字 (1-100):",
            WS_CHILD | WS_VISIBLE,
            30, 86, 270, 26, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticHint, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hEditInput = CreateWindowA("edit", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_NUMBER,
            310, 85, 110, 28, hwnd, (HMENU)ID_EDIT_INPUT, NULL, NULL);
        SendMessage(hEditInput, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hBtnGuess = CreateWindowA("button", "确定猜测",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            430, 85, 80, 28, hwnd, (HMENU)ID_BTN_GUESS, NULL, NULL);
        SendMessage(hBtnGuess, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
        EnableWindow(hBtnGuess, FALSE);

        hStaticRemain = CreateWindowA("static", "剩余次数: 5",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            30, 122, 160, 24, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticRemain, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hStaticTime = CreateWindowA("static", "已用时: 0.0 秒",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            190, 122, 160, 24, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticTime, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hStaticScore = CreateWindowA("static", "本次得分: 0",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            350, 122, 160, 24, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticScore, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hStaticStatus = CreateWindowA("static", "请选择难度并点击 \"开始游戏\"",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            30, 152, 480, 26, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticStatus, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        hStaticBest = CreateWindowA("static", "历史最高分: 0",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            30, 184, 480, 24, hwnd, NULL, NULL, NULL);
        SendMessage(hStaticBest, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        CreateWindowA("static", "--- 历史记录 ---",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            30, 214, 480, 22, hwnd, NULL, NULL, NULL);

        hList = CreateWindowA("listbox", "",
            WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL |
            LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
            30, 240, 480, 190, hwnd, NULL, NULL, NULL);
        SendMessage(hList, WM_SETFONT,
            (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);

        UpdateBest();
        break;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BTN_PLAY:
            StartGame(hwnd);
            break;
        case ID_BTN_GUESS:
            DoGuess(hwnd);
            break;
        case ID_BTN_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_RETURN)
        {
            if (gameRunning)
                DoGuess(hwnd);
        }
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "GuessNumDesktop";
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0, CLASS_NAME, "猜数字小游戏 - 桌面版",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 560, 500,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}