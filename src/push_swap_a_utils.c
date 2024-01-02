/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_a_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:11:33 by souaguen          #+#    #+#             */
/*   Updated: 2024/01/02 08:13:27 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	read_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	read_list((*lst).next);
	ft_putendl_fd((char *)(*lst).content, 1);
}

int	*init_tab(char **tab, int size)
{
	int	*tmp;
	int	i;

	i = -1;
	tmp = malloc(sizeof(int) * size);
	while ((++i) < size)
		tmp[i] = ft_atoi(tab[i]);
	return (tmp);
}

int	get_first_number_left(t_list *lst, int pivot)
{
	t_list	*cursor;
	int		first;
	int		size;

	cursor = lst;
	first = 0;
	while (cursor != NULL)
	{
		if (*(int *)(*cursor).content == pivot)
			break ;
		first++;
		cursor = (*cursor).next;
	}
	size = ft_lstsize(lst);
	if (first > (size / 2))
		return (first - size);
	return (first);
}

int	get_last_number_left(t_list *lst, int pivot)
{
	t_list	*cursor;
	int		last;
	int		size;
	int		i;

	i = 0;
	last = i;
	cursor = lst;
	while (cursor != NULL)
	{
		if (*(int *)(*cursor).content == pivot)
			last = i;
		cursor = (*cursor).next;
		i++;
	}
	size = ft_lstsize(lst);
	if (last > (size / 2))
		return (last - size);
	return (last);
}
