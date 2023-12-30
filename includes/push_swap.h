/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 03:58:21 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/29 19:03:20 by souaguen         ###   ########.fr       */
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
t_list	*find_and_replace(t_list *lst, t_list *pattern, char **cmd);
t_list	*reverse_list(t_list *lst);
t_list	*clean_prog(t_list *lst, char *s1, char *s2);
t_list	*clean_pattern(t_list *prog, char *pattern, char *replace);
void	undo_reverse(t_list **lst_a, t_list **lst_b, t_list **op, t_args args);
void	read_list(t_list *lst);
void	free_tab(char **tab);
void	init_prog(t_list **lst_a, t_list **prg, char **tab, int siz);
void	simple_sort(t_list **lst_a, t_list **op);
int		reset_pivot(t_list *lst_b, t_args *args);
int		*init_tab(char **tab, int size);
int		get_first_number_left(t_list *lst, int pivot);
int		get_last_number_left(t_list *lst, int pivot);
int		ft_max(int a, int b);
int		ft_abs(int a);
int		check_number(t_list *lst);
#endif
