#include "Header.h"
#include <stdio.h>

int main() {
    int choice;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Task 1: Sum of even elements\n");
        printf("2. Task 2: Merge two stacks\n");
        printf("0. Exit\n");

        choice = getIntegerInput("Enter your choice: ");

        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 0: printf("Exiting...\n"); break;
        default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}