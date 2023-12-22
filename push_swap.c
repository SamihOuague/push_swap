/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:12:33 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/22 04:07:38 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap_utils.h"
#include "push_swap_prog.h"

void	ft_stack_pivot_right(t_list **lst, t_list **lst_b, int pivot)
{
	if (lst == NULL || *lst == NULL)
		return ;
	if (*(int *)(**lst).content < pivot)
	{
		ft_push(lst, lst_b);
		ft_putstr_fd("pb\n", 1);
		ft_stack_pivot_right(lst, lst_b, pivot);
	}
	else if (*(int *)(**lst).content > pivot)
	{
		ft_rotate(lst);
		ft_putstr_fd("ra\n", 1);
		ft_stack_pivot_right(lst, lst_b, pivot);
	}
	else
	{
		ft_push(lst, lst_b);
		ft_putstr_fd("pb\n", 1);
	}
}

void	ft_stack_pivot_left(t_list **lst, t_list **lst_b, int pivot)
{
	if (lst == NULL || *lst == NULL)
		return ;
	if (*(int *)(**lst).content < pivot)
	{
		ft_push(lst, lst_b);
		ft_putstr_fd("pb\n", 1);
		ft_stack_pivot_left(lst, lst_b, pivot);
	}
	else if (*(int *)(**lst).content > pivot)
	{
		ft_rotate(lst);
		ft_putstr_fd("ra\n", 1);
		ft_stack_pivot_left(lst, lst_b, pivot);
		ft_putstr_fd("rra\n", 1);
	}
	else
	{
		ft_push(lst, lst_b);
		ft_putstr_fd("pb\n", 1);
	}
}

void	quick_sort(t_list *unsorted)
{
	t_arraysize	*tab;
	t_arraysize	*tab1;
	t_list		*lst;
	t_list		*lst_b;
	t_list		*tmp;
	t_list		*tmpp;
	int			pivot;
	int			i;

	lst = unsorted;
	lst_b = NULL;
	tmp = NULL;
	tmpp = NULL;
	tab = NULL;
	while (lst != NULL)
	{
		pivot = *(int *)(*ft_lstlast(lst)).content;
		ft_stack_pivot_right(&lst, &tmp, pivot);
		tab = get_tab(&tmp);
		ft_lstadd_front(&lst_b, ft_lstnew(tab));
	}
	while (lst_b != NULL)
	{
		tmp = ft_pop(&lst_b);
		tab = (t_arraysize *)(*tmp).content;
		tab1 = malloc(sizeof(t_arraysize *));
		(*tab1).size = 1;
		(*tab1).tab = malloc(sizeof(int));
		*(int *)(*tab1).tab = (*tab).tab[0];
		ft_lstadd_front(&lst, ft_lstnew(tab1));
		ft_putstr_fd("pa\n", 1);
		if ((*tab).size > 1)
		{
			(*tab).size = (*tab).size - 1;
			(*tab).tab = (*tab).tab + 1;
			tmpp = tab_to_list(tab);
			tmp = NULL;
			i = 0;
			while ((i++) < (*tab).size)
				ft_putstr_fd("pa\n", 1);
			while (tmpp != NULL)
			{
				pivot = *(int *)(*ft_lstlast(tmpp)).content;
				ft_stack_pivot_left(&tmpp, &tmp, pivot);
				tab = get_tab(&tmp);
				ft_lstadd_front(&lst_b, ft_lstnew(tab));
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_list	*lst;

	lst = NULL;
	if (argc == 1)
		return (1);
	lst = NULL;
	init_list(&lst, &argv[1], argc - 1);
	quick_sort(lst);
	return (0);
}
