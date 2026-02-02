SERVER = bin/server
CLIENT = bin/client
SERVER_BO = bin/server_bonus
CLIENT_BO = bin/client_bonus
NAME = minitalk

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LIBDIR = ./libft/
LIB = ./libft/lib/libft.a

SERVERSRC = src/server.c 
SERVEROBJ = $(SERVERSRC:.c=.o)

CLIENTSRC = src/client.c
CLIENTOBJ = $(CLIENTSRC:.c=.o)

SERVERSRC_BO = src/server_bonus.c
SERVEROBJ_BO = $(SERVERSRC_BO:.c=.o)

CLIENTSRC_BO = src/client_bonus.c
CLIENTOBJ_BO = $(CLIENTSRC_BO:.c=.o)


all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(CLIENT) : $(CLIENTOBJ) $(LIB)
	mkdir -p bin
	$(CC) $(CFLAGS) $(CLIENTOBJ) $(LIB) -o $(CLIENT)

$(SERVER) : $(SERVEROBJ) $(LIB) 
	mkdir -p bin
	$(CC) $(CFLAGS) $(SERVEROBJ) $(LIB) -o $(SERVER)

bonus: $(SERVER_BO) $(CLIENT_BO)

$(CLIENT_BO) : $(CLIENTOBJ_BO) $(LIB)
	mkdir -p bin
	$(CC) $(CFLAGS) $(CLIENTOBJ_BO) $(LIB) -o $(CLIENT_BO)

$(SERVER_BO) : $(SERVEROBJ_BO) $(LIB) 
	mkdir -p bin
	$(CC) $(CFLAGS) $(SERVEROBJ_BO) $(LIB) -o $(SERVER_BO)

$(LIB) :
	make -C $(LIBDIR)
 
.PHONY: all clean fclean re

clean:
	rm -f $(CLIENTOBJ)
	rm -f $(SERVEROBJ)
	rm -f $(CLIENTOBJ_BO)
	rm -f $(SERVEROBJ_BO)
	make clean -C $(LIBDIR)

fclean: clean
	rm -rf bin
	make fclean -C $(LIBDIR)

re: fclean all
