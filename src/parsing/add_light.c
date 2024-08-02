/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:41:01 by uolle             #+#    #+#             */
/*   Updated: 2024/07/23 14:46:30 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_amb_light_parsing(t_pars **pars, char *line)
{
	t_elem	elem;
	char	*tokens[4];

	elem.type = AMBIENT;
	ft_split_tokens(line + 2, tokens, 4);
	elem.brightness = ft_atof(tokens[0]);
	create_tupple(&elem.color_range255, ft_atoi(tokens[1]), ft_atoi(tokens[2]),
		ft_atoi(tokens[3]));
	check_limit_value(-42, elem.brightness, pars);
	check_limit_color(elem.color_range255, pars);
	add_element_to_pars_list(elem, pars);
}

// DIFFUSE LIGHT
// L 6 0 0 0.6 255 255 255
void	add_dif_light_parsing(t_pars **pars, char *line)
{
	t_elem	elem;
	char	*tokens[7];

	elem.type = DIFFUSE;
	ft_split_tokens(line + 2, tokens, 7);
	ft_parse_vector(&tokens[0], elem.center);
	elem.brightness = ft_atof(tokens[3]);
	create_tupple(&elem.color_range255, ft_atoi(tokens[4]), ft_atoi(tokens[5]),
		ft_atoi(tokens[6]));
	check_limit_value(-42, elem.brightness, pars);
	check_limit_color(elem.color_range255, pars);
	add_element_to_pars_list(elem, pars);
}

// SPECULAR LIGHT
// S 1.0 200.0
void	add_spec_light_parsing(t_pars **pars, char *line)
{
	t_elem	elem;
	char	*tokens[3];

	elem.type = SPECULAR;
	ft_split_tokens(line + 2, tokens, 2);
	elem.brightness = ft_atof(tokens[0]);
	elem.shine = ft_atof(tokens[1]);
	check_limit_value(-42, elem.brightness, pars);
	check_limit_value(SPECULAR, elem.shine, pars);
	add_element_to_pars_list(elem, pars);
}
