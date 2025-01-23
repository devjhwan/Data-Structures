#include "arraylist.h"

ArrayList	*create_arraylist(const unsigned int data_size)
{
	ArrayList	*list = (ArrayList *)malloc(sizeof(ArrayList));
	if (list == NULL)
		return NULL;

	list->size = 0;
	list->data_size = data_size;
	list->capacity = 100;
	list->array = malloc(list->capacity * list->data_size);
	if (list->array == NULL)
	{
		free(list);
		return NULL;
	}
	return list;
}

int	add_alist(ArrayList *list, void *data)
{
	if (list == NULL || list->array == NULL)
		return -1;
	if (list->size == list->capacity)
	{
		void *new_array = realloc(list->array, list->capacity * list->data_size * 2);
		if (new_array == NULL)
			return -2;
		list->capacity <<= 1;
		list->array = new_array;
	}

	void *target = list->array + (list->size * list->data_size);
	memcpy(target, data, list->data_size);
	list->size++;
	return 0;
}

int	add_index_alist(ArrayList *list, size_t index, void *data)
{
	if (list == NULL || list->array == NULL)
		return -1;
	if (index > list->size)
		return -2;
	if (list->size == list->capacity)
	{
		list->capacity *= 1.2;
		list->array = realloc(list->array, list->capacity * list->data_size);
	}

	void *target = list->array + (index * list->data_size);
	if (index < list->size)
		memmove(target + list->data_size, target, (list->size - index) * list->data_size);
	memcpy(target, data, list->data_size);
	list->size++;
	return 0;
}

int	get_alist(ArrayList *list, size_t index, void *output)
{
	if (list == NULL || list->array == NULL)
		return -1;
	if (index >= list->size)
		return -2;

	void *source = list->array + (index * list->data_size);
	memcpy(output, source, list->data_size);
	return 0;
}

int	clear_alist(ArrayList *list)
{
	if (list == NULL || list->array == NULL)
		return -1;
	memset(list->array, 0, list->capacity * list->data_size);
	list->size = 0;
}

ArrayList	*clone_alist(ArrayList *list)
{
	if (list == NULL || list->array == NULL)
		return -1;

	ArrayList	*newList = (ArrayList *)malloc(sizeof(ArrayList));
	if (newList == NULL)
		return NULL;

	newList->size = list->size;
	newList->data_size = list->data_size;
	newList->capacity = list->capacity;
	newList->array = malloc(list->capacity * list->data_size);
	if (list->array == NULL)
	{
		free(list);
		return NULL;
	}

	memcpy(newList->array, list->array, list->size * list->data_size);
	return newList;
}

int	contains_alist(ArrayList *list, void *object)
{
	if (list == NULL || list->array == NULL)
		return -1;
	
	void *end = list->size * list->data_size;
	for (void *index = list->array; index < end; index += list->data_size)
	{
		if (memcmp(index, object, list->data_size) == 0)
			return 1;
	}
	return 0;
}

long long	indexOf_alist(ArrayList *list, void *object)
{
	if (list == NULL || list->array == NULL)
		return -1;
	
	void *end = list->size * list->data_size;
	for (void *index = list->array; index < end; index += list->data_size)
	{
		if (memcmp(index, object, list->data_size) == 0)
			return (long long)((index - list->array) / list->data_size);
	}
	return -2;
}

int isEmpty_alist(ArrayList *list)
{
	if (list == NULL || list->array == NULL)
		return -1;

	if (list->size == 0)
		return 1;
	return 0;
}

long long	last_indexOf_alist(ArrayList *list, void *object)
{
	if (list == NULL || list->array == NULL)
		return -1;

	void *last_index = -2;

	for (void *index = list->array; index < (list->size * list->data_size); index += list->data_size)
	{
		if (memcmp(index, object, list->data_size) == 0)
			last_index = (long long)((index - list->array) / list->data_size);
	}
	return last_index;
}

int	remove_alist(ArrayList *list, size_t index, void *output)
{
	if (list == NULL || list->array == NULL)
		return -1;
	if (index > list->size)
		return -2;

	void *target = list->array + (index * list->data_size);
	if (output != NULL)
		memcpy(output, target, list->data_size);

	memmove(target, target + list->data_size, (list->size - index - 1) * list->data_size);

	target = list->array + (list->size * list->data_size);
	memset(target, 0, list->data_size);
	list->size--;
	return 0;
}

int	remove_object_alist(ArrayList *list, void *object)
{
	if (list == NULL || list->array == NULL)
		return -1;

	void *target;
	for (target = list->array; target < (list->size * list->data_size); target += list->data_size)
	{
		if (memcmp(target, object, list->data_size) == 0)
			break;
	}
	if (target == (list->size * list->data_size))
		return -2;

	memmove(target, target + list->data_size, (list->size - 1) * list->data_size - (size_t)target);

	target = list->array + (list->size * list->data_size);
	memset(target, 0, list->data_size);
	list->size--;
	return 0;
}

int	set_alist(ArrayList *list, size_t index, void *object)
{
	if (list == NULL || list->array == NULL)
		return -1;
	if (index > list->size)
		return -2;

	void *target = list->array + (index * list->data_size);
	memcpy(target, object, list->data_size);
	return 0;
}

size_t	size_alist(ArrayList *list)
{
	if (list == NULL || list->array == NULL)
		return -1;
	
	return list->size;
}

void	free_alist(ArrayList **list)
{
	if (*list != NULL)
	{
		free((*list)->array);
		(*list)->array = NULL;
	}
	free(*list);
	*list = NULL;
}