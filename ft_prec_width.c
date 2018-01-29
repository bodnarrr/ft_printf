/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:15:15 by abodnar           #+#    #+#             */
/*   Updated: 2018/01/17 16:15:16 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_apply_precision(char **temp, t_params *params)
{
	char	*zrs;
	char	*fordel;
	int		adding;

	if (params->dot && params->conv != 'c' && params->conv != 's'
		&& params->conv != '%' && params->conv != 'S')
		params->f_zero = 0;
	if ((params->conv == 'd' || params->conv == 'D' || params->conv == 'i' ||
		params->conv == 'o' || params->conv == 'O' || params->conv == 'u' ||
		params->conv == 'U' || params->conv == 'x' || params->conv == 'X' ||
		params->conv == 'p' || params->conv == 'S') && params->dot
		&& **temp != '-')
	{
		if (params->prec > (int)ft_strlen(*temp))
		{
			adding = params->prec - ft_strlen(*temp);
			if ((params->conv == 'o' || params->conv == 'O') && params->f_sharp)
				adding--;
			zrs = ft_strnew(adding);
			zrs = ft_memset(zrs, '0', adding);
			fordel = *temp;
			*temp = ft_strjoin(zrs, *temp);
			ft_strdel(&zrs);
			ft_strdel(&fordel);
		}
		if ((params->prec == 0 && params->conv != 'p' && !ft_strcmp(*temp, "0"))
			|| (params->prec == 0 && params->conv == 'S'))
		{
			fordel = *temp;
			*temp = ft_strdup("");
			ft_strdel(&fordel);
		}
	}
	else if ((params->conv == 'd' || params->conv == 'D' || params->conv == 'i'
			|| params->conv == 'o' || params->conv == 'O' || params->conv == 'u'
			|| params->conv == 'U' || params->conv == 'x' || params->conv == 'X'
			|| params->conv == 'p') && params->dot && **temp == '-'
			&& params->prec > (int)ft_strlen(*temp) - 1)
	{
		adding = params->prec - ft_strlen(*temp) + 1;
		zrs = ft_strnew(adding);
		zrs = ft_memset(zrs, '0', adding);
		fordel = *temp;
		*temp = ft_strjoin(zrs, *temp + 1);
		ft_strdel(&zrs);
		ft_strdel(&fordel);
		fordel = *temp;
		*temp = ft_strjoin("-", *temp);
		ft_strdel(&fordel);
	}
	else if (params->conv == 's' && params->dot &&
		params->prec < (int)ft_strlen(*temp))
	{
		zrs = ft_strnew(params->prec);
		zrs = ft_memcpy(zrs, *temp, params->prec);
		fordel = *temp;
		*temp = ft_strdup(zrs);
		ft_strdel(&zrs);
		ft_strdel(&fordel);
	}
}

void		ft_apply_width(char **temp, t_params *params)
{
	char	*spc;
	char	*fordel;
	int		wd;

	if ((params->conv == 'd' || params->conv == 'D' || params->conv == 'i'
		|| params->conv == 'o' || params->conv == 'O' || params->conv == 'u'
		|| params->conv == 'U' || params->conv == 'x' || params->conv == 'X'
		|| params->conv == 'p' || params->conv == 's' || params->conv == '%'
		|| params->conv == 'c' || params->conv == 'S')
		&& params->width > (int)ft_strlen(*temp))
	{
		wd = params->width - (int)ft_strlen(*temp);
		if (params->f_sharp && params->f_zero)
			wd -= 2;
		spc = ft_strnew(wd);
		spc = ft_memset(spc, ' ', wd);
		fordel = *temp;
		if (params->f_min)
			*temp = ft_strjoin(*temp, spc);
		else
			*temp = ft_strjoin(spc, *temp);
		ft_strdel(&spc);
		ft_strdel(&fordel);
	}
}
