MAKEFLAGS += -j

NAME := test
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
	@sleep 0.1
	@make -sC lib/zlib
	@printf "\033[32m[✔] Created zlib\n\033[0m"

$(NAME): $(ZLIB) $(BIN)
	@$(CC) -o $(NAME) $(BIN) -lz -L lib/zlib
	@printf "\033[32m[✔] Created $(NAME)\n\033[0m"

bin/%.o: src/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I include -I lib/zlib

clean:
	@rm -rf bin
	@test -f lib/zlib/libz.so && make -siC lib/zlib clean || true
	@printf "\033[31m[✗] Cleaned $(NAME)\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -sC lib/zlib distclean
	@printf "\033[31m[✗] Fcleaned $(NAME)\n\033[0m"

re: fclean
	@make -s

.PHONY: all clean fclean re
