/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 03:49:38 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/29 16:22:12 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_prog.h"
#include "push_swap_utils.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_list	*lst_a;
	//t_list	*lst_b;
	t_list	*str_list;
	t_list	*cursor;
	char		*c;
	int		i;

	c = 0;
	lst_a = NULL;
	cursor = NULL;
	//lst_b = NULL;
	str_list = NULL;
	if (argc == 1)
		return (1);
	init_list(&lst_a, (argv + 1), argc - 1);
	c = malloc(sizeof(char));
	while (read(0, c, 1))
	{
		ft_lstadd_back(&str_list, ft_lstnew(c));
		c = malloc(sizeof(char));
	}
	free(c);
	c = malloc(sizeof(char) * ft_lstsize(str_list) + 1);
	ft_bzero(c, ft_lstsize(str_list));
	cursor = str_list;
	i = 0;
	while (cursor != NULL)
	{
		*(c + i) = *(char *)(*cursor).content;
		cursor = (*cursor).next;
		i++;
	}
	c[i] = '\0';
	printf("%s", c);
	free(c);
	ft_lstclear(&str_list, free);
	ft_lstclear(&lst_a, free);
	return (0);
}
