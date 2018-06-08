/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:41:51 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/08 13:34:17 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**      Extract text between quotes from a line
*/

char		*extract_text(char *line)
{
	size_t		i;
	int			j;
	size_t		len;
	char		*new;

	len = ft_strlen(line);
	i = 0;
	while (line[i] != '"' && i < len - 1)
		i++;
	i++;
	new = (char*)malloc(sizeof(char) * len - i + 1);
	j = 0;
	while (line[i] != '"' && i < len - 1)
	{
		new[j] = line[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

/*
**      Extract a vd3 {x, y, z} from a line
*/

t_vector3d	extract_vd3(char *line)
{
	t_vector3d	new;
	size_t		i;
	size_t		len;

	len = ft_strlen(line);
	i = 0;
	while (line[i] != '{' && i < len - 1)
		i++;
	i++;
	new.x = ft_atof(line + i);
//	printf("\'%s\' => x = %f\n", line + i, new.x);
	while (line[i] != ',' && i < len - 1)
		i++;
	i++;
	new.y = ft_atof(line + i);
//	printf("\'%s\' => y = %f\n", line + i, new.y);
	while (line[i] != ',' && i < len - 1)
		i++;
	i++;
	new.z = ft_atof(line + i);
//	printf("\'%s\' => z = %f\n", line + i, new.z);
	return (new);
}

/*
**	custom gnl : stop at the given lines
*/

int			rt_get_next_line(int fd, char **line)
{
	int			res;

	res = get_next_line(fd, line);
	if (!ft_strcmp(*line, "##END##") || !ft_strcmp(*line, "# Scene information")
			|| !ft_strcmp(*line, "# Objects") || !ft_strcmp(*line, "# Lights"))
		return (0);
	return (res);
}
