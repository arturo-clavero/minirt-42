/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle>                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:51:21 by uolle             #+#    #+#             */
/*   Updated: 2024/07/21 18:50:56 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim(char *str)
{
	char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	end[1] = '\0';
	return (str);
}
