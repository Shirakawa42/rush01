CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra -I include

NAME = fixed

SRC = src/Player.cpp src/Enemy.cpp src/GameManager.cpp

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