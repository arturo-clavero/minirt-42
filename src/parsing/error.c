/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:33:59 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 01:45:04 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_limit_color(t_vec value, t_pars **pars)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (value[i] < 0.00f || value[i] > 255.0f)
			pars_error("Colors need to be within range [0-255]\n", pars, NULL);
	}
}

void	check_limit_value(int type, float value, t_pars **pars)
{
	if (type == CAMERA && (value < 0 || value > 180))
		pars_error("Camera fov needs to be between 0 and 180\n", pars, NULL);
	else if (type == SPECULAR && (value < 0 || value > 250))
		pars_error("Light specular shine needs to be between 0 and 250\n",
			pars, NULL);
	else if (type == -42 && (value < 0 || value > 1))
		pars_error("Light value needs to be between 0 and 1\n", pars, NULL);
}

void	pars_error(char *error_message, t_pars **par, char *ln)
{
	t_pars	*temp;
	t_pars	*next;
	int		i;

	i = -1;
	while (error_message && error_message[++i])
		write(2, &error_message[i], 1);
	if (ln)
	{
		write(2, "Line: ", 6);
		i = -1;
		while (ln && ln[++i])
			write(2, &ln[i], 1);
	}
	if (par == NULL)
		exit(EXIT_FAILURE);
	while (*par)
	{
		temp = *par;
		next = temp->next;
		free(temp);
		*par = next;
	}
	exit(EXIT_FAILURE);
}

int	line_is_empty(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
	}
	return (1);
}

void	ft_check_comma(t_pars **pars, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
		{
			while (str[++i] && !ft_isdigit(str[i]))
			{
				if (str[i] != ' ' && str[i] != '\t' \
				&& str[i] != '+' && str[i] != '-')
					pars_error("Error: incorrect character (1)\n", pars, str);
				if (str[i] == '-' || str[i] == '+' || str[i] == ',')
					break ;
			}
		}
	}
}
