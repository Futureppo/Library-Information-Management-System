#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 999         // 最大图书数量
#define MAX_STR_LEN 999        // 字符串最大长度
#define DEFAULT_FILE "books.json"  // 默认数据文件

typedef struct {
    int id;                     // 登录号
    char title[MAX_STR_LEN];    // 书名
    char author[MAX_STR_LEN];   // 作者
    char category[MAX_STR_LEN]; // 分类号
    char publisher[MAX_STR_LEN];// 出版单位
    int year;                   // 出版时间(年份)
    float price;                // 价格
} Book;

Book books[MAX_BOOKS];          // 图书数组
int bookCount = 0;              // 当前图书数量
char currentFile[MAX_STR_LEN] = DEFAULT_FILE;  // 当前文件名

void showMenu(void);
void addBook(void);
void browseBooks(void);
void searchByTitle(void);
void searchByAuthor(void);
void searchMenu(void);
void sortByCategory(void);
void sortByYear(void);
void sortByPrice(void);
void sortMenu(void);
void deleteBook(void);
void modifyBook(void);
void saveToFile(void);
void loadFromFile(void);
void openFile(void);
void printBook(Book *book);
void printTableHeader(void);
void clearInputBuffer(void);
void pause(void);


int main() {
    int choice;
    loadFromFile();
    while (1) {
        showMenu();
        printf("请输入选项 (0-8): ");
        
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\n[错误] 请输入有效数字！\n");
            continue;
        }
        clearInputBuffer();
        
        switch (choice) {
            case 1: addBook(); break;
            case 2: browseBooks(); break;
            case 3: searchMenu(); break;
            case 4: sortMenu(); break;
            case 5: deleteBook(); break;
            case 6: modifyBook(); break;
            case 7: saveToFile(); break;
            case 8: openFile(); break;
            case 0:
                printf("\n已退出\n");
                return 0;
            default:
                printf("\n[错误] 无效选项，请重新输入！\n");
        }
    }
    
    return 0;
}

void showMenu(void) {
    printf("\n");
    printf("┌────────────────────────────────────┐\n");
    printf("│           图书管理系统             │\n");
    printf("├────────────────────────────────────┤\n");
    printf("│  1. 录入图书                       │\n");
    printf("│  2. 浏览图书                       │\n");
    printf("│  3. 查询图书                       │\n");
    printf("│  4. 排序图书                       │\n");
    printf("│  5. 删除图书                       │\n");
    printf("│  6. 修改图书                       │\n");
    printf("│  7. 保存数据                       │\n");
    printf("│  8. 打开文件                       │\n");
    printf("│  0. 退出系统                       │\n");
    printf("└────────────────────────────────────┘\n");
    printf("  当前文件: %s | 图书数量: %d\n", currentFile, bookCount);
}

void addBook(void) {
    if (bookCount >= MAX_BOOKS) {
        printf("\n[错误] 图书数量已达上限！\n");
        return;
    }
    
    Book *newBook = &books[bookCount];
    
    printf("\n===== 录入新图书 =====\n");
    
    // 输入登录号
    printf("请输入登录号: ");
    scanf("%d", &newBook->id);
    clearInputBuffer();
    
    // 检查登录号是否重复
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == newBook->id) {
            printf("[错误] 登录号已存在！\n");
            return;
        }
    }
    
    // 输入其他信息
    printf("请输入书名: ");
    fgets(newBook->title, MAX_STR_LEN, stdin);
    newBook->title[strcspn(newBook->title, "\n")] = '\0';
    
    printf("请输入作者: ");
    fgets(newBook->author, MAX_STR_LEN, stdin);
    newBook->author[strcspn(newBook->author, "\n")] = '\0';
    
    printf("请输入分类号: ");
    fgets(newBook->category, MAX_STR_LEN, stdin);
    newBook->category[strcspn(newBook->category, "\n")] = '\0';
    
    printf("请输入出版单位: ");
    fgets(newBook->publisher, MAX_STR_LEN, stdin);
    newBook->publisher[strcspn(newBook->publisher, "\n")] = '\0';
    
    printf("请输入出版年份: ");
    scanf("%d", &newBook->year);
    clearInputBuffer();
    
    printf("请输入价格: ");
    scanf("%f", &newBook->price);
    clearInputBuffer();
    
    bookCount++;
    printf("\n[成功] 图书录入成功！\n");
}

