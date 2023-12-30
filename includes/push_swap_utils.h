/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:46:36 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/30 09:12:38 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_UTILS_H
# define PUSH_SWAP_UTILS_H
# include "libft/libft.h"

t_list		*ft_pop(t_list **lst);
void		clear_poped(t_list *poped);
void		init_list(t_list **lst, char **tab);
void		ft_sort(int *tab, int size, t_list **list);

#endif
