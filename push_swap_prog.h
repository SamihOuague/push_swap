/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_prog.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 04:03:22 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/22 04:12:35 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_PROG_H
# define PUSH_SWAP_PROG_H

void	ft_swap(int *a, int *b);
void	ft_push(t_list **a, t_list **b);
void	ft_rotate(t_list **lst);
void	ft_reverse_rotate(t_list **lst);
#endif
