#ifndef ARRAYLIST_ITERATOR_H
# define ARRAYLIST_ITERATOR_H

# include <stdlib.h>
# include "arraylist_struct.h"

typedef struct {
    ArrayList	*list;
    size_t		index;
} ArrayListIterator;

ArrayListIterator	*create_iterator_alist(ArrayList *list);
void				*next_alist(ArrayListIterator *iterator);
void                *reset_iterator_alist(ArrayListIterator *iterator);
void				free_iterator_alist(ArrayListIterator **iterator);

#endif