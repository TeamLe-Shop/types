#include <stdio.h>

#include "../src/list.h"

/* This example demonstrates the use of the List type. */

int main()
{
    List(double, mylist);
    List_Append(mylist, 2.54);
    List_Append(mylist, 3.14);
    List_Append(mylist, 7.16);

    double sum = 0;

    printf("The sum of ");
    for (size_t i = 0; i < mylist->size; i++) {
        printf("%f ", mylist->list[i]);
        sum += mylist->list[i];
    }
    printf("is %f.\n", sum);

    List_Destroy(mylist);

    return 0;
}
