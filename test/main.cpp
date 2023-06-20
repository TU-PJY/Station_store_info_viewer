#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#define MAX_LINE_LENGTH 100

using namespace std;

string cmd; //명령어 입력받는 스트링
string option; //옵션 입력받는 스트링
string mem_line, mem_station, mem_fee; //추천 데이터 검색 시 사용하는 스트링

int main() {
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

    //정렬 출력용 파일
    const char* sorted_fee = "data_fee.txt";
    const char* sorted_m2 = "data_m2.txt";

    //파일 읽어서 저장
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
    ArrayList* list_work_type = readFile(work_type);
    ArrayList* list_end_date = readFile(end_date);

    //인덱스 순서를 바꾸기 위해 사용하는 별도의 리스트
    ArrayList* sorted_list_fee = readFile(sorted_fee);
    ArrayList* sorted_list_m2 = readFile(sorted_m2);

    clock_t start, finish;
    double duration;

    //하나라도 정상 로드가 되지 않을 경우 종료
    if (list_place_type -> size != list_line -> size && list_place_type -> size != list_station -> size) {
        printf("|출력| 파일 불러오기를 할 수 없습니다.\n"); return 1; 
    }
    //모두 로드되면 프로그램 준비
    else printf("|출력| 파일 불러오기를 성공하였습니다.\n");

    //나중에 인덱스 순서 교환을 위해 인덱스를 1부터 끝 인덱스까지 저장한다.
    for (int i = 0; i < list_place_type->size; i++) {
        mem_index_fee[i] = i;
        mem_index_m2[i] = i;
    }

    while(1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "=======================================" << endl;
        cout << "서울교통공사 상가 데이터 검색 프로그램" << endl;
        cout << "데이터 기준: 2023.04.30" << endl;
        cout << "=======================================" << endl;
        printMenu(); printf("명령어 입력>> ");
        cin >> cmd;

        switch (atoi(cmd.c_str())) {
        case 1: //cmd = 1  모든 데이터 출력
            system("CLS"); end_for = false;
            for (;;) {
                if (end_for == true) break;
                cout << "===============검색 옵션===============" << endl;
                cout << "1: 임대료 표시된 데이터만 검색" << endl;
                cout << "2: 면적 표시된 데이터만 검색" << endl;
                cout << "3: 면적 낮은 순(2번 옵션 자동 활성화)" << endl;
                cout << "4: 면적 높은 순(2번 옵션 자동 활성화)" << endl;
                cout << "5: 낮은 가격 순(1번 옵션 자동 활성화)" << endl;
                cout << "6: 높은 가격 순(1번 옵션 자동 활성화)" << endl;
                cout << "7: 옵션 선택 안 함" << endl;
                cout << "=======================================" << endl;
                cout << "옵션 >> ";
                cin >> option;

                switch (atoi(option.c_str())) {
                case 1: //임대료 표시된 데이터만 검색
                    print_option = without0; end_for = true;
                    break;

                case 2: //면적 표시된 데이터만 검색
                    print_option = without0_width; end_for = true;
                    break;

                case 3: //면적 오름차순
                    print_option = up_width; end_for = true;
                    break;

                case 4: //면적 내림차순
                    print_option = down_width; end_for = true;
                    break;

                case 5: //임대료 오름차순
                    print_option = up_price; end_for = true;
                    break;

                case 6: //임대료 내림차순
                    print_option = down_price; end_for = true;
                    break;

                case 7: //선택 안 함
                    print_option = none_set;  end_for = true;
                    break;

                default:
                    system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                    break;
                }
            }

            system("CLS"); printBorder();

            switch (print_option) {
            case none_set: //옵션 없음
                for (int i = 0; i < list_place_type->size; i++)
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                break;


            case up_width: //면적 오름차순
                start = clock();
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, up_width);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index_m2[i]]) > 0)
                        printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                }
                break;


            case down_width: //면적 내림차순
                start = clock();
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, down_width);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index_m2[i]]) > 0)
                        printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                }
                break;


            case up_price: //임대료 오름차순
                //데이터 위치 교환 없이 인덱스 순서만 교환함
                //단, 인덱스 순서 교환을 위해 별도의 리스트를 같이 정렬해야함. 안그러면 인덱스 순서가 제대로 교환이 안됨
                start = clock();
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, up_price);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index_fee[i]]) > 0)
                        printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                }
                break;


            case down_price: //임대료 내림차순
                start = clock();
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, down_price);
                finish = clock();
                is_downsorted = true;
                is_upsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index_fee[i]]) > 0)
                        printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                }
                break;


            case without0: //임대료 표시 안 된 데이터 제외
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[i]) > 0)
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                }
                break;


            case without0_width: //면적 표시 안 된 데이터 제외
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[i]) > 0)
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                }
                break;
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printBorder(); cout << endl << "|출력| 데이터를 모두 출력하였습니다. 검색 옵션: ";
            if (print_option == without0) cout << "임대료 표시된 데이터만" << endl;
            else if (print_option == without0_width) cout << "면적 표시된 데이터만" << endl;
            else if (print_option == up_width) cout << "면적 낮은 순" << endl;
            else if (print_option == down_width) cout << "면적 높은 순" << endl;
            else if (print_option == up_price) cout << "낮은 가격 순" << endl;
            else if (print_option == down_price) cout << "높은 가격 순" << endl;
            else if (print_option == none_set) cout << "선택 안 함" << endl;

            if (print_option != without0 && print_option != without0_width) {
                duration = (double)(finish - start) / CLOCKS_PER_SEC;
                cout << "|처리 시간| " << duration << "ms" << endl;
            }

            break;


        case 2: //cmd = 2  노선 기준 검색
            //검색 전 초기 상태
            system("CLS"); search = false; is_number = true; end_for = false;
            color_out = false; //같은 노선의 데이터만 나오므로 색상 비활성화
            cout << "|출력| 어떤 노선을 검색 하시겠습니까?" << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(예: '1', '2', '3') >> ";
            cin >> cmd;

            //번호 외의 다른 문자열이 있을 경우 검색 안 함
            for (int i = 0; i < cmd.length(); i++) {
                if (isdigit(cmd[i]) == 0) is_number = false;
            }

            //만약 올바른 검색어라면 옵션 입력 후 출력 시작
            if (is_number == true) {
                system("CLS");
                for (;;) {
                    if (end_for == true) break;
                    cout << "===============검색 옵션===============" << endl;
                    cout << "1: 임대료 표시된 데이터만 검색" << endl;
                    cout << "2: 면적 표시된 데이터만 검색" << endl;
                    cout << "3: 면적 낮은 순(2번 옵션 자동 활성화)" << endl;
                    cout << "4: 면적 높은 순(2번 옵션 자동 활성화)" << endl;
                    cout << "5: 낮은 가격 순(1번 옵션 자동 활성화)" << endl;
                    cout << "6: 높은 가격 순(1번 옵션 자동 활성화)" << endl;
                    cout << "7: 옵션 선택 안 함" << endl;
                    cout << "=======================================" << endl;
                    cout << "옵션 >> ";
                    cin >> option;

                    switch (atoi(option.c_str())) {
                    case 1: //임대료 표시된 데이터만 검색
                        print_option = without0; end_for = true;
                        break;

                    case 2: //면적 표시된 데이터만 검색
                        print_option = without0_width; end_for = true;
                        break;

                    case 3: //면적 오름차순
                        print_option = up_width; end_for = true;
                        break;

                    case 4: //면적 내림차순
                        print_option = down_width; end_for = true;
                        break;

                    case 5: //임대료 오름차순
                        print_option = up_price; end_for = true;
                        break;

                    case 6: //임대료 내림차순
                        print_option = down_price; end_for = true;
                        break;

                    case 7: //선택 안 함
                        print_option = none_set;  end_for = true;
                        break;

                    default:
                        system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                        break;
                    }
                }


                system("CLS"); printBorder();

                switch (print_option) {
                case none_set: //옵션 없음
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_line->lines[i]) == atoi(cmd.c_str()))
                            printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                    }
                    break;


                case up_width: //면적 오름차순
                    start = clock();
                    mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, up_width);
                    finish = clock();
                    is_upsorted = true;
                    is_downsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && atoi(list_line->lines[mem_index_m2[i]]) == atoi(cmd.c_str()))
                            printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                    }
                    break;


                case down_width: //면적 내림차순
                    start = clock();
                    mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, down_width);
                    finish = clock();
                    is_upsorted = true;
                    is_downsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && atoi(list_line->lines[mem_index_m2[i]]) == atoi(cmd.c_str()))
                            printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                    }
                    break;


                case up_price: //임대료 오름차순
                    //데이터 위치 교환 없이 인덱스 순서만 교환함
                    //단, 인덱스 순서 교환을 위해 별도의 리스트를 같이 정렬해야함. 안그러면 인덱스 순서가 제대로 교환이 안됨
                    start = clock();
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, up_price);
                    finish = clock();
                    is_upsorted = true;
                    is_downsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && atoi(list_line->lines[mem_index_fee[i]]) == atoi(cmd.c_str()))
                            printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                    }
                    break;


                case down_price: //임대료 내림차순
                    start = clock();
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, down_price);
                    finish = clock();
                    is_downsorted = true;
                    is_upsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && atoi(list_line->lines[mem_index_fee[i]]) == atoi(cmd.c_str()))
                            printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                    }
                    break;


                case without0: //임대료 표시 안 된 데이터 제외
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[i]) > 0 && atoi(list_line->lines[i]) == atoi(cmd.c_str()))
                            printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                    }
                    break;


                case without0_width: //면적 표시 안 된 데이터 제외
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atof(list_m2->lines[i]) > 0 && atoi(list_line->lines[i]) == atoi(cmd.c_str()))
                            printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                    }
                    break;
                }

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printBorder(); cout << endl << "|출력| 데이터를 모두 출력하였습니다. 검색 옵션: ";
                if (print_option == without0) cout << "임대료 표시된 데이터만" << endl;
                else if (print_option == without0_width) cout << "면적 표시된 데이터만";
                else if (print_option == up_width) cout << "면적 낮은 순";
                else if (print_option == down_width) cout << "면적 높은 순";
                else if (print_option == up_price) cout << "낮은 가격 순";
                else if (print_option == down_price) cout << "높은 가격 순";
                else if (print_option == none_set) cout << "선택 안 함";
                cout << "| " << "검색 노선: " << cmd << "호선" << endl;

                if (print_option != without0 && print_option != without0_width) {
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;
                    cout << "|처리 시간| " << duration << "ms" << endl;
                }
            }
            
           else if (is_number == false) {
               system("CLS"); cout << "|출력| 올바른 검색어가 아닙니다." << endl;
           }

            color_out = true;
            break;


        case 3: //cmd = 3  역명 기준 검색
            //검색 전 초기 상태
            system("CLS"); search = false;

            cout << "|출력| 어떤 역을 검색 하시겠습니까?" << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(예: '길음', '혜화'| 환승역의 경우 '천호(8)','잠실(2)') >> ";
            cin >> cmd;

            system("CLS");
            for (;;) {
                if (end_for == true) break;
                cout << "===============검색 옵션===============" << endl;
                cout << "1: 임대료 표시된 데이터만 검색" << endl;
                cout << "2: 면적 표시된 데이터만 검색" << endl;
                cout << "3: 면적 낮은 순(2번 옵션 자동 활성화)" << endl;
                cout << "4: 면적 높은 순(2번 옵션 자동 활성화)" << endl;
                cout << "5: 낮은 가격 순(1번 옵션 자동 활성화)" << endl;
                cout << "6: 높은 가격 순(1번 옵션 자동 활성화)" << endl;
                cout << "7: 옵션 선택 안 함" << endl;
                cout << "=======================================" << endl;
                cout << "옵션 >> ";
                cin >> option;

                switch (atoi(option.c_str())) {
                case 1: //임대료 표시된 데이터만 검색
                    print_option = without0; end_for = true;
                    break;

                case 2: //면적 표시된 데이터만 검색
                    print_option = without0_width; end_for = true;
                    break;

                case 3: //면적 오름차순
                    print_option = up_width; end_for = true;
                    break;

                case 4: //면적 내림차순
                    print_option = down_width; end_for = true;
                    break;

                case 5: //임대료 오름차순
                    print_option = up_price; end_for = true;
                    break;

                case 6: //임대료 내림차순
                    print_option = down_price; end_for = true;
                    break;

                case 7: //선택 안 함
                    print_option = none_set;  end_for = true;
                    break;

                default:
                    system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                    break;
                }
            }


            system("CLS"); printBorder();

            switch (print_option) {
            case none_set: //옵션 없음
                for (int i = 0; i < list_place_type->size; i++) {
                    if (strstr(list_station->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case up_width: //면적 오름차순
                start = clock();
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, up_width);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && strstr(list_station->lines[mem_index_m2[i]], cmd.c_str())) {
                        printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case down_width: //면적 내림차순
                start = clock();
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, down_width);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && strstr(list_station->lines[mem_index_m2[i]], cmd.c_str())) {
                        printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case up_price: //임대료 오름차순
                //데이터 위치 교환 없이 인덱스 순서만 교환함
                //단, 인덱스 순서 교환을 위해 별도의 리스트를 같이 정렬해야함. 안그러면 인덱스 순서가 제대로 교환이 안됨
                start = clock();
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, up_price);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && strstr(list_station->lines[mem_index_fee[i]], cmd.c_str())) {
                        printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case down_price: //임대료 내림차순
                start = clock();
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, down_price);
                finish = clock();
                is_downsorted = true;
                is_upsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && strstr(list_station->lines[mem_index_fee[i]], cmd.c_str())) {
                        printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case without0: //임대료 표시 안 된 데이터 제외
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[i]) > 0 && strstr(list_station->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case without0_width: //면적 표시 안 된 데이터 제외
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[i]) > 0 && strstr(list_station->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;
            }

            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 역명| 검색어: " << cmd << endl;
            }
            //검색결과가 나오지 않으면 그대로 false
            else if (search == false) {
                system("CLS"); cout << "|출력| 그런 데이터가 없습니다." << endl;
            }
            break;


        case 4:  //cmd = 4  업종 기준 검색
            //검색 전 초기 상태
            system("CLS");  search = false; end_for = false;

            cout << "|출력| 어떤 업종을 검색 하시겠습니까?" << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(예: '플라워', '화장품', '화', '무인' 등) >> ";
            cin >> cmd;

            system("CLS");
            for (;;) {
                if (end_for == true) break;
                cout << "===============검색 옵션===============" << endl;
                cout << "1: 임대료 표시된 데이터만 검색" << endl;
                cout << "2: 면적 표시된 데이터만 검색" << endl;
                cout << "3: 면적 낮은 순(2번 옵션 자동 활성화)" << endl;
                cout << "4: 면적 높은 순(2번 옵션 자동 활성화)" << endl;
                cout << "5: 낮은 가격 순(1번 옵션 자동 활성화)" << endl;
                cout << "6: 높은 가격 순(1번 옵션 자동 활성화)" << endl;
                cout << "7: 옵션 선택 안 함" << endl;
                cout << "=======================================" << endl;
                cout << "옵션 >> ";
                cin >> option;

                switch (atoi(option.c_str())) {
                case 1: //임대료 표시된 데이터만 검색
                    print_option = without0; end_for = true;
                    break;

                case 2: //면적 표시된 데이터만 검색
                    print_option = without0_width; end_for = true;
                    break;

                case 3: //면적 오름차순
                    print_option = up_width; end_for = true;
                    break;

                case 4: //면적 내림차순
                    print_option = down_width; end_for = true;
                    break;

                case 5: //임대료 오름차순
                    print_option = up_price; end_for = true;
                    break;

                case 6: //임대료 내림차순
                    print_option = down_price; end_for = true;
                    break;

                case 7: //선택 안 함
                    print_option = none_set;  end_for = true;
                    break;

                default:
                    system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                    break;
                }
            }


            system("CLS"); printBorder();

            switch (print_option) {
            case none_set: //옵션 없음
                for (int i = 0; i < list_place_type->size; i++) {
                    if (strstr(list_work_type->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case up_width: //면적 오름차순
                start = clock();
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, up_width);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && strstr(list_work_type->lines[mem_index_m2[i]], cmd.c_str())) {
                        printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case down_width: //면적 내림차순
                start = clock();
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, down_width);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && strstr(list_work_type->lines[mem_index_m2[i]], cmd.c_str())) {
                        printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case up_price: //임대료 오름차순
                //데이터 위치 교환 없이 인덱스 순서만 교환함
                //단, 인덱스 순서 교환을 위해 별도의 리스트를 같이 정렬해야함. 안그러면 인덱스 순서가 제대로 교환이 안됨
                start = clock();
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, up_price);
                finish = clock();
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && strstr(list_work_type->lines[mem_index_fee[i]], cmd.c_str())) {
                        printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case down_price: //임대료 내림차순
                start = clock();
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, down_price);
                finish = clock();
                is_downsorted = true;
                is_upsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && strstr(list_work_type->lines[mem_index_fee[i]], cmd.c_str())) {
                        printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case without0: //임대료 표시 안 된 데이터 제외
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[i]) > 0 && strstr(list_work_type->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;


            case without0_width: //면적 표시 안 된 데이터 제외
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[i]) > 0 && strstr(list_work_type->lines[i], cmd.c_str())) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                        search = true;
                    }
                }
                break;
            }

            
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printBorder(); cout << endl << "|출력| 데이터를 모두 출력하였습니다. 검색 옵션: ";
                if (print_option == without0) cout << "임대료 표시된 데이터만" << endl;
                else if (print_option == without0_width) cout << "면적 표시된 데이터만" << endl;
                else if (print_option == up_width) cout << "면적 낮은 순" << endl;
                else if (print_option == down_width) cout << "면적 높은 순" << endl;
                else if (print_option == up_price) cout << "낮은 가격 순" << endl;
                else if (print_option == down_price) cout << "높은 가격 순" << endl;
                else if (print_option == none_set) cout << "선택 안 함" << endl;
                cout << "| " << "검색어: " << cmd << endl;

                if (print_option != without0 && print_option != without0_width) {
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;
                    cout << "|처리 시간| " << duration << "ms" << endl;
                }
            }
            //검색결과가 나오지 않으면 그대로 false
            else if (search == false) {
                system("CLS"); cout << "|출력| 그런 데이터가 없습니다." << endl;
            }
            break;


        case 5: //cmd = 5  임대료 기준 검색
            system("CLS");  search = false; is_number = true; end_for = false;

            cout << "|출력| 임대료 상한선을 입력해주세요." << endl;
            cout << "===============검색어 입력===============" << endl;
            cout << "(숫자만 입력, 예: 1120000, 340000) >> ";
            cin >> cmd;
            
            //입력한 커맨드가 숫자인지 아닌지 검색, 숫자 이외의 다른 문자가 껴 있을 경우 숫자로 판정 안되어 검색 진행 하지 않음
            for (int i = 0; i < cmd.length(); i++) {
                if (isdigit(cmd[i]) == 0) is_number = false;
            }


            if (is_number == true) {
                for (;;) {
                    if (end_for == true) break;
                    cout << "===============검색 옵션===============" << endl;
                    cout << "1: 가격 높은 순" << endl;
                    cout << "2: 가격 낮은 순" << endl;
                    cout << "3: 옵션 선택 안 함" << endl;
                    cout << "=======================================" << endl;
                    cout << "옵션 >> ";
                    cin >> option;
                    
                    switch(atoi(option.c_str())) {
                    case 1: //내림차순
                        print_option = down; end_for = true;
                        break;

                    case 2: //오름차순
                        print_option = up; end_for = true; 
                        break;

                    case 3: //선택 안 함
                        print_option = none;  end_for = true;
                        break;

                    default:
                        system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                        break;
                    }
                }

                system("CLS"); printBorder(); 
                switch (print_option) {
                case none:
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[i]) < atoi(cmd.c_str()) && atoi(list_fee->lines[i]) > 0) {
                            printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                            search = true; //검색결과가 나오면 true
                        }
                    }
                    break;

                case up: //오름차순
                    //데이터 위치 교환 없이 인덱스 순서만 교환함
                    //단, 인덱스 순서 교환을 위해 별도의 리스트를 같이 정렬해야함. 안그러면 인덱스 순서가 제대로 교환이 안됨
                    start = clock();
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, up);
                    finish = clock();
                    is_upsorted = true;
                    is_downsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && atoi(list_fee->lines[mem_index_fee[i]]) < atoi(cmd.c_str())) {
                            printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                            search = true; //검색결과가 나오면 true
                        }
                    }
                    break;


                case down: //내림차순
                    start = clock();
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, down);
                    finish = clock();
                    is_downsorted = true;
                    is_upsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && atoi(list_fee->lines[mem_index_fee[i]]) < atoi(cmd.c_str())) {
                            printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                            search = true; //검색결과가 나오면 true
                        }
                    }
                    break;
                }
                
                if (search == true) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printBorder(); cout << endl << "|출력| 검색한 데이터를 모두 출력하였습니다. 검색 기준: 임대료| 상한선: " << cmd << "￦| "; 

                    if (is_upsorted == true) cout << "옵션: 낮은 가격 순" << endl;
                    else if (is_downsorted == true) cout << "옵션: 높은 가격 순" << endl;
                    else cout << "옵션: 선택 안 함" << endl;

                    duration = (double)(finish - start) / CLOCKS_PER_SEC;
                    cout << "|처리 시간| " << duration << "ms" << endl;
                }
                else if (search == false) {
                    system("CLS"); cout << "|출력| 해당 상한선 내의 임대료 데이터를 찾을 수 없습니다." << endl;
                }
            }
            else if (is_number == false) {
                system("CLS"); cout << "|출력| 올바른 숫자가 아닙니다." << endl;
            }
            break;

        case 6: //cmd = 6  추천 데이터 검색
            system("CLS"); 
            is_number = true; is_escape = false;
           
            for (;;) {
                if (is_escape == true) break;
                end_for = false;
                
                switch (current_state) {
                case input:
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
                            system("CLS"); cout << "|출력| 올바르지 않은 검색어 입니다." << endl;
                            is_number = true;
                        }
                    }
                    system("CLS");
                    current_state = check;
                    break;
                    
                case check: //확인 단계
                    for (;;) {
                        if (end_for == true) break;
                        cout << "|출력| 지금까지 입력한 필터는 다음과 같습니다." << endl << endl;
                        cout << "노선: " << mem_line << "호선 | " << "역명: " << mem_station << " | " << "임대료 상한선: " << mem_fee << "￦" << endl << endl;
                        cout << "===============메뉴 선택===============" << endl;
                        cout << "1: 입력 데이터 확정 후 검색" << endl;
                        cout << "2: 다시 입력하기" << endl;
                        cout << "3: 취소 후 나가기" << endl;
                        cout << "=======================================" << endl;
                        printf("명령어 입력>> ");
                        cin >> cmd;

                        switch (atoi(cmd.c_str())) {
                        case 1:
                            system("CLS"); current_state = output; end_for = true;
                            break;

                        case 2:
                            system("CLS");  current_state = input; end_for = true;
                            break;

                        case 3:
                            system("CLS"); is_escape = true; end_for = true; current_state = input;
                            break;

                        default:
                            system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                            break;
                        }
                    }
                    if (end_for == true && current_state == input) break;

                    system("CLS"); end_for = false;
                    for (;;) {
                        if (end_for == true) {
                            break;
                        }
                        cout << "===============검색 옵션===============" << endl;
                        cout << "1: 임대료 표시된 데이터만 검색" << endl;
                        cout << "2: 면적 표시된 데이터만 검색" << endl;
                        cout << "3: 면적 낮은 순(2번 옵션 자동 활성화)" << endl;
                        cout << "4: 면적 높은 순(2번 옵션 자동 활성화)" << endl;
                        cout << "5: 낮은 가격 순(1번 옵션 자동 활성화)" << endl;
                        cout << "6: 높은 가격 순(1번 옵션 자동 활성화)" << endl;
                        cout << "7: 옵션 선택 안 함" << endl;
                        cout << "=======================================" << endl;
                        cout << "옵션 >> ";
                        cin >> option;

                        switch (atoi(option.c_str())) {
                        case 1: //임대료 표시된 데이터만 검색
                            print_option = without0; end_for = true;
                            break;

                        case 2: //면적 표시된 데이터만 검색
                            print_option = without0_width; end_for = true;
                            break;

                        case 3: //면적 오름차순
                            print_option = up_width; end_for = true;
                            break;

                        case 4: //면적 내림차순
                            print_option = down_width; end_for = true;
                            break;

                        case 5: //임대료 오름차순
                            print_option = up_price; end_for = true;
                            break;

                        case 6: //임대료 내림차순
                            print_option = down_price; end_for = true;
                            break;

                        case 7: //선택 안 함
                            print_option = none_set;  end_for = true;
                            break;

                        default:
                            system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                            break;
                        }
                    }

                    break;


                case output: //출력 단계
                    search = false; end_for = false;
                    system("CLS"); printBorder();

                    switch (print_option) {
                    case none_set: //옵션 없음
                        for (int i = 0; i < list_place_type->size; i++) {
                            if (strstr(list_line->lines[i], mem_line.c_str()) && strstr(list_station->lines[i], mem_station.c_str()) &&
                                atoi(list_fee->lines[i]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[i]) > 0) {
                                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                                search = true;
                            }
                        }
                        break;


                    case up_width: //면적 오름차순
                        start = clock();
                        mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, up_width);
                        finish = clock();
                        is_upsorted = true;
                        is_downsorted = false;

                        for (int i = 0; i < list_place_type->size; i++) {
                            if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && strstr(list_line->lines[mem_index_m2[i]], mem_line.c_str()) && strstr(list_station->lines[mem_index_m2[i]], mem_station.c_str()) &&
                                atoi(list_fee->lines[mem_index_m2[i]]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[mem_index_m2[i]]) > 0) {
                                printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                                search = true;
                            }
                        }
                        break;


                    case down_width: //면적 내림차순
                        start = clock();
                        mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index_m2, 0, sorted_list_m2->size - 1, down_width);
                        finish = clock();
                        is_upsorted = true;
                        is_downsorted = false;

                        for (int i = 0; i < list_place_type->size; i++) {
                            if (atof(list_m2->lines[mem_index_m2[i]]) > 0 && strstr(list_line->lines[mem_index_m2[i]], mem_line.c_str()) && strstr(list_station->lines[mem_index_m2[i]], mem_station.c_str()) &&
                                atoi(list_fee->lines[mem_index_m2[i]]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[mem_index_m2[i]]) > 0) {
                                printData(mem_index_m2[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                                search = true;
                            }
                        }
                        break;


                    case up_price: //임대료 오름차순
                        //데이터 위치 교환 없이 인덱스 순서만 교환함
                        //단, 인덱스 순서 교환을 위해 별도의 리스트를 같이 정렬해야함. 안그러면 인덱스 순서가 제대로 교환이 안됨
                        start = clock();
                        mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, up_price);
                        finish = clock();
                        is_upsorted = true;
                        is_downsorted = false;

                        for (int i = 0; i < list_place_type->size; i++) {
                            if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && strstr(list_line->lines[mem_index_fee[i]], mem_line.c_str()) && strstr(list_station->lines[mem_index_fee[i]], mem_station.c_str()) &&
                                atoi(list_fee->lines[mem_index_fee[i]]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[mem_index_fee[i]]) > 0) {
                                printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                                search = true;
                            }
                        }
                        break;


                    case down_price: //임대료 내림차순
                        start = clock();
                        mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index_fee, 0, sorted_list_fee->size - 1, down_price);
                        finish = clock();
                        is_downsorted = true;
                        is_upsorted = false;

                        for (int i = 0; i < list_place_type->size; i++) {
                            if (atoi(list_fee->lines[mem_index_fee[i]]) > 0 && strstr(list_line->lines[mem_index_fee[i]], mem_line.c_str()) && strstr(list_station->lines[mem_index_fee[i]], mem_station.c_str()) &&
                                atoi(list_fee->lines[mem_index_fee[i]]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[mem_index_fee[i]]) > 0) {
                                printData(mem_index_fee[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                                search = true;
                            }
                        }
                        break;


                    case without0: //임대료 표시 안 된 데이터 제외
                        for (int i = 0; i < list_place_type->size; i++) {
                            if (atoi(list_fee->lines[i]) > 0 && strstr(list_line->lines[i], mem_line.c_str()) && strstr(list_station->lines[i], mem_station.c_str()) &&
                                atoi(list_fee->lines[i]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[i]) > 0) {
                                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                                search = true;
                            }
                        }
                        break;


                    case without0_width: //면적 표시 안 된 데이터 제외
                        for (int i = 0; i < list_place_type->size; i++) {
                            if (atof(list_m2->lines[i]) > 0 && strstr(list_line->lines[i], mem_line.c_str()) && strstr(list_station->lines[i], mem_station.c_str()) &&
                                atoi(list_fee->lines[i]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[i]) > 0) {
                                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date, color_out);
                                search = true;
                            }
                        }
                        break;
                    }


                    if (search == true) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printBorder(); cout << endl << "|출력| 데이터를 모두 출력하였습니다. 검색 옵션: ";
                        if (print_option == without0) cout << "임대료 표시된 데이터만" << endl;
                        else if (print_option == without0_width) cout << "면적 표시된 데이터만" << endl;
                        else if (print_option == up_width) cout << "면적 낮은 순" << endl;
                        else if (print_option == down_width) cout << "면적 높은 순" << endl;
                        else if (print_option == up_price) cout << "낮은 가격 순" << endl;
                        else if (print_option == down_price) cout << "높은 가격 순" << endl;
                        else if (print_option == none_set) cout << "선택 안 함" << endl;
                        cout << "|검색 필터| 노선: " << mem_line << "호선 | " << "역명: " << mem_station << " | " << "임대료 상한선: " << mem_fee << "￦" << endl;

                        if (print_option != without0 && print_option != without0_width) {
                            duration = (double)(finish - start) / CLOCKS_PER_SEC;
                            cout << "|처리 시간| " << duration << "ms" << endl;
                        }
                        
                        current_state = input; is_escape = true; break;
                    }

                    else if (search == false) {
                        system("CLS"); cout << "|출력| 필터에 맞는 데이터가 없는것 같습니다. 다시 입력하시겠습니까?" << endl;

                        for (;;) {
                            if (end_for == true) break;
                            cout << "===============메뉴 선택===============" << endl;
                            cout << "1: 다시 입력하기" << endl;
                            cout << "2: 취소 후 나가기" << endl;
                            cout << "=======================================" << endl;
                            cin >> cmd;

                            switch (atoi(cmd.c_str())) {
                            case 1:
                                system("CLS"); current_state = input; end_for = true;
                                break;

                            case 2:
                                system("CLS"); current_state = input; mem_line = ""; mem_station = ""; mem_fee = ""; is_escape = true; end_for = true;
                                break;

                            default:
                                system("CLS"); cout << "|출력| 알 수 없는 명령어 입니다." << endl;
                                break;
                            }
                        }
                    }
                    break;

                }
            }
            break;

            default: //텍스트 지우기
                system("CLS"); cout << "|출력| 텍스트를 모두 지웠습니다." << endl;
                break;
        }

        if (cmd == "q") { //cmd = q  프로그램 종료
            system("CLS"); cout << "|출력| 프로그램을 종료합니다." << endl; break;
        }
    }

    return 0;
}

