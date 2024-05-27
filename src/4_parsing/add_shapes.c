/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:34:10 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 22:16:52 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//for all shapes we can have 0 or multiple, anything is ok!


//lets parse this line>
//	cy	50.0,0.0,20.6	0.0,0.0,1.0 	14.2	21.42	10,0,255
void	add_cylinder(t_pars **head)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element.type = CYLINDER;
	new->element.diameter = 14.2;
	new->element.height = 21.42;
	//check that diameter and height are bigger than 0! 
	//if not, incorrect user input, we stop here
//HOW TO ADD A POINT (METHOD 1)
	//we can add the point 50.0,0.0,20.6 like this
	new->element.center[X] = 50; // X has a define of 0 for first float value
	new->element.center[Y] = 0; // Y has a define of 1 for second float value
	new->element.center[Z] = 20.6; // Z has a define of 2 for third float value
	new->element.center[TYPE] = POINT; //TYPE has a define of 3 for fourth value of type POINT which has a define of 1
//HOW TO ADD A POINT (METHOD 2)
	//we can add the point 50.0,0.0,20.6 like so>
	//STEP 1 we use create_tupple to fill data, just one line!
	create_tupple(&new->element.center, 50.0, 0, 20.6); 
	//the first argument is the address of t_vec, then the X, Y, Z values and the ft will automatically
	//add the value of w as point

//HOW TO ADD A VECTOR (METHOD 1)
	//we can add the vector 10,0,255 like this
	new->element.color_range255[0] = 10;
	new->element.color_range255[1] = 0;
	new->element.color_range255[2] = 255;
	new->element.color_range255[TYPE] = VECTOR; //TYPE has a define of 3 for fourth value of type VECTOR which has a define of 1
	//if these values are outside 0-255 range, user input is wrong, we stop here

//HOW TO ADD A VECTOR (METHOD 2)
	//we can add the vector 0.0,0.0,1.0 like so>
	//STEP 1 we use create_vector to fill data, just one line!
	create_tupple(&new->element.orientation, 0, 0, 1);
//CHECK ORIENTATION
	//lets check that is normalised, (aka its length is equal to 1) if not, incorrect user input!
	if (length_t_vec(new->element.orientation) != 1)
		exit(1);
	store_this_element_in_list(new, head);
}

//lets parse this line>
//	sp	0.0,0.0,20.6 	12.6	10,0,255
void	add_sphere(t_pars **head)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element.type = SPHERE;
	create_tupple(&new->element.center, 0, 0, 20.6);
	new->element.diameter = 12.6;
	create_vector(&new->element.color_range255, 10, 0, 255);
	store_this_element_in_list(new, head);
}

//lets parse this line>
//	pl	0.0,0.0,-10.0	0.0,1.0,0.0		0,0,225
void	add_plane(t_pars **head)
{
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element.type = PLANE;
	create_tupple(&new->element.center, 0, 0, -10);
	create_vector(&new->element.orientation, 0, 1, 0);
	if (length_t_vec(new->element.orientation) != 1)
		exit(1);
	create_vector(&new->element.color_range255, 0, 0, 255);
	store_this_element_in_list(new, head);
}
