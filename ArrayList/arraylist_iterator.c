#include "arraylist_iterator.h"

ArrayListIterator	*create_iterator(ArrayList *list)
{
	if (list == NULL || list->array == NULL)
		return NULL;

	ArrayListIterator *iterator = malloc(sizeof(ArrayListIterator));
	if (iterator == NULL)
		return NULL;

	iterator->list = list;
	iterator->index = 0;
	return iterator;
}

void	*next(ArrayListIterator *iterator)
{
	if (iterator == NULL || iterator->index >= iterator->list->size)
		return NULL;

	return (char *)iterator->list->array + (iterator->index++ * iterator->list->data_size);
}

void	free_iterator(ArrayListIterator *iterator)
{
	free(iterator);
}