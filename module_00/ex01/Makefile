MAKEFLAGS += -j

NAME := graph
SRC := 	main.cpp \
		Vector2.cpp \
		Graph.cpp \
		png.cpp \
		draw.cpp
BIN := $(addprefix bin/, $(SRC:.cpp=.o))

CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -g3

ZLIB := lib/zlib/libz.so

all: $(NAME)

$(ZLIB):
	@cd lib/zlib && ./configure > /dev/null
	@make -sC lib/zlib
	@printf "\033[32m[✔] Created %s\n\033[0m" "zlib"

$(NAME): $(ZLIB) $(BIN)
	@$(CC) -o $(NAME) $(BIN) -lz -L lib/zlib
	@printf "\033[32m[✔] Created %s\n\033[0m" "$(NAME)"

bin/%.o: src/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I include -I lib/zlib

clean:
	@rm -rf bin
	@make -sC lib/zlib clean
	@printf "\033[31m[✔] Cleaned %s\n\033[0m" "$(NAME)"

fclean: clean
	@rm -f $(NAME)
	@make -sC lib/zlib distclean
	@printf "\033[31m[✔] Fcleaned %s\n\033[0m" "$(NAME)"

re: fclean
	@make -s

.PHONY: all clean fclean re
