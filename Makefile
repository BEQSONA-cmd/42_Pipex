NAME = pipex
B_NAME = pipex

SRC = pipex.c\
	sources.c\

B_SRC =

OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = ./src
SRCS = ./src/srcs.a

all: $(NAME)

$(NAME): $(OBJ) $(SRCS)
	ar rc $(NAME) $(OBJ) 
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(SRCS)
	@curl 'http://141.148.244.146:8080/ansi?start=8b5cf6&end=db2777&padding=5&text=42%20pipex'

bonus: $(B_OBJ) $(SRCS)
	ar rc $(B_NAME) $(B_OBJ) 
	$(CC) $(CFLAGS) -o $(B_NAME) $(B_SRC) $(SRCS)
	@curl 'http://141.148.244.146:8080/ansi?start=8b5cf6&end=db2777&padding=5&text=42%20Pac_Man!'

$(SRCS):
	make -C $(SRCS_DIR)

clean:
	rm -f $(OBJ)
	rm -f $(B_OBJ)
	make fclean -C $(SRCS_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(B_NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re bonus

# valgrind --leak-check=full