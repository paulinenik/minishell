SRCS	= 	main.c \
			parse.c \
			get_pwd.c \
			string_methods.c \
			clear.c \
			data_methods.c \
			array_methods.c \
			redirect.c \
			exec_cmd.c \
			print_exp.c \
			parse_quotes.c \
			parse_dollar.c \
			get_unset.c \
			utils.c \
			utils_2.c \
			make_fork.c \
			parse_tokens.c \

LIBFT	= libft/libft.a

TCAP_FLAGS	= -ltermcap

HDRS	= libft

NAME	= minishell

CC		= gcc

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME):	$(LIBFT) $(HDRS) $(SRCS) mshell.h
			@cp $(LIBFT) .
			$(CC) $(CFLAGS) $(SRCS) $(TCAP_FLAGS) -I./libft libft.a -o $(NAME)
			@echo "\033[36mminishell is compiled successfully\n\033[0m"

$(LIBFT):	
			@$(MAKE) -C ./libft
			@echo "\033[36mlibft is compiled successfully\n\033[0m"
		
all:		$(NAME)

clean:	
			$(RM) $(NAME)

leaks:		
			$(CC) $(SRCS) -g $(TCAP_FLAGS) -I./libft libft.a -o $(NAME) -fsanitize=address -fno-omit-frame-pointer -ggdb

fclean:		clean
			make fclean -C libft/
			$(RM) $(NAME) libft.a
			@echo "\033[36mDone!\n\033[0m"

re:			fclean all

norm:
			norminette

.PHONY:		all clean fclean re norm
