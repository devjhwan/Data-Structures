#ifndef ARRAYLIST_ITERATOR_H
# define ARRAYLIST_ITERATOR_H

# include "arraylist_struct.h"

ArrayListIterator   *create_iterator(ArrayList *list);
void                *next(ArrayListIterator *iterator);
void            	free_iterator(ArrayListIterator *iterator);

#endif