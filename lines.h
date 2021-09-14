#ifndef clox_lines_h
#define clox_lines_h

#include "common.h"

typedef struct {
    int line;
    int repetitions;
} Line;

typedef struct {
    int count;
    int capacity;
    Line* lines;
} Lines;

void initLines(Lines* pointer);
void freeLines(Lines* pointer);
void addLine(Lines* pointer, int line);
int getLine(Lines *pointer, int count);

#endif