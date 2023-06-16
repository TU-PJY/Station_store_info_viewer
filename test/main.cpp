#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "ArrayList.h"

#define MAX_LINE_LENGTH 100

using namespace std;

string cmd; //명령어 입력받는 스트링
string line_search;

int main() {
    //특정한 데이터 출력시 사용하는 인덱스 저장 배열
    int data_index[1000] = { 0 };
    int idx = -1;

    //상가 유형
    const char* place_type = "data_place_type.txt";
    //노선
    const char* line = "data_line.txt";
    //상가 번호
    const char* place_number = "data_place_number.txt";
    //역명
    const char* station = "data_station.txt";
    //상가 면적
    const char* m2 = "data_m2.txt";
    //월 임대료
    const char* fee = "data_fee.txt";
    
    //파일 읽어서 저장
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
   

    //하나라도 정상 로드가 되지 않을 경우 종료
    if (list_place_type == NULL || line == NULL) {
        printf("파일을 읽을 수 없습니다.\n");
        return 1;
    }
    //모두 로드되면 프로그램 준비
    else printf("파일을 불러오는데에 성공하였습니다.\n");

    for (;;) {
        printf("명령어 입력>> ");
        cin >> cmd;
        //모든 데이터 출력
        if (cmd == "print-all") {
            system("CLS");
            printBorder();
            for (int i = 0; i < list_place_type->size; i++) {
                cout.width(5); cout << i << "| ";
                cout << list_line->lines[i] << "| ";
                cout.width(25); cout << list_station->lines[i] << "| ";
                cout.width(10); cout << list_place_number->lines[i] << "| ";
                cout.width(15); cout << list_place_type->lines[i] << "| ";
                cout.width(10); cout << list_m2->lines[i] << " m^2| ";
                cout.width(10); cout << list_fee->lines[i] << " ￦| ";
                cout << endl;
            }
            printBorder();
            cout << "데이터를 모두 출력하였습니다." << endl << endl;
        }

        else if (cmd == "search-line") {
            system("CLS");
            idx = -1;
            int error = 0;
            char search_line[20] = { 0 };
            cout << "어떤 노선을 검색 하시겠습니까?" << endl;
            cout << ">> ";
            cin >> cmd;

            for (int i = 0; i < list_place_type->size; i++) {
                if (strstr(list_line->lines[i], cmd.c_str())) {
                    cout.width(5); cout << i << "| ";
                    cout << list_line->lines[i] << "| ";
                    cout.width(25); cout << list_station->lines[i] << "| ";
                    cout.width(10); cout << list_place_number->lines[i] << "| ";
                    cout.width(15); cout << list_place_type->lines[i] << "| ";
                    cout.width(10); cout << list_m2->lines[i] << " m^2| ";
                    cout.width(10); cout << list_fee->lines[i] << " ￦| ";
                    cout << endl;
                    idx++; //데이터 존재 유무 판별용 변수, -1이면 존재하지 않음
                }
            }

            if (idx >= 0) {
                printBorder();
                cout << "검색한 데이터를 모두 출력하였습니다." << endl;
            }

            else if (idx == -1)
                cout << "그런 데이터가 없습니다." << endl;
        }
            /*
            if (idx >= 0) {
                printBorder();
                for (int i = 0; i < idx; i++) {
                    if (idx >= 0) {
                        for (int i = 0; i < idx; i++) {
                          
                        }
                    }
                }
                cout << "검색한 데이터를 모두 출력하였습니다." << endl;
            }

            else if (idx == -1)
                cout << "그런 데이터가 없습니다." << endl;
                */
     //   }

        else {
            system("CLS");
            printf("알 수 없는 명령어 입니다.\n");
        }
    }
        


    destroyArrayList(list_place_type);
    return 0;
}