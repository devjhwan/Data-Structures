CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

ARRAYLIST_DIR = ..
LIB_DIR = $(ARRAYLIST_DIR)
INCLUDE_DIR = $(ARRAYLIST_DIR)
LIBRARY = $(LIB_DIR)/libarraylist.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)
TARGET = unit_test

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) -larraylist

$(LIBRARY):
	make -C $(ARRAYLIST_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(ARRAYLIST_DIR) fclean

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
