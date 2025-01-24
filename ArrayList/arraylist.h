#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# include "arraylist_iterator.h"
# include "arraylist_struct.h"

# define DEFAULT_CAPACITY 100
# define ALIST_OK 0
# define ALIST_NULL -1
# define ALIST_INDEX_OUT_OF_BOUNDS -2
# define ALIST_RESIZE_FAIL -3
# define TRUE 1
# define FALSE 0

ArrayList	*create_arraylist(const unsigned int data_size, unsigned int initial_capacity);
int			add_alist(ArrayList *list, void *data);
int			add_index_alist(ArrayList *list, size_t index, void *data);
int			set_alist(ArrayList *list, size_t index, void *object);
int			get_alist(ArrayList *list, size_t index, void *output);
int			remove_alist(ArrayList *list, size_t index, void *output);
int			remove_object_alist(ArrayList *list, void *object);
int			clear_alist(ArrayList *list);
int			contains_alist(ArrayList *list, void *object, int (*comparator)(const void *, const void *));
long long	index_of_alist(ArrayList *list, void *object, int (*comparator)(const void *, const void *));
long long	last_index_of_alist(ArrayList *list, void *object, int (*comparator)(const void *, const void *));
ArrayList	*clone_alist(ArrayList *list);
int			sort_alist(ArrayList *list, int (*comparator)(const void *, const void *));
int			binary_search_alist(ArrayList *list, void *key, int (*comparator)(const void *, const void *));
void		free_alist(ArrayList **list);
void 		free_alist_with_destructor(ArrayList **list, void (*destructor)(void *));

#endif