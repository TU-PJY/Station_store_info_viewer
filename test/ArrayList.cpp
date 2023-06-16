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
        printf("파일을 열 수 없습니다.\n");
        return NULL;
    }

    ArrayList* list = createArrayList();
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // 개행 문자 제거
        buffer[strcspn(buffer, "\n")] = '\0';
        addLine(list, buffer);
    }

    fclose(file);
    return list;
}

void printBorder() {
    cout.width(5); cout << "번호" << "| ";
    cout << " 노선" << "| ";
    cout.width(25); cout << "역명" << "| ";
    cout.width(10); cout << "상가변호" << "| ";
    cout.width(15); cout << "상가유형" << "|     ";
    cout.width(10); cout << "상가면적" << "|    ";
    cout.width(10); cout << "월 임대료" << "| ";
    cout << endl;
}
