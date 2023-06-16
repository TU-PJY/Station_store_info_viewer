#pragma once
#define MAX_LINE_LENGTH 100

typedef struct {
    char** lines;
    int size;
} ArrayList;

ArrayList* createArrayList();
void destroyArrayList(ArrayList* list);
void addLine(ArrayList* list, const char* line);
ArrayList* readFile(const char* filename);
void printBorder();