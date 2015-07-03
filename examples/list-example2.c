#include <stdio.h>
#include <string.h>

#include "../src/list.h"

/* This example demonstrates the use of the List type similar to list-example,
 * but in this example the List will have two functions registered that will be
 * called upon deletion of the List, or removal of an element respectively.
 *
 * As mentioned in the documentation, this is useful if you want to free the
 * elements of a list if they were allocated using the memory allocation
 * functions.
 */

void OnDestroy(void* l)
{
    ListStruct(char*)* x = l;

    for (size_t i = 0; i < x->size; i++) {
        free(x->list[i]);
    }
}

void OnErase(void* l, size_t index)
{
    ListStruct(char*)* x = l;
    free(x->list[index]);
}

int main()
{
    ListWithHandlers(char*, strlist, OnDestroy, OnErase);
    List_Append(strlist, strdup("The"));
    List_Append(strlist, strdup("Slim"));
    List_Append(strlist, strdup("Shady"));
    List_Append(strlist, strdup("Please Stand Up"));
    List_Append(strlist, strdup("Gimmicks"));

    List_Insert(strlist, strdup("Real"), 1);
    List_Erase(strlist, 4);

    for (size_t i = 0; i < strlist->size - 1; i++) {
        printf("%s ", strlist->list[i]);
    }
    printf("\n");

    printf("Obie Trice - %s Name No %s\n", strlist->list[1], strlist->list[4]);

    List_Destroy(strlist);
    return 0;
}
