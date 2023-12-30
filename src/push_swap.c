/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 04:06:35 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/30 18:30:43 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_prog.h"
#include "push_swap_utils.h"
#include "check_parameters.h"

t_list	*find_and_replace(t_list *lst, t_list *pattern, char **cmd)
{
	t_list	*new;
	t_list	*cursor;
	int		count;

	new = NULL;
	cursor = pattern;
	while (lst != NULL)
	{
		ft_lstadd_front(&new, ft_pop(&lst));
		if (ft_strncmp((*new).content, (*cursor).content, 3) == 0)
			cursor = (*cursor).next;
		else
			cursor = pattern;
		if (cursor == NULL)
		{
			count = ft_lstsize(pattern);
			while ((count--) > 0)
				clear_poped(ft_pop(&new));
			count = -1;
			while (cmd[++count] != NULL)
				ft_lstadd_front(&new, ft_lstnew(ft_strdup(cmd[count])));
			cursor = pattern;
		}
	}
	return (reverse_list(new));
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[(i++)]);
	free(tab);
}

t_list	*clean_pattern(t_list *prog, char *pattern, char *replace)
{
	t_list	*pattern_list;
	t_list	*tmp_pat;
	char	**p_tab;
	int		i;

	i = 0;
	p_tab = ft_split(pattern, ' ');
	pattern_list = NULL;
	while (p_tab[i] != NULL)
	{
		ft_lstadd_front(&pattern_list, ft_lstnew(ft_strdup(p_tab[i])));
		free(p_tab[(i++)]);
	}
	i = 0;
	free(p_tab);
	p_tab = ft_split(replace, ' ');
	tmp_pat = find_and_replace(prog, pattern_list, p_tab);
	free_tab(p_tab);
	ft_lstclear(&pattern_list, free);
	return (tmp_pat);
}

void	init_prog(t_list **lst_a, t_list **prg, char **tab, int siz)
{
	t_list	*lst_b;
	t_list	*lst;
	int		*n_tab;
	int		i;

	lst_b = NULL;
	lst = NULL;
	if (is_sorted(lst_a))
		return ;
	else if (ft_lstsize(*lst_a) > 300)
		i = siz / 10;
	else if (ft_lstsize(*lst_a) > 12)
		i = siz / 5;
	else
	{
		simple_sort(lst_a, prg);
		return ;
	}
	n_tab = init_tab(tab, siz);
	ft_sort(n_tab, siz, &lst);
	lst_b = push_stack_b(lst_a, reverse_list(lst), prg, ft_max(4, i));
	lst = NULL;
	ft_sort(n_tab, siz, &lst);
	*lst_a = push_stack_a(&lst_b, lst, prg, ft_max(4, i));
	free(n_tab);
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
			clear_poped(ft_pop(&new));
			clear_poped(ft_pop(&cursor));
		}
		else
			ft_lstadd_front(&new, ft_pop(&cursor));
	}
	cursor = NULL;
	while (new != NULL)
		ft_lstadd_front(&cursor, ft_pop(&new));
	return (cursor);
}
