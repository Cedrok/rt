/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:19:04 by tmilon            #+#    #+#             */
/*   Updated: 2017/11/21 09:17:52 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i] != '\0')
	{
		if (s2[i] == '\0')
			return (1);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
