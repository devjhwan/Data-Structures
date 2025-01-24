#ifndef ARRAYLIST_STRUCT_H
# define ARRAYLIST_STRUCT_H

# include <stdlib.h>

typedef struct arraylist {
	void			*array;
	size_t			size;
	size_t			capacity;
	unsigned int	data_size;
} ArrayList;

#endif