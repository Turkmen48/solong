NAME = solong
SRC = main.c solong_utils.c
OBJ = $(SRC:.c=.o)
RM = rm
LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

%.o: %.c $(LIBFT)
	$(CC) -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)

$(LIBFT):
	@make -C $(LIBFT_PATH) all
all: $(NAME)

clean:
	$(RM) -rf $(OBJ)

fclean:
	$(RM) -rf $(OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re
