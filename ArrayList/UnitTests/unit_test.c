#include "unit_test.h"
#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int errno;

static int printerr(int e)
{
    if (e == ALIST_NULL)
        printf("NULL error\n");
    else if (e == ALIST_INDEX_OUT_OF_BOUNDS)
        printf("Index out of bounds error\n");
    else if (e == ALIST_RESIZE_FAIL)
        printf("List resizing failed\n");
    return ERROR;
}

int    UnitTest1()
{
    printf("Unit Test 1: Create ArrayList and Free.\n");
    printf("\n");
    {
        printf("Creating Array List with int with default capacity(100).\n");
        ArrayList *list = create_arraylist(sizeof(int), 0);
        if (list == NULL)
            return printerr(ALIST_NULL);

        printf("list memory    -> %p\n", (void *)list);
        printf("list size      -> %zd\n", list->size);
        printf("list capacity  -> %zd\n", list->capacity);
        printf("list data size -> %u\n", list->data_size);
        free_alist(&list);
    }
    printf("\n");
    {
        printf("Creating Array List with double with capacity(5000).\n");
        ArrayList *list = create_arraylist(sizeof(double), 5000);
        if (list == NULL)
            return printerr(ALIST_NULL);

        printf("list memory    -> %p\n", (void *)list);
        printf("list size      -> %zd\n", list->size);
        printf("list capacity  -> %zd\n", list->capacity);
        printf("list data size -> %u\n", list->data_size);
        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 1 Finished.\n");
    return SUCCESS;
}

int UnitTest2()
{
    printf("Unit Test 2: Add integers in to arraylist and iterate over it.\n");
    printf("\n");
    {
        printf("Creating Array List with int.\n");
        ArrayList *list = create_arraylist(sizeof(int), 0);
        if (list == NULL)
            return printerr(ALIST_NULL);

        printf("Add numbers 1 to 10 to list.\n");
        for (int num = 1; num <= 10; num++)
            if ((errno = add_alist(list, &num)) < 0)
                return printerr(errno);
        printf("\n");

        printf("Create iterator.\n");
        ArrayListIterator *iter = create_iterator_alist(list);
        if (iter == NULL)
            return printerr(ALIST_NULL);

        printf("Iterate over the list.\n");
        int *num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        free_iterator_alist(&iter);
        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 2 Finished.\n");
    return SUCCESS;
}

int UnitTest3()
{
    printf("Unit Test 3: Add, set, get, remove data to/from specific index and clear list.\n");
    printf("\n");
    {

        printf("Creating Array List with int.\n");
        ArrayList *list = create_arraylist(sizeof(int), 0);
        if (list == NULL)
            return printerr(ALIST_NULL);

        printf("Add pair numbers from 2 to 20 to list.\n");
        int num = 0;
        for (num = 2; num <= 20; num += 2)
            if ((errno = add_alist(list, &num)) < 0)
                return printerr(errno);
        printf("\n");

        printf("Create iterator.\n");
        ArrayListIterator *iter = create_iterator_alist(list);
        if (iter == NULL)
            return printerr(ALIST_NULL);

        printf("Iterate over the list.\n");
        int *num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        printf("\n");

        printf("Add 13 to index 3.\n");
        num = 13;
        if ((errno = add_index_alist(list, 3, &num)) < 0)
            return printerr(errno);
        printf("Size of arraylist = %zd.\n", list->size);
        printf("\n");
        
        printf("Set 7 to index 10 (last index).\n");
        num = 7;
        if ((errno = set_alist(list, 10, &num)) < 0)
            return printerr(errno);
        printf("\n");

        printf("Iterate over the list.\n");
        if (reset_iterator_alist(iter) == NULL)
            return printerr(ALIST_NULL);
        num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        printf("\n");
        
        printf("Get data from index 3 and 7.\n");
        if ((errno = get_alist(list, 3, &num)) < 0)
            return printerr(errno);
        printf("Get %d from index 3.\n", num);
        if ((errno = get_alist(list, 7, &num)) < 0)
            return printerr(errno);
        printf("Get %d from index 7.\n", num);
        printf("\n");

        printf("Remove data from index 7.\n");
        if ((errno = remove_alist(list, 7, &num)) < 0)
            return printerr(errno);
        printf("Removed %d from index 7.\n", num);

        printf("Remove 10 from list.\n");
        num = 10;
        if ((errno = remove_object_alist(list, &num)) < 0)
            return printerr(errno);
        printf("Removed 10 from the list.\n");
        printf("\n");
        
        printf("Iterate over the list.\n");
        if (reset_iterator_alist(iter) == NULL)
            return printerr(ALIST_NULL);
        num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        printf("\n");

        printf("Clear list\n");
        if ((errno = clear_alist(list)) < 0)
            return printerr(errno);
        
        printf("list size = %zd\n", list->size);
        free_iterator_alist(&iter);
        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 3 Finished\n");
    return SUCCESS;
}

int UnitTest4()
{
    printf("Unit Test 4: Create list and clone it.\n");
    printf("\n");
    {
        printf("Creating Array List with double.\n");
        ArrayList *list = create_arraylist(sizeof(double), 0);
        if (list == NULL)
            return printerr(ALIST_NULL);

        printf("Add numbers from 1 to 5 to list with 0.5 of steps.\n");
        double num;
        // we can compare double with 5 exactly because 0.5
        // doesn't cause any loosing of bit during the calculations.
        for (num = 1.0; num <= 5; num += 0.5)
            if ((errno = add_alist(list, &num)) < 0)
                return printerr(errno);
        printf("\n");

        printf("Create iterator.\n");
        ArrayListIterator *iter = create_iterator_alist(list);
        if (iter == NULL)
            return printerr(ALIST_NULL);

        printf("Iterate over the list.\n");
        double *num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %.1f\n", i, *num_p);
        printf("\n");

        printf("Clone list.\n");
        ArrayList *cloned_list = clone_alist(list);
        if (cloned_list == NULL)
            return printerr(ALIST_NULL);
        printf("\n");

        printf("Set 12.3 to index 5 of cloned list.\n");
        num = 12.3;
        if ((errno = set_alist(cloned_list, 5, &num)) < 0)
            return printerr(errno);
        printf("\n");

        printf("Create new iterator for cloned list.\n");
        ArrayListIterator *iter2 = create_iterator_alist(cloned_list);
        if (iter2 == NULL)
            return printerr(ALIST_NULL);

        printf("Iterate over the cloned list.\n");
        num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter2)) != NULL || i < cloned_list->size; i++)
            printf("Iter %ld got %.1f\n", i, *num_p);
        printf("\n");

        printf("Iterate over the original list.\n");
        num_p = NULL;
        if (reset_iterator_alist(iter) == NULL)
            return printerr(ALIST_NULL);
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %.1f\n", i, *num_p);

        free_iterator_alist(&iter);
        free_iterator_alist(&iter2);
        free_alist(&list);
        free_alist(&cloned_list);
    }
    printf("\n");
    printf("Unit Test 4 Finished\n");
    return SUCCESS;
}

