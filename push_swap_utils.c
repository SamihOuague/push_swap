/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:33:29 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/22 03:57:10 by souaguen         ###   ########.fr       */
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

t_arraysize	*get_tab(t_list **lst)
{
	t_arraysize	*tabsize;
	t_list		*tmp;
	int			size;
	int			i;

	size = ft_lstsize(*lst);
	tabsize = malloc(sizeof(int) * size);
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

t_list	*tab_to_list(t_arraysize *array)
{
	t_list	*lst;
	int		i;

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
