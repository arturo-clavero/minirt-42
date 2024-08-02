/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:14:48 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/07/21 18:52:20 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_free_buffer(t_list **buffer)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *buffer;
	while (tmp)
	{
		next = tmp->next_string;
		free(tmp->string);
		free(tmp);
		tmp = next;
	}
	*buffer = NULL;
}

void	ft_radd(int fd, t_list **buffer, int byte_readed)
{
	char	*storage;

	while (!ft_found_new_line(*buffer) && byte_readed != 0)
	{
		storage = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!storage)
			return ;
		byte_readed = read(fd, storage, BUFFER_SIZE);
		if ((*buffer == 0 && byte_readed == 0) || byte_readed == -1)
		{
			ft_free_buffer(buffer);
			free(storage);
			return ;
		}
		storage[byte_readed] = '\0';
		ft_badd(buffer, storage, byte_readed);
		free(storage);
	}
}

void	ft_bclean(t_list **buffer)
{
	t_list	*tmp;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (!buffer || !clean_node)
		return ;
	clean_node->next_string = 0;
	tmp = ft_get_last(*buffer);
	i = 0;
	while (tmp->string[i] && tmp->string[i] != '\n')
		i++;
	if (tmp->string && tmp->string[i] == '\n')
		i++;
	clean_node->string = malloc(1 * (ft_strlen(tmp->string) - i + 1));
	if (!clean_node->string)
		return ;
	j = 0;
	while (tmp->string[i])
		clean_node->string[j++] = tmp->string[i++];
	clean_node->string[j] = '\0';
	if (*buffer != 0)
		ft_free_buffer(buffer);
	*buffer = clean_node;
}

char	*get_next_line(int fd)
{
	static t_list	*buffer;
	char			*line;
	int				byte_readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = 0;
	byte_readed = 1;
	ft_radd(fd, &buffer, byte_readed);
	if (buffer == 0)
		return (0);
	if (byte_readed == -1)
	{
		ft_free_buffer(&buffer);
		return (0);
	}
	ft_extract_line(buffer, &line);
	ft_bclean(&buffer);
	if (line[0] == '\0')
	{
		ft_free_buffer(&buffer);
		free(line);
		return (0);
	}
	return (line);
}
