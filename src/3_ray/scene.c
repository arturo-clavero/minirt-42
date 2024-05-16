#include "header.h"
/*
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

void	new_sphere(t_mlx *mlx)
{
	t_obj	sph;

	sph.type = SPHERE;
	create_tupple(&sph.og, 0, 0, -5);
	sph.r = 1;
	sph.is_transformed = FALSE;
	create_vector(&sph.color, 1, 1, 1);
	add_obj_to_list(sph, &mlx->obj_list);
}

void	new_ray(t_ray *ray, float pixel[2], t_mlx *mlx)
{
	t_vec	target;
	t_vec	dir;

	init_ray(mlx->ray);
	create_tupple(&ray->og, 0, 0, 0);
	target[X] = mlx->vp_min[X] + (mlx->pixel_size * pixel[X]);
	target[Y] = mlx->vp_min[Y] - (mlx->pixel_size * pixel[Y]);
	target[Z] = mlx->vp_wall;
	target[TYPE] = POINT;
	substract(target, ray->og, &dir);
	normalize(dir, &ray->dir);
	copy_t_vec(&mlx->ray->target, target);
}

void	init_viewport(t_mlx *mlx)
{
	mlx->vp_size[X] = 80;
	mlx->vp_size[Y] = 40;
	mlx->vp_min[X] = -mlx->vp_size[X] / 2;
	mlx->vp_min[Y] = mlx->vp_size[Y] / 2;
	mlx->vp_wall = 10;
	mlx->win_size[X] = 800;
	mlx->win_size[Y] = 400;
	mlx->pixel_size = mlx->vp_size[X] / mlx->win_size[X];
}

void	free_intersections(t_ray *ray)
{
	t_intersect	*temp;

	while (ray->hit)
	{
		temp = ray->hit->next;
		free(ray->hit);
		ray->hit = temp;
	}
}

void	new_light(t_light *light)
{
	create_tupple(&light->og, 10, 10, 0);
	create_vector(&light->color, 1, 1, 1);
	light->intensity = 1;
	light->ambient = 1;
	light->diffuse = 0;
	light->specular = 0;
	light->shine = 0;
}


*/

#include "header.h"

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

void	new_sphere(t_mlx *mlx)
{
	t_obj	sph;

	sph.type = SPHERE;
	create_tupple(&sph.og, 0, 0, 0);
	sph.r = 1;
	sph.is_transformed = FALSE;
	create_vector(&sph.color, 1, 1, 1);
	add_obj_to_list(sph, &mlx->obj_list);
}

void	new_ray(t_ray *ray, float pixel[2], t_mlx *mlx)
{
	t_vec	target;
	t_vec	dir;

	init_ray(mlx->ray);
	create_tupple(&ray->og, 0, 0, -1.5);
	target[X] = mlx->vp_min[X] + (mlx->pixel_size * pixel[X]);
	target[Y] = mlx->vp_min[Y] - (mlx->pixel_size * pixel[Y]);
	target[Z] = mlx->vp_wall;
	target[TYPE] = POINT;
	substract(target, ray->og, &dir);
	normalize(dir, &ray->dir);
	copy_t_vec(&mlx->ray->target, target);
}

void	init_viewport(t_mlx *mlx)
{
	mlx->vp_size[X] = 80;
	mlx->vp_size[Y] = 40;
	mlx->vp_min[X] = -mlx->vp_size[X] / 2;
	mlx->vp_min[Y] = mlx->vp_size[Y] / 2;
	mlx->vp_wall = 10;
	mlx->win_size[X] = 800;
	mlx->win_size[Y] = 400;
	mlx->pixel_size = mlx->vp_size[X] / mlx->win_size[X];
}

void	free_intersections(t_ray *ray)
{
	t_intersect	*temp;

	if (ray->hit == NULL)
		return ;
	while (ray->hit)
	{
		temp = ray->hit->next;
		free(ray->hit);
		ray->hit = temp;
	}
}

void	new_light(t_light *light)
{
	create_tupple(&light->og, 0, 0, -5);
	create_vector(&light->color, 1, 1, 1);
	light->ambient = 0.1;
	light->specular = 0.9;
	light->diffuse = 1;
	light->shine = 200;
}

void	init_scene(t_mlx *mlx)
{
	t_objlist	*obj;
	float		pixel[2];
	t_mtrx		mt[MAX_TRANSF];
	t_light		light;
	//t_vec		temp;

	(void)mt;
	new_sphere(mlx);
	new_light(&light);
	init_viewport(mlx);
	pixel[X] = - 1;
	while (++pixel[X] < mlx->win_size[X])
	{
		pixel[Y] = -1;
		while (++pixel[Y] < mlx->win_size[Y])
		{
			new_ray(mlx->ray, pixel, mlx);
			obj = mlx->obj_list;
			while (obj)
			{
				intersects_sphere(mlx->ray, obj->obj);
				obj = obj->next;
			}
			if (mlx->ray->closest)
			{
				ft_mlx_pixel_put(&mlx->image, (int)pixel[X], (int)pixel[Y], \
				mlx->ray->color);
			}
			/*else
			{
				printf("pixel %.4f, %.4f\n", pixel[X], pixel[Y]);
				print_intersections(mlx->ray);
				create_vector(&temp, 1, 0, 0);
				ft_mlx_pixel_put(&mlx->image, (int)pixel[X], (int)pixel[Y], temp);
				mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image.img, 0, 0);
				mlx_loop(mlx->mlx);
				while (1)
					;
			}*/
			free_intersections(mlx->ray);
		}
	}
}
