#include "arraylist_iterator.h"

ArrayListIterator	*create_iterator_alist(ArrayList *list)
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

void	*next_alist(ArrayListIterator *iterator)
{
	if (iterator == NULL || iterator->index >= iterator->list->size)
		return NULL;

	return (char *)iterator->list->array + (iterator->index++ * iterator->list->data_size);
}

void	*reset_iterator_alist(ArrayListIterator *iterator)
{
	if (iterator == NULL)
		return NULL;
	iterator->index = 0;
	return (void *)iterator;
}

void	free_iterator_alist(ArrayListIterator **iterator)
{
	if (iterator != NULL)
	{
		free(*iterator);
		*iterator = NULL;
	}
}