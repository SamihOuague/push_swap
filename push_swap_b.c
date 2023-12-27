/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:38:21 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/27 06:42:34 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_utils.h"
#include "push_swap_prog.h"
#include <stdio.h>

static void	tmp_init(t_list **tmp, t_list **tmpp, t_list **sorted, int size)
{
	int	i;

	i = -1;
	while (sorted != NULL && (++i) < size)
	{
		if (i < (size / 2))
			ft_lstadd_front(tmp, ft_pop(sorted));
		else
			ft_lstadd_front(tmpp, ft_pop(sorted));
	}
}

void	check_n_pivot(t_list **la, t_list **lb, t_list **op, int p[2])
{
	if (*(int *)(**la).content <= p[0])
	{
		ft_lstadd_front(lb, ft_pop(la));
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
	}
	else if (*(int *)(**la).content <= p[1])
	{
		ft_lstadd_front(lb, ft_pop(la));
		ft_rotate(lb);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rb")));
	}
	else
	{
		ft_rotate(la);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
	}
}

t_list	*push_stack_b(t_list **lst_a, t_list *sorted, t_list **op, int size)
{
	t_list	*tmp[2];
	t_list	*lst_b;
	int		pivot[2];

	ft_bzero(tmp, sizeof(t_list *) * 2);
	lst_b = NULL;
	while (*lst_a != NULL)
	{
		if (tmp[0] == NULL && tmp[1] == NULL)
		{
			tmp_init(&tmp[0], &tmp[1], &sorted, size);
			pivot[0] = *(int *)(*tmp[0]).content;
			if (tmp[1] != NULL)
				pivot[1] = *(int *)(*tmp[1]).content;
		}
		else
		{
			if (*(int *)(**lst_a).content <= pivot[0])
				ft_pop(&tmp[0]);
			else if (*(int *)(**lst_a).content <= pivot[1])
				ft_pop(&tmp[1]);
			check_n_pivot(lst_a, &lst_b, op, pivot);
		}
	}
	return (lst_b);
}
