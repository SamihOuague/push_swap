/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:38:21 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/27 08:18:54 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_utils.h"
#include "push_swap_prog.h"
#include "quick_sort.h"
#include <stdio.h>

typedef struct	s_args
{
	t_list	*lst_a;
	t_list	*lst_b;
	t_list	*tmp[2];
	t_list	*op;
	int	pivot[2];
	int	n_mov;
}	t_args;

void	read_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	read_list((*lst).next);
	ft_putendl_fd((char *)(*lst).content, 1);
}

static t_list	*reverse_list(t_list *lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (lst != NULL)
		ft_lstadd_front(&tmp, ft_pop(&lst));
	return (tmp);
}

void	print_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	print_list((*lst).next);
	printf("%d\n", *(int *)(*lst).content);
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

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int	get_first_number(t_list *lst, int pivot)
{
	t_list	*cursor;
	int		first;
	int		size;

	cursor = lst;
	first = 0;
	while (cursor != NULL)
	{
		if (*(int *)(*cursor).content >= pivot)
			break ;
		first++;
		cursor = (*cursor).next;
	}
	size = ft_lstsize(lst);
	if (first > (size / 2))
		return (first - size);
	return (first);
}

int	get_last_number(t_list *lst, int pivot)
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
		if (*(int *)(*cursor).content >= pivot)
			last = i;
		cursor = (*cursor).next;
		i++;
	}
	size = ft_lstsize(lst);
	if (last > (size / 2))
		return (last - size);
	return (last);
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

static void	tmp_init(t_list **tmp, t_list **tmpp, t_list **sorted, int size)
{
	int	i;

	i = -1;
	while (sorted != NULL && (++i) < (size / 2))
	{
		if (i < (size / 4))
			ft_lstadd_front(tmp, ft_pop(sorted));
		else
			ft_lstadd_front(tmpp, ft_pop(sorted));
	}
}

int	reset_pivot(t_list *lst_b, t_list *tmp, t_list *tmpp, int *pivot, int *pivot_2)
{
	int	n_mov;

	n_mov = 0;
	if (tmp != NULL)
	{
		*pivot = *(int *)(*tmp).content;
		*pivot_2 = *pivot;
	}
	if (tmpp != NULL)
		*pivot_2 = *(int *)(*tmpp).content;
	n_mov = get_first_number_left(lst_b, *pivot);
	if (ft_abs(n_mov) > ft_abs(get_last_number_left(lst_b, *pivot)))
		n_mov = get_last_number_left(lst_b, *pivot);
	return (n_mov);
}

void	undo_reverse(t_list **lst_a, t_list **lst_b, t_list **op, int n_mov, int count_n)
{
	int	i;

	i = -1;
	while ((++i) < count_n)
	{
		if (ft_abs(n_mov) > i && n_mov < 0)
		{
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rrr")));
			ft_reverse_rotate(lst_b);
		}
		else
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
		ft_reverse_rotate(lst_a);
	}
}

