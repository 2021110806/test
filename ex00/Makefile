CPP = c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
NAME = btc
SRCS = main.cpp BitcoinExchange.cpp
HEADER = BitcoinExchange.hpp
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