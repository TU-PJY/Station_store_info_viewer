#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#include "ArrayList.h"

#define MAX_LINE_LENGTH 100

using namespace std;

//배열 라스트 생성
ArrayList* createArrayList() {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->lines = NULL; list->size = 0; return list; 
}

//배열 리스트에 한 줄씩 읽은 텍스트 라인 추가
void addLine(ArrayList* list, const char* line) {
    list->lines = (char**)realloc(list->lines, (list->size + 1) * sizeof(char*));
    list->lines[list->size] = (char*)malloc((strlen(line) + 1) * sizeof(char));
    strcpy(list->lines[list->size], line);
    list->size++;
}

//파일 읽기
ArrayList* readFile(const char* filename) {
    ArrayList* list = createArrayList();
    char buffer[MAX_LINE_LENGTH];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n"); return NULL; 
    }
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // 개행 문자 제거
        addLine(list, buffer);
    }
    fclose(file); return list; 
}

//데이터 분류 출력
void printBorder() {
    cout << "================================================================================================================" << endl;
    cout.width(5); cout << "번호" << "| ";
    cout << " 노선" << "| ";
    cout.width(25); cout << "역명" << "| ";
    cout.width(10); cout << "상가변호" << "| ";
    cout.width(15); cout << "상가유형" << "| ";
    cout.width(10); cout << "업종유형" << "|     ";
    cout.width(10); cout << "상가면적" << "|    ";
    cout.width(10); cout << "월 임대료" << "| ";
    cout << endl;
    cout << "================================================================================================================" << endl;
}

void printMenu() {
    cout << "===============메뉴 선택===============" << endl;
    cout << "1: 모든 데이터 보기" << endl;
    cout << "2: 노선 기준 검색" << endl;
    cout << "3: 역명 기준 검색" << endl;
    cout << "4: 업종 기준 검색" << endl;
    cout << "5: 임대료 기준 검색" << endl;
    cout << "6: 추천 데이터 검색" << endl;
    cout << "q: 프로그램 종료" << endl << endl;
    cout << "텍스트를 지우려면 메뉴에 없는 키 입력" << endl;
    cout << "=======================================" << endl;
}

