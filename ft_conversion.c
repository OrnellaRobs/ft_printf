/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafin <orazafin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:46:22 by orazafin          #+#    #+#             */
/*   Updated: 2017/05/14 08:01:13 by orazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*reminder : # define STR_CONVERSION "sSpcC%dDioOuUxX" */
/* FLAG 0 à gérer pour la conversion de CHAR (undefined behavior)*/
/* FLAG space à gérer pour la conversion des HEXA (undefined behavior) */
/* CE QU'IL RESTE A GÉRER : S, D, O, U, C*/

char	*ft_get_tab_unsigned(t_option *option, char *format, long long nb, char *tab)
{
	int		base;
	int		upper_case;

	if (*format == 'o' || *format == 'O')
		base = 8;
	else if (*format == 'x' || *format == 'X')
		base = 16;
	else
		base = 10;
	upper_case = (*format == 'X') ? 1 : 0;
	if (option->modifier == 'm')
		tab = ft_lltoa_base_unsigned((unsigned long long)nb, base, upper_case, 1);
	else if (option->modifier == 'l')
		tab = ft_lltoa_base_unsigned((unsigned long)nb, base, upper_case, 1);
	else if (option->modifier == 'i')
		tab = ft_lltoa_base_unsigned((unsigned char)nb, base, upper_case, 1);
	else if (option->modifier == 'h')
		tab = ft_lltoa_base_unsigned((unsigned short)nb, base, upper_case, 1);
	else if (option->modifier == 'z')
		tab = ft_lltoa_base_unsigned((size_t)nb, base, upper_case, 1);
	else if (option->modifier == 'j')
		tab = ft_lltoa_base_unsigned((uintmax_t)nb, base,upper_case, 1);
	else if (*format == 'u' || *format == 'U')
		tab = ft_itoa_base_printf((unsigned int)nb, 10, upper_case, 1);
	else if (*format == 'x' || *format == 'X')
		tab = ft_itoa_base_printf((unsigned int)nb, 16, upper_case, 1);
	else if (*format == 'o' || *format == 'O')
		tab = ft_itoa_base_printf((unsigned int)nb, 8, upper_case, 1);
	return (tab);
}

char	*ft_get_tab_int(t_option *option, char *format, long long nb, char *tab)
{
	int base;

	base = 10;
	if (*format == 'D' || *format == 'O' || *format == 'U')
		option->modifier = 'l';
	if (*format != 'd' && *format != 'i' && *format != 'D')
		return (ft_get_tab_unsigned(option, format, nb, tab));
	if (option->modifier == 'm')
		tab = ft_lltoa_base_sign((long long)nb, base, 0, 1);
	else if (option->modifier == 'l')
	{
		tab = ft_lltoa_base_sign((long)nb, base, 0, 1);
		if (tab == NULL)
			printf("\ntab = %s\n", tab);
	}
	else if (option->modifier == 'i')
		tab = ft_lltoa_base_sign((signed char)nb, base, 0, 1);
	else if (option->modifier == 'h')
		tab = ft_lltoa_base_sign((short)nb, base, 0, 1);
	else if (option->modifier == 'z')
		tab = ft_lltoa_base_sign((size_t)nb, base, 0, 1);
	else if (option->modifier == 'j')
		tab = ft_lltoa_base_sign((intmax_t)nb, base, 0, 1);
	else
		tab = ft_itoa_base_printf((unsigned int)nb, base, 0, 0);
	return (tab);
}
/*sSpcC%dDioOuUxX*/

int		ft_convert_all_int(t_option *option, char *format, long long nb)
{
	char *tab;
	int result;

	result = 0;
	tab = ft_get_tab_int(option, format, nb, tab);
	if (*format == 'x' || *format == 'X')
		result += ft_convert_hexa(option, tab, format);
	else if (*format == 'o' || *format == 'O')
		result += ft_convert_octal(option, tab);
	else if (*format == 'd' || *format == 'i' || *format == 'D')
		result += ft_conv_int(option, tab);
	else if (*format == 'u' || *format == 'U')
		result += ft_conv_unsigned_int(option, tab);
	return (result);
}

int		conversion(char *format, t_option *option, va_list lst)
{
	int	i;
	int	(*convert[5])(va_list, t_option *);
	char *tab;
	i = 0;
	convert[0] = &ft_conv_string;
	// convert[1] = &ft_convert_S;
	convert[2] = &ft_conv_pointer;
	convert[3] = ft_conv_char;
	// convert[5] = ft_convert_C;
	while (STR_CONVERSION[i])
	{
		if (i < 5 && STR_CONVERSION[i] == *format)
			return (convert[i](lst, option));
		else if (*format == '%')
			return (ft_percent(option));
		else if (i >= 6 && STR_CONVERSION[i] == *format)
			return (ft_convert_all_int(option, format, va_arg(lst, long long)));
		i++;
	}
	return (0);
}
