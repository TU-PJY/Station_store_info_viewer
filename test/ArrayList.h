#pragma once

//�迭 ����Ʈ ����ü
typedef struct {
    char** lines;
    int size;
} ArrayList;

//��õ ������ �˻� �� ����ϴ� ������ ����
enum state {
    input, check, output
};

static bool search = false;  //������ ���� ���� �Ǻ��� ����, �� ���� �˻����� ������ true�� ���� �ʾ� ���� ���
static int state = input;

//�Լ�
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();
void printMenu();