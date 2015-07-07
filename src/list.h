#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ListStruct(type) \
    struct { \
        type* list; \
        size_t size; \
        void (*handler_destroy)(void*); \
        void (*handler_erase)(void*, size_t); \
    }


/* This is a List initialisation macro for existing List objects. Use this to
 * initialise List objects created with ListStruct.
 */
#define ListInit(l, destroy, erase) \
    l = malloc(ListSize); \
    l->list = NULL; \
    l->size = 0; \
    l->handler_destroy = NULL; \
    l->handler_erase = NULL;

#define ListSize sizeof(ListStruct(void))

/* This creates a new anonymous structure with a `type` pointer and allocates
 * sufficient memory for the structure.
 *
 * After creation, the list's data pointer is set to NULL and the size is set
 * to 0.
 */
#define List(type, name) \
    ListStruct(type)* name = malloc(ListSize); \
    name->list = NULL; \
    name->size = 0; \
    name->handler_destroy = NULL; \
    name->handler_erase = NULL

/* This macro calls the normal List creation macro and passes in the first two
 * parameters.
 *
 * The last two parameters can be left NULL, but if given a non-NULL value,
 * they are expected to be valid function pointers.
 *
 * The first of the two function pointer parameters is called when the List
 * is destroyed via List_Destroy.
 * The function must take a single parameter, which is a pointer to the List.
 *
 * The second is called when any of the element removal macros are called on
 * the List (e.g. List_Pop, List_Erase).
 * The function must take two parameters: a pointer to the List, and an index,
 *
 * This is useful in scenarios where the data being stored by the list
 * was allocated using any of the memory allocation functions and needs
 * to be freed upon removal of the element or destruction of the List.
 */

#define ListWithHandlers(type, name, destroy, erase) \
    List(type, name); \
    name->handler_destroy = destroy; \
    name->handler_erase = erase

#define List_Append(l, object) \
    l->list = realloc(l->list, (l->size+1) * sizeof(*(l->list))); \
    l->list[l->size] = object; \
    l->size++

#define List_Insert(l, object, index) \
    l->list = realloc(l->list, (l->size+1) * sizeof(*(l->list))); \
    if (index != l->size) { \
        memmove(&l->list[index + 1], &l->list[index], \
                ((l->size - index) * sizeof(*(l->list)))); \
    } \
    l->list[index] = object; \
    l->size++

/* Erase the element at `index`.
 *
 * This calls the List's erase handler (list->handler_erase) before erasing
 * the specified element if the function pointer is not NULL.
 */
#define List_Erase(l, index) \
    if (l->handler_erase != NULL) { \
        l->handler_erase(l, index); \
    } \
    if (index != l->size - 1) { \
        memmove(&l->list[index], &l->list[index + 1], \
                ((l->size - 1 - index) * sizeof(*(l->list)))); \
    } \
    l->list = realloc(l->list, (l->size-1) * sizeof(*(l->list))); \
    l->size--


#define List_Pop(l) \
    List_Erase(l, l->size - 1)

/* This invokes the List's destroy handler (list->handler_destroy) before
 * freeing the memory if the function pointer does not point to NULL.
 */
#define List_Destroy(l) \
    if (l->handler_destroy != NULL) { \
        l->handler_destroy(l); \
    } \
    free(l->list); \
    free(l)

#endif /* LIST_H */
