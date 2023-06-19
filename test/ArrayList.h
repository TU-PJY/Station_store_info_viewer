#pragma once

//�迭 ����Ʈ ����ü
typedef struct {
    char** lines;
    int size;
} ArrayList;

//��õ ������ �˻� �� ����ϴ� ������ ����
enum state {
    input, check, output
};

enum option_set {
    up, down, none
};

enum option_all {
    none_set , without0, without0_width, up_width, up_price, down_width, down_price
};

static bool search = false;  //������ ���� ���� �Ǻ��� ����, �� ���� �˻����� ������ true�� ���� �ʾ� ���� ���
static int current_state = input;    //��õ ������ �˻� �� ����ϴ� ����, �� ���¿� ���� ǥ�õǴ� �ؽ�Ʈ�� ����� �ٸ�
static bool color_out = true; //�� ������ true�� �� ������ ��� �� ���� ���
static bool is_number = true; //true�� �˻� ����, false�� ����
static bool is_escape = false; //true�� �ݺ��� ��������, false�� ��� ����
static bool end_for = false; //true�� for(;;)�� ��������
static int print_option = none; //��� �ɼ�, option_set �������� ���� ��� ���°� �޶���
static int mem_index[3000] = { 0 }; //�ε��� ������ �����ϴ� �迭, ������ ��ġ ��ȯ ���� �ε��� ������ ��ȯ��
 
static bool is_upsorted = false; //��������, �������� ���� ����
static bool is_downsorted = false;


//�Լ�
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void merge(char* arr[], int l, int m, int r, int index[], int index_l, int index_m, int index_r, int state);
void mergeSort(char* arr[], int l, int r, int index[], int index_l, int index_r, int state);
void printBorder();
void printMenu();