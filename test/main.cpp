#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#define MAX_LINE_LENGTH 100

using namespace std;

string cmd; //명령어 입력받는 스트링
string line_search; //검색어가 올바른지 검사하는 스트링

//데이터 출력 함수
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList*list_place_number, ArrayList* list_place_type, 
                ArrayList* list_work_type, ArrayList*list_m2, ArrayList* list_fee, ArrayList * list_end_date) {   
    //노선에 따라 색상이 다르게 출력
    if(strstr(list_line->lines[i], "1호선"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    else if(strstr(list_line->lines[i], "2호선"))
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

    cout.width(5); cout << i << "| ";
    cout << list_line->lines[i] << "| ";
    cout.width(25); cout << list_station->lines[i] << "| ";
    cout.width(10); cout << list_place_number->lines[i] << "| ";
    cout.width(15); cout << list_place_type->lines[i] << "| ";
    cout.width(10); cout << list_work_type->lines[i] << "| ";
    cout.width(10); cout << list_m2->lines[i] << " m^2| ";
    cout.width(10); cout << list_fee->lines[i] << " ￦| ";
    cout.width(10); cout << list_end_date->lines[i] << " |";
    cout << endl;
}

int main() {
    //특정한 데이터 출력시 사용하는 인덱스 저장 배열
    int data_index[1000] = { 0 };

    //노선
    const char* line = "data_line.txt";
    //역명
    const char* station = "data_station.txt";
    //상가 번호
    const char* place_number = "data_place_number.txt";
    //상가 유형
    const char* place_type = "data_place_type.txt";
    //상가 면적
    const char* m2 = "data_m2.txt";
    //월 임대료
    const char* fee = "data_fee.txt";
    //업종
    const char* work_type = "data_work_type.txt";
    //계약 만기일
    const char* end_date = "data_end_date.txt";

    //파일 읽어서 저장
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
    ArrayList* list_work_type = readFile(work_type);
    ArrayList* list_end_date = readFile(end_date);

    //하나라도 정상 로드가 되지 않을 경우 종료
    if (list_place_type -> size != list_line -> size && list_place_type -> size != list_station -> size) {
        printf("|출력| 파일 불러오기를 할 수 없습니다.\n"); return 1; 
    }
    //모두 로드되면 프로그램 준비
    else printf("|출력| 파일 불러오기를 성공하였습니다.\n");

    while(1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
       
        cout << "=======================================" << endl;
        cout << "서울교통공사 상가 데이터 검색 프로그램" << endl;
        cout << "데이터 기준: 2023.04.30" << endl;
        cout << "=======================================" << endl;
        printMenu(); printf("명령어 입력>> ");
        cin >> cmd;

        //cmd = 1
        //모든 데이터 출력
        if (cmd == "1") {
            system("CLS"); printBorder();
           
            for (int i = 0; i < list_place_type->size; i++)
                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printBorder(); cout << endl << "|출력| 데이터를 모두 출력하였습니다." << endl; 
        }


        //cmd = 2
        //특정 노선 검색
        else if (cmd == "2") {
            //검색 전 초기 상태
            system("CLS"); search = false; bool is_number = true;
            
            cout << "|출력| 어떤 노선을 검색 하시겠습니까?" << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(예: '1', '2', '3') >> ";
            cin >> cmd;
             
            //번호 외의 다른 문자열이 있을 경우 검색 안 함
            for (int i = 0; i < cmd.length(); i++) {
                if (isdigit(cmd[i]) == 0) is_number = false;
            }
            
            //만약 올바른 검색어라면 출력 시작
            if (is_number == true) {
                cout << endl;
                printBorder();
                for (int i = 0; i < list_place_type->size; i++) {
                    if (strstr(list_line->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                        search = true;
                    }
                }
                if (search == true) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 노선 번호" << endl; 
                }
                else if (search == false) {
                    system("CLS"); cout << "|출력| 그런 데이터가 없습니다." << endl;
                }
            }
            else if (is_number == false) {
                system("CLS"); cout << "|출력| 올바른 숫자가 아닙니다." << endl;
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
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                    search = true; //검색결과가 나오면 true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
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
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                    search = true; //검색결과가 나오면 true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 업종" << endl;
            } 
            //검색결과가 나오지 않으면 그대로 false
            else if (search == false) {
                system("CLS"); cout << "|출력| 그런 데이터가 없습니다." << endl;
            }
        }

        //cmd = 5
        //임대료 기준 검색
        else if (cmd == "5") {
            system("CLS");  search = false; bool is_number = true;

            cout << "|출력| 임대료 상한선을 입력해주세요." << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(숫자만 입력, 예: 1120000, 340000) >> ";
            cin >> cmd;

            //입력한 커맨드가 숫자인지 아닌지 검색, 숫자 이외의 다른 문자가 껴 있을 경우 숫자로 판정 안되어 검색 진행 하지 않음
            for (int i = 0; i < cmd.length(); i++) {
                if (isdigit(cmd[i]) == 0) is_number = false; 
            }

            if (is_number == true) {
                cout << endl;
                printBorder();
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[i]) < atoi(cmd.c_str()) && atoi(list_fee->lines[i]) > 0) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                        search = true; //검색결과가 나오면 true
                    }
                }
                if (search == true) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 임대료" << endl;
                }
                else if (search == false) {
                    system("CLS"); cout << "|출력| 해당 상한선 내의 임대료 데이터를 찾을 수 없습니다." << endl;
                }
            }
            else if (is_number == false) {
                system("CLS"); cout << "|출력| 올바른 숫자가 아닙니다." << endl;
            }
        }

        //cmd = 6
        //자신에게 맞는 추천 데이터 검색
        else if (cmd == "6") {
            system("CLS");
            string mem_line, mem_station, mem_fee;
            bool is_number = true;
            bool is_escape = false;
            for (;;) {
                if (is_escape == true) {
                    system("CLS"); break; 
                }

                //입력 단계
                if (state == input) {
                    for (;;) {
                        cout << "|출력| 노선을 입력해 주세요." << endl;
                        cout << "===============필터 입력===============" << endl;
                        cout << "(예: '1', '2', '3') >> ";

                        cin >> mem_line;

                        for (int i = 0; i < mem_line.length(); i++) {
                            if (isdigit(mem_line[i]) == 0) is_number = false;
                        }
                        if (is_number == true)  break;
                        else if (is_number == false) {
                            system("CLS"); cout << "|출력| 올바르지 않은 검색어입니다." << endl;
                            is_number = true;
                        }
                    }
                    system("CLS");


                    for (;;) {
                        cout << "|출력| 역명을 입력해 주세요." << endl;
                        cout << "===============필터 입력===============" << endl;
                        cout << "(예: '동대문', '천호' 또는 '1', '2') >> ";

                        cin >> mem_station;
                        break;
                    }
                    system("CLS");

                    for (;;) {
                        cout << "|출력| 임대료 상한선을 입력해주세요." << endl;
                        cout << "===============필터 입력===============" << endl;
                        cout << "(숫자만 입력, 예: 1120000, 340000) >> ";

                        cin >> mem_fee;

                        for (int i = 0; i < cmd.length(); i++) {
                            if (isdigit(cmd[i]) == 0) is_number = false;
                        }
                        if (is_number == true) break;
                        if (is_number == false) {
                            system("CLS"); cout << "올바르지 않은 검색어 입니다." << endl;
                            is_number = true;
                        }
                    }
                    system("CLS");
                    state = check;
                }

                //확인 단계
                else if (state == check) {
                    for (;;) {
                        cout << "|출력| 지금까지 입력한 필터는 다음과 같습니다." << endl << endl;
                        cout << "노선: " << mem_line << "호선 | " << "역명: " << mem_station << " | " << "임대료 상한선: " << mem_fee << "￦" << endl << endl;
                        cout << "===============메뉴 선택===============" << endl;
                        cout << "1: 입력 데이터 확정 후 검색" << endl;
                        cout << "2: 다시 입력하기" << endl;
                        cout << "3: 취소 후 나가기" << endl;
                        cout << "=======================================" << endl;
                        printf("명령어 입력>> ");
                        cin >> cmd;

                        //나가기
                        if (cmd == "3") {
                            is_escape = true; break;
                        }
                        //재입력
                        else if (cmd == "2") {
                            system("CLS");  state = input; break;
                        }
                        //데이터 검색 및 출력
                        else if (cmd == "1") {
                            system("CLS");  state = output; break;
                        }
                        else {
                            system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                        }
                    }
                }

                //필터에 맞는 데이터 검색
                else if (state == output) {
                    search = false;
                    printBorder();
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (strstr(list_line->lines[i], mem_line.c_str()) && strstr(list_station->lines[i], mem_station.c_str()) &&
                            atoi(list_fee->lines[i]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[i]) > 0) {
                            printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                            search = true; //검색결과가 나오면 true
                        }
                    }

                    if (search == true) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printBorder();  cout << endl << "|출력| 데이터를 기반으로 추천드리는 데이터는 위와 같습니다." << endl;

                        state = input; is_escape = true; break;
                    }

                    else if(search == false) {
                        system("CLS"); cout << "|출력| 필터에 맞는 데이터가 없는것 같습니다. 다시 입력하시겠습니까?" << endl;

                        for (;;) {
                            cout << "===============메뉴 선택===============" << endl;
                            cout << "1: 다시 입력하기" << endl;
                            cout << "2: 취소 후 나가기" << endl;
                            cout << "=======================================" << endl;
                            cin >> cmd;
                            if (cmd == "2") {
                                state = input; mem_line = ""; mem_station = ""; mem_fee = ""; is_escape = true; break;
                            }
                            else if (cmd == "1") {
                                system("CLS");  state = input; break;
                            }
                            else {
                                system("CLS"); cout << "알 수 없는 명령어 입니다." << endl;
                            } 
                        }
                    }
                }
            }
        }

        //cmd = q
        //프로그램 종료하기
        else if (cmd == "q") {
            system("CLS"); cout << "프로그램을 종료합니다." << endl; break;
        }
           
        //정해진 커맨드 외의 커맨드, 텍스트 지우기
        else {
            system("CLS"); cout << "|출력| 텍스트를 모두 지웠습니다." << endl; 
        }
    }

    return 0;
}

