# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 08:37:09 by  souaguen         #+#    #+#              #
#    Updated: 2023/12/29 15:57:06 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=push_swap
BONUS_NAME=checker
SRC=push_swap.c \
    push_swap_a.c \
    simple_sort.c \
    push_swap_a_two.c \
    push_swap_b.c \
    ft_quick_sort.c \
    push_swap_utils.c \
    push_swap_a_utils.c \
    push_swap_prog.c \
    main.c
SRC_BONUS=checker_utils.c \
	  push_swap_prog.c \
	  push_swap_utils.c \
	  checker.c
OBJ=$(SRC:.c=.o)
OBJ_BONUS=$(SRC_BONUS:.c=.o)
CFLAGS=-Wall -Werror -Wextra -c -g
LIBFT=libft.a
LIBFT_DIR=./libft

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR) all bonus
	$(CC) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -l:$(LIBFT)

all: $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

bonus: $(OBJ_BONUS)
	make -C $(LIBFT_DIR) all bonus
	$(CC) $(OBJ_BONUS) -o $(BONUS_NAME) -L$(LIBFT_DIR) -l:$(LIBFT)

re: fclean all

.PHONY: all clean fclean re $(NAME)
