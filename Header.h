#pragma once
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
    int maxSize;
} Stack;

void initStack(Stack* stack, int maxSize);
bool isEmpty(Stack* stack);
bool isFull(Stack* stack);
bool push(Stack* stack, int value);
bool pop(Stack* stack, int* value);
bool peek(Stack* stack, int* value);
void displayStack(Stack* stack);
int sumEvenElements(Stack* stack);
void task1();
void task2();
int getIntegerInput(const char* prompt);