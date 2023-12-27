# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 08:37:09 by  souaguen         #+#    #+#              #
#    Updated: 2023/12/27 03:22:55 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=push_swap
SRC=push_swap_v3.c \
    quick_sort.c \
    push_swap_utils.c \
    push_swap_prog.c
OBJ=$(SRC:.c=.o)
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

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)
