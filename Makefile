################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = cubo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

LIBFT_DIR = ./inc/Mylib
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./inc/mlx_linux
MLX = $(MLX_DIR)/libmlx.a

SRCS = main.c           			\
       src/parse/parse_utils.c     \
       src/init/init.c  			\


################################################################################
#                                  Makefile objs                               #
################################################################################

OBJS = $(SRCS:.c=.o)

all: $(MLX) $(LIBFT) $(NAME)
	@echo "\033[0;32mCompilation Successful!\033[0m"

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
	echo "Cloning MiniLibX..."; \
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT):
$(NAME): $(MLX) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lm -lXext -lX11 -o $(NAME)

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@
%.o: sources/%.c
clean:
	$(RM) $(OBJS)
	@$(MAKE) clean -C $(MLX_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) fclean -C $(MLX_DIR)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

.PHONY: all clean fclean re