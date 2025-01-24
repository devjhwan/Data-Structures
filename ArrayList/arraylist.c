#include "arraylist.h"
#include <stdint.h>
#include <string.h>

ArrayList	*create_arraylist(const unsigned int data_size, unsigned int initial_capacity)
{
	ArrayList	*list = (ArrayList *)malloc(sizeof(ArrayList));
	if (list == NULL)
		return NULL;

	list->size = 0;
	list->data_size = data_size;
	list->capacity = (initial_capacity > 0) ? initial_capacity : DEFAULT_CAPACITY;
	list->array = malloc(list->capacity * list->data_size);
	if (list->array == NULL)
	{
		free(list);
		return NULL;
	}
	return list;
}

static int	resize_alist(ArrayList *list)
{
	size_t new_capacity;

	if (list == NULL || list->array == NULL)
		return ALIST_NULL;
	if (list->capacity >= SIZE_MAX / list->data_size / 2)
		return ALIST_RESIZE_FAIL;
	else
		new_capacity = list->capacity << 1;

	void *new_array = realloc(list->array, new_capacity * list->data_size);
	if (new_array == NULL)
		return ALIST_NULL;
	list->capacity = new_capacity;
	list->array = new_array;
	return ALIST_OK;
}

int	add_alist(ArrayList *list, void *data)
{
	if (list == NULL || list->array == NULL)
		return ALIST_NULL;
	if (list->size == list->capacity && resize_alist(list) < 0)
		return ALIST_RESIZE_FAIL -3;

	char *target = (char *)list->array + (list->size * list->data_size);
	memcpy(target, data, list->data_size);
	list->size++;
	return ALIST_OK;
}

int	add_index_alist(ArrayList *list, size_t index, void *data)
{
	if (list == NULL || list->array == NULL)
		return ALIST_NULL;
	if (index > list->size)
		return ALIST_INDEX_OUT_OF_BOUNDS;
	if (list->size == list->capacity && resize_alist(list) < 0)
		return ALIST_RESIZE_FAIL -3;

	char *target = (char *)list->array + (index * list->data_size);
	if (index < list->size)
		memmove(target + list->data_size, target, (list->size - index) * list->data_size);
	memcpy(target, data, list->data_size);
	list->size++;
	return ALIST_OK;
}

int	set_alist(ArrayList *list, size_t index, void *object)
{
	if (list == NULL || list->array == NULL)
		return ALIST_NULL;
	if (index >= list->size)
		return ALIST_INDEX_OUT_OF_BOUNDS;

	char *target = (char *)list->array + (index * list->data_size);
	memcpy(target, object, list->data_size);
	return ALIST_OK;
}

int	get_alist(ArrayList *list, size_t index, void *output)
{
	if (list == NULL || list->array == NULL || output == NULL)
		return ALIST_NULL;
	if (index >= list->size)
		return ALIST_INDEX_OUT_OF_BOUNDS;

	char *source = (char *)list->array + (index * list->data_size);
	memcpy(output, source, list->data_size);
	return ALIST_OK;
}

static void shrink_alist(ArrayList *list)
{
	if (list->capacity > DEFAULT_CAPACITY && list->size < list->capacity / 4)
	{
		size_t new_capacity = list->capacity / 2;
		void *new_array = realloc(list->array, new_capacity * list->data_size);
		if (new_array != NULL)
		{
			list->array = new_array;
			list->capacity = new_capacity;
		}
	}
}

static void remove_element(ArrayList *list, char *target)
{
	size_t remaining_bytes = (size_t)((char *)list->array + (list->size * list->data_size) - (target + list->data_size));

	if (remaining_bytes > 0)
		memmove(target, target + list->data_size, remaining_bytes);

	memset((char *)list->array + (list->size - 1) * list->data_size, 0, list->data_size);
	list->size--;
	shrink_alist(list);
}

