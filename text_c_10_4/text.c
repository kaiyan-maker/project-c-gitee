#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define DATA_FILE "students.txt"
#define TEMP_FILE "students.txt.tmp"

/* 学生管理系统：带头结点的有序单链表，按学号升序保存。 */
typedef struct StudentNode
{
    int id;
    int age;
    char name[20];
    char tel[20];
    struct StudentNode* next;
} StudentNode;

static int InitLink(StudentNode** s);
static void welcome(void);
static void emun(void);
static int ReadLine(char* buffer, int size);
static int ParseInteger(const char* text, int* value);
static int ReadInteger(const char* prompt, int* value);
static StudentNode* FindById(StudentNode* h, int id);
static int ReadStudent(StudentNode* h, const StudentNode* excluded, StudentNode* s);
static int LocateElem(StudentNode* h, StudentNode s);
static int InsertLink(StudentNode* h, int num, StudentNode s);
static int SaveToFile(StudentNode* h);
static int LoadFromFile(StudentNode* h);
static void Add(StudentNode* h);
static void Display(StudentNode* h);
static void Modify(StudentNode* h);
static void DelStudent(StudentNode* h, int id);
static void Find(StudentNode* h);
static void exit_system(StudentNode** h);

static int InitLink(StudentNode** s)
{
    if (s == NULL)
        return 0;
    *s = (StudentNode*)calloc(1, sizeof(StudentNode));
    if (*s == NULL)
    {
        printf("内存分配失败\n");
        return 0;
    }
    return 1;
}

static void welcome(void)
{
    printf("------------------------------------------------------\n");
    printf("                欢迎使用学生管理系统\n");
    printf("------------------------------------------------------\n");
}

static void emun(void)
{
    printf("\n------------------------------------------------------\n");
    printf("            1. 添加信息     2. 显示信息\n");
    printf("            3. 修改信息     4. 删除信息\n");
    printf("            5. 查找信息     6. 退出系统\n");
    printf("------------------------------------------------------\n");
}

/* 返回 1 表示成功，0 表示输入结束，-1 表示输入过长。
   过长的输入整行丢弃，避免影响下一次读取。 */
static int ReadLine(char* buffer, int size)
{
    size_t length;
    int ch;

    if (fgets(buffer, size, stdin) == NULL)
        return 0;
    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
        return 1;
    }

    ch = getchar();
    if (ch == '\n' || ch == EOF)
        return 1;
    while (ch != '\n' && ch != EOF)
        ch = getchar();
    printf("输入过长，请重新输入。\n");
    return -1;
}

static int ParseInteger(const char* text, int* value)
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

static int ReadInteger(const char* prompt, int* value)
{
    char line[256];
    char token[256];
    char extra[2];
    int result;

    for (;;)
    {
        printf("%s", prompt);
        fflush(stdout);
        result = ReadLine(line, (int)sizeof(line));
        if (result == 0)
            return 0;
        if (result < 0)
            continue;
        if (sscanf(line, "%255s %1s", token, extra) == 1 &&
            ParseInteger(token, value))
            return 1;
        printf("请输入一个有效的整数。\n");
    }
}

static StudentNode* FindById(StudentNode* h, int id)
{
    StudentNode* p;
    if (h == NULL)
        return NULL;
    for (p = h->next; p != NULL; p = p->next)
    {
        if (p->id == id)
            return p;
    }
    return NULL;
}

static int ReadStudent(StudentNode* h, const StudentNode* excluded, StudentNode* s)
{
    char line[256];
    char idText[256];
    char ageText[256];
    char nameText[256];
    char telText[256];
    char extra[2];
    StudentNode* p;
    size_t i;
    int result;
    int valid;

    for (;;)
    {
        printf("请输入学号、年龄、姓名、电话（用空格分隔）：");
        fflush(stdout);
        result = ReadLine(line, (int)sizeof(line));
        if (result == 0)
            return 0;
        if (result < 0)
            continue;

        if (sscanf(line, "%255s %255s %255s %255s %1s",
                   idText, ageText, nameText, telText, extra) != 4 ||
            !ParseInteger(idText, &s->id) ||
            !ParseInteger(ageText, &s->age) ||
            strlen(nameText) >= sizeof(s->name))
        {
            printf("格式错误：需要学号、年龄、姓名、电话四项；姓名不能含空格，且不能超过19字节。\n");
            continue;
        }
        if (s->id <= 0 || s->age < 0 || s->age > 150)
        {
            printf("学号必须大于0，年龄必须在0到150之间。\n");
            continue;
        }
        valid = strlen(telText) == 11;
        for (i = 0; valid && telText[i] != '\0'; ++i)
        {
            if (telText[i] < '0' || telText[i] > '9')
                valid = 0;
        }
        if (!valid)
        {
            printf("电话必须为11位数字，请重新输入。\n");
            continue;
        }

        valid = 1;
        for (p = h->next; p != NULL; p = p->next)
        {
            if (p == excluded)
                continue;
            if (p->id == s->id || strcmp(p->tel, telText) == 0)
            {
                printf("学号或电话重复，请重新输入。\n");
                valid = 0;
                break;
            }
        }
        if (valid)
        {
            strcpy(s->name, nameText);
            strcpy(s->tel, telText);
            s->next = NULL;
            return 1;
        }
    }
}

