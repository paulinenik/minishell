SRCS	= 	main.c \
			parse.c \
			get_pwd.c \
			delete_char.c \
			clear.c \
			data_func.c \
			redirect.c \

LIBFT	= libft/libft.a

TCAP_FLAGS	= -ltermcap

HDRS	= libft

NAME	= minishell

CC		= gcc

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME):	$(LIBFT) $(HDRS) $(SRCS) mshell.h
			@cp $(LIBFT) .
			$(CC) $(SRCS) -g $(TCAP_FLAGS) -I./libft libft.a -o $(NAME)
			@echo "\033[36mminishell is compiled successfully\n\033[0m"

$(LIBFT):	
			@$(MAKE) -C ./libft
			@echo "\033[36mlibft is compiled successfully\n\033[0m"
		
all:		$(NAME)

f:			
			$(CC) $(CFLAGS) $(SRCS) -g $(TCAP_FLAGS) -I./libft libft.a -o $(NAME)

clean:	
			$(RM) $(NAME)

fclean:		clean
			make fclean -C libft/
			$(RM) $(NAME) libft.a
			@echo "\033[36mDone!\n\033[0m"

re:			fclean all

norm:
			norminette

.PHONY:		all clean fclean re norm
