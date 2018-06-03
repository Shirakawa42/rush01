CXX = clang++

CXXFLAGS = -g -lncurses -I include #-Wall -Wextra -Werror

NAME = game

SRC = src/Player.cpp src/Enemy.cpp src/GameManager.cpp src/main.cpp src/Star.cpp src/Projectile.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
