/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_prog.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:57:49 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/22 04:08:43 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static void	ft_set_to_null(void *content)
{
	content = NULL;
}

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
	ft_lstadd_front(b, ft_lstnew((**a).content));
	*a = (**a).next;
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
	t_list	*tmp;

	if (lst == NULL || *lst == NULL || (*(*lst)).next == NULL)
		return ;
	tmp = *lst;
	while ((*tmp).next != NULL && (*(*tmp).next).next != NULL)
		tmp = (*tmp).next;
	ft_lstadd_front(lst, ft_lstnew((*(*tmp).next).content));
	ft_lstdelone((*tmp).next, &ft_set_to_null);
	(*tmp).next = NULL;
}
