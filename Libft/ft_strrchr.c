/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:18:46 by julessainth       #+#    #+#             */
/*   Updated: 2024/05/27 11:37:34 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (s[i] == '\0' && (unsigned char)c == '\0')
		return ((char *) &(s[i]));
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *) &(s[i]));
		i--;
	}
	return (NULL);
}
