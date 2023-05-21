MAIN = main.c
TOOLS = read_map.c algorithm.c utils.c move_pic.c map_modification.c hooks.c

OMAIN = $(MAIN:.c=.o)
OTOOLS = $(TOOLS:.c=.o)

FDF = fdf

MLX42 = MLX42/build/libmlx42.a
HEADERS = -I ./include -I ./MLX42/include -I ./libft/libft.h
LIBFT = libft/libft.a
ifeq ($(shell uname -s),Darwin)			# Mac
	MLXFLAGS = MLX42/build/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit -lglfw3
else ifeq ($(shell uname -s),Linux)		# Linux
	MLXFLAGS = MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
endif

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f

RESET = \033[0m
YELLOW = \33[1;33m
LIGHT_CYAN=\033[1;36m
LIGHT_GREEN=\033[1;32m
RED=\03

all: $(FDF)

$(FDF):$(OMAIN) $(OTOOLS) $(MLX42) $(LIBFT)
	cc $(FLAGS) $(OMAIN) $(OTOOLS) $(MLXFLAGS) $(LIBFT) $(MLX42) -o $(FDF)
	@printf "\n$(LIGHT_CYAN)Created executable $(FDF)$(RESET)\n\n"

%.o: %.cc
	cc $(FLAGS) -c $< $@ $(HEADERS)

$(LIBFT):
	make -C libft

$(MLX42):
	cmake MLX42 -B MLX42/build
	make -C MLX42/build

clean:
	$(RM) $(OMAIN) $(OTOOLS)
	@printf "\n$(YELLOW)Removed object files$(RESET)\n\n"

fclean: clean
	$(RM) $(FDF)
	rm -rf MLX42/build
	make fclean -C libft
	@printf "\n$(RED)Cleaned up everything$(RESET)\n\n"

re: fclean all

.PHONY: all clean fclean re