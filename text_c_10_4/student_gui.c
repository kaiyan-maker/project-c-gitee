#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <errno.h>
#include <limits.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "comdlg32.lib")

#define APP_CLASS L"StudentManagerGuiClass"
#define APP_TITLE L"学生信息管理系统"
#define DATA_FILE L"students.txt"
#define TEMP_FILE L"students.txt.tmp"

#define IDC_LIST 1001
#define IDC_ID 1002
#define IDC_AGE 1003
#define IDC_NAME 1004
#define IDC_TEL 1005
#define IDC_SEARCH 1006
#define IDC_ADD 1007
#define IDC_UPDATE 1008
#define IDC_DELETE 1009
#define IDC_CLEAR 1010
#define IDC_REFRESH 1011
#define IDC_OPEN_FILE 1012
#define IDC_STATUS 1013
#define IDC_TITLE 1014
#define IDC_SUBTITLE 1015
#define IDC_LABEL_ID 1016
#define IDC_LABEL_AGE 1017
#define IDC_LABEL_NAME 1018
#define IDC_LABEL_TEL 1019
#define IDC_LABEL_SEARCH 1020

typedef struct Student
{
    int id;
    int age;
    wchar_t name[20];
    wchar_t tel[20];
    struct Student* next;
} Student;

static HINSTANCE g_instance;
static HWND g_main;
static HWND g_list;
static HWND g_id;
static HWND g_age;
static HWND g_name;
static HWND g_tel;
static HWND g_search;
static HWND g_status;
static HFONT g_font;
static HFONT g_title_font;
static HBRUSH g_background;
static HBRUSH g_panel_brush;
static HBRUSH g_edit_brush;
static Student* g_students;
static wchar_t g_data_path[MAX_PATH];
static int g_selected_id = -1;
static int g_loaded_count;
static int g_skipped_count;

static void show_error(HWND owner, const wchar_t* text)
{
    MessageBoxW(owner, text, APP_TITLE, MB_OK | MB_ICONERROR);
}

static void show_info(HWND owner, const wchar_t* text)
{
    MessageBoxW(owner, text, APP_TITLE, MB_OK | MB_ICONINFORMATION);
}

static int file_exists(const wchar_t* path)
{
    DWORD attributes = GetFileAttributesW(path);
    return attributes != INVALID_FILE_ATTRIBUTES &&
           (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

static int build_data_path(void)
{
    DWORD length = GetModuleFileNameW(NULL, g_data_path, MAX_PATH);
    wchar_t* slash;

    if (length == 0 || length >= MAX_PATH)
        return 0;
    slash = wcsrchr(g_data_path, L'\\');
    if (slash == NULL)
        return 0;
    slash[1] = L'\0';
    if (wcslen(g_data_path) + wcslen(DATA_FILE) >= MAX_PATH)
        return 0;
    wcscat_s(g_data_path, MAX_PATH, DATA_FILE);
    return 1;
}

static void free_students(void)
{
    Student* current = g_students;
    while (current != NULL)
    {
        Student* next = current->next;
        free(current);
        current = next;
    }
    g_students = NULL;
}

static Student* find_student(int id)
{
    Student* current;
    for (current = g_students; current != NULL; current = current->next)
    {
        if (current->id == id)
            return current;
    }
    return NULL;
}

static void insert_sorted(Student* student)
{
    Student** position = &g_students;
    while (*position != NULL && (*position)->id < student->id)
        position = &(*position)->next;
    student->next = *position;
    *position = student;
}

static int phone_is_valid(const wchar_t* phone)
{
    size_t i;
    if (wcslen(phone) != 11)
        return 0;
    for (i = 0; phone[i] != L'\0'; ++i)
    {
        if (phone[i] < L'0' || phone[i] > L'9')
            return 0;
    }
    return 1;
}

static int duplicate_phone(const wchar_t* phone, const Student* ignored)
{
    Student* current;
    for (current = g_students; current != NULL; current = current->next)
    {
        if (current != ignored && wcscmp(current->tel, phone) == 0)
            return 1;
    }
    return 0;
}

static int utf8_to_wide(const char* source, wchar_t* target, int capacity)
{
    int count = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, source, -1, target, capacity);
    return count > 0;
}

static int wide_to_utf8(const wchar_t* source, char* target, int capacity)
{
    int count = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, source, -1,
                                    target, capacity, NULL, NULL);
    return count > 0;
}

