/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:11:47 by uolle             #+#    #+#             */
/*   Updated: 2024/07/31 16:08:49 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*ft_find_next_token(char *str, const char *delim)
{
	if (!str || !delim)
		return (NULL);
	while (*str && ft_strchr(delim, *str))
		str++;
	if (!*str)
		return (NULL);
	return (str);
}

void	add_element_to_pars_list(t_elem elem, t_pars **pars)
{
	t_pars	*list;
	t_pars	*new;

	new = malloc(sizeof(t_pars));
	if (!new)
		return ;
	new->element = elem;
	new->next = NULL;
	list = *pars;
	if (*pars == NULL)
		*pars = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

void	ft_parse_vector(char **str, t_vec vec)
{
	int	i;

	i = -1;
	while (++i < 3 && str[i])
		vec[i] = ft_atof(str[i]);
}

void	ft_split_tokens(char *str, char **tokens, int max_tokens)
{
	int			i;
	int			j;
	char		*token;
	const char	*delim;

	i = -1;
	delim = " \t,";
	token = ft_find_next_token(str, delim);
	while (++i < max_tokens && token != NULL)
	{
		j = 0;
		ft_validation_tokens(token, &j);
		tokens[i] = token;
		str = token;
		while (*str && !ft_strchr(delim, *str))
			str++;
		str = ft_close_str(str);
		token = ft_find_next_token(str, delim);
	}
	while (i < max_tokens)
	{
		tokens[i] = NULL;
		i++;
	}
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*static_str;
	char		*token;

	if (str)
		static_str = str;
	static_str = ft_find_next_token(static_str, delim);
	if (!static_str)
		return (NULL);
	token = static_str;
	while (*static_str && !ft_strchr(delim, *static_str))
		static_str++;
	if (*static_str)
	{
		*static_str = '\0';
		static_str++;
	}
	else
		static_str = NULL;
	return (token);
}
