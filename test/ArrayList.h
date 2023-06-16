#pragma once
#define MAX_LINE_LENGTH 100

typedef struct {
    char** lines;
    int size;
} ArrayList;

static bool search = false;  //������ ���� ���� �Ǻ��� ����, �� ���� �˻����� ������ true�� ���� �ʾ� ���� ���
static bool err = false;
static bool number_find = false;

ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();
void printMenu();