void printTableHeader(void) {
    printf("\n");
    printf("┌──────┬────────────────────┬──────────────┬────────┬────────────────┬──────┬─────────┐\n");
    printf("│登录号│        书名        │     作者     │ 分类号 │    出版单位    │ 年份 │  价格   │\n");
    printf("├──────┼────────────────────┼──────────────┼────────┼────────────────┼──────┼─────────┤\n");
}

void printBook(Book *book) {
    printf("│%6d│%-20.20s│%-14.14s│%-8.8s│%-16.16s│%6d│%9.2f│\n",
           book->id,
           book->title,
           book->author,
           book->category,
           book->publisher,
           book->year,
           book->price);
}

void browseBooks(void) {
    if (bookCount == 0) {
        printf("\n[提示] 暂无图书记录！\n");
        return;
    }
    
    printf("\n===== 图书列表 (共%d本) =====", bookCount);
    printTableHeader();
    
    for (int i = 0; i < bookCount; i++) {
        printBook(&books[i]);
    }
    
    printf("└──────┴────────────────────┴──────────────┴────────┴────────────────┴──────┴─────────┘\n");
}


void searchMenu(void) {
    int choice;
    printf("\n===== 查询图书 =====\n");
    printf("1. 按书名查询\n");
    printf("2. 按作者查询\n");
    printf("0. 返回\n");
    printf("请选择: ");
    
    scanf("%d", &choice);
    clearInputBuffer();
    
    switch (choice) {
        case 1: searchByTitle(); break;
        case 2: searchByAuthor(); break;
        case 0: break;
        default: printf("[错误] 无效选项！\n");
    }
}

void searchByTitle(void) {
    char keyword[MAX_STR_LEN];
    int found = 0;
    
    printf("请输入书名关键字: ");
    fgets(keyword, MAX_STR_LEN, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    
    printTableHeader();
    
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) != NULL) {
            printBook(&books[i]);
            found++;
        }
    }
    
    printf("└──────┴────────────────────┴──────────────┴────────┴────────────────┴──────┴─────────┘\n");
    printf("找到 %d 条记录\n", found);
}


void searchByAuthor(void) {
    char keyword[MAX_STR_LEN];
    int found = 0;
    
    printf("请输入作者关键字: ");
    fgets(keyword, MAX_STR_LEN, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    
    printTableHeader();
    
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].author, keyword) != NULL) {
            printBook(&books[i]);
            found++;
        }
    }
    
    printf("└──────┴────────────────────┴──────────────┴────────┴────────────────┴──────┴─────────┘\n");
    printf("找到 %d 条记录\n", found);
}


void sortMenu(void) {
    int choice;
    printf("\n===== 排序图书 =====\n");
    printf("1. 按分类号排序\n");
    printf("2. 按出版时间排序\n");
    printf("3. 按价格排序\n");
    printf("0. 返回\n");
    printf("请选择: ");
    
    scanf("%d", &choice);
    clearInputBuffer();
    
    switch (choice) {
        case 1: sortByCategory(); break;
        case 2: sortByYear(); break;
        case 3: sortByPrice(); break;
        case 0: break;
        default: printf("[错误] 无效选项！\n");
    }
}

void sortByCategory(void) {
    Book temp;
    
    // 使用冒泡排序
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - 1 - i; j++) {
            if (strcmp(books[j].category, books[j + 1].category) > 0) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    
    printf("\n[成功] 已按分类号排序！\n");
    browseBooks();
}

void sortByYear(void) {
    Book temp;
    
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - 1 - i; j++) {
            if (books[j].year > books[j + 1].year) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    
    printf("\n[成功] 已按出版时间排序！\n");
    browseBooks();
}

