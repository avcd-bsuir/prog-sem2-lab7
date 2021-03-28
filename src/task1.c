// License: CC BY-NC-SA 4.0
/*
 * task1.c
 *
 * Lists.
 *
 * Written by AlexeyFilich
 * 28 mar 2021
 */

#include <stdio.h>

#define STORAGE_OPTIMAL

#include "Interactions.h"
#include "storage/Storage.h"

void printList(List * list) {
    if (!list) {
        printf("NULL > NULL\n");
        return;
    }
    List * current = list;
    while (list->prev)
        aListPrev(&list);

    printf("NULL > ");
    while (list->next) {
        if (list == current) printf("*");
        printf("%d > ", aListDataAs(&list, int));
        aListNext(&list);
    }
    if (list == current) printf("*");
    printf("%d > ", aListDataAs(&list, int));
    printf("NULL\n");
}

int main(int argc, char* args[]) {
    List * list;
    List * sum;
    aListInit(&list);
    aListInit(&sum);
    // Read name of the file and size
    char filename[128];
    aScanCheck("File name: ", "%s", &filename);
    int size, tmp;
    aScanCheck("Size: ", "%d", &size);

    // Write to file
    FILE * file = fopen(filename, "w+");
    for (int i = 0; i < size; i++) {
        aScanCheck("Number: ", "%d", &tmp);
        fprintf(file, "%d ", tmp);
    }
    fclose(file);

    // Read and print
    file = fopen(filename, "r+");
    while (fscanf(file, "%d", &tmp) == 1)
        aListAddEnd(&list, &tmp);
    fclose(file);

    while (list->next) {
        tmp = aListDataAs(&list, int);
        aListNext(&list);
        tmp += aListDataAs(&list, int);
        aListAddEnd(&sum, &tmp);
    }

    printList(list);
    printList(sum);
    return 0;
}
