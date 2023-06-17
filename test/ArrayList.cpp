#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#include "ArrayList.h"

#define MAX_LINE_LENGTH 100

using namespace std;

//�迭 ��Ʈ ����
ArrayList* createArrayList() {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->lines = NULL; list->size = 0; return list; 
}

//�迭 ����Ʈ�� �� �پ� ���� �ؽ�Ʈ ���� �߰�
void addLine(ArrayList* list, const char* line) {
    list->lines = (char**)realloc(list->lines, (list->size + 1) * sizeof(char*));
    list->lines[list->size] = (char*)malloc((strlen(line) + 1) * sizeof(char));
    strcpy(list->lines[list->size], line);
    list->size++;
}

//���� �б�
ArrayList* readFile(const char* filename) {
    ArrayList* list = createArrayList();
    char buffer[MAX_LINE_LENGTH];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n"); return NULL; 
    }
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // ���� ���� ����
        addLine(list, buffer);
    }
    fclose(file); return list; 
}

//������ �з� ���
void printBorder() {
    cout << "================================================================================================================" << endl;
    cout.width(5); cout << "��ȣ" << "| ";
    cout << " �뼱" << "| ";
    cout.width(25); cout << "����" << "| ";
    cout.width(10); cout << "�󰡺�ȣ" << "| ";
    cout.width(15); cout << "������" << "| ";
    cout.width(10); cout << "��������" << "|     ";
    cout.width(10); cout << "�󰡸���" << "|    ";
    cout.width(10); cout << "�� �Ӵ��" << "| ";
    cout << endl;
    cout << "================================================================================================================" << endl;
}

void printMenu() {
    cout << "===============�޴� ����===============" << endl;
    cout << "1: ��� ������ ����" << endl;
    cout << "2: �뼱 ���� �˻�" << endl;
    cout << "3: ���� ���� �˻�" << endl;
    cout << "4: ���� ���� �˻�" << endl;
    cout << "5: �Ӵ�� ���� �˻�" << endl;
    cout << "6: ��õ ������ �˻�" << endl;
    cout << "q: ���α׷� ����" << endl << endl;
    cout << "�ؽ�Ʈ�� ������� �޴��� ���� Ű �Է�" << endl;
    cout << "=======================================" << endl;
}

