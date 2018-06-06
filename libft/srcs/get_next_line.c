/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 10:09:45 by cpieri            #+#    #+#             */
/*   Updated: 2018/05/30 13:42:25 by cpieri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		cpy_to_line(char **save, char **line, char *chr)
{
	char	*tmp;

	if (chr != NULL)
	{
		*line = ft_strsub(*save, 0, chr - *save);
		tmp = *save;
		*save = ft_strsub(tmp, chr - tmp + 1, ft_strlen(tmp));
		ft_strdel(&tmp);
	}
	else
	{
		*line = ft_strdup(*save);
		ft_strdel(&*save);
	}
}

static void		cpy_in_read(char *buffer, char **save)
{
	char	*tmp;

	if (*save == NULL)
		*save = ft_strdup(buffer);
	else
	{
		tmp = *save;
		*save = ft_strjoin(tmp, buffer);
		ft_strdel(&tmp);
	}
}

static int		read_fd(int fd, char **save, char **line)
{
	char	buffer[BUFF_SIZE + 1];
	char	*chr;
	int		ret;

	while ((ret = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[ret] = '\0';
		cpy_in_read(buffer, save);
		chr = ft_strchr(*save, '\n');
		if (chr != NULL || ret < BUFF_SIZE)
		{
			cpy_to_line(save, line, chr);
			return (1);
		}
	}
	if (ret == 0 && *save != NULL && ft_strcmp(*save, "\0") != 0)
	{
		chr = ft_strchr(*save, '\n');
		cpy_to_line(save, line, chr);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*save = NULL;
	char			*tmp;

	tmp = NULL;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || read(fd, tmp, 0) == -1)
		return (-1);
	tmp = ft_strchr(save, '\n');
	if (tmp != NULL)
		cpy_to_line(&save, line, tmp);
	else
	{
		if (read_fd(fd, &save, line) == 0)
		{
			ft_strdel(&save);
			return (0);
		}
	}
	return (1);
}
