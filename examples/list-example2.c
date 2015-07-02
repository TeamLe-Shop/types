#include <stdio.h>
#include <string.h>

#include "../src/list.h"

/* This example demonstrates the use of the List type similar to list-example,
 * but in this example the List will have a function registered that will be
 * called upon deletion of the List.
 *
 * As mentioned in the documentation, this is useful if you want to free the
 * elements of a list if they were allocated using the memory allocation
 * functions.
 */

void* list = NULL;

void FreeMemory(void* l, size_t typesize)
{
    ListStruct(char*)* x = l;

    for (size_t i = 0; i < x->size; i++) {
        free(x->list[i]);
    }
}

int main()
{
    List(char*, strlist, FreeMemory);
    list = strlist;
    List_Add(strlist, strdup("The"));
    List_Add(strlist, strdup("Real"));
    List_Add(strlist, strdup("Slim"));
    List_Add(strlist, strdup("Shady"));
    List_Add(strlist, strdup("Gimmicks"));

    for (size_t i = 0; i < strlist->size - 1; i++) {
        printf("%s ", strlist->list[i]);
    }
    printf("\n");

    printf("Obie Trice - Real Name No %s\n", strlist->list[4]);

    List_Destroy(strlist);
    return 0;
}
