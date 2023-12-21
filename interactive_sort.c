/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:49:38 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/21 02:58:04 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

typedef struct s_arraysize
{
	int	size;
	int	*tab;
}	t_arraysize;

void	init_list(t_list **lst, char **tab, int size)
{
	int	*tmp;

	tmp = NULL;
	if (size > 1)
		init_list(lst, &tab[1], size - 1);
	tmp = malloc(sizeof(int));
	*tmp = ft_atoi(tab[0]);
	ft_lstadd_front(lst, ft_lstnew(tmp));
}

void	print_list(t_list *lst)
{
	t_list	*cursor;

	cursor = lst;
	while (cursor != NULL)
        {
                printf("%d ", *(int *)(*cursor).content);
                cursor = (*cursor).next;
        }
}

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_set_to_null(void *content)
{
	content = NULL;
}

void	ft_push(t_list **a, t_list **b)
{
	t_list	*tmp;

	tmp = *a;
	if (a == NULL || *a == NULL)
		return ;
	ft_lstadd_front(b, ft_lstnew((*(*a)).content));
	*a = (*(*a)).next;
	ft_lstdelone(tmp, &ft_set_to_null);
}

void	ft_rotate(t_list **lst)
{
	t_list	*tmp;
	
	if (lst == NULL || *lst == NULL || (**lst).next == NULL)
		return ;
	tmp = ft_lstlast(*lst);
	(*tmp).next = *lst;
	*lst = (**lst).next;
	(*(*tmp).next).next = NULL;
}

void	ft_reverse_rotate(t_list **lst)
{
	t_list  *tmp;

        if (lst == NULL || *lst == NULL || (*(*lst)).next == NULL)
                return ;
	tmp = *lst;
	while ((*tmp).next != NULL && (*(*tmp).next).next != NULL)
		tmp = (*tmp).next;
	ft_lstadd_front(lst, ft_lstnew((*(*tmp).next).content));
	ft_lstdelone((*tmp).next, &ft_set_to_null);
	(*tmp).next = NULL;
}

void	ft_stack_pivot_right(t_list **lst, t_list **lst_b, int pivot)
{
	if (lst == NULL || *lst == NULL)
                return ;
	if (*(int *)(**lst).content < pivot)
	{
		ft_push(lst, lst_b);
		printf("pb\n");
		ft_stack_pivot_right(lst, lst_b, pivot);
	}
	else if (*(int *)(**lst).content > pivot)
	{
		ft_rotate(lst);
		printf("ra\n");
		ft_stack_pivot_right(lst, lst_b, pivot);
	}
	else
	{
		ft_push(lst, lst_b);
		printf("pb\n");
	}
}

t_list	*ft_pop(t_list **lst)
{
	t_list	*tmp;

	tmp = NULL;
	if (lst == NULL || *lst == NULL)
		return (NULL);
	tmp = *lst;
	*lst = (**lst).next;
	return (tmp);
}

t_list	*ft_find_next_pivot(t_list *lst, int limit)
{
	t_list	*cursor;
	int		i;

	i = 1;
	cursor = lst;
	while (limit > 0 && cursor != NULL && (*cursor).next != NULL)
	{
		if (i == limit)
			return (cursor);
		i++;
		cursor = (*cursor).next;
	}
	return (NULL);
}

void	get_infos(t_list *lst, t_list *lst_b)
{
	printf("# Stack A => ");
	print_list(lst);
	printf("\n");
	printf("# Stack B => ");
	print_list(lst_b);
	printf("\n\n");
}
/*
void	quick_sort(t_list *unsorted)
{
	t_list	*lst;
	t_list	*lst_b;
	t_list	*left;
	t_list	*right;
	t_list	*tmp;
	int	pivot;

	lst = unsorted;
	right = NULL;
	left = NULL;
	tmp = NULL;
	while (right != NULL || lst != NULL)
	{
		pivot = *(int *)(*ft_lstlast(lst)).content;
		while (lst != NULL)
		{
			if (pivot > *(int *)(*lst).content)
				tmp = (*right).content;	
			else
				tmp = (*left).content;
			ft_push(&lst, &tmp);	
		}
		
		if (left != NULL)
			lst = (*ft_pop(&left)).content;
		else
			lst = (*ft_pop(&right)).content;
		
		printf("%d\n", *(int *)(*lst).content);
	}
}
*/

t_arraysize	*get_tab(t_list **lst)
{
	int			size;
	int			i;
	t_arraysize	*tabsize;
	t_list		*tmp;

	size = ft_lstsize(*lst);
	tabsize = malloc(sizeof(tabsize));
	(*tabsize).size = size;
	(*tabsize).tab = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		tmp = ft_pop(lst);
		(*tabsize).tab[i] = *(int *)(*tmp).content;
		i++;
	}
	return (tabsize);
}

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