static int parse_number(const char* text, int* value)
{
    char* end;
    long number;

    errno = 0;
    number = strtol(text, &end, 10);
    if (text == end || *end != '\0' || errno == ERANGE ||
        number < INT_MIN || number > INT_MAX)
        return 0;
    *value = (int)number;
    return 1;
}

static int load_students(void)
{
    FILE* file;
    char line[1024];
    char id_text[256];
    char age_text[256];
    char name_utf8[256];
    char tel_utf8[256];
    char extra[2];

    g_loaded_count = 0;
    g_skipped_count = 0;
    free_students();

    file = _wfopen(g_data_path, L"rb");
    if (file == NULL)
    {
        if (errno == ENOENT)
            return 1;
        return 0;
    }

    while (fgets(line, (int)sizeof(line), file) != NULL)
    {
        Student* student;
        Student* current;
        wchar_t name[20];
        wchar_t tel[20];
        int id;
        int age;
        int valid = 1;

        if (strchr(line, '\n') == NULL && !feof(file))
        {
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF)
                ;
            ++g_skipped_count;
            continue;
        }
        line[strcspn(line, "\r\n")] = '\0';
        if (sscanf_s(line, "%255s %255s %255s %255s %1s",
                     id_text, (unsigned)_countof(id_text),
                     age_text, (unsigned)_countof(age_text),
                     name_utf8, (unsigned)_countof(name_utf8),
                     tel_utf8, (unsigned)_countof(tel_utf8),
                     extra, (unsigned)_countof(extra)) != 4 ||
            !parse_number(id_text, &id) || !parse_number(age_text, &age) ||
            id <= 0 || age < 0 || age > 150 ||
            !utf8_to_wide(name_utf8, name, (int)_countof(name)) ||
            !utf8_to_wide(tel_utf8, tel, (int)_countof(tel)) ||
            !phone_is_valid(tel))
        {
            ++g_skipped_count;
            continue;
        }

        for (current = g_students; current != NULL; current = current->next)
        {
            if (current->id == id || wcscmp(current->tel, tel) == 0)
            {
                valid = 0;
                break;
            }
        }
        if (!valid)
        {
            ++g_skipped_count;
            continue;
        }

        student = (Student*)calloc(1, sizeof(Student));
        if (student == NULL)
        {
            fclose(file);
            return 0;
        }
        student->id = id;
        student->age = age;
        wcscpy_s(student->name, _countof(student->name), name);
        wcscpy_s(student->tel, _countof(student->tel), tel);
        insert_sorted(student);
        ++g_loaded_count;
    }

    if (ferror(file) || fclose(file) != 0)
        return 0;
    return 1;
}

