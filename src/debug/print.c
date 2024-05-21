/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 21:37:12 by arturo            #+#    #+#             */
/*   Updated: 2024/05/21 07:50:03 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_matrix(t_mtrx m, int mt_size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mt_size)
	{
		j = -1;
		while (++j < mt_size)
		{
			if (m[i][j] >= 0)
				printf(" ");
			if (fabs(m[i][j]) < 10.00)
				printf(" ");
			if (fabs(m[i][j]) < 100.00)
				printf(" ");
			printf("%.5f ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void	print_t_vec(t_vec vec)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (vec[i] >= 0)
			printf(" ");
		if (fabs(vec[i]) < 10.00)
			printf(" ");
		if (fabs(vec[i]) < 100.00)
			printf(" ");
		if (i < 3)
			printf("%f ", vec[i]);
	}
	if (vec[3] == VECTOR)
		printf("(vector)\n");
	else
		printf("(point)\n");
}

void	print_shear(float sh[6])
{
	int	i;

	i = -1;
	while (++i < 5)
		printf("%.2f ", sh[i]);
	printf("\n");
}

void	print_intersections(t_ray *ray)
{
	t_intersect	*list;

	list = ray->hit;
	if (list == NULL)
	{
		printf("no intersections\n");
		return ;
	}
	printf("interesctions at:\n");
	while (list)
	{
		printf("%.2f\n", list->dist);
		list = list->next;
	}
	if (ray->closest)
		printf("closest hit: %.2f\n", ray->closest->dist);
	else
		printf("closest hit not recorded\n");
}

void	print_ray(t_ray *ray)
{
	printf("origin: ");
	print_t_vec(ray->og);
	printf("dir: ");
	print_t_vec(ray->dir);
}
