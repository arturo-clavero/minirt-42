/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:14:21 by arturo            #+#    #+#             */
/*   Updated: 2024/05/27 22:07:43 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "header.h"

# define CAMERA 42
# define LIGHT 43

typedef struct s_elem
{
	t_vec	orientation;
	t_vec	center;
	t_vec	color_range255;
	float	diameter;
	float	height;
	float	fov_deg;
	float	brightness;
	int		type;
}		t_elem;

typedef struct s_pars
{
	t_elem			element;
	struct s_pars	*next;
}		t_pars;

//PLEASE READ!

//WHAT IS T_VEC?
	//t_vec is a structure that holds 4 float values
	//When you see 3 numbers separated by commas, we need to use this t_vec data type
	//t_vec hold points and vectors (4th number is to differentiate between the 2...)
	//first float is the x coordinate, we can write it like data[0] or data[X] (X has a define of 0);
	//second float is the y coordinate, we can write it like data[1] or data[Y] (Y has a define of 1);
	//third float is the z coordinate, we can write it like data[2] or data[Z] (Z has a define of 2);
	//fourth float is the w value, which is 1 for point or 0 for vectors
	//it is VERY important that the w value is correct for math operations to work correctly...
	//we can write a point in various ways> 
		//data[3] = 1;
		//data[TYPE] = POINT;
		//or we can use create_tupple(address of t_vec, x_value, y_value, z_value);
		//create_tupple adds the x y and z values to t_vec, and lets the fourth float equal to 1
	//we can write a vector in various ways> 
		//data[3] = 0;
		//data[TYPE] = VECTOR;
		//or we can use create_vector(address of t_vec, x_value, y_value, z_value);
		//create_vector adds the x y and z values to t_vec, and lets the fourth float equal to 0
	//EXTRA STUFF
		//so if I have a t_vec vector1 and t_vec vector2, and I want vector 2 to equal vector 1
		// we can not say vector2 = vector1, but we can use this function>
		// copy_t_vec(&vector2, vector1);
		// it copies any t_vec struct, to another struct regardless of if its a vector or point...

//IS IT A POINT OR A VECTOR?
//	A POINT
	// a point is a static 3d coordinate in space, it doesn't move, it is just a location, 
	// i.e in Google maps if you are going from "home" to "school", home is a point and school is another point
	// it has 3 coordinates in the x y and z axis
	// values with only one number, such as a sphere radius, cylinder height, are NOT a point... 
	//ONLY parsing values that are points>
		//	origins
// A VECTOR
	// a vector is an arrow, it describes movement in 3d space. 
	//i.e in Google Maps the path from "home" to "school", would be a vector. 
	//Now this vector is just a set of directions that can be applied to any point of origin
	//Therefore our path vector, will not bring us to "school" if the point of origin is not "home"
	//parsing values that are vectors>
		//  colors (I know, wtf? more on this at the end....)
		//	orientation (watch out! if this value is not normalized == incorrect user input)

//NORMALISED VECTORS
		//a normalised vector is a vector that has a "length" of 1;
	//HOW TO CHECK IF A VECTOR IS NORMALISED?
	//we can calculate the length of t_vec vector like so>
	// float	length_of_a_vector = fsqrt(dot_product(vector, vector));
	//if length_length_of_a_vector != 1 -> exit(1);
	//dot product is my own function but dont worry it works!

//F*CKING COLORS
	// we store as vectors simply because a "w" value of 0 (vector), works better for color math...
	// R, G ,B values correspond to X, Y, Z, meaning that ...
	// color[0] = R-value, or, color[X] = R-value
	// color[1] = G-value, or, color[Y] = G-value
	// color[2] = B-value, or, color[Z] = B-value
	// and lastly color[3] = 0, or, color[TYPE] = VECTOR;

//MORE DETAILED NOTES IN ADD CYLINDER FUNCTION IN ADD SHAPES.C FILE, PLEASE READ THIS FIRST

float	length_t_vec(t_vec vec);
void	store_this_element_in_list(t_pars *new, t_pars **head);
void	add_cylinder(t_pars **head);
void	add_sphere(t_pars **head);
void	add_plane(t_pars **head);
void	add_light1(t_pars **head);
void	add_light2(t_pars **head);
void	add_light3(t_pars **head);
void	add_camera(t_pars **head);

#endif