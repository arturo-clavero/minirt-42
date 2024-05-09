/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:36:04 by arturo            #+#    #+#             */
/*   Updated: 2024/05/09 17:25:19 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(void)
{
	t_mtrx	m1 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	t_mtrx	m2 = ;
	int		mt_size1;
	int		mt_size2;

	mt_size1 = 3;
	mt_size2 = 4;
//	create_matrix_4x4(&m1, );
	//copy_matrix(&m2, m1, mt_size1);
//	m2[0][0] = 1.00001;
	printf("m1:\n");
	print_matrix(m1, mt_size2);
	//printf("m2:\n");
	//print_matrix(m2, mt_size1);
	//if (matrix_comparison(m1, m2, mt_size1, mt_size2) == EXIT_FAILURE)
	//	printf("NOT EQUAL!\n");
//	else
	//	printf("EQUAL!\n");
	return (0);
}
