/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:38:31 by uolle             #+#    #+#             */
/*   Updated: 2024/08/04 01:29:07 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_cam_parsing(t_pars **pars, char *line)
{
	t_elem	elem;
	float	len;
	char	*tokens[7];

	elem.type = CAMERA;
	ft_split_tokens(line + 2, tokens, 7);
	if (tokens[0])
		ft_parse_vector(&tokens[0], elem.center);
	else
		pars_error("Error: Missing camera center\n", pars, NULL);
	ft_check_orientation(tokens, &elem, pars, &len);
	check_limit_value(CAMERA, elem.fov_in_deg, pars);
	if (elem.fov_in_deg < 0 + EPSILON)
		elem.fov_in_deg += EPSILON;
	if (elem.fov_in_deg > 180 - EPSILON)
		elem.fov_in_deg -= EPSILON;
	add_element_to_pars_list(elem, pars);
}

// CYLINDER
// cy 0,0,0 0,0,1 2 3 0,255,0
void	add_cylinder_parsing(t_pars **pars, char *line)
{
	t_elem	elem;
	float	len;
	char	*tokens[11];

	elem.type = CYLINDER;
	ft_split_tokens(line + 3, tokens, 11);
	ft_parse_vector(&tokens[0], elem.center);
	ft_parse_vector(&tokens[3], elem.orientation);
	len = sqrtf(dot_product(elem.orientation, elem.orientation));
	if (len > 1 + EPSILON || len < 1 - EPSILON)
		pars_error("Cylinder orientation not normalised\n", pars, NULL);
	elem.diameter = ft_atof(tokens[6]);
	elem.height = ft_atof(tokens[7]);
	if (elem.height < 0 || elem.diameter < 0)
		pars_error("Cylinder size values have to be positive\n", pars, NULL);
	create_tupple(&elem.color_range255, ft_atoi(tokens[8]), ft_atoi(tokens[9]),
		ft_atoi(tokens[10]));
	check_limit_color(elem.color_range255, pars);
	add_element_to_pars_list(elem, pars);
}

// SPHERE
// sp 2,0,0 5 0,0,255
void	add_sphere_parsing(t_pars **pars, char *line)
{
	t_elem	elem;
	char	*tokens[7];

	elem.type = SPHERE;
	ft_split_tokens(line + 3, tokens, 7);
	ft_parse_vector(&tokens[0], elem.center);
	elem.diameter = ft_atof(tokens[3]);
	create_tupple(&elem.color_range255, ft_atoi(tokens[4]), ft_atoi(tokens[5]),
		ft_atoi(tokens[6]));
	if (elem.diameter < 0)
		pars_error("Sphere size values have to be positive\n", pars, NULL);
	check_limit_color(elem.color_range255, pars);
	add_element_to_pars_list(elem, pars);
}

int	find_plane(t_elem elem, t_pars **pars)
{
	t_pars	*temp;
	int		i;

	temp = *pars;
	if (pars == NULL)
		return (0);
	while (temp)
	{
		if (temp->element.type == PLANE)
		{
			i = -1;
			while (++i < 3)
			{
				if (elem.orientation[i] == 1
					&& temp->element.orientation[i] == 1
					&& elem.center[i] == temp->element.center[i])
					return (1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

// PLANE
// pl 0,0,-20 0,0,1 255,255,255
void	add_plane_parsing(t_pars **pars, char *line)
{
	t_elem	elem;
	float	len;
	char	*tokens[9];

	elem.type = PLANE;
	ft_split_tokens(line + 3, tokens, 9);
	ft_parse_vector(&tokens[0], elem.center);
	ft_parse_vector(&tokens[3], elem.orientation);
	len = sqrtf(dot_product(elem.orientation, elem.orientation));
	if (len > 1 + EPSILON || len < 1 - EPSILON)
		pars_error("Plane orientation not normalised\n", pars, NULL);
	create_tupple(&elem.color_range255, ft_atoi(tokens[6]), ft_atoi(tokens[7]),
		ft_atoi(tokens[8]));
	check_limit_color(elem.color_range255, pars);
	if (find_plane(elem, pars) == 1)
		return ;
	add_element_to_pars_list(elem, pars);
}
