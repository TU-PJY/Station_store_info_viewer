#pragma once

//배열 리스트 구조체
typedef struct {
    char** lines;
    int size;
} ArrayList;


//추천 데이터 검색 시 사용하는 열거자
enum state {
    input, check, output
};
//출력 타입
enum option_set {
    up, down, none
};
enum option_all {
    none_set, without0, without0_width, up_width, up_price, down_width, down_price
};

static bool search = false;  //데이터 존재 유무 판별용 변수, 한 개라도 검색되지 않으면 true가 되지 않아 오류 출력
static int current_state = input;    //추천 데이터 검색 시 사용하는 변수, 각 상태에 따라 표시되는 텍스트와 기능이 다름
static bool color_out = true; //이 변수가 true일 때 데이터 출력 시 색상 출력
static bool is_number = true; //true면 검색 진행, false면 종료
static bool is_escape = false; //true면 반복문 빠져나옴, false면 계속 진행
static bool end_for = false; //true면 for(;;)문 빠져나옴
static int print_option = none; //출력 옵션, option_set 열거형에 따라 출력 형태가 달라짐
static int mem_index_fee[2000]; //sorted_list_fee의 인덱스 순서를 저장하는 배열, 데이터 위치 교환 없이 인덱스 순서만 교환함
static int mem_index_m2[2000]; //sorted_list_m2의 인덱스 순서를 저장하는 배열, 데이터 위치 교환 없이 인덱스 순서만 교환함

static bool is_upsorted = false; //오름차순, 내림차순 정렬 여부
static bool is_downsorted = false;

static bool line_op, station_op, type_op, fee_op, m2_op, work_op;

//함수
ArrayList* createArrayList();
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void merge(char* arr[], int l, int m, int r, int index[], int index_l, int index_m, int index_r, int state);
void mergeSort(char* arr[], int l, int r, int index[], int index_l, int index_r, int state);
void printData(int i, ArrayList* list_line, ArrayList* list_station, ArrayList* list_place_number, ArrayList* list_place_type,
    ArrayList* list_work_type, ArrayList* list_m2, ArrayList* list_fee, ArrayList* list_end_date, bool color_out);
void printBorder();
void printMenu();