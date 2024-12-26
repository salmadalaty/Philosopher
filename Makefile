NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
HEADERS := philo.h

SRC_DIR = src/
SOURCES := $(SRC_DIR)main.c $(SRC_DIR)dinner.c $(SRC_DIR)utils.c $(SRC_DIR)init.c $(SRC_DIR)monitor.c $(SRC_DIR)validation.c $(SRC_DIR)status.c

OBJ_DIR = obj
INC_DIRS := include
OBJS := $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIRS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
