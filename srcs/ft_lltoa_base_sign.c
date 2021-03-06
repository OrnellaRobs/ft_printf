/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafin <orazafin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 19:29:01 by orazafin          #+#    #+#             */
/*   Updated: 2017/06/06 19:39:39 by orazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int		ft_get_size_for_malloc(long long value, int base)
{
	int total_number;

	total_number = 0;
	while (value != 0)
	{
		total_number++;
		value = value / base;
	}
	return (total_number);
}

static int		turn_negative_to_positive(int number)
{
	if (number < 0)
		return (0 - number);
	return (number);
}

char			*ft_lltoa_base_sign(long long value, int base, int sign)
{
	char	*tab;
	int		total_number;
	int		negatif;

	if (base < 2 || base > 16)
		return (NULL);
	else if (base == 10 && sign == 0)
		return (ft_itoa((int)value));
	if (value == 0)
		return (ft_strdup("0"));
	negatif = (value < 0) ? 1 : 0;
	total_number = ft_get_size_for_malloc(value, base) + negatif;
	if (!(tab = malloc(sizeof(char) * (total_number + 1))))
		return (NULL);
	tab[total_number--] = '\0';
	while (total_number >= negatif)
	{
		tab[total_number] = (char)(turn_negative_to_positive(value % 10) + '0');
		total_number--;
		value = value / base;
	}
	if (negatif == 1)
		tab[total_number] = '-';
	return (tab);
}
