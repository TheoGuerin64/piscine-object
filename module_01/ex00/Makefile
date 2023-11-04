MAKEFLAGS += -j

NAME := test
SRC := 	main.cpp \
		Position.cpp \
		Statistic.cpp \
		Worker.cpp \
		Tool.cpp \
		Shovel.cpp \
		Hammer.cpp \
		Workshop.cpp
BIN := $(addprefix bin/, $(SRC:.cpp=.o))

CC := c++
CFLAGS  := -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(BIN)
	@$(CC) -o $(NAME) $(BIN)
	@printf "\033[32m[✔] Created $(NAME)\n\033[0m"

bin/%.o: src/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I include

clean:
	@rm -rf bin
	@printf "\033[31m[✗] Cleaned $(NAME)\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@printf "\033[31m[✗] Fcleaned $(NAME)\n\033[0m"

re: fclean
	@make -s

.PHONY: all clean fclean re
