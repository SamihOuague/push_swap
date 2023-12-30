/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 04:06:35 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/30 11:31:03 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include "push_swap_prog.h"
#include "push_swap_utils.h"
#include "check_parameters.h"

int	main(int argc, char **argv)
{
	t_list	*lst_a;
	t_list	*prog;
	char	**tab;

	if (argc < 2)
		return (1);
	lst_a = NULL;
	prog = NULL;
	tab = join_n_split_params(argv + 1, argc - 1);
	if (!check_params(tab))
	{
		ft_putendl_fd("Error", 2);
		free_tab(tab);
		return (2);
	}
	init_list(&lst_a, tab);
	init_prog(&lst_a, &prog, tab, ft_lstsize(lst_a));
	free_tab(tab);
	prog = clean_prog(clean_prog(prog, "pa", "pb"), "pb", "pa");
	prog = clean_pattern(clean_pattern(prog, "ra rb", "rr"), "rb ra", "rr");
	read_list(prog);
	ft_lstclear(&prog, free);
	ft_lstclear(&lst_a, free);
	return (0);
}
