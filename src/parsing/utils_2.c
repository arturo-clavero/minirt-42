/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:43:33 by uolle             #+#    #+#             */
/*   Updated: 2024/07/26 17:01:06 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_validation_tokens(char *token, int *i)
{
	int	j;

	j = *i;
	while (token[++j] != '\0')
		if (ft_isalpha(token[j]) && token[j] != ',' && token[j] != '.'
			&& token[j] != ' ')
			pars_error("Error: Invalid tokens\n", NULL);
	*i = j;
}

char	*ft_close_str(char *str)
{
	if (*str)
	{
		*str = '\0';
		str++;
	}
	return (str);
}

void	ft_check_orientation(char *tokens[7], t_elem *elem, t_pars **pars,
		float *len)
{
	if (tokens[2])
	{
		ft_parse_vector(&tokens[3], elem->orientation);
		*len = sqrtf(dot_product(elem->orientation, elem->orientation));
		if (*len > 1 + EPSILON || *len < 1 - EPSILON)
			pars_error("Camera orientation not normalised\n", pars);
	}
	else
		pars_error("Error: Missing camera orientation\n", pars);
	if (tokens[5])
		elem->fov_in_deg = ft_atoi(tokens[6]);
	else
		pars_error("Error: Missing camera field of view\n", pars);
}
