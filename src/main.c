/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:55:23 by uolle             #+#    #+#             */
/*   Updated: 2024/08/04 01:53:35 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_file_extension(const char *filename, const char *ext)
{
	const char	*dot = ft_strrchr(filename, '.');

	if (!dot || dot == filename)
		return (0);
	return (ft_strcmp(dot + 1, ext) == 0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_pars	*pars;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename.rt>\n", argv[0]);
		return (1);
	}
	if (!check_file_extension(argv[1], "rt"))
	{
		fprintf(stderr, "Error: File extension must be .rt\n");
		return (1);
	}
	pars = NULL;
	parse_file(argv[1], &pars);
	initialize_mlx(&mlx);
	lexer(&mlx, pars);
	init_scene(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.image.img, 0, 0);
	mlx_hook(mlx.win, 2, 1, key_press_hook, &mlx);
	mlx_hook(mlx.win, 17, 0L, x_button, &mlx);
	mlx_loop(mlx.mlx);
	clean(&mlx);
	return (0);
}
