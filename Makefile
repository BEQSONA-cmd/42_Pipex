NAME = pipex

B_NAME = pipex

SRC = Mandatory/pipex.c\
	Mandatory/source.c\
	Mandatory/utils1.c\

B_SRC = Bonus/pipex.c\
	Mandatory/source.c\
	Mandatory/utils1.c\
	Bonus/utils.c\
	Bonus/get_next_line.c\
	Bonus/get_next_line_utils.c\
	

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

bonus: $(B_OBJ)
	$(CC) $(CFLAGS) -o $(B_NAME) $(B_SRC)

clean:
	rm -f $(OBJ)
	rm -f $(B_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY:	all clean fclean re bonus
