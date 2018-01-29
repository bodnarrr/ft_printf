/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <abodnar@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 16:15:00 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/29 15:18:12 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_replace_zeros(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup(str);
	while (*(res + i))
	{
		if (*(res + i) == -100)
			*(res + i) = 0;
		i++;
	}
	return (res);
}

char			*ft_take_clear(char **format, char **buff)
{
	size_t		i;
	char		*temp1;
	char		*temp2;

	i = 0;
	while (*(*format + i) != '%' && *(*format + i))
		i++;
	temp1 = (char*)malloc(sizeof(char) * (i + 1));
	temp1 = ft_memcpy(temp1, *format, i);
	temp1[i] = '\0';
	temp2 = *buff;
	*buff = ft_strjoin(*buff, temp1);
	ft_strdel(&temp1);
	ft_strdel(&temp2);
	*format += i;
	return (*buff);
}

char			*ft_take_current_arg(char **buff, t_params *params, va_list ap)
{
	char		*temp;
	char		*fordel;
	uint		for_uni;

	if (params->conv == 0)
		temp = ft_strnew(0);
	else if (params->conv == 'i' || params->conv == 'd')
		temp = ft_get_int(params, ap);
	else if (params->conv == 'D')
		temp = ft_get_longint(params, ap);
	else if (params->conv == 'o')
		temp = ft_get_octal(params, ap);
	else if (params->conv == 'O')
		temp = ft_get_longoctal(params, ap);
	else if (params->conv == 'x' || params->conv == 'X')
		temp = ft_get_hexadec(params, ap);
	else if (params->conv == 'u')
		temp = ft_get_unsign(params, ap);
	else if (params->conv == 'U')
		temp = ft_get_longunsign(params, ap);
	else if (params->conv == 'p')
		temp = ft_get_ptr(params, ap);
	else if (params->conv == 'C' || (params->conv == 'c' && params->len >= 4
		&& params->len < 8))
	{
		for_uni = va_arg(ap, uint);
		temp = ft_get_unichar(for_uni);
	}
	else if (params->conv == 'S' || (params->conv == 's' && params->len >= 4
		&& params->len < 8))
		temp = ft_get_unistr(ap);
	else if (params->conv == 'c' || params->conv == 's' || params->conv == '%')
		temp = ft_get_char_str_perc(&temp, params->conv, ap);
	ft_apply_precision(&temp, params);
	if (params->f_sharp)
		ft_apply_sharp(&temp, params);
	ft_apply_space(&temp, params);
	if (params->f_plus)
		ft_apply_plus(&temp, params);
	ft_apply_width(&temp, params);
	ft_apply_zero(&temp, params);
	fordel = *buff;
	*buff = ft_strjoin(*buff, temp);
	ft_strdel(&fordel);
	ft_strdel(&temp);
	return (*buff);
}

int				ft_print(va_list ap, char *format)
{
	char		*buff;
	t_params	params;
	char		*res;
	int			ret;

	if (!format)
		return (-1);
	buff = ft_strnew(0);
	while (*format)
	{
		ft_bzero(&params, sizeof(t_params));
		params.prec = -1;
		params.width = -1;
		buff = ft_take_clear(&format, &buff);
		if (*format && *format == '%')
		{
			format++;
			ft_parse_printf(&format, &params, ap);
		}
		if (params.conv)
			buff = ft_take_current_arg(&buff, &params, ap);
		else
			continue ;
	}
	res = ft_replace_zeros(buff);
	ret = (int)write(1, res, ft_strlen(buff));
	ft_strdel(&buff);
	ft_strdel(&res);
	return (ret);
}

int				ft_printf(char *format, ...)
{
	va_list	ap;
	int		res;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	res = ft_print(ap, format);
	va_end(ap);
	return (res);
}
