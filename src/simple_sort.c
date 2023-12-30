/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:28:26 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/30 12:22:37 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_prog.h"
#include "push_swap_utils.h"

int	check_number(t_list *lst)
{
	if (*(int *)(*lst).content > *(int *)(*(*lst).next).content)
		return (0);
	return (1);
}

int	get_min(t_list *lst)
{
	t_list	*cursor;
	int		min;

	cursor = lst;
	min = *(int *)(*lst).content;
	while (cursor != NULL)
	{
		if (*(int *)(*cursor).content < min)
			min = *(int *)(*cursor).content;
		cursor = (*cursor).next;
	}
	return (min);
}

void	three_sort(t_list **la, t_list **op)
{
	if (ft_lstsize(*la) < 2)
		return ;
	if (*(int *)(*ft_lstlast(*la)).content == get_min(*la))
	{
		if (!check_number(*la) && ft_lstsize(*la) >= 3)
			ft_lstadd_front(op, ft_lstnew(ft_strdup("sa")));
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
	}
	else if (ft_lstsize(*la) >= 3)
	{
		if (!check_number((**la).next)
			&& *(int *)(**la).content == get_min(*la))
		{
			ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
			ft_lstadd_front(op, ft_lstnew(ft_strdup("sa")));
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
		}
		else if (*(int *)(**la).content != get_min(*la))
		{
			if (*(int *)(**la).content > *(int *)(*ft_lstlast(*la)).content)
				ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
			else
				ft_lstadd_front(op, ft_lstnew(ft_strdup("sa")));
		}
	}
}

void	simple_sort_push_b(t_list **lst_a, t_list **lst_b, t_list **op)
{
	while (ft_lstsize(*lst_a) > 3)
	{
		if ((*(int *)(**lst_a).content == get_min(*lst_a)))
		{
			ft_push(lst_a, lst_b);
			ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
		}
		else
		{
			if (get_first_number_left(*lst_a, get_min(*lst_a)) > 0)
			{
				ft_rotate(lst_a);
				ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
			}
			else
			{
				ft_reverse_rotate(lst_a);
				ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
			}
		}
	}
}

void	simple_sort(t_list **lst_a, t_list **op)
{
	t_list	*lst_b;

	lst_b = NULL;
	if (ft_lstsize(*lst_a) > 3
		&& *(int *)(*ft_lstlast(*lst_a)).content == get_min(*lst_a))
	{
		ft_reverse_rotate(lst_a);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
	}
	simple_sort_push_b(lst_a, &lst_b, op);
	three_sort(lst_a, op);
	while (lst_b != NULL)
	{
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
		ft_push(&lst_b, lst_a);
	}
}
