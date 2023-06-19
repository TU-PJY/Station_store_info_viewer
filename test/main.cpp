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
    const char* sorted_m2 = "data_m2.txt";

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
    ArrayList* sorted_list_m2 = readFile(sorted_m2);

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
            system("CLS"); end_for = false;
            for (;;) {
                if (end_for == true) break;
                cout << "===============�˻� �ɼ�===============" << endl;
                cout << "1: �Ӵ�� ǥ�õ� �����͸� �˻�" << endl;
                cout << "2: ���� ǥ�õ� �����͸� �˻�" << endl;
                cout << "3: ���� ���� ��(2�� �ɼ� �ڵ� Ȱ��ȭ)" << endl;
                cout << "4: ���� ���� ��(1�� �ɼ� �ڵ� Ȱ��ȭ)" << endl;
                cout << "5: ���� ���� ��(2�� �ɼ� �ڵ� Ȱ��ȭ)" << endl;
                cout << "6: ���� ���� ��(1�� �ɼ� �ڵ� Ȱ��ȭ)" << endl;
                cout << "7: �ɼ� ���� �� ��" << endl;
                cout << "=======================================" << endl;
                cout << "�ɼ� >> ";
                cin >> option;

                switch (atoi(option.c_str())) {
                case 1: //�Ӵ�� ǥ�õ� �����͸� �˻�
                    print_option = without0; end_for = true;
                    break;

                case 2:
                    print_option = without0_width; end_for = true;
                    break;

                case 3: //���� ��������
                    print_option = up_width; end_for = true;
                    break;

                case 4: //�Ӵ�� ��������
                    print_option = up_price; end_for = true;
                    break;

                case 5: //���� ��������
                    print_option = down_width; end_for = true;
                    break;

                case 6: //�Ӵ�� ��������
                    print_option = down_price; end_for = true;
                    break;

                case 7: //���� �� ��
                    print_option = none_set;  end_for = true;
                    break;


                default:
                    system("CLS"); cout << "|���| �� �� ���� ��ɾ� �Դϴ�." << endl;
                    break;
                }
            }

            system("CLS"); printBorder();

            switch (print_option) {
            case none_set: //�ɼ� ����
                for (int i = 0; i < list_place_type->size; i++)
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                break;


            case up_width: //���� ��������
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index, 0, sorted_list_m2->size - 1, up_width);
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index[i]]) > 0)
                        printData(mem_index[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                }
                break;


            case up_price: //�Ӵ�� ��������
                //������ ��ġ ��ȯ ���� �ε��� ������ ��ȯ��
                //��, �ε��� ���� ��ȯ�� ���� ������ ����Ʈ�� ���� �����ؾ���. �ȱ׷��� �ε��� ������ ����� ��ȯ�� �ȵ�
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index, 0, sorted_list_fee->size - 1, up_price);
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index[i]]) > 0)
                        printData(mem_index[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                }
                break;


            case down_width: //���� ��������
                mergeSort(sorted_list_m2->lines, 0, sorted_list_m2->size - 1, mem_index, 0, sorted_list_m2->size - 1, down_width);
                is_upsorted = true;
                is_downsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[mem_index[i]]) > 0)
                        printData(mem_index[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                }
                break;


            case down_price: //�Ӵ�� ��������
                mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index, 0, sorted_list_fee->size - 1, down_price);
                is_downsorted = true;
                is_upsorted = false;

                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[mem_index[i]]) > 0)
                        printData(mem_index[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                }
                break;

            case without0: //�Ӵ�� ǥ�� �� �� ������ ����
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[i]) > 0)
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                }
                break;


            case without0_width: //���� ǥ�� �� �� ������ ����
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atof(list_m2->lines[i]) > 0)
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                }
                break;
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printBorder(); cout << endl << "|���| �����͸� ��� ����Ͽ����ϴ�. �˻� �ɼ�: " << cmd << endl;
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
                    cout << "�ɼ� >> ";
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
                    //������ ��ġ ��ȯ ���� �ε��� ������ ��ȯ��
                    //��, �ε��� ���� ��ȯ�� ���� ������ ����Ʈ�� ���� �����ؾ���. �ȱ׷��� �ε��� ������ ����� ��ȯ�� �ȵ�
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index, 0, sorted_list_fee->size - 1, up);
                    is_upsorted = true;
                    is_downsorted = false;

                    for (int i = 0; i < list_place_type->size; i++) {
                        if (atoi(list_fee->lines[mem_index[i]]) > 0 && atoi(list_fee->lines[mem_index[i]]) < atoi(cmd.c_str())) {
                            printData(mem_index[i], list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                            search = true; //�˻������ ������ true
                        }
                    }
                    break;


                case down: //��������
                    mergeSort(sorted_list_fee->lines, 0, sorted_list_fee->size - 1, mem_index, 0, sorted_list_fee->size - 1, down);
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

