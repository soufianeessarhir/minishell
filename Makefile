NAME = minishell
SOURCES = main.c gc/ft_free.c gc/ft_lstadd_back.c gc/ft_lstadd_front.c gc/ft_lstclear.c gc/ft_lstdelone.c gc/ft_lstlast.c gc/ft_lstnew.c gc/ft_lstsize.c gc/ft_malloc.c \
	    parsing/dll_utils.c parsing/dll_utils1.c parsing/tokenize.c parsing/parser.c signals.c parsing/qu_sp.c parsing/redirections.c parsing/build_command.c parsing/her_doc.c \
        parsing/env_handling.c parsing/env_utils.c parsing/cmd_utils.c parsing/env_utils2.c parsing/env_utils3.c parsing/env_utils4.c parsing/redir_utils.c parsing/env_utils5.c\
        bltn_func/cd.c bltn_func/export.c execute/execute_cmd.c bltn_func/ft_builtin_func.c bltn_func/pwd.c bltn_func/echo.c bltn_func/exit.c bltn_func/env.c bltn_func/utils.c\
        bltn_func/unset.c execute/getpath_programe.c execute/exitstatus_handler.c bltn_func/utils_display_exported_var.c bltn_func/utils_export_to_env.c parsing/env_utils6.c execute/utils_execute_cmd.c

OBJECTS = $(SOURCES:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SOURCES :=  $(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_bzero.c $(LIBFT_DIR)/ft_calloc.c \
                $(LIBFT_DIR)/ft_isalnum.c $(LIBFT_DIR)/ft_isalpha.c $(LIBFT_DIR)/ft_isascii.c \
                $(LIBFT_DIR)/ft_isdigit.c $(LIBFT_DIR)/ft_isprint.c $(LIBFT_DIR)/ft_itoa.c \
                $(LIBFT_DIR)/ft_memchr.c $(LIBFT_DIR)/ft_memcmp.c $(LIBFT_DIR)/ft_memcpy.c \
                $(LIBFT_DIR)/ft_memmove.c $(LIBFT_DIR)/ft_memset.c $(LIBFT_DIR)/ft_putchar_fd.c \
                $(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_putnbr_fd.c $(LIBFT_DIR)/ft_putstr_fd.c \
                $(LIBFT_DIR)/ft_split.c $(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strdup.c \
                $(LIBFT_DIR)/ft_striteri.c $(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_strlcat.c \
                $(LIBFT_DIR)/ft_strlcpy.c $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_strmapi.c \
                $(LIBFT_DIR)/ft_strncmp.c $(LIBFT_DIR)/ft_strnstr.c $(LIBFT_DIR)/ft_strrchr.c \
                $(LIBFT_DIR)/ft_strtrim.c $(LIBFT_DIR)/ft_substr.c $(LIBFT_DIR)/ft_tolower.c \
                $(LIBFT_DIR)/ft_toupper.c
				
LIBFT_OBJECTS := $(LIBFT_SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f

HEADERS = minishell.h ./gc/gc.h
LIBFT_HEADERS = $(LIBFT_DIR)/libft.h

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline -ltermcap

$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c $(LIBFT_HEADERS)
	$(MAKE) -C $(LIBFT_DIR)
	
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_OBJECTS)
	$(MAKE) -C $(LIBFT_DIR)


clean:
	$(RM) $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re