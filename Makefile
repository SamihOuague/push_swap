# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 08:37:09 by  souaguen         #+#    #+#              #
#    Updated: 2023/12/30 15:34:57 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=push_swap
BONUS_NAME=checker
SRC=src/push_swap.c \
    src/push_swap_a.c \
    src/simple_sort.c \
    src/push_swap_a_two.c \
    src/push_swap_b.c \
    src/ft_quick_sort.c \
    src/push_swap_utils.c \
    src/push_swap_a_utils.c \
    src/push_swap_prog.c \
    src/check_parameters.c
SRC_BONUS=src/checker_utils.c \
	  src/checker.c
SRC_DIR=src
OBJ=$(SRC:.c=.o)
OBJ_BONUS=$(SRC_BONUS:.c=.o)
CFLAGS=-Wall -Werror -Wextra -I./includes -I./
LIBFT=libft.a
LIBFT_DIR=./libft

$(NAME): $(OBJ) main.o
	make -C $(LIBFT_DIR) all bonus
	$(CC) $(OBJ) main.o -o $(NAME) -L$(LIBFT_DIR) -l:$(LIBFT)

all: $(NAME)

clean: 
	rm -f $(OBJ) main.o
	rm -f $(OBJ_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean

bonus: $(OBJ) $(OBJ_BONUS)
	make -C $(LIBFT_DIR) all bonus
	$(CC) $(OBJ) $(OBJ_BONUS) -o $(BONUS_NAME) -L$(LIBFT_DIR) -l:$(LIBFT)

re: fclean all

.PHONY: all clean fclean re $(NAME)
