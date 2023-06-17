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
string line_search; //검색어가 올바른지 검사하는 스트링

//데이터 출력 함수
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList*list_place_number, ArrayList* list_place_type, ArrayList* list_work_type, ArrayList*list_m2, ArrayList* list_fee) {   
    //노선에 따라 색상이 다르게 출력
    if(strstr(list_line->lines[i], "1호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    else if(strstr(list_line->lines[i], "2호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else if (strstr(list_line->lines[i], "3호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    else if (strstr(list_line->lines[i], "4호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else if (strstr(list_line->lines[i], "5호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    else if (strstr(list_line->lines[i], "6호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    else if (strstr(list_line->lines[i], "7호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    else if (strstr(list_line->lines[i], "8호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

    cout.width(5); cout << i << "| ";
    cout << list_line->lines[i] << "| ";
    cout.width(25); cout << list_station->lines[i] << "| ";
    cout.width(10); cout << list_place_number->lines[i] << "| ";
    cout.width(15); cout << list_place_type->lines[i] << "| ";
    cout.width(10); cout << list_work_type->lines[i] << "| ";
    cout.width(10); cout << list_m2->lines[i] << " m^2| ";
    cout.width(10); cout << list_fee->lines[i] << " ￦| ";
    cout << endl;
}

int main() {
    //특정한 데이터 출력시 사용하는 인덱스 저장 배열
    int data_index[1000] = { 0 };

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
    //업종
    const char* work_type = "data_work_type.txt";

    //파일 읽어서 저장
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
    ArrayList* list_work_type = readFile(work_type);

    //하나라도 정상 로드가 되지 않을 경우 종료
    if (list_place_type -> size != list_line -> size && list_place_type -> size != list_station -> size) {
        printf("|출력| 파일 불러오기를 할 수 없습니다.\n"); return 1; 
    }
    //모두 로드되면 프로그램 준비
    else printf("|출력| 파일 불러오기를 성공하였습니다.\n");

    while(1) {
        printMenu(); printf("명령어 입력>> ");
        cin >> cmd;

        //cmd = 1
        //모든 데이터 출력
        if (cmd == "1") {
            system("CLS"); printBorder();
           
            for (int i = 0; i < list_place_type->size; i++)
                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            printBorder(); cout << endl << "|출력| 데이터를 모두 출력하였습니다." << endl; 
        }


        //cmd = 2
        //특정 노선 검색
        else if (cmd == "2") {
            //검색 전 초기 상태
            system("CLS"); search = false; number_find = false;
            
            cout << "|출력| 어떤 노선을 검색 하시겠습니까?" << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(예: '1', '2', '3') >> ";
            cin >> cmd;

            //노선 검색 시 번호 포함 안하면 검색 불가
            if (number_find == false) {
                for (int i = 1; i < 9; i++) {
                    //i를 itoa변환 후 ch가 받고 이를 스트링 변수가 받아서 c_str() 변환 과정을 거쳐 비교 할 수 있도록 만듬
                    char ch[2] = { 0 }; string number = _itoa(i, ch, 10); 
                    //서울교통공사는 1호선~8호선까지 운영하므로 반복문을 통해 해당 노선 번호가 cmd에 존재하는지 검사
                    //있으면 true가 되어 출력부로 넘어감
                    if (strstr(cmd.c_str(), number.c_str()) && strlen(cmd.c_str()) == 1) number_find = true;
                } 
                //없다면 그대로 false가 되어 출력 안 됨
                if (number_find == false) {
                    system("CLS"); cout << "|출력| 알 수 없는 검색어 입니다." << endl; 
                }
            }
            
            //만약 올바른 검색어라면 출력 시작
            if (number_find == true) {
                cout << endl;
                printBorder();
                for (int i = 0; i < list_place_type->size; i++) {
                    if (strstr(list_line->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee);
                        search = true;
                    }
                }
                if (search == true) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                    printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 노선 번호" << endl; 
                }
            }
        }


        //cmd = 3
        //특정 역명 검색
        else if (cmd == "3") {
            //검색 전 초기 상태
            system("CLS"); search = false;
            
            cout << "|출력| 어떤 역을 검색 하시겠습니까?" << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(예: '동대문', '천호' 또는 '1', '2') >> ";
            cin >> cmd;

            //일단 검색
            cout << endl;
            printBorder();
            for (int i = 0; i < list_place_type->size; i++) {
                if (strstr(list_station->lines[i], cmd.c_str())) {
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee);
                    search = true; //검색결과가 나오면 true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 역명" << endl; 
            } 
            //검색결과가 나오지 않으면 그대로 false
            else if (search == false) {
                system("CLS"); cout << "|출력| 그런 데이터가 없습니다." << endl; 
            }
        }

        //cmd = 4
        //업종 기준 검색
        else if (cmd == "4") {
            //검색 전 초기 상태
            system("CLS");  search = false;

            cout << "|출력| 어떤 업종을 검색 하시겠습니까?" << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(예: '플라워', '화장품', '화', '무인' 등) >> ";
            cin >> cmd;

            cout << endl;
            printBorder();
            
            for (int i = 0; i < list_place_type->size; i++) {
                if (strstr(list_work_type->lines[i], cmd.c_str())) {
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee);
                    search = true; //검색결과가 나오면 true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 업종" << endl;
            } 
            //검색결과가 나오지 않으면 그대로 false
            else if (search == false) {
                system("CLS"); cout << "|출력| 그런 데이터가 없습니다." << endl;
            }
        }


        //cmd = c
        //콘솔창 텍스트 지우기
        else if (cmd == "c") {
            system("CLS"); cout << "|출력| 텍스트를 모두 지웠습니다." << endl; 
        }

        //cmd = e
        //프로그램 종료하기
        else if (cmd == "q") {
            cout << "프로그램을 종료합니다." << endl; break; 
        }
           
        //정해진 커맨드 외의 커맨드
        else {
            system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl; 
        }
    }

        

    return 0;
}

