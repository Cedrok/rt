/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 11:16:21 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/08 13:34:01 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*remove_dot(const char *str)
{
	char	*new;
	int		i;
	int		j;
	size_t	len;

	len = ft_strlen(str) - 1;
	new = (char*)malloc(sizeof(char) * len);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '.')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (new);
}

static size_t	search_dot(const char *str)
{
	int		i;

	i = 0;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		return (i);
	else
		return (0);
}

double			ft_atof(const char *str)
{
	int		i;
	size_t	dot_pos;
	char	*tmp;
	double	res;

	if (!ft_strchr(str, '.'))
		return (ft_atoi(str));
	i = 0;
	dot_pos = search_dot(str);
	if (dot_pos == ft_strlen(str))
		dot_pos = 0;
	tmp = remove_dot(str);
	res = ft_atoi(tmp);
	ft_strdel(&tmp);
	if (dot_pos && res < 0)
		dot_pos--;
	while (dot_pos && --dot_pos > 0)
		res = res * 0.1;
	return (res);
}
