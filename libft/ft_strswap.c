/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 20:51:40 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:20:17 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strswap(char **str1, char **str2)
{
	char *temp;

	if (str1 == NULL || str2 == NULL)
		return ;
	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}