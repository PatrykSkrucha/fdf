FILES = main.c

OFILES = $(FILES:.c=.o)

FDF = fdf

HEADERS = -I ./include -I ./MLX42/include -I ./libft/libft.h
LIBFT = libft/libft.a
MLX42 = MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

FLAGS = -Wall -Wextra -Werror
RM = rm -f

RESET = \033[0m
YELLOW = \33[1;33m
LIGHT_CYAN=\033[1;36m
LIGHT_GREEN=\033[1;32m
RED=\03

all: $(FDF)

$(FDF):$(OFILES) $(LIBFT) $(MLX42)
	cc $(FLAGS) $(OFILES) $(LIBFT) $(MLX42) -o $(FDF)
	@printf "\n$(LIGHT_CYAN)Created executable $(FDF)$(RESET)\n\n"

%.o: %.cc
	cc $(FLAGS) -c $< $@ $(HEADERS)

$(LIBFT):
	make -C libft

$(MLX42):
	make -C MLX42/build

clean:
	$(RM) $(OFILES)
	@printf "\n$(YELLOW)Removed object files$(RESET)\n\n"

fclean: clean
	$(RM) $(FDF)
	make fclean -C libft
	make clean -C MLX42/build
	@printf "\n$(RED)Cleaned up everything$(RESET)\n\n"

re: fclean all

.PHONY: all clean fclean re