static int LocateElem(StudentNode* h, StudentNode s)
{
    int position = 1;
    StudentNode* p;
    if (h == NULL)
        return -1;
    for (p = h->next; p != NULL && p->id < s.id; p = p->next)
        ++position;
    return position;
}

static int InsertLink(StudentNode* h, int num, StudentNode s)
{
    StudentNode* previous = h;
    StudentNode* node;
    int position;

    if (h == NULL || num < 1)
        return 0;
    for (position = 1; position < num && previous != NULL; ++position)
        previous = previous->next;
    if (previous == NULL)
    {
        printf("插入节点的位置有误\n");
        return 0;
    }

    node = (StudentNode*)malloc(sizeof(StudentNode));
    if (node == NULL)
    {
        printf("申请节点失败\n");
        return 0;
    }
    *node = s;
    node->next = previous->next;
    previous->next = node;
    return 1;
}

/* 先写临时文件，成功后再替换旧文件，避免写入失败破坏原数据。 */
static int SaveToFile(StudentNode* h)
{
    FILE* file;
    StudentNode* p;
    int failed = 0;

    if (h == NULL)
        return 0;
    file = fopen(TEMP_FILE, "w");
    if (file == NULL)
    {
        printf("无法创建临时文件 %s，保存失败；数据仍保留在内存中。\n", TEMP_FILE);
        return 0;
    }

    for (p = h->next; p != NULL; p = p->next)
    {
        if (fprintf(file, "%d\t%d\t%s\t%s\n",
                    p->id, p->age, p->name, p->tel) < 0)
        {
            failed = 1;
            break;
        }
    }
    if (fclose(file) != 0)
        failed = 1;
    if (failed)
    {
        remove(TEMP_FILE);
        printf("写入文件时发生错误，保存失败；原数据文件未被替换。\n");
        return 0;
    }
#ifdef _WIN32
    if (!MoveFileExA(TEMP_FILE, DATA_FILE,
                    MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
#else
    if (rename(TEMP_FILE, DATA_FILE) != 0)
#endif
    {
        remove(TEMP_FILE);
        printf("无法替换数据文件 %s，保存失败；数据仍保留在内存中。\n", DATA_FILE);
        return 0;
    }
    return 1;
}

/* 程序启动时读取已有数据；无文件表示首次运行，不属于错误。 */
static int LoadFromFile(StudentNode* h)
{
    FILE* file;
    char line[512];
    char idText[256];
    char ageText[256];
    char name[256];
    char tel[256];
    char extra[2];
    StudentNode s;
    StudentNode* p;
    size_t i;
    int loaded = 0;
    int skipped = 0;
    int valid;

    if (h == NULL)
        return 0;
    file = fopen(DATA_FILE, "r");
    if (file == NULL)
    {
        if (errno == ENOENT)
            return 1;
        printf("无法打开数据文件 %s，已停止运行以保护原数据。\n", DATA_FILE);
        return 0;
    }

    while (fgets(line, (int)sizeof(line), file) != NULL)
    {
        if (strchr(line, '\n') == NULL && !feof(file))
        {
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF)
                ;
            ++skipped;
            continue;
        }
        if (sscanf(line, "%255s %255s %255s %255s %1s",
                   idText, ageText, name, tel, extra) != 4 ||
            !ParseInteger(idText, &s.id) || !ParseInteger(ageText, &s.age) ||
            s.id <= 0 || s.age < 0 || s.age > 150 ||
            strlen(name) >= sizeof(s.name) || strlen(tel) != 11)
        {
            ++skipped;
            continue;
        }

        valid = 1;
        for (i = 0; tel[i] != '\0'; ++i)
        {
            if (tel[i] < '0' || tel[i] > '9')
            {
                valid = 0;
                break;
            }
        }
        for (p = h->next; valid && p != NULL; p = p->next)
        {
            if (p->id == s.id || strcmp(p->tel, tel) == 0)
                valid = 0;
        }
        if (!valid)
        {
            ++skipped;
            continue;
        }

        strcpy(s.name, name);
        strcpy(s.tel, tel);
        s.next = NULL;
        if (!InsertLink(h, LocateElem(h, s), s))
        {
            fclose(file);
            return 0;
        }
        ++loaded;
    }

    if (ferror(file))
    {
        printf("读取数据文件 %s 时发生错误。\n", DATA_FILE);
        fclose(file);
        return 0;
    }
    if (fclose(file) != 0)
    {
        printf("关闭数据文件时发生错误，已停止运行以保护原数据。\n");
        return 0;
    }
    printf("已从 %s 读取 %d 条学生信息。\n", DATA_FILE, loaded);
    if (skipped > 0)
        printf("数据文件中有 %d 条无效或重复记录，已跳过。\n", skipped);
    return 1;
}

static void Add(StudentNode* h)
{
    StudentNode s;
    if (h == NULL)
        return;
    if (ReadStudent(h, NULL, &s) && InsertLink(h, LocateElem(h, s), s))
    {
        printf("插入数据成功\n");
        SaveToFile(h);
    }
}

static void Display(StudentNode* h)
{
    StudentNode* p;
    if (h == NULL)
        return;
    if (h->next == NULL)
    {
        printf("暂无学生信息\n");
        return;
    }
    printf("学号 年龄 姓名 电话\n");
    for (p = h->next; p != NULL; p = p->next)
        printf("%d %d %s %s\n", p->id, p->age, p->name, p->tel);
}

static void Modify(StudentNode* h)
{
    int id;
    StudentNode s;
    StudentNode* node;
    StudentNode* previous;

    if (h == NULL || !ReadInteger("请输入需要修改的学生的学号：", &id))
        return;
    node = FindById(h, id);
    if (node == NULL)
    {
        printf("学生不存在\n");
        return;
    }
    /* 先验证新信息，再重用原节点；输入失败时保留原来的记录。 */
    if (!ReadStudent(h, node, &s))
        return;
    previous = h;
    while (previous->next != node)
        previous = previous->next;
    previous->next = node->next;

    previous = h;
    while (previous->next != NULL && previous->next->id < s.id)
        previous = previous->next;
    *node = s;
    node->next = previous->next;
    previous->next = node;
    printf("信息修改成功\n");
    SaveToFile(h);
}

static void DelStudent(StudentNode* h, int id)
{
    StudentNode* previous;
    StudentNode* node;
    if (h == NULL)
        return;
    previous = h;
    while (previous->next != NULL)
    {
        node = previous->next;
        if (node->id == id)
        {
            previous->next = node->next;
            free(node);
            printf("删除信息成功\n");
            SaveToFile(h);
            return;
        }
        previous = node;
    }
    printf("学生不存在\n");
}

static void Find(StudentNode* h)
{
    int id;
    StudentNode* p;
    if (h == NULL || !ReadInteger("请输入要查找的学生的学号：", &id))
        return;
    p = FindById(h, id);
    if (p == NULL)
        printf("学号不存在\n");
    else
        printf("%d %d %s %s\n", p->id, p->age, p->name, p->tel);
}

static void exit_system(StudentNode** h)
{
    StudentNode* p;
    StudentNode* next;
    if (h == NULL)
        return;
    p = *h;
    while (p != NULL)
    {
        next = p->next;
        free(p);
        p = next;
    }
    *h = NULL;
}

int main(void)
{
    int choice;
    int id;
    StudentNode* head = NULL;

    if (!InitLink(&head))
        return EXIT_FAILURE;
    if (!LoadFromFile(head))
    {
        exit_system(&head);
        return EXIT_FAILURE;
    }
    welcome();

    for (;;)
    {
        emun();
        if (!ReadInteger("请输入选项：", &choice))
            break;
        switch (choice)
        {
        case 1:
            Add(head);
            break;
        case 2:
            Display(head);
            break;
        case 3:
            Modify(head);
            break;
        case 4:
            if (ReadInteger("请输入要删除的学生的学号：", &id))
                DelStudent(head, id);
            break;
        case 5:
            Find(head);
            break;
        case 6:
            if (!SaveToFile(head))
            {
                printf("请解决文件写入问题后，再选择6保存并退出。\n");
                break;
            }
            exit_system(&head);
            printf("已退出系统\n");
            return EXIT_SUCCESS;
        default:
            printf("输入的选项不符合要求，请输入1到6。\n");
            break;
        }
    }

    if (!SaveToFile(head))
    {
        exit_system(&head);
        return EXIT_FAILURE;
    }
    exit_system(&head);
    printf("\n输入结束，已退出系统\n");
    return EXIT_SUCCESS;
}
