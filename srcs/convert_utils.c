/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:15:54 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/11 11:55:11 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	get_digit(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	result;
	int	base_len;
	int	digit;
	int	i;

	if (!str || !base)
		return (0);
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		str += 2;
	result = 0;
	base_len = ft_strlen(base);
	i = 0;
	while (str[i])
	{
		digit = get_digit(str[i], base);
		if (digit == -1)
			break ;
		result = result * base_len + digit;
		i++;
	}
	return (result);
}
