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
string line_search;

int main() {
    //Ư���� ������ ��½� ����ϴ� �ε��� ���� �迭
    int data_index[1000] = { 0 };
    int idx = -1;

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
    
    //���� �о ����
    ArrayList* list_place_type = readFile(place_type);
    ArrayList* list_line = readFile(line);
    ArrayList* list_station = readFile(station);
    ArrayList* list_place_number = readFile(place_number);
    ArrayList* list_m2 = readFile(m2);
    ArrayList* list_fee = readFile(fee);
   

    //�ϳ��� ���� �ε尡 ���� ���� ��� ����
    if (list_place_type == NULL || line == NULL) {
        printf("������ ���� �� �����ϴ�.\n");
        return 1;
    }
    //��� �ε�Ǹ� ���α׷� �غ�
    else printf("������ �ҷ����µ��� �����Ͽ����ϴ�.\n");

    for (;;) {
        printf("��ɾ� �Է�>> ");
        cin >> cmd;
        //��� ������ ���
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
                cout.width(10); cout << list_fee->lines[i] << " ��| ";
                cout << endl;
            }
            printBorder();
            cout << "�����͸� ��� ����Ͽ����ϴ�." << endl << endl;
        }

        else if (cmd == "search-line") {
            system("CLS");
            idx = -1;
            int error = 0;
            char search_line[20] = { 0 };
            cout << "� �뼱�� �˻� �Ͻðڽ��ϱ�?" << endl;
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
                    cout.width(10); cout << list_fee->lines[i] << " ��| ";
                    cout << endl;
                    idx++; //������ ���� ���� �Ǻ��� ����, -1�̸� �������� ����
                }
            }

            if (idx >= 0) {
                printBorder();
                cout << "�˻��� �����͸� ��� ����Ͽ����ϴ�." << endl;
            }

            else if (idx == -1)
                cout << "�׷� �����Ͱ� �����ϴ�." << endl;
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
                cout << "�˻��� �����͸� ��� ����Ͽ����ϴ�." << endl;
            }

            else if (idx == -1)
                cout << "�׷� �����Ͱ� �����ϴ�." << endl;
                */
     //   }

        else {
            system("CLS");
            printf("�� �� ���� ��ɾ� �Դϴ�.\n");
        }
    }
        


    destroyArrayList(list_place_type);
    return 0;
}