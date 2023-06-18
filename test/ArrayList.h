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

static bool search = false;  //������ ���� ���� �Ǻ��� ����, �� ���� �˻����� ������ true�� ���� �ʾ� ���� ���
static int current_state = input;    //��õ ������ �˻� �� ����ϴ� ����, �� ���¿� ���� ǥ�õǴ� �ؽ�Ʈ�� ����� �ٸ�
static bool color_out = true; //�� ������ true�� �� ������ ��� �� ���� ���
static bool is_number = true; //true�� �˻� ����, false�� ����
static bool is_escape = false; //true�� �ݺ��� ��������, false�� ��� ����
static bool end_for = false; //true�� for(;;)�� ��������


//�Լ�
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();
void printMenu();