t_list	*tab_to_list(t_arraysize *array)
{
	t_list	*lst;
	int	i;

	if (array == NULL)
		return (NULL);
	i = 0;
	lst = NULL;
	while (i < (*array).size)
	{
		ft_lstadd_front(&lst, ft_lstnew(((*array).tab + i)));
		i++;
	}
	return (lst);
}


void    quick_sort(t_list *unsorted)
{
	t_list	*lst;
	t_list	*lst_b;
	t_list	*tmp;
	t_list	*tmpp;
	t_arraysize	*tab;
	t_arraysize	*tab1;
	t_arraysize	*tab2;
	int	pivot;
	int	i;

	lst = unsorted;
	lst_b = NULL;
	tmp = NULL;
	tab = NULL;
	tmpp = NULL;
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
		printf("pa\n");
		if ((*tab).size > 1)
		{

			(*tab).size = (*tab).size - 1;
			(*tab).tab = (*tab).tab + 1;
			tmpp = tab_to_list(tab);
			tmp = NULL;
			while (tmpp != NULL)
        		{
        		        pivot = *(int *)(*ft_lstlast(tmpp)).content;
        		        ft_stack_pivot_right(&tmpp, &tmp, pivot);
        		        tab = get_tab(&tmp);
        		        ft_lstadd_front(&lst_b, ft_lstnew(tab));
			}
		}
	}
	while (lst != NULL)
	{
		tmp = ft_pop(&lst);
		tab = (t_arraysize *)(*tmp).content;
		printf("%d\n", (*tab).tab[0]);
	}
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*lst_b;
	t_list	*lst_tmp;
	t_list	*right;
	t_list	*left;
	t_list	*temp;
	char	str[4];	
	int		tmp;
	int		*tmpp;
	int		i;

	i = 0;	
	if (argc == 1)
		return (1);
	lst = NULL;
	lst_b = NULL;
	lst_tmp = NULL;
	right = NULL;
	left = NULL;
	ft_bzero(str, 4);
	init_list(&lst, &argv[1], argc - 1);
	quick_sort(lst);
	/*while (lst != NULL)
	{
		i = ft_lstsize(lst_b);
		tmp = *(int *)(*ft_lstlast(lst)).content;
		ft_stack_pivot_right(&lst, &lst_b, tmp);
		i = ft_lstsize(lst_b) - i;
		printf("size => %d\n", i);
		tmpp = malloc(sizeof(int));
		*tmpp = i;
		ft_lstadd_front(&right, ft_lstnew(tmpp));
		get_infos(lst, lst_b);
	}
	*/
	/*i = 0;
	*tmpp = *(int *)(*right).content;
	while (right != NULL)
	{
		i = ft_lstsize(lst);
		temp = ft_find_next_pivot(lst_b, *(int *)(*right).content);
		if (temp == NULL)
			temp = ft_lstlast(lst_b);
		ft_stack_pivot_left(&lst, &lst_b, *(int *)(*temp).content);
		get_infos(lst, lst_b);
		i = ft_lstsize(lst) - i;
		if (i == 1)
		{
			temp = ft_pop(&right);
			ft_push(&lst, &lst_b);
			get_infos(lst, lst_b);
			i = 0;
			while (i < *tmpp)
			{
				ft_push(&lst_b, &lst_tmp);
				get_infos(lst, lst_b);
				i++;
			}
			if (right != NULL)
				*tmpp = *(int *)(*right).content;
			else
				break ;
		}
		else
		{
			tmp = *(int *)(*ft_lstlast(lst)).content;
                	ft_stack_pivot_right(&lst, &lst_b, tmp);
			*(int *)(*right).content = *(int *)(*right).content - 1;
			get_infos(lst, lst_b);
		}
	}
	while (lst_tmp != NULL)
		ft_push(&lst_tmp, &lst_b);
	while (lst_b != NULL)
		ft_push(&lst_b, &lst);
	get_infos(lst, lst_b);
	//tmp = *(int *)(*ft_lstlast(lst)).content;
        //printf("%d\n", *(int *)(*ft_find_next_pivot(lst, tmp)).content);
        //ft_stack_pivot_right(&lst, &lst_b, tmp);
        //get_infos(lst, lst_b);
	i = 0;
	while (right != NULL)
	{
		
		printf("%d\n", *(int *)(*right).content);
		get_infos(lst, lst_b);
		ft_stack_pivot_left(&lst, &lst_b, *(int *)(*right).content);
		temp = ft_pop(right);
		if (right != NULL && )
	//	ft_lstadd_front(&pivots, ft_lstnew((*lst_b).content));
	
	//	ft_stack_pivot_left(&lst, &lst_b, *(int *)(*pivots).content);
        //	ft_push(&lst_b, &lst);
	//
	}*/
	/*lst = NULL;
	init_list(&lst, &argv[1], argc - 1);
	lst_b = NULL;
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
	}*/
	//printf("%d LENGTH\n", i);
	//ft_lstclear(&lst, free);
	return (0);
}
