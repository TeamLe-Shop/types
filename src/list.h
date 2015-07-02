#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Macros */

#define ListStruct(type) \
    struct { \
        type* list; \
        size_t size; \
        void (*function)(void*, size_t); \
    }

#define ListSize sizeof(ListStruct(void))

/* This creates a new anonymous structure with a `type` pointer and allocates
 * sufficient memory for the structure.
 *
 * After creation, the list's data pointer is set to NULL and the size is set
 * to 0.
 *
 * The parameter `func` can be left NULL, but if given a non-NULL value,
 * is a function pointer that is called whenever the list is destroyed via
 * List_Destroy.
 * This is useful in scenarios where the data being stored by the list
 * was allocated using any of the memory allocation functions and needs
 * to be freed when the list is destroyed.
 *
 * The handler must take a pointer to the List object.
 */
#define List(type, name, func) \
    ListStruct(type)* name = malloc(ListSize); \
    name->list = NULL; \
    name->size = 0; \
    name->function = func

#define List_Add(l, object) \
    l->list = realloc(l->list, (l->size+1) * sizeof(*(l->list))); \
    l->list[l->size] = object; \
    l->size++

#define List_Destroy(l) \
    if (l->function != NULL) { \
        l->function(l, sizeof(*(l->list))); \
    } \
    free(l->list); \
    free(l)

#endif /* LIST_H */
