/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:38:21 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/25 10:59:22 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap_utils.h"
#include "push_swap_prog.h"
#include <stdio.h>

int     ft_get_left_size(int *tab, int pivot, int size)
{
        int     i;
        int     c;

        c = 0;
        i = 0;
        while (i < size)
        {
                if (tab[i] < pivot)
                        c++;
                i++;
        }
        return (c);
}

int     ft_get_right_size(int *tab, int pivot, int size)
{
        int     i;
        int     c;

        c = 0;
        i = 0;
        while (i < size)
        {
                if (tab[i] > pivot)
                        c++;
                i++;
        }
        return (c);
}

void    ft_quick_sort(int *tab, int size, t_list **list)
{
        int     *tab_1;
        int     *tab_2;
        int     *pivot;
        int     i;
        int     j;
        int     left;
        int     right;
        int     limit;

        if (size == 0)
                return ;
        pivot = malloc(sizeof(int));
        *pivot = tab[size - 1];
        left = ft_get_left_size(tab, *pivot, size);
        right = ft_get_right_size(tab, *pivot, size);
        if (size <= 1)
        {
                ft_lstadd_front(list, ft_lstnew(pivot));
                return ;
        }
        tab_1 = malloc(sizeof(int) * left);
        tab_2 = malloc(sizeof(int) * right);
        if (tab_1 == NULL || tab_2 == NULL)
        {
                free(tab_1);
                free(tab_2);
                return ;
        }
        i = 0;
        j = 0;
        limit = left;
        while (j < limit)
        {
                if (tab[i] < *pivot)
                {
                        tab_1[j] = tab[i];
                        j++;
                }
                i++;
        }
        i = 0;
        j = 0;
        limit = right;
        while (j < limit)
        {
                if (tab[i] > *pivot)
                {
                        tab_2[j] = tab[i];
                        j++;
                }
                i++;
        }
        if (left)
                ft_quick_sort(tab_1, left, list);
        ft_lstadd_front(list, ft_lstnew(pivot));
        if (right)
                ft_quick_sort(tab_2, right, list);
        free(tab_1);
        free(tab_2);
}

void    read_list(t_list *lst)
{       
        if (lst == NULL)
                return ;
        read_list((*lst).next);
        ft_putendl_fd((char *)(*lst).content, 1);
}

t_list	*reverse_list(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst != NULL)
		ft_lstadd_front(&tmp, ft_pop(&lst));
	return (tmp);
}

void    print_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	print_list((*lst).next);
	printf("%d\n", *(int *)(*lst).content);
}

int    *init_tab(char **tab, int size)
{
        int     *tmp;
	int	i;

	i = -1;
        tmp = malloc(sizeof(int) * size);
        while ((++i) < size)
		tmp[i] = ft_atoi(tab[i]);
	return (tmp);
}

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int     ft_abs(int n)
{                       
        if (n < 0)
                return (n * -1);
        return (n);
} 

int     get_first_number_left(t_list *lst, int pivot)
{
        t_list  *cursor;
        int             first;
        int             size;

        cursor = lst;
        first = 0;
        while (cursor != NULL)
        {       
                if (*(int *)(*cursor).content <= pivot)
                        break ;
                first++; 
                cursor = (*cursor).next;
        }
        size = ft_lstsize(lst);
        if (first > (size / 2))
                return (first - size);
        return (first);
}

int     get_last_number_left(t_list *lst, int pivot)
{
        t_list  *cursor;
        int     last;
        int     size;
        int     i;

        i = 0;
        last = i;
        cursor = lst;
        while (cursor != NULL)
        {       
                if (*(int *)(*cursor).content <= pivot)
                        last = i;
                cursor = (*cursor).next;
                i++;
        }
        size = ft_lstsize(lst);
        if (last > (size / 2))
                return (last - size);
        return (last);
}

int     get_first_number(t_list *lst, int pivot)
{
        t_list  *cursor;
        int             first;
        int             size;

        cursor = lst;
        first = 0;
        while (cursor != NULL)
        {
                if (*(int *)(*cursor).content >= pivot)
                        break ;
                first++;
                cursor = (*cursor).next;
        }
        size = ft_lstsize(lst);
        if (first > (size / 2))
                return (first - size);
        return (first);
}

