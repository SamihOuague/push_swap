/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 11:28:47 by  souaguen         #+#    #+#             */
/*   Updated: 2023/12/30 11:54:09 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_PARAMETERS_H
# define CHECK_PARAMETERS_H

char	**join_n_split_params(char **array, int size);
int		is_overflow(char *str);
int		check_params(char **tab);
int		check_repeat(int *tab, int size);

#endif
