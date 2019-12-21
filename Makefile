SRCS = ./SRCS/main.c

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

re: fclean all

debug:
	@gcc $(SRCS) -L $(LIBFT) -lft -o $(NAME) -g -fsanitize=address