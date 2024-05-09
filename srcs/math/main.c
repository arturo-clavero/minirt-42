/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arturo <arturo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:36:04 by arturo            #+#    #+#             */
/*   Updated: 2024/05/08 20:03:33 by arturo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(void)
{
	t_vec	tup1;
	t_vec	tup2;
	t_vec	result;
	int		i;

	create_tupple(&tup1, 1, 0.2, 0.4);
	create_tupple(&tup2, 0.9, 1, 0.1);
	//float x = dot_product(tup1, tup2);
	blend_colors(tup2, tup1, &result);
	i = -1;
	printf("1: ");
	while (++i < 4)
		printf("%.2f ", tup1[i]);
	printf("\n");
	i = -1;
	printf("2: ");
	while (++i < 4)
		printf("%.2f ", tup2[i]);
	printf("\n");
	i = -1;
	printf("-> ");
	while (++i < 4)
		printf("%.2f ", result[i]);
	printf("\n");
//	printf("-> %f\n", x);
	return (0);
}
