/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:32:27 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 22:24:15 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	store_this_element_in_list(t_pars *new, t_pars **head)
{
	t_pars	*prev;

	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		prev = *head;
		while (prev->next)
			prev = prev->next;
		prev->next = new;
	}
}

float	length_t_vec(t_vec vec)
{
	return (sqrtf(dot_product(vec, vec)));
}
//We will consider every line from user input as a separate element
//We will add these elements in a list, using int type to describe the element, 
//and adding in the relevant information for each type of element;
void	parsing(t_pars **pars_head)
{
	add_camera(pars_head);
	add_light1(pars_head);
	add_light2(pars_head);
	add_light3(pars_head);
	add_sphere(pars_head);
	add_plane(pars_head);
	add_cylinder(pars_head);
}
