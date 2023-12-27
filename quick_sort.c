/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:38:21 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/27 03:24:01 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap_utils.h"
#include "push_swap_prog.h"
#include <stdio.h>

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

void    ft_quick_sort(int *tab, int size, t_list **list)
{
        int     *tab_1;
        int     *tab_2;
        int     *pivot;
        int     i;
        int     j;
        int     left;
        int     right;
        int     limit;

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
/*int     main(int argc, char **argv)
{
        t_list  *lst;
	t_list	*lst_a;
	t_list	*lst_b;
	t_list	*prog;
	t_list	*pattern_list;
	char		**pattern;
	int			i;
        if (argc < 2)
		return (1);
	
	lst = NULL;
	lst_a = NULL;	
	lst_b = NULL;
	prog = NULL;

	init_list(&lst_a, &argv[1], argc - 1);
	if (ft_lstsize(lst_a) > 300)
		i = ft_lstsize(lst_a) / 10;
	else
		i = ft_lstsize(lst_a) / 5;
	ft_quick_sort(init_tab(argv + 1, argc - 1), argc - 1, &lst);
        push_stack_b(&lst_a, &lst_b, lst, &prog, ft_max(4, i));
        lst = NULL;
        ft_quick_sort(init_tab(argv + 1, argc - 1), argc - 1, &lst);
        push_stack_a(&lst_a, &lst_b, lst, &prog, ft_max(4, i));

	i = 0;
	pattern = ft_split("rb ra", ' ');
        pattern_list = NULL;
        while (pattern[i] != NULL)
        {
                ft_lstadd_front(&pattern_list, ft_lstnew(pattern[i]));
                i++;
        }
	pattern = ft_split("rr", ' ');
        prog = find_and_replace(&prog, pattern_list, pattern);
	prog = clean_prog(prog, "rrb", "rb");
	i = 0;
	read_list(prog);
	ft_lstclear(&lst_a, free);
	ft_lstclear(&pattern_list, free);
	i = -1;
	while (pattern[(++i)] != NULL)
		free(pattern[i]);
	free(pattern);
	return (0);
}*/
