#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# include <stdlib.h>

typedef struct arraylist {
	void				*array;
	unsigned long long	size;
	unsigned int		data_size;
	unsigned long long	capacity;
} ArrayList;

ArrayList	*init_arraylist(const unsigned int data_size);

#endif