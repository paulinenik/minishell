SRCS	= 	srcs/main.c \
			srcs/redirect.c \
			srcs/exec_cmd/exec_cmd.c \
			srcs/exec_cmd/make_fork.c \
			srcs/builtins/get_basic_commands.c \
			srcs/builtins/get_unset.c \
			srcs/builtins/print_exp.c \
			srcs/parse/parse.c \
			srcs/parse/parse_tokens.c \
			srcs/parse/parse_quotes.c \
			srcs/parse/parse_dollar.c \
			srcs/utils/string_methods.c \
			srcs/utils/clear.c \
			srcs/utils/data_methods.c \
			srcs/utils/array_methods.c \
			srcs/utils/utils.c \
			srcs/utils/utils_2.c \
			srcs/utils/utils_3.c \
			srcs/termc/term_caps.c \
			srcs/termc/select_cap.c \
			srcs/termc/create_history.c \
			srcs/termc/signal.c \

LIBFT	= libft/libft.a

TCAP_FLAGS	= -ltermcap

HDRS	= libft

NAME	= minishell

CC		= gcc

RM		= rm -f

CFLAGS = 

$(NAME):	$(LIBFT) $(HDRS) $(SRCS) mshell.h
			@cp $(LIBFT) .
			$(CC) $(CFLAGS) $(SRCS) $(TCAP_FLAGS) -I./libft -I. libft.a -o $(NAME)
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
			echo > bash.txt
			@echo "\033[36mDone!\n\033[0m"

re:			fclean all

norm:
			norminette

.PHONY:		all clean fclean re norm
