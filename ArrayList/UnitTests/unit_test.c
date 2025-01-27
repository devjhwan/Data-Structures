#include "unit_test.h"
#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>

int    UnitTest1()
{
    printf("Unit Test 1: Create ArrayList and Free\n");
    printf("\n");
    {
        printf("Creating Array List with int with default capacity(100)\n");
        ArrayList *list = create_arraylist(sizeof(int), 0);
        if (list == NULL)
            return ERROR;

        printf("list memory    -> %p\n", (void *)list);
        printf("list size      -> %zd\n", list->size);
        printf("list capacity  -> %zd\n", list->capacity);
        printf("list data size -> %u\n", list->data_size);
        free_alist(&list);
    }
    printf("\n");
    {
        printf("Creating Array List with double with capacity(5000)\n");
        ArrayList *list = create_arraylist(sizeof(double), 5000);
        if (list == NULL)
            return ERROR;

        printf("list memory    -> %p\n", (void *)list);
        printf("list size      -> %zd\n", list->size);
        printf("list capacity  -> %zd\n", list->capacity);
        printf("list data size -> %u\n", list->data_size);
        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 1 Finished\n");
    return SUCCESS;
}

int UnitTest2()
{
    printf("Unit Test 2: Create ArrayList and Free\n");

    {
        printf("Creating Array List with int\n");
        ArrayList *list = create_arraylist(sizeof(int), 0);
        if (list == NULL)
            return ERROR;

        printf("Add numbers 1 to 10 to list\n");
        for (int num = 1; num <= 10; num++)
            if (add_alist(list, &num) < 0)
                return ERROR;

        printf("Create iterator\n");
        ArrayListIterator *iter = create_iterator_alist(list);
        if (iter == NULL)
            return ERROR;

        printf("Iterate over the list\n");
        int *num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        free_iterator_alist(&iter);
        free_alist(&list);
    }
    printf("Unit Test 2 Finished\n");
    return SUCCESS;
}
