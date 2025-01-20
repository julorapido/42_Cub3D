/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalnum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:57:21 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/11 16:35:33 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isalnum(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