static int save_students(void)
{
    wchar_t temporary[MAX_PATH];
    FILE* file;
    Student* current;

    if (swprintf_s(temporary, _countof(temporary), L"%s.tmp", g_data_path) < 0)
        return 0;
    file = _wfopen(temporary, L"wb");
    if (file == NULL)
        return 0;

    for (current = g_students; current != NULL; current = current->next)
    {
        char name_utf8[128];
        char tel_utf8[128];
        if (!wide_to_utf8(current->name, name_utf8, (int)_countof(name_utf8)) ||
            !wide_to_utf8(current->tel, tel_utf8, (int)_countof(tel_utf8)) ||
            fprintf(file, "%d\t%d\t%s\t%s\n",
                    current->id, current->age, name_utf8, tel_utf8) < 0)
        {
            fclose(file);
            DeleteFileW(temporary);
            return 0;
        }
    }
    if (fflush(file) != 0 || fclose(file) != 0)
    {
        DeleteFileW(temporary);
        return 0;
    }
    if (!MoveFileExW(temporary, g_data_path,
                     MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
    {
        DeleteFileW(temporary);
        return 0;
    }
    return 1;
}

static void set_status(const wchar_t* text)
{
    SetWindowTextW(g_status, text);
}

static void refresh_list(const wchar_t* filter)
{
    Student* current;
    wchar_t id_text[32];
    wchar_t age_text[32];
    int count = 0;
    int has_filter = filter != NULL && filter[0] != L'\0';

    ListView_DeleteAllItems(g_list);
    for (current = g_students; current != NULL; current = current->next)
    {
        LVITEMW item;
        wchar_t full[128];

        swprintf_s(id_text, _countof(id_text), L"%d", current->id);
        swprintf_s(age_text, _countof(age_text), L"%d", current->age);
        swprintf_s(full, _countof(full), L"%s %s %s %s",
                   id_text, age_text, current->name, current->tel);
        if (has_filter && wcsstr(full, filter) == NULL)
            continue;

        ZeroMemory(&item, sizeof(item));
        item.mask = LVIF_TEXT | LVIF_PARAM;
        item.iItem = count;
        item.pszText = id_text;
        item.lParam = (LPARAM)current->id;
        ListView_InsertItem(g_list, &item);
        ListView_SetItemText(g_list, count, 1, age_text);
        ListView_SetItemText(g_list, count, 2, current->name);
        ListView_SetItemText(g_list, count, 3, current->tel);
        ++count;
    }

    {
        wchar_t status[128];
        if (has_filter)
            swprintf_s(status, _countof(status), L"找到 %d 条结果", count);
        else
            swprintf_s(status, _countof(status), L"共 %d 条学生信息 · 数据自动保存", count);
        set_status(status);
    }
}

static void clear_form(void)
{
    SetWindowTextW(g_id, L"");
    SetWindowTextW(g_age, L"");
    SetWindowTextW(g_name, L"");
    SetWindowTextW(g_tel, L"");
    g_selected_id = -1;
    ListView_SetItemState(g_list, -1, 0, LVIS_SELECTED | LVIS_FOCUSED);
    SetFocus(g_id);
}

static void fill_form_from_selection(void)
{
    int selected = ListView_GetNextItem(g_list, -1, LVNI_SELECTED);
    LVITEMW item;
    Student* student;
    wchar_t text[32];

    if (selected < 0)
        return;
    ZeroMemory(&item, sizeof(item));
    item.mask = LVIF_PARAM;
    item.iItem = selected;
    if (!ListView_GetItem(g_list, &item))
        return;
    student = find_student((int)item.lParam);
    if (student == NULL)
        return;

    g_selected_id = student->id;
    swprintf_s(text, _countof(text), L"%d", student->id);
    SetWindowTextW(g_id, text);
    swprintf_s(text, _countof(text), L"%d", student->age);
    SetWindowTextW(g_age, text);
    SetWindowTextW(g_name, student->name);
    SetWindowTextW(g_tel, student->tel);
    set_status(L"已选择记录，可修改或删除");
}

static int parse_edit_integer(HWND edit, int minimum, int maximum, int* value)
{
    wchar_t text[64];
    wchar_t* end;
    long number;

    GetWindowTextW(edit, text, (int)_countof(text));
    errno = 0;
    number = wcstol(text, &end, 10);
    if (text == end || *end != L'\0' || errno == ERANGE ||
        number < minimum || number > maximum)
        return 0;
    *value = (int)number;
    return 1;
}

static int read_form(Student* value)
{
    if (!parse_edit_integer(g_id, 1, INT_MAX, &value->id))
    {
        show_error(g_main, L"学号必须是大于 0 的整数。");
        SetFocus(g_id);
        return 0;
    }
    if (!parse_edit_integer(g_age, 0, 150, &value->age))
    {
        show_error(g_main, L"年龄必须是 0 到 150 之间的整数。");
        SetFocus(g_age);
        return 0;
    }
    GetWindowTextW(g_name, value->name, (int)_countof(value->name));
    GetWindowTextW(g_tel, value->tel, (int)_countof(value->tel));
    if (value->name[0] == L'\0')
    {
        show_error(g_main, L"姓名不能为空。");
        SetFocus(g_name);
        return 0;
    }
    if (wcspbrk(value->name, L" \t\r\n") != NULL)
    {
        show_error(g_main, L"姓名中不能包含空格。");
        SetFocus(g_name);
        return 0;
    }
    if (!phone_is_valid(value->tel))
    {
        show_error(g_main, L"电话必须是 11 位数字。");
        SetFocus(g_tel);
        return 0;
    }
    value->next = NULL;
    return 1;
}

static void add_student(void)
{
    Student input;
    Student* student;

    ZeroMemory(&input, sizeof(input));
    if (!read_form(&input))
        return;
    if (find_student(input.id) != NULL)
    {
        show_error(g_main, L"这个学号已经存在。");
        return;
    }
    if (duplicate_phone(input.tel, NULL))
    {
        show_error(g_main, L"这个电话号码已经存在。");
        return;
    }

    student = (Student*)malloc(sizeof(Student));
    if (student == NULL)
    {
        show_error(g_main, L"内存不足，无法添加记录。");
        return;
    }
    *student = input;
    insert_sorted(student);
    if (!save_students())
    {
        Student** position = &g_students;
        while (*position != student)
            position = &(*position)->next;
        *position = student->next;
        free(student);
        show_error(g_main, L"无法保存数据，添加操作已撤销。");
        return;
    }
    refresh_list(NULL);
    clear_form();
    set_status(L"添加成功，数据已保存");
}

static void update_student(void)
{
    Student input;
    Student* student;
    Student** position;
    Student backup;

    if (g_selected_id < 0)
    {
        show_info(g_main, L"请先从表格中选择要修改的记录。");
        return;
    }
    student = find_student(g_selected_id);
    if (student == NULL)
    {
        show_error(g_main, L"选中的记录已经不存在，请刷新后重试。");
        return;
    }

    ZeroMemory(&input, sizeof(input));
    if (!read_form(&input))
        return;
    if (input.id != g_selected_id && find_student(input.id) != NULL)
    {
        show_error(g_main, L"修改后的学号已经存在。");
        return;
    }
    if (duplicate_phone(input.tel, student))
    {
        show_error(g_main, L"修改后的电话号码已经存在。");
        return;
    }

    backup = *student;
    position = &g_students;
    while (*position != student)
        position = &(*position)->next;
    *position = student->next;
    *student = input;
    insert_sorted(student);

    if (!save_students())
    {
        position = &g_students;
        while (*position != student)
            position = &(*position)->next;
        *position = student->next;
        *student = backup;
        insert_sorted(student);
        show_error(g_main, L"无法保存数据，修改操作已撤销。");
        return;
    }
    refresh_list(NULL);
    clear_form();
    set_status(L"修改成功，数据已保存");
}

static void delete_student(void)
{
    Student** position;
    Student* student;
    Student* next;

    if (g_selected_id < 0)
    {
        show_info(g_main, L"请先从表格中选择要删除的记录。");
        return;
    }
    if (MessageBoxW(g_main, L"确定要删除选中的学生信息吗？",
                    APP_TITLE, MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
        return;

    position = &g_students;
    while (*position != NULL && (*position)->id != g_selected_id)
        position = &(*position)->next;
    if (*position == NULL)
    {
        show_error(g_main, L"选中的记录已经不存在。");
        return;
    }
    student = *position;
    next = student->next;
    *position = next;

    if (!save_students())
    {
        insert_sorted(student);
        show_error(g_main, L"无法保存数据，删除操作已撤销。");
        return;
    }
    free(student);
    refresh_list(NULL);
    clear_form();
    set_status(L"删除成功，数据已保存");
}

static void do_search(void)
{
    wchar_t text[64];
    GetWindowTextW(g_search, text, (int)_countof(text));
    refresh_list(text);
}

static void reload_students(void)
{
    if (!load_students())
    {
        show_error(g_main, L"无法读取数据文件。当前列表保持不变的操作暂不可用。");
        return;
    }
    refresh_list(NULL);
    clear_form();
    if (g_skipped_count > 0)
    {
        wchar_t message[128];
        swprintf_s(message, _countof(message),
                   L"已加载 %d 条记录，跳过 %d 条无效或重复记录。",
                   g_loaded_count, g_skipped_count);
        show_info(g_main, message);
    }
}

static HWND make_control(const wchar_t* class_name, const wchar_t* text,
                         DWORD style, int id)
{
    HWND control = CreateWindowExW(
        0, class_name, text, WS_CHILD | WS_VISIBLE | style,
        0, 0, 10, 10, g_main, (HMENU)(INT_PTR)id, g_instance, NULL);
    if (control != NULL)
        SendMessageW(control, WM_SETFONT, (WPARAM)g_font, TRUE);
    return control;
}

static void create_columns(void)
{
    const wchar_t* names[] = {L"学号", L"年龄", L"姓名", L"电话"};
    int widths[] = {120, 90, 180, 210};
    int i;
    for (i = 0; i < 4; ++i)
    {
        LVCOLUMNW column;
        ZeroMemory(&column, sizeof(column));
        column.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
        column.pszText = (LPWSTR)names[i];
        column.cx = widths[i];
        column.iSubItem = i;
        ListView_InsertColumn(g_list, i, &column);
    }
}

static void layout_controls(HWND window)
{
    RECT client;
    int width;
    int height;
    int margin = 24;
    int title_height = 72;
    int panel_width = 275;
    int gap = 22;
    int table_x;
    int table_width;
    int table_top = 124;
    int table_bottom;
    int x;
    int y;
    int edit_width;
    HDWP layout;

    GetClientRect(window, &client);
    width = client.right;
    height = client.bottom;
    table_bottom = height - 54;
    if (table_bottom < table_top + 160)
        table_bottom = table_top + 160;
    table_x = margin;
    table_width = width - panel_width - gap - margin * 2;
    if (table_width < 420)
        table_width = 420;
    x = table_x + table_width + gap;
    edit_width = panel_width;
    y = table_top;

    layout = BeginDeferWindowPos(20);
#define MOVE(id, px, py, pw, ph) layout = DeferWindowPos(layout, GetDlgItem(window, id), NULL, px, py, pw, ph, SWP_NOZORDER)
    MOVE(IDC_TITLE, margin, 20, width - margin * 2, 34);
    MOVE(IDC_SUBTITLE, margin, 57, width - margin * 2, 24);
    MOVE(IDC_LABEL_SEARCH, margin, 91, 48, 24);
    MOVE(IDC_SEARCH, margin + 50, 88, 260, 31);
    MOVE(IDC_REFRESH, margin + 320, 88, 88, 31);
    MOVE(IDC_OPEN_FILE, margin + 416, 88, 110, 31);
    MOVE(IDC_LIST, table_x, table_top, table_width, table_bottom - table_top);

    MOVE(IDC_LABEL_ID, x, y, edit_width, 22);
    MOVE(IDC_ID, x, y + 25, edit_width, 33);
    y += 73;
    MOVE(IDC_LABEL_AGE, x, y, edit_width, 22);
    MOVE(IDC_AGE, x, y + 25, edit_width, 33);
    y += 73;
    MOVE(IDC_LABEL_NAME, x, y, edit_width, 22);
    MOVE(IDC_NAME, x, y + 25, edit_width, 33);
    y += 73;
    MOVE(IDC_LABEL_TEL, x, y, edit_width, 22);
    MOVE(IDC_TEL, x, y + 25, edit_width, 33);
    y += 78;
    MOVE(IDC_ADD, x, y, 130, 38);
    MOVE(IDC_UPDATE, x + 145, y, 130, 38);
    y += 50;
    MOVE(IDC_DELETE, x, y, 130, 38);
    MOVE(IDC_CLEAR, x + 145, y, 130, 38);
    MOVE(IDC_STATUS, margin, height - 39, width - margin * 2, 25);
#undef MOVE
    EndDeferWindowPos(layout);
}

static void paint_background(HWND window)
{
    PAINTSTRUCT paint;
    RECT client;
    RECT panel;
    HDC dc = BeginPaint(window, &paint);

    GetClientRect(window, &client);
    FillRect(dc, &client, g_background);
    panel.left = client.right - 323;
    panel.top = 107;
    panel.right = client.right - 24;
    panel.bottom = client.bottom - 53;
    FillRect(dc, &panel, g_panel_brush);
    EndPaint(window, &paint);
}

static LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    switch (message)
    {
    case WM_CREATE:
    {
        LOGFONTW log_font;
        INITCOMMONCONTROLSEX controls;

        g_main = window;
        controls.dwSize = sizeof(controls);
        controls.dwICC = ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES;
        InitCommonControlsEx(&controls);

        ZeroMemory(&log_font, sizeof(log_font));
        log_font.lfHeight = -18;
        wcscpy_s(log_font.lfFaceName, LF_FACESIZE, L"Microsoft YaHei UI");
        g_font = CreateFontIndirectW(&log_font);
        log_font.lfHeight = -28;
        log_font.lfWeight = FW_SEMIBOLD;
        g_title_font = CreateFontIndirectW(&log_font);
        g_background = CreateSolidBrush(RGB(244, 247, 248));
        g_panel_brush = CreateSolidBrush(RGB(255, 255, 255));
        g_edit_brush = CreateSolidBrush(RGB(255, 255, 255));

        make_control(L"STATIC", APP_TITLE, SS_LEFT, IDC_TITLE);
        SendDlgItemMessageW(window, IDC_TITLE, WM_SETFONT, (WPARAM)g_title_font, TRUE);
        make_control(L"STATIC", L"集中管理学生档案，所有修改自动保存到本地文件",
                     SS_LEFT, IDC_SUBTITLE);
        make_control(L"STATIC", L"搜索", SS_LEFT, IDC_LABEL_SEARCH);
        g_search = make_control(L"EDIT", L"", WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL,
                                IDC_SEARCH);
        make_control(L"BUTTON", L"刷新", WS_TABSTOP | BS_PUSHBUTTON, IDC_REFRESH);
        make_control(L"BUTTON", L"打开数据文件", WS_TABSTOP | BS_PUSHBUTTON, IDC_OPEN_FILE);

        g_list = CreateWindowExW(WS_EX_CLIENTEDGE, WC_LISTVIEWW, L"",
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT |
                    LVS_SINGLESEL | LVS_SHOWSELALWAYS,
                    0, 0, 10, 10, window, (HMENU)(INT_PTR)IDC_LIST, g_instance, NULL);
        SendMessageW(g_list, WM_SETFONT, (WPARAM)g_font, TRUE);
        ListView_SetExtendedListViewStyle(g_list,
                    LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);
        create_columns();

        make_control(L"STATIC", L"学号", SS_LEFT, IDC_LABEL_ID);
        g_id = make_control(L"EDIT", L"", WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL |
                            ES_NUMBER, IDC_ID);
        make_control(L"STATIC", L"年龄", SS_LEFT, IDC_LABEL_AGE);
        g_age = make_control(L"EDIT", L"", WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL |
                             ES_NUMBER, IDC_AGE);
        make_control(L"STATIC", L"姓名", SS_LEFT, IDC_LABEL_NAME);
        g_name = make_control(L"EDIT", L"", WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL,
                              IDC_NAME);
        make_control(L"STATIC", L"电话", SS_LEFT, IDC_LABEL_TEL);
        g_tel = make_control(L"EDIT", L"", WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL |
                             ES_NUMBER, IDC_TEL);
        SendMessageW(g_id, EM_SETLIMITTEXT, 10, 0);
        SendMessageW(g_age, EM_SETLIMITTEXT, 3, 0);
        SendMessageW(g_name, EM_SETLIMITTEXT, 19, 0);
        SendMessageW(g_tel, EM_SETLIMITTEXT, 11, 0);

        make_control(L"BUTTON", L"添加", WS_TABSTOP | BS_DEFPUSHBUTTON, IDC_ADD);
        make_control(L"BUTTON", L"保存修改", WS_TABSTOP | BS_PUSHBUTTON, IDC_UPDATE);
        make_control(L"BUTTON", L"删除", WS_TABSTOP | BS_PUSHBUTTON, IDC_DELETE);
        make_control(L"BUTTON", L"清空表单", WS_TABSTOP | BS_PUSHBUTTON, IDC_CLEAR);
        g_status = make_control(L"STATIC", L"", SS_LEFT, IDC_STATUS);

        if (!build_data_path())
        {
            show_error(window, L"无法确定数据文件位置，程序将退出。");
            return -1;
        }
        if (!load_students())
        {
            show_error(window, L"无法读取 students.txt，请检查文件权限或文件占用。");
            return -1;
        }
        refresh_list(NULL);
        if (g_skipped_count > 0)
        {
            wchar_t message_text[128];
            swprintf_s(message_text, _countof(message_text),
                       L"已加载 %d 条记录，跳过 %d 条无效或重复记录。",
                       g_loaded_count, g_skipped_count);
            show_info(window, message_text);
        }
        return 0;
    }

    case WM_SIZE:
        if (g_list != NULL)
            layout_controls(window);
        return 0;

    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* limits = (MINMAXINFO*)l_param;
        limits->ptMinTrackSize.x = 900;
        limits->ptMinTrackSize.y = 620;
        return 0;
    }

    case WM_COMMAND:
        switch (LOWORD(w_param))
        {
        case IDC_ADD:
            add_student();
            return 0;
        case IDC_UPDATE:
            update_student();
            return 0;
        case IDC_DELETE:
            delete_student();
            return 0;
        case IDC_CLEAR:
            clear_form();
            return 0;
        case IDC_REFRESH:
            reload_students();
            return 0;
        case IDC_OPEN_FILE:
            if (!file_exists(g_data_path))
            {
                if (!save_students())
                {
                    show_error(window, L"无法创建数据文件。");
                    return 0;
                }
            }
            ShellExecuteW(window, L"open", g_data_path, NULL, NULL, SW_SHOWNORMAL);
            return 0;
        case IDC_SEARCH:
            if (HIWORD(w_param) == EN_CHANGE)
                do_search();
            return 0;
        default:
            break;
        }
        break;

    case WM_NOTIFY:
        if (((LPNMHDR)l_param)->idFrom == IDC_LIST &&
            ((LPNMHDR)l_param)->code == LVN_ITEMCHANGED)
        {
            LPNMLISTVIEW change = (LPNMLISTVIEW)l_param;
            if ((change->uChanged & LVIF_STATE) &&
                (change->uNewState & LVIS_SELECTED))
                fill_form_from_selection();
        }
        return 0;

    case WM_CTLCOLORSTATIC:
        SetBkMode((HDC)w_param, TRANSPARENT);
        SetTextColor((HDC)w_param, RGB(38, 50, 56));
        return (LRESULT)g_background;

    case WM_CTLCOLOREDIT:
        SetBkColor((HDC)w_param, RGB(255, 255, 255));
        SetTextColor((HDC)w_param, RGB(22, 32, 38));
        return (LRESULT)g_edit_brush;

    case WM_ERASEBKGND:
        return 1;

    case WM_PAINT:
        paint_background(window);
        return 0;

    case WM_DESTROY:
        free_students();
        if (g_font != NULL)
            DeleteObject(g_font);
        if (g_title_font != NULL)
            DeleteObject(g_title_font);
        if (g_background != NULL)
            DeleteObject(g_background);
        if (g_panel_brush != NULL)
            DeleteObject(g_panel_brush);
        if (g_edit_brush != NULL)
            DeleteObject(g_edit_brush);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(window, message, w_param, l_param);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE previous, PWSTR command_line, int show)
{
    WNDCLASSEXW window_class;
    HWND window;
    MSG message;
    HACCEL accelerators = NULL;

    (void)previous;
    (void)command_line;
    g_instance = instance;

    ZeroMemory(&window_class, sizeof(window_class));
    window_class.cbSize = sizeof(window_class);
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = window_proc;
    window_class.hInstance = instance;
    window_class.hIcon = LoadIconW(NULL, IDI_APPLICATION);
    window_class.hCursor = LoadCursorW(NULL, IDC_ARROW);
    window_class.hbrBackground = NULL;
    window_class.lpszClassName = APP_CLASS;
    window_class.hIconSm = LoadIconW(NULL, IDI_APPLICATION);

    if (!RegisterClassExW(&window_class))
    {
        show_error(NULL, L"无法注册程序窗口。");
        return EXIT_FAILURE;
    }

    window = CreateWindowExW(
        0, APP_CLASS, APP_TITLE, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1120, 720,
        NULL, NULL, instance, NULL);
    if (window == NULL)
        return EXIT_FAILURE;

    ShowWindow(window, show);
    UpdateWindow(window);

    while (GetMessageW(&message, NULL, 0, 0) > 0)
    {
        if (!TranslateAcceleratorW(window, accelerators, &message) &&
            !IsDialogMessageW(window, &message))
        {
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }
    return (int)message.wParam;
}

