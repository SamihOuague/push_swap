/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 03:58:21 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/27 23:33:35 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"

typedef struct s_args
{
	t_list	*tmp[2];
	int		pivot[2];
	int		n_mov;
	int		count_n;
}	t_args;

t_list	*push_stack_b(t_list **lst_a, t_list *sorted, t_list **op, int size);
t_list	*push_stack_a(t_list **lst_b, t_list *sorted, t_list **op, int size);
t_list	*reverse_list(t_list *lst);
void	undo_reverse(t_list **lst_a, t_list **lst_b, t_list **op, t_args args);
void	read_list(t_list *lst);
int		reset_pivot(t_list *lst_b, t_args *args);
int		*init_tab(char **tab, int size);
int		get_first_number_left(t_list *lst, int pivot);
int		get_last_number_left(t_list *lst, int pivot);
int		ft_max(int a, int b);
int		ft_abs(int a);
#endif
