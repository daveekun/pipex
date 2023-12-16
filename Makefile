NAME	=	pipex
FLAGS	=	-Wall -Wextra -Werror

LIBFT	= 	libft/
LIB		=	$(LIBFT)libft.a
MAIN	=	src/main.c
MAIN_B	=	src/main_bonus.c
SRC_DIR	=	src/
SRC		=	$(addprefix $(SRC_DIR), arg_split.c commands.c errors.c \
				file_descriptors.c find_command.c utils.c)
OBJ_DIR	=	obj/
OBJ		=	$(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@cc $(FLAGS) $(MAIN) $(OBJ) $(LIB) -I $(LIBFT)includes -I include/ -o $(NAME)
	@echo "compiling pipex"

$(LIB):
	@make -C $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@cc $(FLAGS) -c $< -I $(LIBFT)includes -I include/ -o $@
	@echo "compiling file $@"

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

bonus: .bonus

.bonus: $(LIB) $(OBJ_B) 
	@cc $(FLAGS) $(MAIN_B) $(OBJ) $(LIB) -I $(LIBFT)includes -I include/ -o $(NAME)
	@echo "compiling pipex bonus"
	
clean:
	@rm -rf $(OBJ) $(OBJ_B) $(OBJ_DIR)
	@make clean -C $(LIBFT)
	@rm -rf .bonus

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -rf $(NAME)

re: fclean all
