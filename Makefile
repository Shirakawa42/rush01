NAME		=	ft_retro

CC			=	clang++
FLAGS		=	-Wall -Wextra -Werror -std=c++98

SRC_DIR		=	src/
INC_DIR		=	include/
OBJ_DIR		=	objs/

SRC_BASE	=	Enemy.cpp GameManager.cpp main.cpp Player.cpp Projectile.cpp Star.cpp \

SRCS = $(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_BASE:.cpp=.o))

all : $(NAME)

$(NAME):		$(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) \
		$(FLAGS) -lncurses
	@echo "\033[1;34m"$(NAME)" compiled"

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.cpp | $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;33mall is clean";

fclean: clean
	@rm -f $(NAME)
	@echo "\033[3;0;31mall files have been scratched";

re:				fclean all

.PHONY :		fclean clean re

-include $(OBJS:.o=.d)
