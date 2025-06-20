################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fPIE

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

LIBFT_DIR = ./inc/Mylib
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./inc/mlx_linux
MLX = $(MLX_DIR)/libmlx.a

SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), main.c \
       							init/00_init.c \
								parse/00_parse.c \
								parse/01_ch_map.c \
								parse/02_ch_map_info.c \
								parse/03_rgb_info.c \
       							parse/04_parse_utils.c \
								close/00_close_and_free.c)

TMP = ./tmp

################################################################################
#                                  COLORS                                      #
################################################################################

RED		= "\033[0;31m"
GRN		= "\033[0;32m"  
YEL		= "\033[0;33m"
BLU		= "\033[0;34m"
BLA		= "\033[0;30m"
CYA		= "\033[0;36m"
GREY	= "\033[0;90m"
BBLA	= "\033[30;1m"
BRED 	= "\033[31;1m"
BGRN	= "\033[32;1m"
BYEL	= "\033[33;1m"
BBLU	= "\033[34;1m"
BMAG	= "\033[35;1m"
BCYA	= "\033[36;1m"
BWHI	= "\033[37;1m"
RESET	= "\033[0m"

################################################################################
#                                  Makefile objs                               #
################################################################################

all: $(NAME)

OBJS = $(patsubst $(SRCS_DIR)%,$(TMP)/%,$(SRCS:.c=.o))

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lm -lXext -lX11 -o $(NAME)
	@clear
	@echo $(BBLU) "   ____ _   _ ____  _____  ____  "
	@echo $(BBLU) "  / ___| | | | __ )|___ / |  _ \ "
	@echo $(BBLU) " | |   | | | |  _ \  |_ \ | | | |"
	@echo $(BBLU) " | |___| |_| | |_)  ___) || |_| |"
	@echo $(BBLU) "  \____|\___/|____/|____/ |____/ " $(RESET)
	@echo "\n"
	@echo $(BGRN) "Compilation Successful!"$(RESET)
	@echo $(BYEL)" This $(NAME) was created by icunha-t and jpedro-c!" $(RESET)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
	echo $(BYEL) "Cloning MiniLibX..." $(RESET); \
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(TMP)/%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

valgrind:
	/usr/bin/valgrind --track-fds=yes --leak-check=full -s --show-leak-kinds=all ./$(NAME)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C $(MLX_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@clear
	@rm -rf $(TMP)
	@echo $(BRED)"-> .o files removed"$(RESET)

fclean: clean
	@$(RM) $(NAME)
	@clear
	@echo $(BRED)"-> $(NAME) and .o files removed"$(RESET)

fcleanall: clean fclean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(MLX_DIR)
	@clear
	@echo $(BRED)"-> $(NAME), .o files, mlx and libft removed"$(RESET)

re: fclean all

.PHONY: all clean fclean fcleanall valgrind re