int	remove_alist(ArrayList *list, size_t index, void *output)
{
	if (list == NULL || list->array == NULL)
		return ALIST_NULL;
	if (index >= list->size)
		return ALIST_INDEX_OUT_OF_BOUNDS;

	char *target = (char *)list->array + (index * list->data_size);
	if (output != NULL)
		memcpy(output, target, list->data_size);
	remove_element(list, target);
	return ALIST_OK;
}

int	remove_object_alist(ArrayList *list, void *object)
{
	if (list == NULL || list->array == NULL)
		return ALIST_NULL;

	char *target;
	char *end = (char *)list->array + (list->size * list->data_size);
	for (target = list->array; target < end; target += list->data_size)
		if (memcmp(target, object, list->data_size) == 0)
			break;
	if (target >= end)
		return ALIST_INDEX_OUT_OF_BOUNDS;
	remove_element(list, target);
	return ALIST_OK;
}

int	clear_alist(ArrayList *list)
{
	if (list == NULL || list->array == NULL)
		return ALIST_NULL;
	list->size = 0;
	memset(list->array, 0, list->capacity * list->data_size);
	return ALIST_OK;
}

static long long find_element(ArrayList *list, void *object, int (*comparator)(const void *, const void *), int reverse)
{
	if (list == NULL || list->array == NULL)
		return ALIST_NULL;

	size_t i = reverse ? list->size : 0;
	while (reverse ? i-- : i < list->size)
	{
		char *current = (char *)list->array + (i * list->data_size);
		if ((comparator && comparator(current, object) == 0) || (!comparator && memcmp(current, object, list->data_size) == 0))
			return i;
	}
	return ALIST_INDEX_OUT_OF_BOUNDS;
}

int	contains_alist(ArrayList *list, void *object, int (*comparator)(const void *, const void *))
{
	return find_element(list, object, comparator, 0) >= 0 ? TRUE : FALSE;
}

long long	index_of_alist(ArrayList *list, void *object, int (*comparator)(const void *, const void *))
{
	return find_element(list, object, comparator, 0);
}

long long	last_index_of_alist(ArrayList *list, void *object, int (*comparator)(const void *, const void *))
{
	return find_element(list, object, comparator, 1);
}

ArrayList	*clone_alist(ArrayList *list)
{
	if (list == NULL || list->array == NULL)
		return NULL;

	ArrayList	*newList = (ArrayList *)malloc(sizeof(ArrayList));
	if (newList == NULL)
		return NULL;

	newList->size = list->size;
	newList->data_size = list->data_size;
	newList->capacity = list->capacity;
	newList->array = malloc(list->capacity * list->data_size);
	if (newList->array == NULL)
	{
		free(newList);
		return NULL;
	}

	if (list->size > 0)
		memcpy(newList->array, list->array, list->size * list->data_size);
	return newList;
}

int	sort_alist(ArrayList *list, int (*comparator)(const void *, const void *))
{
	if (list == NULL || list->array == NULL || comparator == NULL)
		return ALIST_NULL;

	qsort(list->array, list->size, list->data_size, comparator);
	return ALIST_OK;
}

int	binary_search_alist(ArrayList *list, void *key, int (*comparator)(const void *, const void *))
{
	if (list == NULL || list->array == NULL || comparator == NULL)
		return ALIST_NULL;

	void *result = bsearch(key, list->array, list->size, list->data_size, comparator);
	if (result == NULL)
		return ALIST_INDEX_OUT_OF_BOUNDS;

	return (int)(((char *)result - (char *)list->array) / list->data_size);
}

void	free_alist(ArrayList **list)
{
	if (list == NULL || *list == NULL)
		return ;
	free((*list)->array);
	free(*list);
	*list = NULL;
}

void free_alist_with_destructor(ArrayList **list, void (*destructor)(void *))
{
	if (list == NULL || *list == NULL)
		return;

	if (destructor != NULL)
	{
		char *end = (char *)(*list)->array + ((*list)->size * (*list)->data_size);
		for (char *index = (*list)->array; index < end; index += (*list)->data_size)
			destructor(index);
	}

	free((*list)->array);
	free(*list);
	*list = NULL;
}
