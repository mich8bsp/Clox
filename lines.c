#include "lines.h"
#include "memory.h"

void initLines(Lines *pointer)
{
    pointer->capacity = 0;
    pointer->count = 0;
    pointer->lines = NULL;
}

void freeLines(Lines *pointer)
{
    FREE_ARRAY(Line, pointer->lines, pointer->capacity);
    initLines(pointer);
}

void addLine(Lines *pointer, int line)
{
    if(pointer->count > 0 && pointer->lines[pointer->count-1].line == line){
        pointer->lines[pointer->count-1].repetitions++;
    }else{
        if (pointer->capacity < pointer->count + 1){
            int oldCapacity = pointer->capacity;
            pointer->capacity = GROW_CAPACITY(oldCapacity);
            pointer->lines = GROW_ARRAY(Line, pointer->lines, oldCapacity, pointer->capacity);
        }
        Line lineStruct;
        (&lineStruct)->repetitions = 1;
        (&lineStruct)->line = line;
        pointer->lines[pointer->count] = lineStruct;
        pointer->count++;
    }
}

int getLine(Lines *pointer, int count){
    int i = 0;
    int left = count;
    while(i<pointer->capacity){
        if(pointer->lines[i].repetitions>=left){
            return pointer->lines[i].line;
        }else{
            left = left - (pointer->lines[i].repetitions);
            i++;
        }
    }
    
    return -1;
}