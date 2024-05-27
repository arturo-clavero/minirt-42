/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:21:48 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 22:24:32 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//lets parse this line> (camera)
//like ambient light, to render scene we need 1 Camara element
//if no C, or multiple C are provided, we will not render....
//	C	-50.0,0,20		0,0,1	70
void	add_camera(t_pars **head)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element.type = CAMERA;
	create_tupple(&new->element.center, -50, 0, 20);
	create_vector(&new->element.orientation, 0, 0, 1);
	if (length_t_vec(new->element.orientation) != 1)
		exit(1);
	new->element.fov_deg = 70;
	store_this_element_in_list(new, head);
}

//lets parse this line> (ambient light)
// it is absolutely required that an element A is provided,
// if there is no A element, or multiple A elements, this is user input error
// only 1 A allowed!
//	A	0.2		255,255,255
void	add_light1(t_pars **head)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element.type = AMBIENT;
	new->element.brightness = 0.2;
	//check that brightness is between 0 and 1, if not, error
	create_vector(&new->element.color_range255, 255, 255, 255);
	store_this_element_in_list(new, head);
}

//lets parse this line> (diffuse light)
// so we will call a normal light diffuse light, we can have 0 or 1 L elements
// multiple L elements will not be handled!
//	L	-40.0,50.0,0.0	0.6		10,0,255
void	add_light2(t_pars **head)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element.type = DIFFUSE;
	create_tupple(&new->element.center, -40, 50, 0);
	new->element.brightness = 0.6;
	create_vector(&new->element.color_range255, 10, 0, 255);
	store_this_element_in_list(new, head);
}

//we will parse a line that is not included in the subject
//this will be for spot brightness, which is required in mandatory part,
//but there are no examples on how to parse this value ... 
//you can choose to call it whatever you want, let's use SB for now ...
// we can have 0 or 1 SB elements
// multiple SB elements will not be handled!
//	SB	0.3		255,255,255
void	add_light3(t_pars **head)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element.type = SPECULAR;
	new->element.brightness = 0.3;
	create_vector(&new->element.color_range255, 255, 255, 255);
	store_this_element_in_list(new, head);
}
