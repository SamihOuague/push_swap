/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 04:06:35 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/29 14:58:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_prog.h"
#include "push_swap_utils.h"

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
	prog = clean_prog(clean_prog(prog, "pa", "pb"), "pb", "pa");
	prog = clean_pattern(clean_pattern(prog, "ra rb", "rr"), "rb ra", "rr");
	read_list(prog);
	ft_lstclear(&prog, free);
	ft_lstclear(&lst_a, free);
	return (0);
}
