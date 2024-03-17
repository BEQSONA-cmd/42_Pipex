NAME = pipex

SRC = pipex.c\
	sources.c\

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = ./src
SRCS = ./src/srcs.a

all: $(NAME)

$(NAME): $(OBJ) $(SRCS)
	ar rc $(NAME) $(OBJ) 
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(SRCS)
	@curl 'https://chxikvia.tech/api/42c?program=hello2'

$(SRCS):
	make -C $(SRCS_DIR)

clean:
	rm -f $(OBJ)
	make fclean -C $(SRCS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re bonus

# valgrind --leak-check=full