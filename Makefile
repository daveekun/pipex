NAME	=	pipex
FLAGS	=	-Wall -Wextra -Werror
#FLAGS	+=	-fsanitize=address

LIBFT	= 	libft/
LIB		=	$(LIBFT)libft.a
SRC		=	main.c
OBJ		=	$(SRC:.c=.o)

ARG		=	file1 cmd1 cmd2 file2

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@cc $(FLAGS) $(OBJ) -o $(NAME)
	@echo "compiling $@"

$(LIB):
	@make -C $(LIBFT)

run: $(NAME)
	@./$(NAME) $(ARG)

%.o: %.c
	@cc $(FLAGS) -c $< -o $@ -I $(LIBFT)/includes
	@echo "compiling file $@"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
