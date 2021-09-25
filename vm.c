#include "vm.h"
#include <stdio.h>
#include "debug.h"
#include "memory.h"
VM vm;

static void resetStack()
{
    vm.stackSize = STACK_INITIAL_SIZE;
    vm.stackTop = vm.stack;
}

void initVM()
{
    resetStack();
}

void freeVM()
{
}

void push(Value value)
{
    if((vm.stackTop - vm.stack) >= vm.stackSize){
        int newStackSize = vm.stackSize * 2;
        
        if(vm.stackSize >= STACK_MAX){
            //if we're at the limit of stack size - we can't grow it so we throw SO
            printf("Stack overflow");
            exit(1);
        }
        if(newStackSize > STACK_MAX){
            //if current stack size is less then MAX but doubling it will make it larger than MAX, we grow it up to MAX
            newStackSize = STACK_MAX;
        }

        GROW_ARRAY(Value, vm.stack, vm.stackSize, newStackSize);
        vm.stackSize = newStackSize;
    }
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop()
{
    return *(--vm.stackTop);
}

static InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false) //wtf
    for (;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
        //printin stack
        printf("         ");
        for (Value *slot = vm.stack; slot < vm.stackTop; slot++)
        {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");

        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
        case OP_CONSTANT:
        {
            Value constant = READ_CONSTANT();
            push(constant);
            break;
        }
        case OP_CONSTANT_LONG:
        {
            int32_t constantIndex = READ_BYTE() |
                                    (READ_BYTE() << 8) |
                                    (READ_BYTE() << 16);
            Value constantLong = vm.chunk->constants.values[constantIndex];
            push(constantLong);
            break;
        }
        case OP_NEGATE:
        {
            push(-pop());
            break;
        }
        case OP_ADD: BINARY_OP(+); break;
        case OP_SUBTRACT: BINARY_OP(-); break;
        case OP_MULTIPLY: BINARY_OP(*); break;
        case OP_DIVIDE: BINARY_OP(/); break;
        case OP_RETURN:
        {
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
        }
        }
    }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

InterpretResult interpret(const char* source)
{
    compile(source);
    return INTERPRET_OK;
}
