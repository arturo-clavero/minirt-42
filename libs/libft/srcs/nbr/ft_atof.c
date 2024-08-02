/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:52:22 by uolle             #+#    #+#             */
/*   Updated: 2024/07/26 16:36:38 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_atof_utils(const char *str, float *fraction, float *divisor)
{
	if (*str == '.')
	{
		str++;
		while (*str && ft_isdigit((unsigned char)*str))
		{
			*fraction += (*str - '0') / *divisor;
			*divisor *= 10.0;
			str++;
		}
	}
	return ((char *)str);
}

float	ft_atof(const char *str)
{
	float	res;
	float	fraction;
	float	divisor;
	int		sign;

	res = 0.0;
	fraction = 0.0;
	divisor = 10.0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		sign = 1 - 2 * (*str++ == '-');
	while (*str && ft_isdigit((unsigned char)*str))
	{
		res = res * 10.0 + (*str - '0');
		str++;
	}
	str = ft_atof_utils(str, &fraction, &divisor);
	return (sign * (res + fraction));
}