int IntegerComparator(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int UnitTest5()
{
    printf("Unit Test 5: Check if data contains in list and find the index of data.\n");
    printf("\n");
    {
        printf("Creating Array List with int.\n");
        ArrayList *list = create_arraylist(sizeof(int), 0);
        if (list == NULL)
            return printerr(ALIST_NULL);

        printf("Add numbers with f(x) = x^2 | x = {-3, 3}, x = Z.\n");
        int num;
        for (int i = -3; i <= 3; i++)
        {
            num = i * i;
            if ((errno = add_alist(list, &num)) < 0)
                return printerr(errno);
        }
        printf("\n");

        printf("Create iterator.\n");
        ArrayListIterator *iter = create_iterator_alist(list);
        if (iter == NULL)
            return printerr(ALIST_NULL);

        printf("Iterate over the list.\n");
        int *num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        printf("\n");

        printf("Check if a list contains 4.\n");
        printf("contains_alist(list, &num, IntegerComparator)?\n");
        num = 4;
        if ((errno = contains_alist(list, &num, IntegerComparator)) < 0)
            return printerr(errno);
        else
            printf("List contains num 4.\n");
        printf("\n");
        
        printf("Check the first occurance of 9.\n");
        printf("index = index_of_alist(list, &num, IntegerComparator)\n");
        long long index;
        num = 9;
        if ((index = index_of_alist(list, &num, IntegerComparator)) < 0)
            return printerr(index);
        else
            printf("The first occurence of num 9 is on index %lld.\n", index);
        printf("\n");

        printf("Check the last occurance of 9.\n");
        printf("index = last_index_of_alist(list, &num, NULL)\n");
        if ((index = last_index_of_alist(list, &num, NULL)) < 0)
            return printerr((int)index);
        else
            printf("The last occurence of num 9 is on index %lld.\n", index);
        printf("\n");

        printf("Check the last occurance of 1.\n");
        printf("index = last_index_of_alist(list, &num, NULL)\n");
        num = 1;
        if ((index = last_index_of_alist(list, &num, NULL)) < 0)
            return printerr((int)index);
        else
            printf("The last occurence of num 1 is on index %lld.\n", index);
        printf("\n");
        
        printf("Check the occurance of 3\n");
        printf("index = index_of_alist(list, &num, NULL)\n");
        num = 3;
        if ((index = index_of_alist(list, &num, NULL)) < 0)
            printf("Number not found\n");

        free_iterator_alist(&iter);
        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 5 Finished\n");
    return SUCCESS;
}

int UnitTest6()
{
    printf("Unit Test 6: Sort list and try binary search.\n");
    printf("\n");
    {
        printf("Creating Array List with int.\n");
        ArrayList *list = create_arraylist(sizeof(int), 0);
        if (list == NULL)
            return printerr(ALIST_NULL);
        
        srand(time(NULL));

        printf("Add 10 random integer numbers between 0 to 100 to list.\n");
        int num;
        for (int i = 0; i < 10; i++)
        {
            num = rand() % 101;
            if ((errno = add_alist(list, &num)) < 0)
                return printerr(errno);
        }
        printf("\n");

        printf("Create iterator.\n");
        ArrayListIterator *iter = create_iterator_alist(list);
        if (iter == NULL)
            return printerr(ALIST_NULL);

        printf("Iterate over the list.\n");
        int *num_p = NULL;
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        printf("\n");

        printf("Sort list\n");
        if ((errno = sort_alist(list, IntegerComparator)) < 0)
            return printerr(errno);
        printf("\n");

        printf("Iterate over the list.\n");
        num_p = NULL;
        if (reset_iterator_alist(iter) == NULL)
            return printerr(ALIST_NULL);
        for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
            printf("Iter %ld got %d\n", i, *num_p);
        printf("\n");

        printf("Get any number from index 5\n");
        if ((errno = get_alist(list, 5, &num)) < 0)
            return printerr(errno);
        printf("Got %d from index 5\n", num);
        printf("\n");

        printf("Execute binary search for number %d\n", num);
        printf("index = binary_search_alist(list, &num, IntegerComparator)\n");
        int index;
        if ((index = binary_search_alist(list, &num, IntegerComparator)) < 0)
            return printerr(index);
        printf("Found %d in index %d\n", num, index);

        free_iterator_alist(&iter);
        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 6 Finished.\n");
    return SUCCESS;
}

int UnitTest7()
{
    printf("Unit Test 7: Edge Cases for add, add_Index, set, get, remove, remove_object.\n");
    printf("\n");
    {
        ArrayList *list = create_arraylist(sizeof(int), 2);
        if (list == NULL)
            return printerr(ALIST_NULL);
        
        int a = 10, b = 20, c = 30;
        
        printf("Adding elements beyond initial capacity.\n");
        add_alist(list, &a);
        add_alist(list, &b);
        add_alist(list, &c); // This should trigger a resize
        printf("New capacity: %zd\n", list->capacity);
        printf("\n");
        
        printf("Testing add_index at out-of-bounds index.\n");
        if (add_index_alist(list, 5, &a) == ALIST_INDEX_OUT_OF_BOUNDS)
            printf("ERROR: Added at an invalid index!\n");
        printf("\n");
        
        printf("Testing set at out-of-bounds index.\n");
        if (set_alist(list, 10, &b) == ALIST_INDEX_OUT_OF_BOUNDS)
            printf("ERROR: Set operation succeeded at an invalid index!\n");
        printf("\n");
        
        printf("Testing get at out-of-bounds index.\n");
        int num;
        if (get_alist(list, -1, &num) == ALIST_INDEX_OUT_OF_BOUNDS && 
            get_alist(list, 10, &num) == ALIST_INDEX_OUT_OF_BOUNDS)
            printf("ERROR: Retrieved value from an invalid index!\n");
        printf("\n");
        
        printf("Testing remove at out-of-bounds index.\n");
        if (remove_alist(list, 10, &num) == ALIST_INDEX_OUT_OF_BOUNDS)
            printf("ERROR: Removed an item from an invalid index!\n");
        printf("\n");
        
        printf("Testing remove_object with a non-existent object...\n");
        int d = 40;
        if (remove_object_alist(list, &d) == ALIST_INDEX_OUT_OF_BOUNDS)
            printf("ERROR: Removed a non-existent object!\n");

        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 7 completed.\n");
    return SUCCESS;
}

int UnitTest8()
{
    printf("Unit Test 8: \n");
    printf("\n");
    {
        ArrayList *list = create_arraylist(sizeof(int), 2);
        if (list == NULL)
            return printerr(ALIST_NULL);

        free_alist(&list);
    }
    printf("\n");
    printf("Unit Test 8 completed.\n");
    return SUCCESS;
}
