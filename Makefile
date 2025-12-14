NAME = so_long

SOURCE = check_and_find.c check_path.c game.c gamehook.c input_and_all.c \
         mapstuff.c moves.c so_long.c

HEADER = so_long.h

CFLAGS = -Wall -Wextra -Werror -Imlx_linux -O3

OBJECTS = $(SOURCE:.c=.o)

LIBFT = libft/libft.a

CC = cc

RM = rm -f

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -lXtst 

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C mlx_linux
	$(MAKE) -C libft
	$(CC) $(OBJECTS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

clean:
	$(RM) $(OBJECTS)
	$(MAKE) -C mlx_linux clean
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
