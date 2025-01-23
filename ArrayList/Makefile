CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

SRCS = arraylist.c arraylist_iterator.c
HEADERS = arraylist.h arraylist_iterator.h arraylist_struct.h
OBJ_DIR = .obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

STATIC_LIB = libarraylist.a

all: $(OBJ_DIR) $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	@ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p .obj

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(STATIC_LIB)

re: fclean all

.PHONY: all clean fclean re
