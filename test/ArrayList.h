#pragma once

//�迭 ����Ʈ ����ü
typedef struct {
    char** lines;
    int size;
} ArrayList;


//��õ ������ �˻� �� ����ϴ� ������
enum state {
    input, check, output
};
//��� Ÿ��
enum option_set {
    up, down, none
};
enum option_all {
    none_set, without0, without0_width, up_width, up_price, down_width, down_price
};

static bool search = false;  //������ ���� ���� �Ǻ��� ����, �� ���� �˻����� ������ true�� ���� �ʾ� ���� ���
static int current_state = input;    //��õ ������ �˻� �� ����ϴ� ����, �� ���¿� ���� ǥ�õǴ� �ؽ�Ʈ�� ����� �ٸ�
static bool color_out = true; //�� ������ true�� �� ������ ��� �� ���� ���
static bool is_number = true; //true�� �˻� ����, false�� ����
static bool is_escape = false; //true�� �ݺ��� ��������, false�� ��� ����
static bool end_for = false; //true�� for(;;)�� ��������
static int print_option = none; //��� �ɼ�, option_set �������� ���� ��� ���°� �޶���
static int mem_index_fee[2000]; //sorted_list_fee�� �ε��� ������ �����ϴ� �迭, ������ ��ġ ��ȯ ���� �ε��� ������ ��ȯ��
static int mem_index_m2[2000]; //sorted_list_m2�� �ε��� ������ �����ϴ� �迭, ������ ��ġ ��ȯ ���� �ε��� ������ ��ȯ��

static bool is_upsorted = false; //��������, �������� ���� ����
static bool is_downsorted = false;

static bool line_op, station_op, type_op, fee_op, m2_op, work_op;

//�Լ�
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void merge(char* arr[], int l, int m, int r, int index[], int index_l, int index_m, int index_r, int state);
void mergeSort(char* arr[], int l, int r, int index[], int index_l, int index_r, int state);
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList* list_place_number, ArrayList* list_place_type,
    ArrayList* list_work_type, ArrayList* list_m2, ArrayList* list_fee, ArrayList* list_end_date, bool color_out);
void printBorder();
void printMenu();