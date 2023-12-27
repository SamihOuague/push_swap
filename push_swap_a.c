/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 02:38:21 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/27 10:40:18 by souaguen         ###   ########.fr       */
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
	t_list	*tmp[2];
	int	pivot[2];
	int	n_mov;
	int	count_n;
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

static void	tmp_init(t_args *args, t_list **sorted, int size)
{
	int	i;

	i = -1;
	while (sorted != NULL && (++i) < (size / 2))
	{
		if (i < (size / 4))
			ft_lstadd_front(&(*args).tmp[0], ft_pop(sorted));
		else
			ft_lstadd_front(&(*args).tmp[1], ft_pop(sorted));
	}
}

int	reset_pivot(t_list *lst_b, t_args *args)
{
	int	n_mov;

	n_mov = 0;
	if ((*args).tmp[0] != NULL)
	{
		(*args).pivot[0] = *(int *)(*(*args).tmp[0]).content;
		(*args).pivot[1] = (*args).pivot[0];
	}
	if ((*args).tmp[1] != NULL)
		(*args).pivot[1] = *(int *)(*(*args).tmp[1]).content;
	n_mov = get_first_number_left(lst_b, (*args).pivot[0]);
	if (ft_abs(n_mov) > ft_abs(get_last_number_left(lst_b, (*args).pivot[0])))
		n_mov = get_last_number_left(lst_b, (*args).pivot[0]);
	return (n_mov);
}

void	undo_reverse(t_list **lst_a, t_list **lst_b, t_list **op, t_args args)
{
	int	i;

	i = -1;
	while ((++i) < args.count_n)
	{
		if (ft_abs(args.n_mov) > i && args.n_mov < 0)
		{
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rrr")));
			ft_reverse_rotate(lst_b);
		}
		else
			ft_lstadd_front(op, ft_lstnew(ft_strdup("rra")));
		ft_reverse_rotate(lst_a);
	}
}

void	push_n_rotate(t_list **lst_a, t_list **lst_b, t_list **op, t_args *args)
{
	ft_push(lst_b, lst_a);
	ft_rotate(lst_a);
	ft_pop(&(*args).tmp[1]);
	ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
	(*args).n_mov = reset_pivot(*lst_b, args);
	if ((*args).n_mov > 0)
	{
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rr")));
		ft_rotate(lst_b);
	}
	else
		ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
}

void	rotate_n_b(t_list **lst, t_list **op, t_args args)
{
	if (args.n_mov >= 0)
	{
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rb")));
		ft_rotate(lst);
	}
	else
	{
		ft_lstadd_front(op, ft_lstnew(ft_strdup("rrb")));
		ft_reverse_rotate(lst);
	}
}

void	conditional_function(t_list **lst_a, t_list **lst_b, t_list **op, t_args *args)
{
	if ((*args).tmp[0] == NULL)
	{
		(*args).tmp[0] = reverse_list((*args).tmp[1]);
		(*args).tmp[1] = NULL;
	}
	else if (*(int *)(**lst_b).content == (*args).pivot[0])
	{
		ft_push(lst_b, lst_a);
		ft_pop(&(*args).tmp[0]);
		ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
	}
	else if (*(int *)(**lst_b).content == (*args).pivot[1])
	{
		push_n_rotate(lst_a, lst_b, op, args);
		(*args).count_n++;
	}
	else
		rotate_n_b(lst_b, op, *args);
}

void	push_stack_a(t_list **lst_a, t_list **lst_b, t_list *sorted, t_list **op, int size)
{
	t_args	args;

	if (lst_a == NULL || lst_b == NULL || *lst_b == NULL)
		return ;
	
	args.tmp[0] = NULL;
	args.tmp[1] = NULL;
	args.count_n = 0;
	while (*lst_b != NULL)
	{
		if (args.tmp[0] == NULL && args.tmp[1] == NULL)
		{
			tmp_init(&args, &sorted, size);
			args.n_mov = reset_pivot(*lst_b, &args);
			undo_reverse(lst_a, lst_b, op, args);
			args.count_n = 0;
			args.tmp[0] = reverse_list(args.tmp[0]);
		}
		else
			conditional_function(lst_a, lst_b, op, &args);
		if (*lst_b != NULL)
			args.n_mov = reset_pivot(*lst_b, &args);
	}
	undo_reverse(lst_a, lst_b, op, args);
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