void sortByPrice(void) {
    Book temp;
    
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = 0; j < bookCount - 1 - i; j++) {
            if (books[j].price > books[j + 1].price) {
                temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }
    
    printf("\n[成功] 已按价格排序！\n");
    browseBooks();
}

void deleteBook(void) {
    int id, index = -1;
    
    if (bookCount == 0) {
        printf("\n[提示] 暂无图书记录！\n");
        return;
    }
    
    printf("\n===== 删除图书 =====\n");
    printf("请输入要删除的登录号: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    // 查找图书
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("[错误] 未找到该登录号的图书！\n");
        return;
    }
    
    // 显示要删除的图书信息
    printf("\n即将删除以下图书:\n");
    printTableHeader();
    printBook(&books[index]);
    printf("└──────┴────────────────────┴──────────────┴────────┴────────────────┴──────┴─────────┘\n");
    
    printf("确认删除? (1=是, 0=否): ");
    int confirm;
    scanf("%d", &confirm);
    clearInputBuffer();
    
    if (confirm == 1) {
        // 后面的前移
        for (int i = index; i < bookCount - 1; i++) {
            books[i] = books[i + 1];
        }
        bookCount--;
        printf("\n[成功] 图书已删除！\n");
    } else {
        printf("\n[取消] 删除操作已取消。\n");
    }
}

void modifyBook(void) {
    int id, index = -1;
    
    if (bookCount == 0) {
        printf("\n[提示] 暂无图书记录！\n");
        return;
    }
    
    printf("\n===== 修改图书 =====\n");
    printf("请输入要修改的登录号: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    // 查找图书
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("[错误] 未找到该登录号的图书！\n");
        return;
    }
    
    // 显示当前信息
    printf("\n当前图书信息:\n");
    printTableHeader();
    printBook(&books[index]);
    printf("└──────┴────────────────────┴──────────────┴────────┴────────────────┴──────┴─────────┘\n");
    
    printf("\n请输入新信息 (直接回车保持原值):\n");
    char buffer[MAX_STR_LEN];
    
    // 修改书名
    printf("书名 [%s]: ", books[index].title);
    fgets(buffer, MAX_STR_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(books[index].title, buffer);
    }
    
    // 修改作者
    printf("作者 [%s]: ", books[index].author);
    fgets(buffer, MAX_STR_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(books[index].author, buffer);
    }
    
    // 修改分类号
    printf("分类号 [%s]: ", books[index].category);
    fgets(buffer, MAX_STR_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(books[index].category, buffer);
    }
    
    // 修改出版单位
    printf("出版单位 [%s]: ", books[index].publisher);
    fgets(buffer, MAX_STR_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(books[index].publisher, buffer);
    }
    
    // 修改年份
    printf("出版年份 [%d]: ", books[index].year);
    fgets(buffer, MAX_STR_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        books[index].year = atoi(buffer);
    }
    
    // 修改价格
    printf("价格 [%.2f]: ", books[index].price);
    fgets(buffer, MAX_STR_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        books[index].price = (float)atof(buffer);
    }
    
    printf("\n[成功] 图书信息已更新！\n");
}

void saveToFile(void) {
    FILE *fp = fopen(currentFile, "w");
    
    if (fp == NULL) {
        printf("\n[错误] 无法打开文件进行保存！\n");
        return;
    }
    
    // 写入JSON
    fprintf(fp, "{\n");
    fprintf(fp, "  \"books\": [\n");
    
    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "    {\n");
        fprintf(fp, "      \"id\": %d,\n", books[i].id);
        fprintf(fp, "      \"title\": \"%s\",\n", books[i].title);
        fprintf(fp, "      \"author\": \"%s\",\n", books[i].author);
        fprintf(fp, "      \"category\": \"%s\",\n", books[i].category);
        fprintf(fp, "      \"publisher\": \"%s\",\n", books[i].publisher);
        fprintf(fp, "      \"year\": %d,\n", books[i].year);
        fprintf(fp, "      \"price\": %.2f\n", books[i].price);
        fprintf(fp, "    }%s\n", (i < bookCount - 1) ? "," : "");
    }
    
    fprintf(fp, "  ]\n");
    fprintf(fp, "}\n");
    
    fclose(fp);
    printf("\n[成功] 数据已保存到 %s\n", currentFile);
}

