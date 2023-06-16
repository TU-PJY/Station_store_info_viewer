#pragma once

//배열 리스트 구조체
typedef struct {
    char** lines;
    int size;
} ArrayList;

static bool search = false;  //데이터 존재 유무 판별용 변수, 한 개라도 검색되지 않으면 true가 되지 않아 오류 출력
static bool number_find = false; //노선 검색 시 검색어가 올바르면 true, 올바르지 않으면 false

//함수
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();
void printMenu();