/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:20:45 by ugolin-olle       #+#    #+#             */
/*   Updated: 2023/10/06 13:48:04 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_found_new_line(t_list *buffer)
{
	int		i;
	t_list	*tmp;

	if (buffer == 0)
		return (0);
	tmp = ft_get_last(buffer);
	i = 0;
	while (tmp->string[i])
	{
		if (tmp->string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_get_last(t_list *buffer)
{
	t_list	*current;

	current = buffer;
	while (current && current->next_string)
		current = current->next_string;
	return (current);
}

void	ft_badd(t_list **buffer, char *storage, int byte_readed)
{
	int		i;
	t_list	*tmp;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next_string = 0;
	new_node->string = (char *)malloc(sizeof(char) * (byte_readed + 1));
	if (!new_node->string)
		return ;
	i = 0;
	while (storage[i] && i < byte_readed)
	{
		new_node->string[i] = storage[i];
		i++;
	}
	new_node->string[i] = '\0';
	if (!*buffer)
	{
		*buffer = new_node;
		return ;
	}
	tmp = ft_get_last(*buffer);
	tmp->next_string = new_node;
}

void	ft_extract_line(t_list *buffer, char **line)
{
	int	i;
	int	j;

	if (!buffer)
		return ;
	ft_create_line(line, buffer);
	if (!*line)
		return ;
	j = 0;
	while (buffer)
	{
		i = 0;
		while (buffer->string[i])
		{
			if (buffer->string[i] == '\n')
			{
				(*line)[j++] = buffer->string[i];
				break ;
			}
			(*line)[j++] = buffer->string[i++];
		}
		buffer = buffer->next_string;
	}
	(*line)[j] = '\0';
}

void	ft_create_line(char **line, t_list *buffer)
{
	int	i;
	int	stor;

	stor = 0;
	while (buffer)
	{
		i = 0;
		while (buffer->string[i])
		{
			if (buffer->string[i] == '\n')
			{
				stor++;
				break ;
			}
			stor++;
			i++;
		}
		buffer = buffer->next_string;
	}
	*line = (char *)malloc(sizeof(char) * (stor + 1));
	if (!*line)
		return ;
}
