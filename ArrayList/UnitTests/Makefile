CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

ARRAYLIST_DIR = ..
LIB_DIR = $(ARRAYLIST_DIR)
INCLUDE_DIR = $(ARRAYLIST_DIR)
LIBRARY = $(LIB_DIR)/libarraylist.a

SRCS = main.c unit_test.c
OBJ_DIR = .obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
TARGET = unit_test

all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -larraylist

$(LIBRARY):
	make -C $(ARRAYLIST_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(ARRAYLIST_DIR) fclean

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
