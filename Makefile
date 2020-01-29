SRCS = ./SRCS/main.c ./SRCS/ft_signal.c ./SRCS/ft_mini_init.c ./SRCS/ft_mini_tools.c ./SRCS/ft_mini_tools2.c ./SRCS/exp_tild_handles.c ./SRCS/ft_mini_b_checks.c ./SRCS/ft_mini_b_checks2.c ./SRCS/ft_exec.c ./SRCS/ft_mini_print.c 

NAME = minishell

FLAGS = -Wall -Werror -Wextra

LIBFT = libft

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@gcc $(SRCS) -L $(LIBFT) -lft -o $(NAME)

clean:
	@rm -rf $(NAME)
	@make clean -C $(LIBFT)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -rf *.dSYM

re: fclean all

debug:
	@gcc $(SRCS) -L $(LIBFT) -lft -o $(NAME) -g -fsanitize=address
