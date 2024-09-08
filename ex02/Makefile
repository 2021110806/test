CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
NAME = ex02
SRCS = main.cpp PmergeMe.cpp
HEADER = PmergeMe.hpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

%.o : %.cpp $(HEADER)
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all