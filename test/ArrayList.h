#pragma once

//�迭 ����Ʈ ����ü
typedef struct {
    char** lines;
    int size;
} ArrayList;

static bool search = false;  //������ ���� ���� �Ǻ��� ����, �� ���� �˻����� ������ true�� ���� �ʾ� ���� ���
static bool number_find = false; //�뼱 �˻� �� �˻�� �ùٸ��� true, �ùٸ��� ������ false

//�Լ�
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();
void printMenu();