int     get_last_number(t_list *lst, int pivot)
{
        t_list  *cursor;
        int     last;
        int     size;
        int     i;

        i = 0;
        last = i;
        cursor = lst;
        while (cursor != NULL)
        {
                if (*(int *)(*cursor).content >= pivot)
                        last = i;
                cursor = (*cursor).next;
                i++;
        }
        size = ft_lstsize(lst);
        if (last > (size / 2))
                return (last - size);
        return (last);
}

void	push_number_list(t_list **lst_a, t_list **lst_b, t_list **n, t_list **op)
{
	int	n_mov;

	n_mov = get_first_number(*lst_b, *(int *)(**n).content);
	if (ft_abs(get_first_number(*lst_b, *(int *)(**n).content)) > ft_abs(get_last_number(*lst_b, *(int *)(**n).content)))
		n_mov = get_last_number(*lst_b, *(int *)(**n).content);
	if (lst_a == NULL || lst_b == NULL || *lst_b == NULL)
		return ;
	if (*(int *)(**lst_b).content == *(int *)(**n).content)
	{
		ft_push(lst_b, lst_a);
		ft_pop(n);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
	}
	else
	{
		if (n_mov >= 0)
		{
			ft_rotate(lst_b);
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rb")));
		}
		else
		{
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rrb")));
			ft_reverse_rotate(lst_b);
		}
		push_number_list(lst_a, lst_b, n, op);
	}

}

void	push_stack_a(t_list **lst_a, t_list **lst_b, t_list *sorted, t_list **op)
{
	while (*lst_b != NULL && sorted != NULL)
		push_number_list(lst_a, lst_b, &sorted, op);
}


void	push_stack_b(t_list **lst_a, t_list **lst_b, t_list *sorted, t_list **op, int size)
{
	t_list	*tmp;
	int		i;
	int		pivot;
	int		n_mov;

	if (lst_a == NULL || lst_b == NULL)
		return ;
	
	tmp = NULL;
	pivot = 0;
	sorted = reverse_list(sorted);
	while (*lst_a != NULL)
	{
		if (tmp == NULL)
		{
			i = -1;
		        while (sorted != NULL && (++i) < size)
        		        ft_lstadd_front(&tmp, ft_pop(&sorted));
			pivot = *(int *)(*tmp).content;
		}
		else if (*(int *)(**lst_a).content <= pivot)
		{
			ft_lstadd_front(lst_b, ft_pop(lst_a));
			ft_pop(&tmp);
			ft_lstadd_front(op, ft_lstnew(ft_strdup("pb")));
		}
		else
		{
			n_mov = get_first_number_left(*lst_a, pivot);
                	if (ft_abs(get_first_number_left(*lst_a, pivot)) > ft_abs(get_last_number_left(*lst_a, pivot)))
                        	n_mov = get_last_number_left(*lst_a, pivot);
			if (n_mov >= 0)
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

t_list  *clean_prog(t_list *lst, char *s1, char *s2)
{
        t_list  *new;
        t_list  *cursor;

        new = NULL;
        cursor = lst;
        while (cursor != NULL)
        {
                if (new != NULL 
                && ft_strncmp((char *)(*new).content, s1, 3) == 0 
                && ft_strncmp((char *)(*cursor).content, s2, 3) == 0)
                {
                        ft_pop(&new);
                        ft_pop(&cursor);
                }
                else
                        ft_lstadd_front(&new, ft_pop(&cursor));
        }
        cursor = NULL;
        while (new != NULL)
                ft_lstadd_front(&cursor, ft_pop(&new));
        return (cursor);
}

int     main(int argc, char **argv)
{
        t_list  *lst;
	t_list	*lst_a;
	t_list	*lst_b;
	t_list	*prog;

        if (argc < 2)
		return (1);
	
	lst = NULL;
	lst_a = NULL;	
	lst_b = NULL;
	prog = NULL;

	init_list(&lst_a, &argv[1], argc - 1);
		
	ft_quick_sort(init_tab(argv + 1, argc - 1), argc - 1, &lst);
	push_stack_b(&lst_a, &lst_b, lst, &prog, ft_max(4, ft_lstsize(lst_a) / 5));
	lst = NULL;
	ft_quick_sort(init_tab(argv + 1, argc - 1), argc - 1, &lst);
	push_stack_a(&lst_a, &lst_b, lst, &prog);
	read_list(prog);
	return (0);
}
