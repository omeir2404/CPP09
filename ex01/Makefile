NAME = RPN
SRCS = main.cpp RPN.cpp
OBJS = $(SRCS:.cpp=.o)
COMPILER = c++
FLAGS = -Wall -Wextra -Werror -g -std=c++98


Black =  \033[0;30m
Red = \033[0;31m
Green = \033[0;32m
Yellow = \033[0;33m
Blue = \033[0;34m
Magenta = \033[0;35m
Cyan = \033[0;36m
White = \033[0;37m


# Bold Text Colors
BBlack = \033[1;30m
BRed = \033[1;31m
BGreen = \033[1;32m
BYellow = \033[1;33m
BBlue = \033[1;34m
BMagenta = \033[1;35m
BCyan = \033[1;36m
BWhite = \033[1;37m


# Background Colors
BGBlack = \033[40m
BGRed = \033[41m
BGGreen = \033[42m
BGYellow = \033[43m
BGBlue = \033[44m
BGMagenta = \033[45m
BGCyan = \033[46m
BGWhite = \033[47m

# Reset Code
Reset = \033[0m

# Text Colors
NAME_COLOR = $(Green)
RULE_COLOR = $(Cyan)

# Rule Texts
all: $(NAME)
	@echo "$(RULE_COLOR)$(NAME_COLOR)$(NAME)$(Reset)"

$(NAME): $(OBJS)
	@$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(RULE_COLOR)Compiled $(NAME)$(Reset)"

clean:
	@echo "$(Red)Cleaning $(NAME_COLOR) $(NAME) $(Cyan) objects$(Reset)"
	@rm -f $(OBJS) val.log

fclean: clean
	@echo "$(RULE_COLOR)Cleaning $(NAME) executable$(Reset)"
	@rm -f $(NAME)

re: fclean all
	@echo "$(RULE_COLOR)Rebuilding $(NAME)$(Reset)"

run: 
	@echo "$(RULE_COLOR)Running $(NAME)$(Reset)"
	@ ./$(NAME)  "8 9 * 9 - 9 - 9 - 4 - 1 +"

mem: re
	@echo "$(RULE_COLOR)Running $(NAME) with memory check$(Reset)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="val.log" ./$(NAME) "1 2 * 2 / 2 * 2 4 - +"

.PHONY: all clean fclean re