#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#include "ArrayList.h"

#define MAX_LINE_LENGTH 100

using namespace std;

//배열 리스트 생성
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
        cout << "파일을 열 수 없습니다." << endl; return NULL;
    }
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // 개행 문자 제거
        addLine(list, buffer);
    }
    fclose(file); return list; 
}

// 머지 소트
void merge(char* arr[], int l, int m, int r, int index[], int index_l, int index_m, int index_r, int state) {
    int n1 = m - l + 1; // 왼쪽 부분 배열의 크기
    int n2 = r - m; // 오른쪽 부분 배열의 크기

    // 임시 배열 생성 및 복사
    char** left_arr = new char* [n1];
    char** right_arr = new char* [n2];
    int* left_index = new int[n1];
    int* right_index = new int[n2];

    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[l + i];
        left_index[i] = index[index_l + i];
    }

    for (int j = 0; j < n2; j++) {
        right_arr[j] = arr[m + 1 + j];
        right_index[j] = index[index_m + 1 + j];
    }

    // 임시 배열을 사용하여 병합
    int i = 0; // 왼쪽 부분 배열의 인덱스
    int j = 0; // 오른쪽 부분 배열의 인덱스
    int k = l; // 병합된 배열의 인덱스

    while (i < n1 && j < n2) {
        // 숫자 문자열을 비교하여 정렬
        //오름차순(정수)
        if (atoi(left_arr[i]) <= atoi(right_arr[j]) && (state == up || state == up_price)) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }
        //내림차순(정수)
        else if (atoi(left_arr[i]) >= atoi(right_arr[j]) && (state == down || state == down_price)) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }

        //오름차순(실수)
        else if (atof(left_arr[i]) <= atof(right_arr[j]) && state == up_width) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }
        //오름차순(실수)
        else if (atof(left_arr[i]) >= atof(right_arr[j]) && state == down_width) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }

        else {
            arr[k] = right_arr[j];
            index[k] = right_index[j];
            j++;
        }
        k++;
    }

    // 남은 요소들을 복사
    while (i < n1) {
        arr[k] = left_arr[i];
        index[k] = left_index[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_arr[j];
        index[k] = right_index[j];
        j++;
        k++;
    }

    // 동적 할당한 메모리 해제
    delete[] left_arr;
    delete[] right_arr;
    delete[] left_index;
    delete[] right_index;
}

// 머지 소트
void mergeSort(char* arr[], int l, int r, int index[], int index_l, int index_r, int state) {
    if (l < r) {
        int m = l + (r - l) / 2; // 중간 지점

        // 왼쪽과 오른쪽 부분 배열을 재귀적으로 정렬
        mergeSort(arr, l, m, index, index_l, index_l + (m - l), state);
        mergeSort(arr, m + 1, r, index, index_l + (m - l) + 1, index_r, state);

        // 정렬된 부분 배열을 병합
        merge(arr, l, m, r, index, index_l, index_l + (m - l), index_r, state);
    }
}

//데이터 출력 함수
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList* list_place_number, ArrayList* list_place_type,
    ArrayList* list_work_type, ArrayList* list_m2, ArrayList* list_fee, ArrayList* list_end_date, bool color_out) {
    string na = "N/A"; //줄을 맞추기 위해 별도의 스트링 변수 사용

    //노선에 따라 색상이 다르게 출력
    if (color_out == true) { //color_out이 true일 때만 색상 출력
        if (strstr(list_line->lines[i], "1호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "2호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "3호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "4호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "5호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "6호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
        else if (strstr(list_line->lines[i], "7호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        else if (strstr(list_line->lines[i], "8호선"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    cout.width(5); cout << i << "| ";
    cout << list_line->lines[i] << "| ";
    cout.width(25); cout << list_station->lines[i] << "| ";
    cout.width(10); cout << list_place_number->lines[i] << "| ";
    cout.width(15); cout << list_place_type->lines[i] << "| ";

    //없는 데이터일경우 N/A 표시
    if (strlen(list_work_type->lines[i]) > 0) {
        cout.width(10); cout << list_work_type->lines[i] << "| ";
    }
    else if (strlen(list_work_type->lines[i]) == 0) {
        cout.width(10); cout << na << "| ";
    }

    if (atof(list_m2->lines[i]) > 0) {
        cout.width(10); cout << list_m2->lines[i] << " m^2| ";
    }
    else if (atof(list_m2->lines[i]) == 0) {
        cout.width(10); cout << na << " m^2| ";
    }

    if (atoi(list_fee->lines[i]) > 0) {
        cout.width(10); cout << list_fee->lines[i] << " ￦| ";
    }
    else if (atoi(list_fee->lines[i]) == 0) {
        cout.width(10); cout << na << " ￦| ";
    }

    if (strlen(list_end_date->lines[i]) > 0) {
        cout.width(10); cout << list_end_date->lines[i] << " |";
    }
    else if (strlen(list_end_date->lines[i]) == 0) {
        cout.width(10); cout << na << " |";
    }
    cout << endl;
}

//데이터 분류 출력
void printBorder() {
    cout << "=============================================================================================================================" << endl;
    cout.width(5); cout << "번호" << "| ";
    cout << " 노선" << "| ";
    cout.width(25); cout << "역명" << "| ";
    cout.width(10); cout << "상가변호" << "| ";
    cout.width(15); cout << "상가유형" << "| ";
    cout.width(10); cout << "업종유형" << "|     ";
    cout.width(10); cout << "상가면적" << "|    ";
    cout.width(10); cout << "월 임대료" << "| ";
    cout.width(10); cout << "계약 만기일" << "|";
    cout << endl;
    cout << "=============================================================================================================================" << endl;
}

//메뉴 출력
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

