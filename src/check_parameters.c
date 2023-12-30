/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 04:06:35 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/30 12:38:59 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_prog.h"
#include "push_swap_utils.h"

char	**join_n_split_params(char **array, int size)
{
	char	*str;
	char	*tmp;
	char	**tab;
	int		i;

	i = 0;
	if (size == 1)
		str = ft_strdup(array[0]);
	else
		str = ft_strdup("");
	while (size != 1 && i < size)
	{
		tmp = str;
		str = ft_strjoin(str, array[(i++)]);
		free(tmp);
		if (i != size)
		{
			tmp = str;
			str = ft_strjoin(str, " ");
			free(tmp);
		}
	}
	tab = ft_split(str, ' ');
	free(str);
	return (tab);
}

int	is_overflow(char *str)
{
	int	siz;

	siz = ft_strlen(str);
	if (siz > 11 || (siz == 11 && *str != '-'))
		return (1);
	if (siz == 11 && *str == '-')
		return (ft_strncmp(str, "-2147483648", siz) > 0);
	else if (siz == 10 && *str != '-')
		return ((ft_strncmp(str, "2147483647", siz) > 0));
	return (0);
}

int	check_repeat(int *tab, int siz)
{
	t_list	*lst;
	t_list	*cursor;
	int		i;

	i = 0;
	lst = NULL;
	ft_sort(tab, siz, &lst);
	cursor = lst;
	while ((*cursor).next != NULL)
	{
		if (*(int *)(*cursor).content == *(int *)(*(*cursor).next).content)
			break ;
		cursor = (*cursor).next;
		i++;
	}
	free(tab);
	ft_lstclear(&lst, free);
	return (i != siz - 1);
}

int	check_params(char **tab)
{
	int	*n_tab;
	int	i;
	int	j;

	i = -1;
	while (tab[(++i)] != NULL)
	{
		j = -1;
		while (tab[i][(++j)] != '\0')
		{
			if (!ft_isdigit(tab[i][j]) && tab[i][j] != '-')
				return (0);
		}
		if (is_overflow(tab[i]))
			return (0);
	}
	n_tab = init_tab(tab, i);
	return (!check_repeat(n_tab, i));
}
