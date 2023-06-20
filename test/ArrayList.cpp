#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "ArrayList.h"
#include "ArrayList.h"

#define MAX_LINE_LENGTH 100

using namespace std;

//�迭 ����Ʈ ����
ArrayList* createArrayList() {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->lines = NULL; list->size = 0; return list; 
}

//�迭 ����Ʈ�� �� �پ� ���� �ؽ�Ʈ ���� �߰�
void addLine(ArrayList* list, const char* line) {
    list->lines = (char**)realloc(list->lines, (list->size + 1) * sizeof(char*));
    list->lines[list->size] = (char*)malloc((strlen(line) + 1) * sizeof(char));
    strcpy(list->lines[list->size], line);
    list->size++;
}

//���� �б�
ArrayList* readFile(const char* filename) {
    ArrayList* list = createArrayList();
    char buffer[MAX_LINE_LENGTH];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        cout << "������ �� �� �����ϴ�." << endl; return NULL;
    }
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // ���� ���� ����
        addLine(list, buffer);
    }
    fclose(file); return list; 
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
        // ���� ���ڿ��� ���Ͽ� ����
        //��������(����)
        if (atoi(left_arr[i]) <= atoi(right_arr[j]) && (state == up || state == up_price)) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }
        //��������(����)
        else if (atoi(left_arr[i]) >= atoi(right_arr[j]) && (state == down || state == down_price)) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }

        //��������(�Ǽ�)
        else if (atof(left_arr[i]) <= atof(right_arr[j]) && state == up_width) {
            arr[k] = left_arr[i];
            index[k] = left_index[i];
            i++;
        }
        //��������(�Ǽ�)
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

//������ ��� �Լ�
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList* list_place_number, ArrayList* list_place_type,
    ArrayList* list_work_type, ArrayList* list_m2, ArrayList* list_fee, ArrayList* list_end_date, bool color_out) {
    string na = "N/A"; //���� ���߱� ���� ������ ��Ʈ�� ���� ���

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

    //���� �������ϰ�� N/A ǥ��
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
        cout.width(10); cout << list_fee->lines[i] << " ��| ";
    }
    else if (atoi(list_fee->lines[i]) == 0) {
        cout.width(10); cout << na << " ��| ";
    }

    if (strlen(list_end_date->lines[i]) > 0) {
        cout.width(10); cout << list_end_date->lines[i] << " |";
    }
    else if (strlen(list_end_date->lines[i]) == 0) {
        cout.width(10); cout << na << " |";
    }
    cout << endl;
}

//������ �з� ���
void printBorder() {
    cout << "=============================================================================================================================" << endl;
    cout.width(5); cout << "��ȣ" << "| ";
    cout << " �뼱" << "| ";
    cout.width(25); cout << "����" << "| ";
    cout.width(10); cout << "�󰡺�ȣ" << "| ";
    cout.width(15); cout << "������" << "| ";
    cout.width(10); cout << "��������" << "|     ";
    cout.width(10); cout << "�󰡸���" << "|    ";
    cout.width(10); cout << "�� �Ӵ��" << "| ";
    cout.width(10); cout << "��� ������" << "|";
    cout << endl;
    cout << "=============================================================================================================================" << endl;
}

//�޴� ���
void printMenu() {
    cout << "===============�޴� ����===============" << endl;
    cout << "1: ��� ������ ����" << endl;
    cout << "2: �뼱 ���� �˻�" << endl;
    cout << "3: ���� ���� �˻�" << endl;
    cout << "4: ���� ���� �˻�" << endl;
    cout << "5: �Ӵ�� ���� �˻�" << endl;
    cout << "6: ��õ ������ �˻�" << endl;
    cout << "q: ���α׷� ����" << endl << endl;
    cout << "�ؽ�Ʈ�� ������� �޴��� ���� Ű �Է�" << endl;
    cout << "=======================================" << endl;
}

