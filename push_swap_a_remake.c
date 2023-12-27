/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_a_remake.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 08:47:15 by souaguen          #+#    #+#             */
/*   Updated: 2023/12/27 08:53:52 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    push_stack_a(t_list **lst_a, t_list **lst_b, t_list *sorted, t_list **op, int size)
{
        t_list  *tmp[2];
        int             n_mov;
        int             pivot[2];
        int             count_n;

        if (lst_a == NULL || lst_b == NULL || *lst_b == NULL)
                return ;
        tmp[0] = NULL;
        tmp[1] = NULL;
        n_mov = 0;
        count_n = 0;
        while (*lst_b != NULL)
        {
                if (tmp[0] == NULL && tmp[1] == NULL)
                {
                        tmp_init(&tmp[0], &tmp[1], &sorted, size);
                        n_mov = reset_pivot(*lst_b, tmp[0], tmp[1], &pivot[0], &pivot[1]);
                        undo_reverse(lst_a, lst_b, op, n_mov, count_n);
                        count_n = 0;
                        tmp[0] = reverse_list(tmp[0]);
                }
                else if (tmp[0] == NULL)
                {
                        tmp[0] = reverse_list(tmp[1]);
                        tmp[1] = NULL;
                }
                else if (*(int *)(**lst_b).content == pivot[0])
                {
                        ft_push(lst_b, lst_a);
                        ft_pop(&tmp[0]);
                        ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
                }
                else if (*(int *)(**lst_b).content == pivot[1])
                {
                        ft_push(lst_b, lst_a);
                        ft_rotate(lst_a);
                        ft_pop(&tmp[1]);
                        ft_lstadd_front(op, ft_lstnew(ft_strdup("pa")));
                        n_mov = reset_pivot(*lst_b, tmp[0], tmp[1], &pivot[0], &pivot[1]);
                        if (n_mov > 0)
                        {
                                ft_lstadd_front(op, ft_lstnew(ft_strdup("rr")));
				                                ft_rotate(lst_b);
                        }
                        else
                                ft_lstadd_front(op, ft_lstnew(ft_strdup("ra")));
                        count_n++;
                }
                else
                {
                        if (n_mov >= 0)
                        {
                                ft_rotate(lst_b);
                                ft_lstadd_front(op, ft_lstnew(ft_strdup("rb")));
                        }
                        else
                        {
                                ft_lstadd_front(op, ft_lstnew(ft_strdup("rrb")));
                                ft_reverse_rotate(lst_b);
                        }
                }
                if (*lst_b != NULL)
                        n_mov = reset_pivot(*lst_b, tmp[0], tmp[1], &pivot[0], &pivot[1]);
        }
        undo_reverse(lst_a, lst_b, op, 0, count_n);
}
