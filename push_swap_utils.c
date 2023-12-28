/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:33:29 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/28 03:59:07 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap_utils.h"

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

void	clear_poped(t_list *poped)
{
	free((*poped).content);
	free(poped);
}

t_list	*reverse_list(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst != NULL)
		ft_lstadd_front(&tmp, ft_pop(&lst));
	return (tmp);
}
