/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_set_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:10:14 by arturo            #+#    #+#             */
/*   Updated: 2024/05/29 13:08:56 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_camera(t_mlx *mlx)
{
	printf("CAMERA\n");
	printf("fov: %f\n", mlx->cam.fov);
	printf("is cam default?");
	if (mlx->cam.default_orient == FALSE)
	{
		printf(" NO\n");
		printf("inv transform:\n");
		print_matrix(mlx->cam.inv_trans, 4);
	}
	else
		printf(" YES\n");
}

void	print_center_ray(t_mlx *mlx)
{
	float	pixel[2];
	t_ray	ray;

	pixel[X] = mlx->win_size[X] / 2;
	pixel[Y] = mlx->win_size[Y] / 2;
	new_parent_ray(mlx->cam, &ray, pixel);
	printf("\nray for pixels (%.2f, %.2f)\n", pixel[X], pixel[Y]);
	print_ray(&ray);
}

void	print_objects(t_mlx *mlx)
{
	t_objlist	*list;

	list = mlx->obj_list;
	if (list == NULL)
		printf("Null list!!!\n");
	else
	{
		while (list)
		{
			printf("OBJ TYPE %d\n", list->obj.type);
			printf("is obj transformed? %d\n", list->obj.is_transformed);
			list = list->next;
		}
	}
}

void	print_set_up(t_mlx *mlx)
{
	print_camera(mlx);
	print_center_ray(mlx);
	print_objects(mlx);
}
