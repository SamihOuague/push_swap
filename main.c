/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 04:06:35 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/29 08:17:39 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_utils.h"

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
	if (ft_lstsize(*lst_a) > 300)
		i = siz / 10;
	else
		i = siz / 5;
	n_tab = init_tab(tab, siz);
	ft_sort(n_tab, siz, &lst);
	lst_b = push_stack_b(lst_a, reverse_list(lst), prg, ft_max(4, i));
	lst = NULL;
	ft_sort(n_tab, siz, &lst);
	*lst_a = push_stack_a(&lst_b, lst, prg, ft_max(4, i));
	*prg = clean_pattern(clean_pattern(*prg, "ra rb", "rr"), "rb ra", "rr");
	*prg = clean_pattern(clean_pattern(*prg, "pa pb", ""), "pb pa", "");
	free(n_tab);
}

int	main(int argc, char **argv)
{
	t_list	*lst_a;
	t_list	*prog;

	if (argc < 2)
		return (1);
	lst_a = NULL;
	prog = NULL;
	init_list(&lst_a, (argv + 1), argc - 1);
	init_prog(&lst_a, &prog, (argv + 1), argc - 1);
	read_list(prog);
	ft_lstclear(&prog, free);
	ft_lstclear(&lst_a, free);
	return (0);
}
