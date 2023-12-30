/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_a_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:41:04 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/27 23:22:48 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "push_swap_prog.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	reset_pivot(t_list *lst_b, t_args *args)
{
	int	n_mov;

	n_mov = 0;
	if ((*args).tmp[0] != NULL)
	{
		(*args).pivot[0] = *(int *)(*(*args).tmp[0]).content;
		(*args).pivot[1] = (*args).pivot[0];
	}
	if ((*args).tmp[1] != NULL)
		(*args).pivot[1] = *(int *)(*(*args).tmp[1]).content;
	n_mov = get_first_number_left(lst_b, (*args).pivot[0]);
	if (ft_abs(n_mov) > ft_abs(get_last_number_left(lst_b, (*args).pivot[0])))
		n_mov = get_last_number_left(lst_b, (*args).pivot[0]);
	return (n_mov);
}

void	undo_reverse(t_list **lst_a, t_list **lst_b, t_list **op, t_args args)
{
	int	i;

	i = -1;
	while ((++i) < args.count_n)
	{
		if (ft_abs(args.n_mov) > i && args.n_mov < 0)
		{
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rrr")));
			ft_reverse_rotate(lst_b);
		}
		else
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
		ft_reverse_rotate(lst_a);
	}
}
