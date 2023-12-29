/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:16:01 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/29 15:39:07 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap_prog.h"

void	check_swap(t_list **lst, t_list **lst_b, char *str)
{

	if (ft_strncmp(str, "sa", 3) == 0 && ft_lstsize(*lst) >= 2)
		ft_swap((int *)(**lst).content, (int *)(*(**lst).next).content);
	else if (ft_strncmp(str, "sb", 3) == 0 && ft_lstsize(*lst_b) >= 2)
		ft_swap((int *)(**lst_b).content, (int *)(*(**lst_b).next).content);
	else if (ft_strncmp(str, "ss", 3) == 0)
	{
		if (ft_lstsize(*lst) >= 2)
			ft_swap((int *)(**lst).content, (int *)(*(**lst).next).content);
		if (ft_lstsize(*lst_b) >= 2)
			ft_swap((int *)(**lst_b).content, (int *)(*(**lst_b).next).content);
	}
}

void	check_push(t_list **lst, t_list **lst_b, char *str)
{
	if (ft_strncmp(str, "pb", 3) == 0 && ft_lstsize(*lst) >= 1)
		ft_push(lst, lst_b);
	else if (ft_strncmp(str, "pa", 3) == 0 && ft_lstsize(*lst_b) >= 1)
		ft_push(lst_b, lst);
}

void	check_rotate(t_list **lst, t_list **lst_b, char *str)
{
	if (ft_strncmp(str, "ra", 3) == 0)
		ft_rotate(lst);
	else if (ft_strncmp(str, "rb", 3) == 0)
		ft_rotate(lst_b);
	else if (ft_strncmp(str, "rr", 3) == 0)
	{
		ft_rotate(lst);
		ft_rotate(lst_b);
	}
}

void	check_reverse_rotate(t_list **lst, t_list **lst_b, char *str)
{
	if (ft_strncmp(str, "rra", 3) == 0)
		ft_reverse_rotate(lst);
	else if (ft_strncmp(str, "rrb", 3) == 0)
		ft_reverse_rotate(lst_b);
	else if (ft_strncmp(str, "rrr", 3) == 0)
	{
		ft_reverse_rotate(lst);
		ft_reverse_rotate(lst_b);
	}
}

void	check_all(t_list **lst, t_list **lst_b, char *str)
{
	check_swap(lst, lst_b, str);
	check_push(lst, lst_b, str);
	check_rotate(lst, lst_b, str);
	check_reverse_rotate(lst, lst_b, str);
}
