NAME	=	pipex
FLAGS	=	-Wall -Wextra -Werror
#FLAGS	+=	-fsanitize=address

LIBFT	= 	libft/
LIB		=	$(LIBFT)libft.a
SRC		=	main.c
OBJ		=	$(SRC:.c=.o)

ARG		=	in.txt "grep ass" "wc -l" outfile

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@cc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo "compiling $@"

$(LIB):
	@make -C $(LIBFT)

run: $(NAME)
	@./$(NAME) $(ARG)

%.o: %.c
	@cc $(FLAGS) -c $< -I $(LIBFT)includes -o $@
	@echo "compiling file $@"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
