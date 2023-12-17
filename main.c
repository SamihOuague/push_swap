/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 04:06:35 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/15 23:04:12 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_nbrslen(char *str)
{
	int	i;
	int	c;
	int	io;

	i = 0;
	c = 0;
	io = 1;
	while (*(str + i) != '\0')
	{
		if (ft_isdigit(*(str + i)) && io)
		{
			io = 0;
			c++;
		}
		else if (*(str + i) == ' ')
			io = 1;
		i++;
	}
	return (c);
}

int	*ft_sort_init(char **tab, int size)
{
	int	*n_tab;
	int	tmp;
	int	i;

	n_tab = malloc(sizeof(int) * size);
	if (n_tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		tmp = ft_atoi(tab[i]);
		n_tab[i] = tmp;
		i++;
	}
	return (n_tab);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int	ft_get_left_size(int *tab, int pivot, int size)
{
	int	i;
	int	c;

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


void	ft_quick_sort(int *tab, int size, t_list **list)
{
	int	*tab_1;
	int	*tab_2;
	int	*pivot;
	int	i;
	int	j;
	int	left;
	int	right;
	int	limit;

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

void	print_list(t_list *lst, int i)
{
	if (lst == NULL)
		return ;
	if ((*lst).next != NULL)
		print_list((*lst).next, i - 1);
	printf("%d: %d\n", i, *(int *)(*lst).content);
}

int	main(int argc, char **argv)
{
	char	**tab;
	t_list	*lst;
	t_list	*cursor;
	int		*n_tab;
	int		min;
	int		max;
	int		size;
	int		i;

	lst = NULL;
	tab = NULL;
	cursor = NULL;
	i = 0;
	if (argc == 2)
	{
		size = ft_nbrslen(argv[1]);
		n_tab = malloc(sizeof(int) * size);
		min = 0;
		max = 1;
		while (argv[1][min] != '\0')
		{
			if (ft_isdigit(argv[1][min]) && max)
			{
				n_tab[i] = ft_atoi(&argv[1][min]);
				max = 0;
				i++;
			}
			else if (argv[1][min] == ' ')
				max = 1;
			min++;
		}
	}
	else
	{
		tab = malloc(sizeof(char *) * argc);
		ft_bzero(tab, sizeof(char *) * argc);
		min = 1;
		size = argc - 1;
		while (min < argc)
		{
			tab[min - 1] = argv[min];
			min++;
		}
		n_tab = ft_sort_init(tab, size);
	}
	ft_quick_sort(n_tab, size, &lst);
	printf("LST SIZE => %d\nTAB SIZE => %d\n", ft_lstsize(lst), size);
	print_list(lst, size - 1);
	free(tab);
	free(n_tab);
	return (0);
}
