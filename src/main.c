/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:36:04 by arturo            #+#    #+#             */
/*   Updated: 2024/05/16 15:48:32 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
/*
//TRANSFORM AN OBJECT:
int	main(void)
{
	t_ray	ray;
	t_ray	r2;
	t_mtrx	mt[MAX_TRANSF];
	t_obj	sph;

	init_ray(&ray);
	create_tupple(&ray.og, 0, 0, -5);
	create_vector(&ray.dir, 0, 0, 1);
	translation(&mt[0], 5, 0, 0);
	init_sphere(&sph);
	copy_ray(&r2, &ray);
	printf("og: ");
	print_t_vec(r2.og);
	printf("dir: ");
	print_t_vec(r2.dir);
	transform_object(mt, 1, sph, &r2);
	printf("og: ");
	print_t_vec(r2.og);
	printf("dir: ");
	print_t_vec(r2.dir);
	intersects_sphere(&r2, sph);
	print_intersections(&r2);
}
*/
/*
int	main(void)
{
	t_light	light;
	t_ray	ray;
	t_obj	sph;

	sph.type = SPHERE;
	create_tupple(&sph.og, 0, 0, 0);
	sph.r = 1;
	sph.is_transformed = FALSE;
	create_vector(&sph.color, 1, 1, 1);
	init_ray(&ray);
	create_tupple(&ray.target, 0, 1, 0);
	calc_light_values(&light, sph, &ray);
	printf("ray dir: ");
	print_t_vec(ray.dir);
	printf("normal: ");
	print_t_vec(light.normal);
	printf("reflect: ");
	print_t_vec(light.reflect);
}*/

//RENDER SCENE

int	main(void)
{
	t_mlx	mlx;

	initialize_mlx(&mlx);
	init_scene(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.image.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}


/*
void	new_light(t_light *light)
{
	create_tupple(&light->og, 0, 0, -5);
	create_vector(&light->color, 1, 0, 0);
	light->intensity = .5;
	light->ambient = 0;
	light->diffuse = 1;
	light->specular = 0;
	light->shine = 0;
}

int	main(void)
{
	t_obj		sph;
	t_light		light;
	t_ray		ray;

	sph.type = SPHERE;
	create_tupple(&sph.og, 0, 0, 0);
	sph.r = 1;
	sph.is_transformed = FALSE;
	create_vector(&sph.color, 1, 1, 1);
	new_light(&light);
	init_ray(&ray);
	create_tupple(&ray.og, 0, 0, -5);
	create_tupple(&ray.target, 0, 0, 0);
	substract(ray.target, ray.og, &ray.dir);
	normalize(ray.dir, &ray.dir);
	intersects_sphere(&ray, sph);
	if (ray.closest)
	{
		calc_light_values(&light, ray.closest->object, &ray);
		print_t_vec(ray.color);
	}
}
*/