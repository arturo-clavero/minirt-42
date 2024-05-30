/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:43:34 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 13:10:49 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_element_to_pars_list(t_elem elem, t_pars **pars)
{
	t_pars	*list;
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
	{
		printf("malloc error\n");
		return ;
	}
	new->element = elem;
	new->next = NULL;
	list = *pars;
	if (*pars == NULL)
		*pars = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}
