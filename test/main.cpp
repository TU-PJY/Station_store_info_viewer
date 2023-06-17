#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "ArrayList.h"
#define MAX_LINE_LENGTH 100

using namespace std;

string cmd; //��ɾ� �Է¹޴� ��Ʈ��
string line_search; //�˻�� �ùٸ��� �˻��ϴ� ��Ʈ��

//������ ��� �Լ�
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList*list_place_number, ArrayList* list_place_type, ArrayList* list_work_type, ArrayList*list_m2, ArrayList* list_fee) {   
    //�뼱�� ���� ������ �ٸ��� ���
    if(strstr(list_line->lines[i], "1ȣ��"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    else if(strstr(list_line->lines[i], "2ȣ��"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else if (strstr(list_line->lines[i], "3ȣ��"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    else if (strstr(list_line->lines[i], "4ȣ��"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    else if (strstr(list_line->lines[i], "5ȣ��"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    else if (strstr(list_line->lines[i], "6ȣ��"))
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
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
    cout << endl;
}

int main() {
    //Ư���� ������ ��½� ����ϴ� �ε��� ���� �迭
    int data_index[1000] = { 0 };

    //�� ����
    const char* place_type = "data_place_type.txt";
    //�뼱
    const char* line = "data_line.txt";
    //�� ��ȣ
    const char* place_number = "data_place_number.txt";
    //����
    const char* station = "data_station.txt";
    //�� ����
    const char* m2 = "data_m2.txt";
    //�� �Ӵ��
    const char* fee = "data_fee.txt";
    //����
    const char* work_type = "data_work_type.txt";

    //���� �о ����
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
    ArrayList* list_work_type = readFile(work_type);

    //�ϳ��� ���� �ε尡 ���� ���� ��� ����
    if (list_place_type -> size != list_line -> size && list_place_type -> size != list_station -> size) {
        printf("|���| ���� �ҷ����⸦ �� �� �����ϴ�.\n"); return 1; 
    }
    //��� �ε�Ǹ� ���α׷� �غ�
    else printf("|���| ���� �ҷ����⸦ �����Ͽ����ϴ�.\n");

    while(1) {
        printMenu(); printf("��ɾ� �Է�>> ");
        cin >> cmd;

        //cmd = 1
        //��� ������ ���
        if (cmd == "1") {
            system("CLS"); printBorder();
           
            for (int i = 0; i < list_place_type->size; i++)
                printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
            printBorder(); cout << endl << "|���| �����͸� ��� ����Ͽ����ϴ�." << endl; 
        }


        //cmd = 2
        //Ư�� �뼱 �˻�
        else if (cmd == "2") {
            //�˻� �� �ʱ� ����
            system("CLS"); search = false; number_find = false;
            
            cout << "|���| � �뼱�� �˻� �Ͻðڽ��ϱ�?" << endl;
            cout << "===============�˻��� �Է�===============" << endl;
            cout << "(��: '1', '2', '3') >> ";
            cin >> cmd;

            //�뼱 �˻� �� ��ȣ ���� ���ϸ� �˻� �Ұ�
            if (number_find == false) {
                for (int i = 1; i < 9; i++) {
                    //i�� itoa��ȯ �� ch�� �ް� �̸� ��Ʈ�� ������ �޾Ƽ� c_str() ��ȯ ������ ���� �� �� �� �ֵ��� ����
                    char ch[2] = { 0 }; string number = _itoa(i, ch, 10); 
                    //���ﱳ������ 1ȣ��~8ȣ������ ��ϹǷ� �ݺ����� ���� �ش� �뼱 ��ȣ�� cmd�� �����ϴ��� �˻�
                    //������ true�� �Ǿ� ��ºη� �Ѿ
                    if (strstr(cmd.c_str(), number.c_str()) && strlen(cmd.c_str()) == 1) number_find = true;
                } 
                //���ٸ� �״�� false�� �Ǿ� ��� �� ��
                if (number_find == false) {
                    system("CLS"); cout << "|���| �� �� ���� �˻��� �Դϴ�." << endl; 
                }
            }
            
            //���� �ùٸ� �˻����� ��� ����
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
                    printBorder(); cout << endl << "|���| �˻��� �����͸� ��� ����Ͽ����ϴ�. �˻� ����: �뼱 ��ȣ" << endl; 
                }
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
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee);
                    search = true; //�˻������ ������ true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
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
                    printData(i, list_line, list_station, list_place_number, list_place_type, list_work_type, list_m2, list_fee);
                    search = true; //�˻������ ������ true
                }
            }
            if (search == true) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                printBorder(); cout << endl << "|���| �˻��� �����͸� ��� ����Ͽ����ϴ�. �˻� ����: ����" << endl;
            } 
            //�˻������ ������ ������ �״�� false
            else if (search == false) {
                system("CLS"); cout << "|���| �׷� �����Ͱ� �����ϴ�." << endl;
            }
        }


        //cmd = c
        //�ܼ�â �ؽ�Ʈ �����
        else if (cmd == "c") {
            system("CLS"); cout << "|���| �ؽ�Ʈ�� ��� �������ϴ�." << endl; 
        }

        //cmd = e
        //���α׷� �����ϱ�
        else if (cmd == "q") {
            cout << "���α׷��� �����մϴ�." << endl; break; 
        }
           
        //������ Ŀ�ǵ� ���� Ŀ�ǵ�
        else {
            system("CLS"); cout << "|���| �� �� ���� ��ɾ� �Դϴ�." << endl; 
        }
    }

        

    return 0;
}

