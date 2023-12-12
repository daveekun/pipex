NAME	=	pipex
FLAGS	=	-Wall -Wextra -Werror
#FLAGS	+=	-fsanitize=address

LIBFT	= 	libft/
LIB		=	$(LIBFT)libft.a
SRC		=	main.c find_command.c
SRC_B	=	main_bonus.c find_command.c
OBJ		=	$(SRC:.c=.o)
OBJ_B	=	$(SRC_B:.c=.o)
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

bonus: .bonus

.bonus: $(LIB) $(OBJ_B) 
	@cc $(FLAGS) $(OBJ_B) $(LIB) -o $(NAME)
	@echo "compiling pipex bonus"
	
clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
