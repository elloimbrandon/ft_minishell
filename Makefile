SRCS = ./SRCS/main.c ./SRCS/ft_signal.c ./SRCS/ft_mini_init.c ./SRCS/ft_mini_tools.c ./SRCS/ft_mini_tools_2.c ./SRCS/exp_tild_handles.c ./SRCS/ft_builtin_checks.c ./SRCS/ft_exp_tilde_checks.c ./SRCS/ft_exec.c ./SRCS/ft_mini_print.c ./SRCS/set_env.c ./SRCS/unset_env.c ./SRCS/ft_mini_parse.c ./SRCS/ft_cd.c

NAME = minishell

FLAGS = -Wall -Werror -Wextra

LIBFT = libft


all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@echo "\x1B[32mmaking minishell!"
	@make msh

msh:
	@gcc $(SRCS) $(FLAGS) -L $(LIBFT) -lft -o $(NAME)

clean:
	@rm -rf $(NAME)
	@make clean -C $(LIBFT)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -rf *.dSYM

re: fclean all

debug:
	@gcc $(SRCS) -L $(LIBFT) -lft -o $(NAME) -g -fsanitize=address
