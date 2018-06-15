/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 09:19:23 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/15 09:24:12 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <sys/stat.h>

static char		*super_strjoin(char *str1, char *str2)
{
	char		*new;

	new = ft_strjoin(str1, str2);
	ft_strdel(&str1);
	ft_strdel(&str2);
	return (new);
}

static char		*build_name(char *title, int i)
{
	char		*str1;
	char		*str2;
	char		*str3;

	str1 = ft_strdup("screenshots/");
	str2 = ft_strdup(title);
	str3 = super_strjoin(str1, str2);
	str1 = ft_strdup("_");
	str2 = super_strjoin(str3, str1);
	str3 = ft_itoa(i);
	str1 = super_strjoin(str2, str3);
	str2 = ft_strdup(".png");
	str3 = super_strjoin(str1, str2);
	return (str3);
}

void			screenshot(t_all *param)
{
	static int	i = 1;
	char		*str;

	mkdir("screenshots", S_IRWXU | S_IRWXG | S_IRWXO);
	str = build_name(param->env->title, i);
	while (open(str, O_RDONLY) != -1)
	{
		i++;
		ft_strdel(&str);
		str = build_name(param->env->title, i);
	}
	put_filter(*param);
	IMG_SavePNG(param->env->s_filter, str);
	ft_strdel(&str);
	i++;
	ft_putendl("Screenshot saved");
}
