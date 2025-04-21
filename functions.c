#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

int getIntegerInput(const char* prompt) {
    int value;
    char ch;

    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d", &value) == 1) {
            // Check for trailing characters
            while ((ch = getchar()) != '\n' && ch != EOF) {
                if (ch < '0' || ch > '9') {
                    printf("Invalid input. Please enter an integer.\n");
                    while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer
                    break;
                }
            }
            if (ch == '\n' || ch == EOF) return value;
        }
        else {
            printf("Invalid input. Please enter an integer.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer
        }
    }
}

void initStack(Stack* stack, int maxSize) {
    stack->top = NULL;
    stack->size = 0;
    stack->maxSize = maxSize;
}

bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

bool isFull(Stack* stack) {
    return stack->size >= stack->maxSize;
}

bool push(Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow!\n");
        return false;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return false;

    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    return true;
}

bool pop(Stack* stack, int* value) {
    if (isEmpty(stack)) return false;

    Node* temp = stack->top;
    *value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return true;
}

bool peek(Stack* stack, int* value) {
    if (isEmpty(stack)) return false;
    *value = stack->top->data;
    return true;
}

void displayStack(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack contents (top first):\n");
    Node* current = stack->top;
    while (current) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int sumEvenElements(Stack* stack) {
    int sum = 0;
    Node* current = stack->top;
    while (current) {
        if (current->data % 2 == 0) sum += current->data;
        current = current->next;
    }
    return sum;
}

void task1() {
    Stack stack;
    printf("=== Task 1 ===\n");
    int maxSize = getIntegerInput("Enter stack size: ");
    initStack(&stack, maxSize);

    printf("Enter elements:\n");
    while (stack.size < stack.maxSize) {
        int num = getIntegerInput("Enter number: ");
        push(&stack, num);
    }

    displayStack(&stack);
    printf("Sum of even elements: %d\n", sumEvenElements(&stack));
}

void task2() {
    Stack stack1, stack2, stack3, tempStack;
    printf("=== Task 2 ===\n");
    int maxSize = getIntegerInput("Enter stack size: ");

    initStack(&stack1, maxSize);
    initStack(&stack2, maxSize);
    initStack(&stack3, maxSize * 2);
    initStack(&tempStack, maxSize * 2);

    // Input for stack1 (descending)
    printf("\nInput for stack1 (descending order):\n");
    int prev = 0;
    bool firstInput = true;
    while (stack1.size < stack1.maxSize) {
        int num = getIntegerInput("Enter number: ");
        if (firstInput || num <= prev) {
            push(&stack1, num);
            prev = num;
            firstInput = false;
        }
        else {
            printf("Number must be <= previous (%d)!\n", prev);
        }
    }

    // Input for stack2 (descending)
    printf("\nInput for stack2 (descending order):\n");
    firstInput = true;
    while (stack2.size < stack2.maxSize) {
        int num = getIntegerInput("Enter number: ");
        if (firstInput || num <= prev) {
            push(&stack2, num);
            prev = num;
            firstInput = false;
        }
        else {
            printf("Number must be <= previous (%d)!\n", prev);
        }
    }

    // Merge stacks
    int val1, val2;
    bool hasVal1 = peek(&stack1, &val1);
    bool hasVal2 = peek(&stack2, &val2);

    while (hasVal1 || hasVal2) {
        if (hasVal1 && hasVal2) {
            if (val1 >= val2) {
                push(&stack3, val1);
                pop(&stack1, &val1);
            }
            else {
                push(&stack3, val2);
                pop(&stack2, &val2);
            }
        }
        else if (hasVal1) {
            push(&stack3, val1);
            pop(&stack1, &val1);
        }
        else {
            push(&stack3, val2);
            pop(&stack2, &val2);
        }
        hasVal1 = peek(&stack1, &val1);
        hasVal2 = peek(&stack2, &val2);
    }

    // Reverse stack3
    int num;
    while (!isEmpty(&stack3)) {
        pop(&stack3, &num);
        push(&tempStack, num);
    }
    stack3 = tempStack;

    // Output results
    printf("\nStack1:\n");
    displayStack(&stack1);
    printf("\nStack2:\n");
    displayStack(&stack2);
    printf("\nStack3 (sorted ascending):\n");
    displayStack(&stack3);
}