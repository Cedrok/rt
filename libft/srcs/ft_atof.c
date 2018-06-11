/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvautrai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 11:16:21 by cvautrai          #+#    #+#             */
/*   Updated: 2018/06/11 17:56:43 by cvautrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
static char		*remove_dot(const char *str)
{
	char				*new;
	int					i;
	int					j;
	size_t				len;

	len = ft_strlen(str);
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
	new[j] = '\0';
	return (new);
}

static int		search_dot(const char *str)
{
	int					i;
	int					b_dot;
	int					dot_pos;

	i = 0;
	b_dot = 0;
	dot_pos = 0;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	while (str[i] && (ft_isdigit(str[i]) || str[i] == '.'))
	{
		if (str[i] == '.')
			b_dot = 1;
		if (b_dot)
			dot_pos++;
		i++;
	}
	if (!b_dot)
		return (-1);
	else
		return (dot_pos - 1 > 6 ? 6 : dot_pos - 1);
}

static int		find_stop(const char *str)
{
	int					i;
	int					res;
	int					dec;

	i = 0;
	res = 0;
	dec = 0;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
		res++;
	}
	if (str[i] == '.')
		while (ft_isdigit(str[++i]))
			dec++;
	return (res + (dec > 6 ? 6 : dec));
}

static double	atod(const char *str, int stop)
{
	int					i;
	int					neg;
	unsigned long long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	stop += i - 1;
	while (ft_isdigit(str[i]) && i <= stop)
	{
		if (i < stop)
			res = res * 10 + str[i] - '0';
		else
			res = res * 10 + (str[i + 1] >= '5' ? str[i] + 1 : str[i]) - '0';
//		printf("%i / %i, res = %llu\n", i, stop, res);//
		i++;
	}
	return ((double)res * neg);
}

double			ft_atof(const char *str)
{
	int					i;
	int					dot_pos;
	char				*tmp;
	double				res;

	printf("_____\n");//
	printf("\'%s\' => atof: %f\n", str, atof(str));//
	i = 0;
	dot_pos = search_dot(str);
	if ((size_t)dot_pos == ft_strlen(str) || dot_pos == -1)
	{//
		printf("go to ft_atol\n");//
		return (ft_atol(str));
	}//
	tmp = remove_dot(str);
	res = atod(tmp, find_stop(str));
//	printf("tmp = %s, res = %f\n", tmp, res);//
	ft_strdel(&tmp);
	while (dot_pos && dot_pos > 0)
	{
		res = res * 0.1;
//		printf("-> %i, res = %f\n", dot_pos, res);//
		dot_pos--;
	}
	return (res);
}
