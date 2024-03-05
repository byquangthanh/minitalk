CC = gcc
CFLAGS = -Wall -Wextra -Werror
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all:$(FT_PRINTF) $(LIBFT) server client

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

server: server.o $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o server server.o -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -lft -lftprintf

client: client.o $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o client client.o -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -lft -lftprintf

server.o: server.c
	$(CC) $(CFLAGS) -c server.c

client.o: client.c
	$(CC) $(CFLAGS) -c client.c

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	rm -f server.o client.o

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	rm -f server client

re: fclean all