void loadFromFile(void) {
    FILE *fp = fopen(currentFile, "r");
    
    if (fp == NULL) {
        printf("[提示] 未找到数据文件 %s，将创建新文件。\n", currentFile);
        return;
    }
    
    bookCount = 0;
    char line[512];
    Book *currentBook = NULL;
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        // 检测新图书对象开始
        if (strstr(line, "\"id\":") != NULL && bookCount < MAX_BOOKS) {
            currentBook = &books[bookCount];
            sscanf(strstr(line, ":") + 1, " %d", &currentBook->id);
        }
        else if (strstr(line, "\"title\":") != NULL && currentBook != NULL) {
            char *start = strchr(line, ':');
            if (start) {
                start = strchr(start, '\"') + 1;
                char *end = strrchr(line, '\"');
                if (start && end && end > start) {
                    int len = end - start;
                    if (len >= MAX_STR_LEN) len = MAX_STR_LEN - 1;
                    strncpy(currentBook->title, start, len);
                    currentBook->title[len] = '\0';
                }
            }
        }
        else if (strstr(line, "\"author\":") != NULL && currentBook != NULL) {
            char *start = strchr(line, ':');
            if (start) {
                start = strchr(start, '\"') + 1;
                char *end = strrchr(line, '\"');
                if (start && end && end > start) {
                    int len = end - start;
                    if (len >= MAX_STR_LEN) len = MAX_STR_LEN - 1;
                    strncpy(currentBook->author, start, len);
                    currentBook->author[len] = '\0';
                }
            }
        }
        else if (strstr(line, "\"category\":") != NULL && currentBook != NULL) {
            char *start = strchr(line, ':');
            if (start) {
                start = strchr(start, '\"') + 1;
                char *end = strrchr(line, '\"');
                if (start && end && end > start) {
                    int len = end - start;
                    if (len >= MAX_STR_LEN) len = MAX_STR_LEN - 1;
                    strncpy(currentBook->category, start, len);
                    currentBook->category[len] = '\0';
                }
            }
        }
        else if (strstr(line, "\"publisher\":") != NULL && currentBook != NULL) {
            char *start = strchr(line, ':');
            if (start) {
                start = strchr(start, '\"') + 1;
                char *end = strrchr(line, '\"');
                if (start && end && end > start) {
                    int len = end - start;
                    if (len >= MAX_STR_LEN) len = MAX_STR_LEN - 1;
                    strncpy(currentBook->publisher, start, len);
                    currentBook->publisher[len] = '\0';
                }
            }
        }
        else if (strstr(line, "\"year\":") != NULL && currentBook != NULL) {
            sscanf(strstr(line, ":") + 1, " %d", &currentBook->year);
        }
        else if (strstr(line, "\"price\":") != NULL && currentBook != NULL) {
            sscanf(strstr(line, ":") + 1, " %f", &currentBook->price);
            bookCount++;  // 价格是最后一个字段，读完后图书数+1
            currentBook = NULL;
        }
    }
    
    fclose(fp);
    printf("[成功] 从 %s 加载了 %d 本图书。\n", currentFile, bookCount);
}

void openFile(void) {
    char filename[MAX_STR_LEN];
    
    printf("\n===== 打开文件 =====\n");
    printf("当前文件: %s\n", currentFile);
    printf("请输入要打开的文件名 (或直接回车取消): ");
    
    fgets(filename, MAX_STR_LEN, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    
    if (strlen(filename) == 0) {
        printf("[取消] 操作已取消。\n");
        return;
    }
    
    // 保存当前数据
    if (bookCount > 0) {
        printf("是否保存当前数据? (1=是, 0=否): ");
        int save;
        scanf("%d", &save);
        clearInputBuffer();
        if (save == 1) {
            saveToFile();
        }
    }
    
    // 切换文件
    strcpy(currentFile, filename);
    bookCount = 0;
    loadFromFile();
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause(void) {
    printf("\n按回车键继续...");
    getchar();
}
