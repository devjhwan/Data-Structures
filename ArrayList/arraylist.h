#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# include <stdlib.h>
# include <string.h>

typedef struct arraylist {
	void			*array;
	size_t			size;
	size_t			capacity;
	unsigned int	data_size;
} ArrayList;

ArrayList	*create_arraylist(const unsigned int data_size);
int			add_alist(ArrayList *list, void *data);
int			add_index_alist(ArrayList *list, size_t index, void *data);
int			get_alist(ArrayList *list, size_t index, void *output);
int			clear_alist(ArrayList *list);
ArrayList	*clone_alist(ArrayList *list);
int			contains_alist(ArrayList *list, void *object);
long long	indexOf_alist(ArrayList *list, void *object);
int 		isEmpty_alist(ArrayList *list);
long long	last_indexOf_alist(ArrayList *list, void *object);
int			remove_alist(ArrayList *list, size_t index, void *output);
int			remove_object_alist(ArrayList *list, void *object);
int			set_alist(ArrayList *list, size_t index, void *object);
size_t		size_alist(ArrayList *list);
void		free_alist(ArrayList *list);

#endif