/*void	conditional_function(t_list **lst_a, t_list **lst_b, t_list **op, t_list *tmp, t_list *tmpp, int *pivot, int *pivot_2, int *n_mov)
{
	if (*(int *)(**lst_b).content == *pivot)
	{
		ft_push(lst_b, lst_a);
		ft_pop(&tmp);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
	}
	else if (*(int *)(**lst_b).content == *pivot_2)
	{
		ft_push(lst_b, lst_a);
		ft_rotate(lst_a);
		ft_pop(&tmpp);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
		n_mov = reset_pivot(*lst_b, tmp, tmpp, pivot, pivot_2);
		if (n_mov > 0)
		{
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rr")));
			ft_rotate(lst_b);
		}
		else
			ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
		count_n++;
	}
	else
	{
		if (n_mov >= 0)
		{
			ft_rotate(lst_b);
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rb")));
		}
		else
		{
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rrb")));
			ft_reverse_rotate(lst_b);
		}
	}
}
*/
void	push_stack_a(t_list **lst_a, t_list **lst_b, t_list *sorted, t_list **op, int size)
{
	t_list	*tmp[2];
	int		n_mov;
	int		pivot[2];
	int		count_n;

	if (lst_a == NULL || lst_b == NULL || *lst_b == NULL)
		return ;
	tmp[0] = NULL;
	tmp[1] = NULL;
	n_mov = 0;
	count_n = 0;
	while (*lst_b != NULL)
	{
		if (tmp[0] == NULL && tmp[1] == NULL)
		{
			tmp_init(&tmp[0], &tmp[1], &sorted, size);
			n_mov = reset_pivot(*lst_b, tmp[0], tmp[1], &pivot[0], &pivot[1]);
			undo_reverse(lst_a, lst_b, op, n_mov, count_n);
			count_n = 0;
			tmp[0] = reverse_list(tmp[0]);
		}
		else if (tmp[0] == NULL)
		{
			tmp[0] = reverse_list(tmp[1]);
			tmp[1] = NULL;
		}
		else if (*(int *)(**lst_b).content == pivot[0])
		{
			ft_push(lst_b, lst_a);
			ft_pop(&tmp[0]);
			ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
		}
		else if (*(int *)(**lst_b).content == pivot[1])
		{
			ft_push(lst_b, lst_a);
			ft_rotate(lst_a);
			ft_pop(&tmp[1]);
			ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
			n_mov = reset_pivot(*lst_b, tmp[0], tmp[1], &pivot[0], &pivot[1]);
			if (n_mov > 0)
			{
				ft_lstadd_front(op, ft_lstnew(ft_strdup("rr")));
				ft_rotate(lst_b);
			}
			else
				ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
			count_n++;
		}
		else
		{
			if (n_mov >= 0)
			{
				ft_rotate(lst_b);
				ft_lstadd_front(op, ft_lstnew(ft_strdup("rb")));
			}
			else
			{
				ft_lstadd_front(op, ft_lstnew(ft_strdup("rrb")));
				ft_reverse_rotate(lst_b);
			}
		}
		if (*lst_b != NULL)
			n_mov = reset_pivot(*lst_b, tmp[0], tmp[1], &pivot[0], &pivot[1]);
	}
	undo_reverse(lst_a, lst_b, op, 0, count_n);
}

t_list	*find_and_replace(t_list **lst, t_list *pattern, char **cmd)
{
	t_list	*new;
	t_list	*cursor;
	int		count;

	if (lst == NULL || *lst == NULL)
		return (NULL);
	if (pattern == NULL)
		return (*lst);
	count = 0;
	new = NULL;
	cursor = pattern;
	while (*lst != NULL)
	{
		ft_lstadd_front(&new, ft_pop(lst));
		if (ft_strncmp((char *)(*new).content, (char *)(*cursor).content, 3) == 0)
			cursor = (*cursor).next;
		else
			cursor = pattern;
		if (cursor == NULL)
		{
			count = ft_lstsize(pattern);
			while (count > 0)
			{
				ft_pop(&new);
				count--;
			}
			count = -1;
			while (cmd[++count] != NULL)
				ft_lstadd_front(&new, ft_lstnew(cmd[count]));
			cursor = pattern;
		}
	}
	cursor = NULL;
	while (new != NULL)
		ft_lstadd_front(&cursor, ft_pop(&new));
	return (cursor);
}

t_list	*clean_prog(t_list *lst, char *s1, char *s2)
{
	t_list	*new;
	t_list	*cursor;

	new = NULL;
	cursor = lst;
	while (cursor != NULL)
	{
		if (new != NULL
		&& ft_strncmp((char *)(*new).content, s1, 3) == 0
		&& ft_strncmp((char *)(*cursor).content, s2, 3) == 0)
		{
			ft_pop(&new);
			ft_pop(&cursor);
		}
		else
			ft_lstadd_front(&new, ft_pop(&cursor));
	}
	cursor = NULL;
	while (new != NULL)
		ft_lstadd_front(&cursor, ft_pop(&new));
	return (cursor);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	t_list	*lst_a;
	t_list	*lst_b;
	t_list	*prog;
	t_list	*pattern_list;
	char	**pattern;
	int		i;
	
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
	lst_b = push_stack_b(&lst_a, reverse_list(lst), &prog, ft_max(4, i));
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
}
