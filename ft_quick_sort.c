/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:27:17 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/27 23:24:08 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_prog.h"

static int	partition(int *tab, int start, int end)
{
	int	i;
	int	j;
	int	pivot;

	i = start;
	j = i - 1;
	pivot = tab[end];
	while (i < end)
	{
		if (tab[i] < pivot)
			ft_swap(&tab[i], &tab[(++j)]);
		i++;
	}
	ft_swap(&tab[j + 1], &tab[end]);
	return (j + 1);
}

void	ft_quick_sort(int *tab, int start, int end)
{
	int	part;

	if (start < end)
	{
		part = partition(tab, start, end);
		ft_quick_sort(tab, start, part - 1);
		ft_quick_sort(tab, part + 1, end);
	}
}

void	ft_sort(int *tab, int size, t_list **lst)
{
	int	i;
	int	*n;

	i = 0;
	n = NULL;
	ft_quick_sort(tab, 0, size - 1);
	while (i < size)
	{
		n = malloc(sizeof(int));
		if (n != NULL)
		{
			*n = tab[i];
			ft_lstadd_front(lst, ft_lstnew(n));
			i++;
		}
		else
			break ;
	}
}
