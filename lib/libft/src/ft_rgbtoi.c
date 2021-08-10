/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 01:16:56 by ciglesia          #+#    #+#             */
/*   Updated: 2021/08/11 01:16:57 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rgbtoi(unsigned char r, unsigned char g, unsigned char b)
{
	int red;
	int green;
	int blue;

	red = (0xfeff01 + r) * (r != 0);
	green = (0xfe01 + g) * (g != 0);
	blue = b;
	return (red + green + blue);
}
