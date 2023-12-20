/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:49:38 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/20 06:53:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

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
		ft_stack_pivot_right(lst, lst_b, pivot);
	}
	else if (*(int *)(**lst).content > pivot)
	{
		ft_rotate(lst);
		ft_stack_pivot_right(lst, lst_b, pivot);
		ft_reverse_rotate(lst);
	}
	else
		ft_push(lst, lst_b);
}

void    ft_stack_pivot_left(t_list **lst, t_list **lst_b, int pivot)
{
        if (lst_b == NULL || *lst_b == NULL)
                return ;
	if (*(int *)(**lst_b).content > pivot)
        {
                ft_push(lst_b, lst);
		ft_stack_pivot_left(lst, lst_b, pivot);
        }
        else if (*(int *)(**lst_b).content < pivot)
        {
                ft_rotate(lst_b);
                ft_stack_pivot_left(lst, lst_b, pivot);
                ft_reverse_rotate(lst_b);
        }
	else
		return ;

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

void	get_infos(t_list *lst, t_list *lst_b)
{
	printf("# Stack A => ");
	print_list(lst);
	printf("\n");
	printf("# Stack B => ");
	print_list(lst_b);
	printf("\n\n");
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*lst_b;
	t_list	*pivots;
	t_list	*temp;
	char	str[4];	
	int		*tmp;
	int		i;
	
	if (argc == 1)
		return (1);
	i = 1;
	lst = NULL;
	lst_b = NULL;
	pivots = NULL;
	ft_bzero(str, 4);
	init_list(&lst, &argv[1], argc - 1);
	i = 0;
	while (lst != NULL)
	{
		ft_stack_pivot_right(&lst, &lst_b, *(int *)(*ft_lstlast(lst)).content);
		ft_lstadd_front(&pivots, ft_lstnew((*lst_b).content));
	}
	
	printf("%d\n", *(int *)(*pivots).content);
	get_infos(lst, lst_b);
	ft_stack_pivot_left(&lst, &lst_b, *(int *)(*pivots).content);
	ft_push(&lst_b, &lst);	
	temp = ft_pop(&pivots);

	
	printf("%d\n", *(int *)(*pivots).content);
        get_infos(lst, lst_b);
	ft_stack_pivot_left(&lst, &lst_b, *(int *)(*pivots).content);
        ft_push(&lst_b, &lst);
	temp = ft_pop(&pivots);
	
	printf("%d\n", *(int *)(*pivots).content);
	get_infos(lst, lst_b);
        ft_stack_pivot_left(&lst, &lst_b, *(int *)(*pivots).content);
        get_infos(lst, lst_b);
        temp = ft_pop(&pivots);
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
	printf("%d LENGTH\n", i);
	ft_lstclear(&lst, free);
	return (0);
}
