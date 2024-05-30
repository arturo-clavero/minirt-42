/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:40:50 by arturo            #+#    #+#             */
/*   Updated: 2024/05/30 13:14:07 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	lex_transf_obj(t_obj *obj, t_elem e, t_mtrx (*mt)[MAX_TRANSF], int *ptr)
{
	int		total;

	obj->is_transformed = FALSE;
	total = *ptr;
	if (e.center[X] != 0 || e.center[Y] != 0 || e.center[Z] != 0)
		translation(&(*mt)[++total], e.center[X], e.center[Y], e.center[Z]);
	if ((e.type == SPHERE || e.type == CYLINDER) && e.diameter != 2)
		scalar(&(*mt)[++total], e.diameter / 2.0f, e.diameter / 2.0f, \
		e.diameter / 2.0f);
	*ptr = total;
}

void	rotate_object(t_mtrx (*mt)[MAX_TRANSF], int *total_ptr, t_elem elem)
{
	int		total;
	float	rad;

	total = *total_ptr;
	if (elem.orientation[X] != 0)
	{
		rad = M_PI * 0.5f * elem.orientation[X];
		if (rad < 0)
			rad += M_PI * 2.f;
		rotation(&(*mt)[++total], rad, 'z');
	}
	if (elem.orientation[Y] != 1)
	{
		rad = (elem.orientation[Y] - 1.0f) * -1.0f;
		rad *= (M_PI * 0.5f);
		rotation(&(*mt)[++total], rad, 'x');
	}
	if (elem.orientation[Z] != 1)
	{
		rad = (0.5f * M_PI) * elem.orientation[Z];
		if (rad < 0)
			rad += (2 * M_PI);
		rotation(&(*mt)[++total], rad, 'x');
	}
	*total_ptr = total;
}

void	transform_object(t_mtrx mt[MAX_TRANSF], int total, \
t_obj *obj)
{
	t_mtrx	temp_mt;
	t_mtrx	new_trans;

	chain_transform(mt, &new_trans, total);
	if (obj->is_transformed == TRUE)
	{
		matrix_by_matrix(new_trans, obj->mt_trans, &temp_mt, 4);
		copy_matrix(&new_trans, temp_mt, 4);
	}
	copy_matrix(&obj->mt_trans, new_trans, 4);
	obj->is_transformed = TRUE;
	invert_matrix(obj->mt_trans, &obj->inv_trans, 4);
}

void	add_obj_to_list(t_obj obj, t_objlist **list)
{
	t_objlist	*new;
	t_objlist	*prev;

	new = malloc(sizeof(t_objlist));
	if (!new)
		return ;
	new->obj = obj;
	new->next = NULL;
	new->prev = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		prev = *list;
		while (prev->next)
			prev = prev->next;
		new->prev = prev;
		prev->next = new;
	}
}
