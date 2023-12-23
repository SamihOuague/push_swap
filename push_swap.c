/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:12:33 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/23 05:54:35 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap_utils.h"
#include "push_swap_prog.h"
#include <stdio.h>

void	ft_stack_pivot_right(t_list **lst, t_list **lst_b, t_list **op, int pivot)
{
	if (lst == NULL || *lst == NULL)
		return ;
	else if (*(int *)(**lst).content < pivot)
	{
		ft_push(lst, lst_b);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
		ft_stack_pivot_right(lst, lst_b, op, pivot);
	}
	else if (*(int *)(**lst).content > pivot)
	{
		ft_rotate(lst);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
		ft_stack_pivot_right(lst, lst_b, op, pivot);
	}
	else
	{
		ft_push(lst, lst_b);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
	}
}

void	ft_stack_pivot_left(t_list **lst, t_list **lst_b, t_list **op, int pivot)
{
	if (lst == NULL || *lst == NULL)
		return ;
	if (*(int *)(**lst).content < pivot)
	{
		ft_push(lst, lst_b);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
		ft_stack_pivot_left(lst, lst_b, op, pivot);
	}
	else if (*(int *)(**lst).content > pivot)
	{
		ft_rotate(lst);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
		ft_stack_pivot_left(lst, lst_b, op, pivot);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
	}
	else
	{
		ft_push(lst, lst_b);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
	}
}

void    get_infos(t_list *lst, t_list *lst_b)
{
	printf("# Stack A => ");
	print_list(lst);
	printf("\n");
	printf("# Stack B => ");
	print_list(lst_b);
	printf("\n\n");
}

t_list	*quick_sort(t_list *unsorted)
{
	t_arraysize	*tab;
	t_arraysize	*tab1;
	t_list		*lst;
	t_list		*lst_b;
	t_list		*tmp;
	t_list		*tmpp;
	t_list		*op;
	int			pivot;
	int			i;


	lst = unsorted;
	lst_b = NULL;
	tmp = NULL;
	tmpp = NULL;
	tab = NULL;
	op = NULL;
	while (lst != NULL)
	{
		pivot = *(int *)(*ft_lstlast(lst)).content;
		ft_stack_pivot_right(&lst, &tmp, &op, pivot);
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
		ft_lstadd_front(&op, ft_lstnew(ft_strdup("pa")));
		if ((*tab).size > 1)
		{
			(*tab).size = (*tab).size - 1;
			(*tab).tab = (*tab).tab + 1;
			tmpp = tab_to_list(tab);
			tmp = NULL;
			i = 0;
			while ((i++) < (*tab).size)
				ft_lstadd_front(&op, ft_lstnew(ft_strdup("pa")));
			while (tmpp != NULL)
			{
				pivot = *(int *)(*ft_lstlast(tmpp)).content;
				ft_stack_pivot_left(&tmpp, &tmp, &op, pivot);
				tab = get_tab(&tmp);
				ft_lstadd_front(&lst_b, ft_lstnew(tab));
			}
		}
	}
	return (op);
}

void    read_list(t_list *lst)
{
        if (lst == NULL)
                return ;
        ft_putendl_fd((char *)(*lst).content, 1);
        read_list((*lst).next);
}

t_list	*clean_pb_prog(t_list *lst)
{
	t_list	*new;
	t_list	*cursor;

	new = NULL;
	cursor = lst;
	while (cursor != NULL)
	{
		if (new != NULL 
		&& ft_strncmp((char *)(*new).content, "pa", 2) == 0 
		&& ft_strncmp((char *)(*cursor).content, "pb", 2) == 0)
		{
			ft_pop(&new);
			ft_pop(&cursor);
		}
		else
			ft_lstadd_front(&new, ft_pop(&cursor));
	}
	return (new);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*lst_b;
	t_list	*prog;
	int	i;
	char	str[4];

	if (argc == 1)
		return (1);
	i = 0;
	lst = NULL;
	lst_b = NULL;
	init_list(&lst, &argv[1], argc - 1);
	prog = quick_sort(lst);
	read_list(clean_pb_prog(prog));
	
	while (1)
        {
                get_infos(lst, lst_b);
                scanf("%3s", str);
                if (ft_strncmp(str, "sa", 3) == 0 && ft_lstsize(lst) >= 2)
                        ft_swap((*lst).content, (*(*lst).next).content);
                else if (ft_strncmp(str, "sb", 3) == 0 && ft_lstsize(lst_b) >= 2)
                        ft_swap((*lst_b).content, (*(*lst_b).next).content);
                else if (ft_strncmp(str, "ss", 3) == 0)
                {
                        if (ft_lstsize(lst) >= 2)
                                ft_swap((*lst).content, (*(*lst).next).content);
                        if (ft_lstsize(lst_b) >= 2)
                                ft_swap((*lst_b).content, (*(*lst_b).next).content);
                }
                else if (ft_strncmp(str, "pb", 3) == 0 && ft_lstsize(lst) >= 1)
                        ft_push(&lst, &lst_b);
                else if (ft_strncmp(str, "pa", 3) == 0 && ft_lstsize(lst_b) >= 1)
                        ft_push(&lst_b, &lst);
                else if (ft_strncmp(str, "ra", 3) == 0)
                        ft_rotate(&lst);
                else if (ft_strncmp(str, "rb", 3) == 0)
                        ft_rotate(&lst_b);
                else if (ft_strncmp(str, "rr", 3) == 0)
                {
                        ft_rotate(&lst);
                        ft_rotate(&lst_b);
                }
                else if (ft_strncmp(str, "rra", 3) == 0)
                        ft_reverse_rotate(&lst);
                else if (ft_strncmp(str, "rrb", 3) == 0)
                        ft_reverse_rotate(&lst_b);
                else if (ft_strncmp(str, "rrr", 3) == 0)
                {
                        ft_reverse_rotate(&lst);
                        ft_reverse_rotate(&lst_b);
                }
                else if (ft_strncmp(str, "qui", 3) == 0)
                        break;
                i++;
        }
	return (0);
}
