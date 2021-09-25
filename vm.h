#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"
#include "common.h"
#include <stdlib.h>

#define STACK_INITIAL_SIZE 256
#define STACK_MAX 2048

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
    int stackSize;
    Value stack[STACK_INITIAL_SIZE];
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);

//stack operations
void push(Value value);
Value pop();

#endif