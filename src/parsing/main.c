/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:46:44 by arturo            #+#    #+#             */
/*   Updated: 2024/08/04 01:30:24 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_parsing_check(t_pars **pars, char *line)
{
	if (line[0] == 's' && line[1] != 'p' && (line[2] != ' ' && line[2] == '\t'))
		pars_error("Error: Invalid identifier 2\n", pars, line);
	else if (line[0] == 'p' && line[1] != 'l' && (line[2] != ' '
			&& line[2] == '\t'))
		pars_error("Error: Invalid identifier 3\n", pars, line);
	else if (line[0] == 'c' && line[1] != 'y' && (line[2] != ' '
			&& line[2] == '\t'))
		pars_error("Error: Invalid identifier 4\n", pars, line);
	else if (!ft_isalpha(line[0]) && line[1] != ' ' && line[1] != '\t')
		pars_error("Error: Invalid identifier 1\n", pars, line);
}

static void	ft_parsing_values(t_pars **pars, char *line)
{
	int		expected_values;
	int		count;
	char	*tmp;
	char	*token;

	tmp = ft_strdup(line);
	expected_values = 0;
	if (line[0] == 'C' || line[0] == 'L' || (line[0] == 's' && line[1] == 'p'))
		expected_values = 7;
	else if (line[0] == 'p' && line[1] == 'l')
		expected_values = 9;
	else if (line[0] == 'c' && line[1] == 'y')
		expected_values = 11;
	else if (line[0] == 'A')
		expected_values = 4;
	count = -1;
	token = ft_strtok(tmp, " \t,");
	while (token && line_is_empty(token) == 0 && ++count > -2)
		token = ft_strtok(NULL, " \t,");
	free(tmp);
	if (count != expected_values)
		pars_error("Error: Invalid number of values.\n", pars, line);
}

static void	ft_multiple_tok_check(t_pars **pars, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '\n' && str[i] != ' ' \
		&& str[i] != '\t' && str[i] != '.' && str[i] != '-' \
		&& str[i] != '+' && str[i] != ',' && i > 1)
			pars_error("Error: incorrect character (0)\n", pars, str);
		else if ((str[i] == '+' || str[i] == '-' || str[i] == '.') && \
		(!str[i + 1] || !ft_isdigit(str[i + 1])))
			pars_error("Error: incorrect character (2)\n", pars, str);
		else if ((str[i] == '+' || str[i] == '-') && (i == 0 || \
		(str[i - 1] != ' ' && str[i - 1] != '\t' && str[i - 1] != ',')))
			pars_error("Error: incorrect character (3)\n", pars, str);
		else if (str[i] == '.' && (i == 0 || !ft_isdigit(str[i - 1])))
			pars_error("Error: incorrect character (4)\n", pars, str);
	}
}

static void	parsing(t_pars **pars, char *l)
{
	if (l == NULL || l[0] == '\0' || l[0] == '#' || l[0] == '\n')
		return ;
	ft_multiple_tok_check(pars, l);
	ft_check_comma(pars, l);
	ft_parsing_check(pars, l);
	ft_parsing_values(pars, l);
	if (l[0] == 'C' && (l[1] == ' ' || l[1] == '\t'))
		add_cam_parsing(pars, l);
	else if (l[0] == 's' && l[1] == 'p' && (l[2] == ' ' || l[2] == '\t'))
		add_sphere_parsing(pars, l);
	else if (l[0] == 'p' && l[1] == 'l' && (l[2] == ' ' || l[2] == '\t'))
		add_plane_parsing(pars, l);
	else if (l[0] == 'c' && l[1] == 'y' && (l[2] == ' ' || l[2] == '\t'))
		add_cylinder_parsing(pars, l);
	else if (l[0] == 'A' && (l[1] == ' ' || l[1] == '\t'))
		add_amb_light_parsing(pars, l);
	else if (l[0] == 'L' && (l[1] == ' ' || l[1] == '\t'))
		add_dif_light_parsing(pars, l);
	else if (l[0] == 'S' && (l[1] == ' ' || l[1] == '\t'))
		add_spec_light_parsing(pars, l);
	else if (line_is_empty(l) == 0)
		pars_error("Error: incorrect character(4)\n", pars, l);
}

void	parse_file(const char *filename, t_pars **pars)
{
	int		fd;
	char	*line;
	int		tmp;

	fd = open(filename, O_RDONLY);
	tmp = 0;
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while (tmp != 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parsing(pars, line);
		free(line);
	}
	close(fd);
}
