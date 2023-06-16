#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "ArrayList.h"

#define MAX_LINE_LENGTH 100

using namespace std;

ArrayList* createArrayList() {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->lines = NULL;
    list->size = 0;
    return list;
}

void destroyArrayList(ArrayList* list) {
    if (list == NULL)
        return;

    for (int i = 0; i < list->size; i++) {
        free(list->lines[i]);
    }
    free(list->lines);
    free(list);
}

void addLine(ArrayList* list, const char* line) {
    list->lines = (char**)realloc(list->lines, (list->size + 1) * sizeof(char*));
    list->lines[list->size] = (char*)malloc((strlen(line) + 1) * sizeof(char));
    strcpy(list->lines[list->size], line);
    list->size++;
}

ArrayList* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return NULL;
    }

    ArrayList* list = createArrayList();
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // ���� ���� ����
        buffer[strcspn(buffer, "\n")] = '\0';
        addLine(list, buffer);
    }

    fclose(file);
    return list;
}

void printBorder() {
    cout.width(5); cout << "��ȣ" << "| ";
    cout << " �뼱" << "| ";
    cout.width(25); cout << "����" << "| ";
    cout.width(10); cout << "�󰡺�ȣ" << "| ";
    cout.width(15); cout << "������" << "|     ";
    cout.width(10); cout << "�󰡸���" << "|    ";
    cout.width(10); cout << "�� �Ӵ��" << "| ";
    cout << endl;
}
