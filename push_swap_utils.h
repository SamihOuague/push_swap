/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:46:36 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/22 04:11:17 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_UTILS_H
# define PUSH_SWAP_UTILS_H

typedef struct s_arraysize
{
	int	size;
	int	*tab;
}	t_arraysize;

t_arraysize	*get_tab(t_list **lst);
t_list		*tab_to_list(t_arraysize *array);
t_list		*ft_pop(t_list **lst);
void		init_list(t_list **lst, char **tab, int size);
#endif
