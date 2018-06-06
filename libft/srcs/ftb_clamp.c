/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftb_clamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmilon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:54:13 by tmilon            #+#    #+#             */
/*   Updated: 2017/11/30 17:55:29 by tmilon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ftb_clamp(int toclamp, int min, int max)
{
	if (toclamp > max || toclamp < min)
		return (toclamp > max ? max : min);
	return (toclamp);
}
