/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:38:21 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/28 03:24:23 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_utils.h"
#include "push_swap_prog.h"
#include <stdio.h>

static void	tmp_init(t_args *args, t_list **sorted, int size)
{
	int	i;

	i = -1;
	while (sorted != NULL && (++i) < (size / 2))
	{
		if (i < (size / 4))
			ft_lstadd_front(&(*args).tmp[0], ft_pop(sorted));
		else
			ft_lstadd_front(&(*args).tmp[1], ft_pop(sorted));
	}
}

static void	push_n_rotate(t_list **la, t_list **lb, t_list **op, t_args *args)
{
	ft_push(lb, la);
	ft_rotate(la);
	clear_poped(ft_pop(&(*args).tmp[1]));
	ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
	(*args).n_mov = reset_pivot(*lb, args);
	if ((*args).n_mov > 0)
	{
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rr")));
		ft_rotate(lb);
	}
	else
		ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
}

static void	rotate_n_b(t_list **lst, t_list **op, t_args args)
{
	if (args.n_mov >= 0)
	{
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rb")));
		ft_rotate(lst);
	}
	else
	{
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rrb")));
		ft_reverse_rotate(lst);
	}
}

static void	cond_func(t_list **la, t_list **lb, t_list **op, t_args *args)
{
	if ((*args).tmp[0] == NULL)
	{
		(*args).tmp[0] = reverse_list((*args).tmp[1]);
		(*args).tmp[1] = NULL;
	}
	else if (*(int *)(**lb).content == (*args).pivot[0])
	{
		ft_push(lb, la);
		clear_poped(ft_pop(&(*args).tmp[0]));
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
	}
	else if (*(int *)(**lb).content == (*args).pivot[1])
	{
		push_n_rotate(la, lb, op, args);
		(*args).count_n++;
	}
	else
		rotate_n_b(lb, op, *args);
}

t_list	*push_stack_a(t_list **lst_b, t_list *sorted, t_list **op, int size)
{
	t_args	args;
	t_list	*lst_a;

	args.tmp[0] = NULL;
	args.tmp[1] = NULL;
	args.count_n = 0;
	lst_a = NULL;
	while (*lst_b != NULL)
	{
		if (args.tmp[0] == NULL && args.tmp[1] == NULL)
		{
			tmp_init(&args, &sorted, size);
			args.n_mov = reset_pivot(*lst_b, &args);
			undo_reverse(&lst_a, lst_b, op, args);
			args.count_n = 0;
			args.tmp[0] = reverse_list(args.tmp[0]);
		}
		else
			cond_func(&lst_a, lst_b, op, &args);
		if (*lst_b != NULL)
			args.n_mov = reset_pivot(*lst_b, &args);
	}
	undo_reverse(&lst_a, lst_b, op, args);
	return (lst_a);
}
