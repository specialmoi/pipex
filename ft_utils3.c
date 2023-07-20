/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthiruma <pthiruma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 08:08:56 by pthiruma          #+#    #+#             */
/*   Updated: 2023/06/23 10:41:11 by pthiruma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (n - 1) && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	i = 0;
	len = ft_strlen(s) + 1;
	ptr = (char *)malloc(sizeof(char) * len);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = *((unsigned char *)(s + i));
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
