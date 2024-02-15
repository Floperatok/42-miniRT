
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
NAME		=	miniRT

SRC_PATH	=	src/
SRC			=	main.c

LIBFT_PATH	=	libs/libft/
LIBFT		=	libs/libft/libft.a
MLX_PATH	=	libs/minilibx-linux/
MLX			=	libs/minilibx-linux/libmlx.a

OBJ_PATH	=	obj/
OBJ			=	$(addprefix $(OBJ_PATH), $(SRC:.c=.o))

INCLUDES	=	./includes/

all:	$(NAME)

$(NAME):	$(OBJ)
	make -C $(LIBFT_PATH)
	make -C $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -lX11 -lXext -o $(NAME) -I $(INCLUDES) -lm

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	rm -rf $(OBJ_PATH)
	make -sC $(LIBFT_PATH) clean
	make -sC $(MLX_PATH) clean

fclean:
	rm -rf $(OBJ_PATH)
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX_PATH) clean

re: fclean all
