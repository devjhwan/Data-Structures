#include "unit_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef int (*UnitTestFunc)(void);

UnitTestFunc* create_unit_test_list(UnitTestFunc first, ...) {
    va_list args;
    va_start(args, first);

    size_t count = 0;
    UnitTestFunc func = first;
    while (func != NULL) {
        count++;
        func = va_arg(args, UnitTestFunc);
    }
    va_end(args);

    UnitTestFunc* unit_tests = (UnitTestFunc*)malloc((count + 1) * sizeof(UnitTestFunc));
    if (!unit_tests) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    va_start(args, first);
    func = first;
    for (size_t i = 0; i < count; i++) {
        unit_tests[i] = func;
        func = va_arg(args, UnitTestFunc);
    }
    va_end(args);

    unit_tests[count] = NULL;
    return unit_tests;
}

int main(void)
{
    UnitTestFunc* unit_tests;
    
    unit_tests = create_unit_test_list(
                    UnitTest1, UnitTest2, UnitTest3, UnitTest4,
                    UnitTest5, UnitTest6, UnitTest7, NULL);
    if (!unit_tests)
        return -1;

    for (int i = 0; unit_tests[i] != NULL; i++) {
        if (unit_tests[i]() == ERROR) {
            printf("Get unexpected error from UnitTest %d.", i + 1);
            free(unit_tests);
            return -1;
        }
        if (unit_tests[i + 1] != NULL)
        {
            printf("\n");
            printf("--------------------------------------------------\n");
            printf("\n");
        }
    }
    free(unit_tests);
    return 0;
    // ArrayList *list = create_arraylist(sizeof(int), 0);
    // if (list == NULL)
    // {
    //     printf("Couldn't create ArrayList\n");
    //     return -1;
    // }
    // printf("Create ArrayList\n");

    // for (int i = 0; i < 20; i += 2)
    // {
    //     if (add_alist(list, &i) < 0)
    //     {
    //         printf("Error while adding data to ArrayList\n");
    //         free_alist(&list);
    //         return -1;
    //     }
    //     printf("Add %d\n", i);
    // }

    // ArrayListIterator *iter = create_iterator_alist(list);
    // if (iter == NULL)
    // {
    //     printf("Couldn't create ArrayListIterator\n");
    //     free_alist(&list);
    //     return -1;
    // }
    // printf("Create Iterator\n");

    // int *num_p = NULL;
    // for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
    //     printf("Iter %ld got %d\n", i, *num_p);
    // printf("Final pointer gotten by iterator -> %p\n", (void *)num_p);

    // free_iterator_alist(&iter);
    // printf("Free iterator\n");

    // int num = -1;
    // if (get_alist(list, 5, &num) < 0)
    // {
    //     printf("Get function error\n");
    //     free_alist(&list);
    //     return -1;
    // }
    // printf("Get %d from index 5\n", num);

    // num = 9;
    // if (set_alist(list, 4, &num) < 0)
    // {
    //     printf("Set function error\n");
    //     free_alist(&list);
    //     return -1;
    // }
    // printf("Set %d to index 4\n", num);

    // num = -1;
    // if (get_alist(list, 4, &num) < 0)
    // {
    //     printf("Get function error\n");
    //     free_alist(&list);
    //     return -1;
    // }
    // printf("Get %d from index 4\n", num);

    // num = 42;
    // if (add_index_alist(list, 3, &num) < 0)
    // {
    //     printf("Error while adding number to index 3\n");
    //     free_alist(&list);
    //     return -1;
    // }

    // iter = create_iterator_alist(list);
    // if (iter == NULL)
    // {
    //     printf("Couldn't create ArrayListIterator\n");
    //     free_alist(&list);
    //     return -1;
    // }
    // printf("Create Iterator\n");

    // for (size_t i = 0; (num_p = next_alist(iter)) != NULL || i < list->size; i++)
    //     printf("Iter %ld got %d\n", i, *num_p);

    // free_iterator_alist(&iter);
    // printf("Free iterator\n");

    // free_alist(&list);
    // printf("Finish unit test and free arraylist variable\n");
    return 0;
}
