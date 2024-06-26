NAME = minishell
SOURCES = main.c\


OBJECTS = $(SOURCES:.c=.o)

LIBFT = cd libft && make
LIB = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror  
RM = rm -f

all: $(NAME)

$(NAME): $(OBJECTS) 
	@$(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME) -lreadline


%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	cd libft && make clean 

fclean: clean
	$(RM) $(NAME)
	cd libft && make fclean 

re: fclean all