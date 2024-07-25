NAME = minishell

SOURCES = main.c  gc/ft_free.c gc/ft_lstadd_back.c gc/ft_lstadd_front.c gc/ft_lstclear.c gc/ft_lstdelone.c gc/ft_lstlast.c  gc/ft_lstnew.c gc/ft_lstsize.c gc/ft_malloc.c \
		parsing/dll_utils.c parsing/dll_utils1.c parsing/tokenize.c parsing/parser.c signals.c parsing/qu_sp.c bltn_func/echo.c bltn_func/pwd.c bltn_func/ft_builtin_func.c\
		bltn_func/exit.c bltn_func/env.c bltn_func/utils.c bltn_func/unset.c\
		parsing/env_handling.c parsing/env_utils.c bltn_func/cd.c bltn_func/export.c execute/execute_cmd.c parsing/her_doc.c  parsing/build_command.c parsing/redirections.c\



OBJECTS = $(SOURCES:.c=.o)

LIBFT = cd libft && make
LIB = libft/libft.a


CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -m64
RM = rm -f

all: $(NAME)

$(NAME): $(OBJECTS) 
	@$(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB) -o $(NAME) -lreadline  -ltermcap 


%.o: %.c minishell.h ./libft/libft.h ./libft/gc/gc.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	cd libft && make clean 

fclean: clean
	$(RM) $(NAME)
	cd libft && make fclean 

re: fclean all