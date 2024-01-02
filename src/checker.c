/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:49:38 by  souaguen         #+#    #+#             */
/*   Updated: 2024/01/02 08:19:07 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "checker_utils.h"
#include "check_parameters.h"

char	*lst_to_str(t_list **lst)
{
	t_list	*cursor;
	char	*str;
	int		i;

	str = malloc(sizeof(char) * ft_lstsize(*lst) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	cursor = *lst;
	ft_bzero(str, ft_lstsize(*lst) + 1);
	while (cursor != NULL && (*cursor).content != NULL)
	{
		str[(i++)] = *(char *)(*cursor).content;
		cursor = (*cursor).next;
	}
	ft_lstclear(lst, free);
	return (str);
}

int	stdin_to_lst(t_list **lst_a, t_list **lst_b)
{
	t_list	*str_list;
	char	*c;

	str_list = NULL;
	c = malloc(sizeof(char));
	while (c != NULL && read(0, c, 1))
	{
		if (*c == '\n')
		{
			free(c);
			c = lst_to_str(&str_list);
			if (!check_all(lst_a, lst_b, c))
			{
				free(c);
				return (0);
			}
			free(c);
		}
		else
			ft_lstadd_back(&str_list, ft_lstnew(c));
		c = malloc(sizeof(char));
	}
	free(c);
	return (1);
}

void	check_lst(t_list **lst_a, t_list **lst_b)
{
	t_list	*cursor;

	cursor = *lst_a;
	while (cursor != NULL && (*cursor).next != NULL)
	{
		if (!check_number(cursor))
		{
			ft_putendl_fd("KO", 1);
			return ;
		}
		cursor = (*cursor).next;
	}
	if (ft_lstsize(*lst_b) != 0)
	{
		ft_putendl_fd("KO", 1);
		return ;
	}
	ft_putendl_fd("OK", 1);
}

void	exec_prog(t_list **lst_a, t_list **lst_b)
{
	if (stdin_to_lst(lst_a, lst_b))
		check_lst(lst_a, lst_b);
	else
		ft_putendl_fd("Error", 2);
}

int	main(int argc, char **argv)
{
	t_list	*lst_a;
	t_list	*lst_b;
	char	**tab;

	lst_a = NULL;
	lst_b = NULL;
	if (argc == 1)
		return (1);
	tab = join_n_split_params(argv + 1, argc - 1);
	if (!check_params(tab))
	{
		ft_putendl_fd("Error", 2);
		free_tab(tab);
		return (2);
	}
	init_list(&lst_a, tab);
	exec_prog(&lst_a, &lst_b);
	free_tab(tab);
	ft_lstclear(&lst_a, free);
	ft_lstclear(&lst_b, free);
	return (0);
}
