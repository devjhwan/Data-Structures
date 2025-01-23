#include "arraylist.h"

ArrayList	*init_arraylist(const unsigned int data_size)
{
	ArrayList	*arraylist;

	arraylist = (ArrayList *)malloc(sizeof(ArrayList));
	if (arraylist == NULL)
		return NULL;
	arraylist->size = 0;
	arraylist->data_size = data_size;
	arraylist->capacity = 100;
	arraylist->array = malloc(arraylist->capacity * arraylist->data_size);
	if (arraylist->array == NULL)
	{
		free(arraylist);
		return NULL;
	}
	return arraylist;
}

void	add_arraylist(ArrayList *arraylist, void *data)
{
	if (arraylist->size == arraylist->capacity)
	{
		//realloc
	}
	//get position pointer
	//do memcpy
}