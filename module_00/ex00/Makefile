MAKEFLAGS += -j

NAME := test
SRC := 	main.cpp \
		Bank.cpp \
		Account.cpp
BIN := $(addprefix bin/, $(SRC:.cpp=.o))

CPPC := c++
CPPFLAGS  := -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(BIN)
	@$(CPPC) -o $(NAME) $(BIN)
	@printf "\033[32m[✔] Created $(NAME)\n\033[0m"

bin/%.o: src/%.cpp
	@mkdir -p $(@D)
	@$(CPPC) $(CPPFLAGS) -c $< -o $@ -I include -I lib/zlib

clean:
	@rm -rf bin
	@printf "\033[31m[✗] Cleaned $(NAME)\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@printf "\033[31m[✗] Fcleaned $(NAME)\n\033[0m"

re: fclean
	@make -s

.PHONY: all clean fclean re
