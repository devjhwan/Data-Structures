#ifndef ARRAYLIST_STRUCT_H
# define ARRAYLIST_STRUCT_H

# include <stdlib.h>

typedef struct arraylist {
	void			*array;
	size_t			size;
	size_t			capacity;
	unsigned int	data_size;
	int 			(*comparator)(const void *, const void *);
} ArrayList;

typedef struct {
    ArrayList *list;
    size_t index;
} ArrayListIterator;

#endif