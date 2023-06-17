#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#define MAX_LINE_LENGTH 100

using namespace std;

string cmd; //��ɾ� �Է¹޴� ��Ʈ��
string line_search; //�˻�� �ùٸ��� �˻��ϴ� ��Ʈ��

//������ ��� �Լ�
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList*list_place_number, ArrayList* list_place_type, 
                ArrayList* list_work_type, ArrayList*list_m2, ArrayList* list_fee, ArrayList * list_end_date) {   
    //�뼱�� ���� ������ �ٸ��� ���
    if(strstr(list_line->lines[i], "1ȣ��"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    else if(strstr(list_line->lines[i], "2ȣ��"))
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
    //Ư���� ������ ��½� ����ϴ� �ε��� ���� �迭
    int data_index[1000] = { 0 };

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

    //���� �о ����
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
    ArrayList* list_work_type = readFile(work_type);
    ArrayList* list_end_date = readFile(end_date);

    //�ϳ��� ���� �ε尡 ���� ���� ��� ����
    if (list_place_type -> size != list_line -> size && list_place_type -> size != list_station -> size) {
        printf("|���| ���� �ҷ����⸦ �� �� �����ϴ�.\n"); return 1; 
    }
    //��� �ε�Ǹ� ���α׷� �غ�
    else printf("|���| ���� �ҷ����⸦ �����Ͽ����ϴ�.\n");

    while(1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
       
        cout << "=======================================" << endl;
        cout << "���ﱳ����� �� ������ �˻� ���α׷�" << endl;
        cout << "������ ����: 2023.04.30" << endl;
        cout << "=======================================" << endl;
        printMenu(); printf("��ɾ� �Է�>> ");
        cin >> cmd;

        //cmd = 1
        //��� ������ ���
        if (cmd == "1") {
            system("CLS"); printBorder();
           
            for (int i = 0; i < list_place_type->size; i++)
                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printBorder(); cout << endl << "|���| �����͸� ��� ����Ͽ����ϴ�." << endl; 
        }


        //cmd = 2
        //Ư�� �뼱 �˻�
        else if (cmd == "2") {
            //�˻� �� �ʱ� ����
            system("CLS"); search = false; bool is_number = true;
            
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
        }


        //cmd = 3
        //Ư�� ���� �˻�
        else if (cmd == "3") {
            //�˻� �� �ʱ� ����
            system("CLS"); search = false;
            
            cout << "|���| � ���� �˻� �Ͻðڽ��ϱ�?" << endl;
            cout << "===============�˻��� �Է�===============" << endl;
            cout << "(��: '���빮', 'õȣ' �Ǵ� '1', '2') >> ";
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
        }

        //cmd = 4
        //���� ���� �˻�
        else if (cmd == "4") {
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
        }

        //cmd = 5
        //�Ӵ�� ���� �˻�
        else if (cmd == "5") {
            system("CLS");  search = false; bool is_number = true;

            cout << "|���| �Ӵ�� ���Ѽ��� �Է����ּ���." << endl;
            cout << "===============�˻��� �Է�===============" << endl;
            cout << "(���ڸ� �Է�, ��: 1120000, 340000) >> ";
            cin >> cmd;

            //�Է��� Ŀ�ǵ尡 �������� �ƴ��� �˻�, ���� �̿��� �ٸ� ���ڰ� �� ���� ��� ���ڷ� ���� �ȵǾ� �˻� ���� ���� ����
            for (int i = 0; i < cmd.length(); i++) {
                if (isdigit(cmd[i]) == 0) is_number = false; 
            }

            if (is_number == true) {
                cout << endl;
                printBorder();
                for (int i = 0; i < list_place_type->size; i++) {
                    if (atoi(list_fee->lines[i]) < atoi(cmd.c_str()) && atoi(list_fee->lines[i]) > 0) {
                        printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee, list_end_date);
                        search = true; //�˻������ ������ true
                    }
                }
                if (search == true) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    printBorder(); cout << endl << "|���| �˻��� �����͸� ��� ����Ͽ����ϴ�. �˻� ����: �Ӵ��" << endl;
                }
                else if (search == false) {
                    system("CLS"); cout << "|���| �ش� ���Ѽ� ���� �Ӵ�� �����͸� ã�� �� �����ϴ�." << endl;
                }
            }
            else if (is_number == false) {
                system("CLS"); cout << "|���| �ùٸ� ���ڰ� �ƴմϴ�." << endl;
            }
        }

        //cmd = 6
        //�ڽſ��� �´� ��õ ������ �˻�
        else if (cmd == "6") {
            system("CLS");
            string mem_line, mem_station, mem_fee;
            bool is_number = true;
            bool is_escape = false;
            for (;;) {
                if (is_escape == true) {
                    system("CLS"); break; 
                }

                //�Է� �ܰ�
                if (state == input) {
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
                            system("CLS"); cout << "�ùٸ��� ���� �˻��� �Դϴ�." << endl;
                            is_number = true;
                        }
                    }
                    system("CLS");
                    state = check;
                }

                //Ȯ�� �ܰ�
                else if (state == check) {
                    for (;;) {
                        cout << "|���| ���ݱ��� �Է��� ���ʹ� ������ �����ϴ�." << endl << endl;
                        cout << "�뼱: " << mem_line << "ȣ�� | " << "����: " << mem_station << " | " << "�Ӵ�� ���Ѽ�: " << mem_fee << "��" << endl << endl;
                        cout << "===============�޴� ����===============" << endl;
                        cout << "1: �Է� ������ Ȯ�� �� �˻�" << endl;
                        cout << "2: �ٽ� �Է��ϱ�" << endl;
                        cout << "3: ��� �� ������" << endl;
                        cout << "=======================================" << endl;
                        printf("��ɾ� �Է�>> ");
                        cin >> cmd;

                        //������
                        if (cmd == "3") {
                            is_escape = true; break;
                        }
                        //���Է�
                        else if (cmd == "2") {
                            system("CLS");  state = input; break;
                        }
                        //������ �˻� �� ���
                        else if (cmd == "1") {
                            system("CLS");  state = output; break;
                        }
                        else {
                            system("CLS"); cout << "|���| �� �� ���� ��ɾ� �Դϴ�." << endl;
                        }
                    }
                }

                //���Ϳ� �´� ������ �˻�
                else if (state == output) {
                    search = false;
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
                        printBorder();  cout << endl << "|���| �����͸� ������� ��õ�帮�� �����ʹ� ���� �����ϴ�." << endl;

                        state = input; is_escape = true; break;
                    }

                    else if(search == false) {
                        system("CLS"); cout << "|���| ���Ϳ� �´� �����Ͱ� ���°� �����ϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?" << endl;

                        for (;;) {
                            cout << "===============�޴� ����===============" << endl;
                            cout << "1: �ٽ� �Է��ϱ�" << endl;
                            cout << "2: ��� �� ������" << endl;
                            cout << "=======================================" << endl;
                            cin >> cmd;
                            if (cmd == "2") {
                                state = input; mem_line = ""; mem_station = ""; mem_fee = ""; is_escape = true; break;
                            }
                            else if (cmd == "1") {
                                system("CLS");  state = input; break;
                            }
                            else {
                                system("CLS"); cout << "�� �� ���� ��ɾ� �Դϴ�." << endl;
                            } 
                        }
                    }
                }
            }
        }

        //cmd = q
        //���α׷� �����ϱ�
        else if (cmd == "q") {
            system("CLS"); cout << "���α׷��� �����մϴ�." << endl; break;
        }
           
        //������ Ŀ�ǵ� ���� Ŀ�ǵ�, �ؽ�Ʈ �����
        else {
            system("CLS"); cout << "|���| �ؽ�Ʈ�� ��� �������ϴ�." << endl; 
        }
    }

    return 0;
}

