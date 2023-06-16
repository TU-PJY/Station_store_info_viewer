#pragma once
#define MAX_LINE_LENGTH 100

typedef struct {
    char** lines;
    int size;
} ArrayList;

static bool search = false;  //데이터 존재 유무 판별용 변수, 한 개라도 검색되지 않으면 true가 되지 않아 오류 출력
static bool err = false;
static bool number_find = false;

ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();
void printMenu();