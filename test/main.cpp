#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#define MAX_LINE_LENGTH 100

using namespace std;

string cmd; //��ɾ� �Է¹޴� ��Ʈ��
string option; //�ɼ� �Է¹޴� ��Ʈ��
string mem_line, mem_station, mem_fee; //��õ ������ �˻� �� ����ϴ� ��Ʈ��
string s_temp;

//������ ��� �Լ�
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList*list_place_number, ArrayList* list_place_type, 
                ArrayList* list_work_type, ArrayList*list_m2, ArrayList* list_fee, ArrayList * list_end_date) {   
    //�뼱�� ���� ������ �ٸ��� ���
    if (color_out == true) { //color_out�� true�� ���� ���� ���
        if (strstr(list_line->lines[i], "1ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "2ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "3ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "4ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "5ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        else if (strstr(list_line->lines[i], "6ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
        else if (strstr(list_line->lines[i], "7ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        else if (strstr(list_line->lines[i], "8ȣ��"))
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    cout.width(5); cout << i << "| ";
    cout << list_line->lines[i] << "| ";
    cout.width(25); cout << list_station->lines[i] << "| ";
    cout.width(10); cout << list_place_number->lines[i] << "| ";
    cout.width(15); cout << list_place_type->lines[i] << "| ";
    cout.width(10); cout << list_work_type->lines[i] << "| ";
    cout.width(10); cout << list_m2->lines[i] << " m^2| ";
    cout.width(10); cout << list_fee->lines[i] << " ��| ";
    cout.width(10); cout << list_end_date->lines[i] << " |";
    cout << endl;
}

// ���� ��Ʈ
void merge(char* arr[], int l, int m, int r, int index[], int index_l, int index_m, int index_r, int state) {
    int n1 = m - l + 1; // ���� �κ� �迭�� ũ��
    int n2 = r - m; // ������ �κ� �迭�� ũ��

    // �ӽ� �迭 ���� �� ����
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

    // �ӽ� �迭�� ����Ͽ� ����
    int i = 0; // ���� �κ� �迭�� �ε���
    int j = 0; // ������ �κ� �迭�� �ε���
    int k = l; // ���յ� �迭�� �ε���

    while (i < n1 && j < n2) {
        //��������
        if (strcmp(left_arr[i], right_arr[j]) <= 0 && state == up) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }

        //��������
        else  if (strcmp(left_arr[i], right_arr[j]) >= 0 && state == down) {
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

    // ���� ��ҵ��� ����
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

    // ���� �Ҵ��� �޸� ����
    delete[] left_arr;
    delete[] right_arr;
    delete[] left_index;
    delete[] right_index;
}

// ���� ��Ʈ
void mergeSort(char* arr[], int l, int r, int index[], int index_l, int index_r, int state) {
    if (l < r) {
        int m = l + (r - l) / 2; // �߰� ����

        // ���ʰ� ������ �κ� �迭�� ��������� ����
        mergeSort(arr, l, m, index, index_l, index_l + (m - l), state);
        mergeSort(arr, m + 1, r, index, index_l + (m - l) + 1, index_r, state);

        // ���ĵ� �κ� �迭�� ����
        merge(arr, l, m, r, index, index_l, index_l + (m - l), index_r, state);
    }
}


int main() {
    //�뼱
    const char* line = "data_line.txt";
    //����
    const char* station = "data_station.txt";
    //�� ��ȣ
    const char* place_number = "data_place_number.txt";
    //�� ����
    const char* place_type = "data_place_type.txt";
    //�� ����
    const char* m2 = "data_m2.txt";
    //�� �Ӵ��
    const char* fee = "data_fee.txt";
    //����
    const char* work_type = "data_work_type.txt";
    //��� ������
    const char* end_date = "data_end_date.txt";

    //���� ��¿� ����
    const char* sorted_fee = "data_fee.txt";

    //���� �о ����
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
    ArrayList* list_work_type = readFile(work_type);
    ArrayList* list_end_date = readFile(end_date);

    //�ε��� ������ �ٲٱ� ���� ����ϴ� ������ ����Ʈ
    ArrayList* sorted_list_fee = readFile(sorted_fee);

    //�ϳ��� ���� �ε尡 ���� ���� ��� ����
    if (list_place_type -> size != list_line -> size && list_place_type -> size != list_station -> size) {
        printf("|���| ���� �ҷ����⸦ �� �� �����ϴ�.\n"); return 1; 
    }
    //��� �ε�Ǹ� ���α׷� �غ�
    else printf("|���| ���� �ҷ����⸦ �����Ͽ����ϴ�.\n");

    //���߿� �ε��� ���� ��ȯ�� ���� �ε����� 1���� �� �ε������� �����Ѵ�.
    for (int i = 0; i < list_place_type->size; i++)
        mem_index[i] = i;

    while(1) {
        is_escape = false;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "=======================================" << endl;
        cout << "���ﱳ����� �� ������ �˻� ���α׷�" << endl;
        cout << "������ ����: 2023.04.30" << endl;
        cout << "=======================================" << endl;
        printMenu(); printf("��ɾ� �Է�>> ");
        cin >> cmd;

        switch (atoi(cmd.c_str())) {
        case 1: //cmd = 1  ��� ������ ���
            system("CLS"); printBorder();

            for (int i = 0; i < list_place_type->size; i++)
                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printBorder(); cout << endl << "|���| �����͸� ��� ����Ͽ����ϴ�." << endl;
            break;


        case 2: //cmd = 2  �뼱 ���� �˻�
            //�˻� �� �ʱ� ����
            system("CLS"); search = false; is_number = true;
            color_out = false; //���� �뼱�� �����͸� �����Ƿ� ���� ��Ȱ��ȭ
            cout << "|���| � �뼱�� �˻� �Ͻðڽ��ϱ�?" << endl;
            cout << "===============�˻��� �Է�===============" << endl;
            cout << "(��: '1', '2', '3') >> ";
            cin >> cmd;

            //��ȣ ���� �ٸ� ���ڿ��� ���� ��� �˻� �� ��
            for (int i = 0; i < cmd.length(); i++) {
                if (isdigit(cmd[i]) == 0) is_number = false;
            }

            //���� �ùٸ� �˻����� ��� ����
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
                    printBorder(); cout << endl << "|���| �˻��� �����͸� ��� ����Ͽ����ϴ�. �˻� ����: �뼱 ��ȣ" << endl;
                }
                else if (search == false) {
                    system("CLS"); cout << "|���| �׷� �����Ͱ� �����ϴ�." << endl;
                }
            }
            else if (is_number == false) {
                system("CLS"); cout << "|���| �ùٸ� ���ڰ� �ƴմϴ�." << endl;
            }
            
            color_out = true;
            break;


        case 3: //cmd = 3  ���� ���� �˻�
            //�˻� �� �ʱ� ����
            system("CLS"); search = false;

            cout << "|���| � ���� �˻� �Ͻðڽ��ϱ�?" << endl;
            cout << "===============�˻��� �Է�===============" << endl;
            cout << "(��: '����', '��ȭ'| ȯ�¿��� ��� 'õȣ(8)','���(2)') >> ";
            cin >> cmd;

            //�ϴ� �˻�
            cout << endl;
            printBorder();
            for (int i = 0; i < list_place_type->size; i++) {
                if (strstr(list_station->lines[i], cmd.c_str())) {
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                    search = true; //�˻������ ������ true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printBorder(); cout << endl << "|���| �˻��� �����͸� ��� ����Ͽ����ϴ�. �˻� ����: ����" << endl;
            }
            //�˻������ ������ ������ �״�� false
            else if (search == false) {
                system("CLS"); cout << "|���| �׷� �����Ͱ� �����ϴ�." << endl;
            }
            break;


        case 4:  //cmd = 4  ���� ���� �˻�
            //�˻� �� �ʱ� ����
            system("CLS");  search = false;

            cout << "|���| � ������ �˻� �Ͻðڽ��ϱ�?" << endl;
            cout << "===============�˻��� �Է�===============" << endl;
            cout << "(��: '�ö��', 'ȭ��ǰ', 'ȭ', '����' ��) >> ";
            cin >> cmd;

            cout << endl;
            printBorder();
            for (int i = 0; i < list_place_type->size; i++) {
                if (strstr(list_work_type->lines[i], cmd.c_str())) {
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                    search = true; //�˻������ ������ true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                printBorder(); cout << endl << "|���| �˻��� �����͸� ��� ����Ͽ����ϴ�. �˻� ����: ����" << endl;
            }
            //�˻������ ������ ������ �״�� false
            else if (search == false) {
                system("CLS"); cout << "|���| �׷� �����Ͱ� �����ϴ�." << endl;
            }
            break;


        case 5: //cmd = 5  �Ӵ�� ���� �˻�
            system("CLS");  search = false; is_number = true; end_for = false;

            cout << "|���| �Ӵ�� ���Ѽ��� �Է����ּ���." << endl;
            cout << "===============�˻��� �Է�===============" << endl;
            cout << "(���ڸ� �Է�, ��: 1120000, 340000) >> ";
            cin >> cmd;
            
            //�Է��� Ŀ�ǵ尡 �������� �ƴ��� �˻�, ���� �̿��� �ٸ� ���ڰ� �� ���� ��� ���ڷ� ���� �ȵǾ� �˻� ���� ���� ����
            for (int i = 0; i < cmd.length(); i++) {
                if (isdigit(cmd[i]) == 0) is_number = false;
            }


            if (is_number == true) {
                for (;;) {
                    if (end_for == true) break;
                    cout << "===============�˻� �ɼ�===============" << endl;
                    cout << "1: ���� ���� ��" << endl;
                    cout << "2: ���� ���� ��" << endl;
                    cout << "3: �ɼ� ���� �� ��" << endl;
                    cout << "=======================================" << endl;
                    cin >> option;
                    
                    switch(atoi(option.c_str())) {
                    case 1: //��������
                        print_option = down; end_for = true;
                        break;

                    case 2: //��������
                        print_option = up; end_for = true; 
                        break;

                    case 3: //���� �� ��
                        print_option = none;  end_for = true;
                        break;

                    default:
                        system("CLS"); cout << "|���| �� �� ���� ��ɾ� �Դϴ�." << endl;
                        break;
                    }
                }

                //system("CLS");
                cout << endl;
                printBorder();
                
                switch (print_option) {
                case none:
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[i]) < atoi(cmd.c_str()) && atoi(list_fee->lines[i]) > 0) {
                            printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                            search = true; //�˻������ ������ true
                        }
                    }
                    break;

                case up: //��������
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index, 0, list_place_type->size - 1, up);
                    //�ɼ� ����� ���� ���� ���� ����
                    is_upsorted = true;
                    is_downsorted = false;
                    
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[mem_index[i]]) > 0 && atoi(list_fee->lines[mem_index[i]]) < atoi(cmd.c_str())) {
                            printData(mem_index[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                            //cout << mem_index[i] << endl;
                            search = true; //�˻������ ������ true
                       }
                    }
                    break;


                case down: //��������
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index, 0, list_place_type->size - 1, down);
                    //�ɼ� ����� ���� ���� ���� ����
                    is_downsorted = true;
                    is_upsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[mem_index[i]]) > 0 && atoi(list_fee->lines[mem_index[i]]) < atoi(cmd.c_str())) {
                            printData(mem_index[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                            search = true; //�˻������ ������ true
                        }
                    }
                    break;
                }
                
                if (search == true) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printBorder(); cout << endl << "|���| �˻��� �����͸� ��� ����Ͽ����ϴ�. �˻� ����: �Ӵ��| ���Ѽ�: " << cmd << "��| "; 
                    if (is_upsorted == true) cout << "�ɼ�: ���� ���� ��" << endl;
                    else if (is_downsorted == true) cout << "�ɼ�: ���� ���� ��" << endl;
                    else cout << "�ɼ�: ���� �� ��" << endl;
                }
                else if (search == false) {
                    system("CLS"); cout << "|���| �ش� ���Ѽ� ���� �Ӵ�� �����͸� ã�� �� �����ϴ�." << endl;
                }
            }
            else if (is_number == false) {
                system("CLS"); cout << "|���| �ùٸ� ���ڰ� �ƴմϴ�." << endl;
            }
            break;

        case 6: //cmd = 7  ��õ ������ �˻�
            system("CLS"); 
            is_number = true; is_escape = false;
           
            for (;;) {
                if (is_escape == true) break;
                end_for = false;
                
                switch (current_state) {
                case input: //�Է� �ܰ�
                    for (;;) {
                        cout << "|���| �뼱�� �Է��� �ּ���." << endl;
                        cout << "===============���� �Է�===============" << endl;
                        cout << "(��: '1', '2', '3') >> ";

                        cin >> mem_line;

                        for (int i = 0; i < mem_line.length(); i++) {
                            if (isdigit(mem_line[i]) == 0) is_number = false;
                        }
                        if (is_number == true)  break;
                        else if (is_number == false) {
                            system("CLS"); cout << "|���| �ùٸ��� ���� �˻����Դϴ�." << endl;
                            is_number = true;
                        }
                    }
                    system("CLS");


                    for (;;) {
                        cout << "|���| ������ �Է��� �ּ���." << endl;
                        cout << "===============���� �Է�===============" << endl;
                        cout << "(��: '���빮', 'õȣ' �Ǵ� '1', '2') >> ";

                        cin >> mem_station;
                        break;
                    }
                    system("CLS");

                    for (;;) {
                        cout << "|���| �Ӵ�� ���Ѽ��� �Է����ּ���." << endl;
                        cout << "===============���� �Է�===============" << endl;
                        cout << "(���ڸ� �Է�, ��: 1120000, 340000) >> ";

                        cin >> mem_fee;

                        for (int i = 0; i < cmd.length(); i++) {
                            if (isdigit(cmd[i]) == 0) is_number = false;
                        }
                        if (is_number == true) break;
                        if (is_number == false) {
                            system("CLS"); cout << "|���| �ùٸ��� ���� �˻��� �Դϴ�." << endl;
                            is_number = true;
                        }
                    }
                    system("CLS");
                    current_state = check;
                    break;


                case check: //Ȯ�� �ܰ�
                    for (;;) {
                        if (end_for == true) break;
                        cout << "|���| ���ݱ��� �Է��� ���ʹ� ������ �����ϴ�." << endl << endl;
                        cout << "�뼱: " << mem_line << "ȣ�� | " << "����: " << mem_station << " | " << "�Ӵ�� ���Ѽ�: " << mem_fee << "��" << endl << endl;
                        cout << "===============�޴� ����===============" << endl;
                        cout << "1: �Է� ������ Ȯ�� �� �˻�" << endl;
                        cout << "2: �ٽ� �Է��ϱ�" << endl;
                        cout << "3: ��� �� ������" << endl;
                        cout << "=======================================" << endl;
                        printf("��ɾ� �Է�>> ");
                        cin >> cmd;

                        switch (atoi(cmd.c_str())) {
                        case 1:
                            system("CLS");  current_state = output; end_for = true;
                            break;

                        case 2:
                            system("CLS");  current_state = input; end_for = true;
                            break;

                        case 3:
                            system("CLS"); is_escape = true; end_for = true; current_state = input;
                            break;

                        default:
                            system("CLS"); cout << "|���| �� �� ���� ��ɾ� �Դϴ�." << endl;
                            break;
                        }
                    }
                    break;


                case output: //��� �ܰ�
                    search = false; end_for = false;
                    printBorder();
                    for (int i = 0; i < list_place_type->size; i++) {
                        if (strstr(list_line->lines[i], mem_line.c_str()) && strstr(list_station->lines[i], mem_station.c_str()) &&
                            atoi(list_fee->lines[i]) < atoi(mem_fee.c_str()) && atoi(list_fee->lines[i]) > 0) {
                            printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                            search = true; //�˻������ ������ true
                        }
                    }

                    if (search == true) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printBorder();  cout << endl << "|���| �����͸� ������� ��õ�帮�� �󰡴� ���� �����ϴ�." << endl;

                        current_state = input; is_escape = true; break;
                    }

                    else if (search == false) {
                        system("CLS"); cout << "|���| ���Ϳ� �´� �����Ͱ� ���°� �����ϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?" << endl;

                        for (;;) {
                            if (end_for == true) break;
                            cout << "===============�޴� ����===============" << endl;
                            cout << "1: �ٽ� �Է��ϱ�" << endl;
                            cout << "2: ��� �� ������" << endl;
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
                                system("CLS"); cout << "|���| �� �� ���� ��ɾ� �Դϴ�." << endl;
                                break;
                            }
                        }
                    }
                    break;

                }
            }
            break;

            default: //�ؽ�Ʈ �����
                system("CLS"); cout << "|���| �ؽ�Ʈ�� ��� �������ϴ�." << endl;
                break;
        }

        if (cmd == "q") { //cmd = q  ���α׷� ����
            system("CLS"); cout << "|���| ���α׷��� �����մϴ�." << endl; break;
        }
    }

    return 0;
}

