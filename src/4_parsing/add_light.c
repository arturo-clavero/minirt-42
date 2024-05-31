/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:07:41 by arturo            #+#    #+#             */
/*   Updated: 2024/05/31 08:17:27 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

//AMBIENT LIGHT:
//A		0.2		255,255,255
void	add_amb_light_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = AMBIENT;
	elem.brightness = 0.2;
	create_tupple(&elem.color_range255, 255, 255, 255);
	add_element_to_pars_list(elem, pars);
}

//DIFFUSE LIGHT:
//L		-1.0,0.0,-5.0	1
void	add_dif_light_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = DIFFUSE;
	elem.brightness = 1;
	create_tupple(&elem.center, -1, 0, -5);
	add_element_to_pars_list(elem, pars);
}

//SPOT BRIGHTNESS
//SB	1.0		200.0
void	add_spec_light_parsing(t_pars **pars)
{
	t_elem	elem;

	elem.type = SPECULAR;
	elem.brightness = 1;
	elem.shine = 200;
	add_element_to_pars_list(elem, pars);
}
