/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_prog.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:57:49 by souaguen          #+#    #+#             */
/*   Updated: 2024/01/02 08:16:53 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_push(t_list **a, t_list **b)
{
	t_list	*tmp;

	if (a == NULL || *a == NULL)
		return ;
	tmp = *a;
	ft_lstadd_front(b, ft_lstnew((*tmp).content));
	*a = (*tmp).next;
	(*tmp).content = NULL;
	free(tmp);
	tmp = NULL;
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
	t_list	*tmp;

	if (lst == NULL || *lst == NULL || (*(*lst)).next == NULL)
		return ;
	tmp = *lst;
	while ((*tmp).next != NULL && (*(*tmp).next).next != NULL)
		tmp = (*tmp).next;
	ft_lstadd_front(lst, ft_lstnew((*(*tmp).next).content));
	free((*tmp).next);
	(*tmp).next = NULL;
}
