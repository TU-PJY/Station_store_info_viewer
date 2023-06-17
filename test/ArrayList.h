#pragma once

//배열 리스트 구조체
typedef struct {
    char** lines;
    int size;
} ArrayList;

//추천 데이터 검색 시 사용하는 열거형 변수
enum state {
    input, check, output
};

static bool search = false;  //데이터 존재 유무 판별용 변수, 한 개라도 검색되지 않으면 true가 되지 않아 오류 출력
static int state = input;

//함수
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();
void printMenu();