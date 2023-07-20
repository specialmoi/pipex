/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthiruma <pthiruma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:39:16 by pthiruma          #+#    #+#             */
/*   Updated: 2023/06/23 08:08:52 by pthiruma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	*ptr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	k = ft_strlen(s);
	i = 0;
	j = 0;
	if (start > k)
		return (ft_strdup(""));
	if (len > (k - start))
		ptr = (unsigned char *)malloc(((k - start + 1)) * sizeof(char));
	else
		(ptr = (unsigned char *)malloc((len + 1) * sizeof(char)));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			ptr[j++] = s[i];
		i++;
	}
	ptr[j] = '\0';
	return ((char *) ptr);
}

static int	ft_countwords(char const *s, char c)
{
	int		elem;
	int		i;
	int		on;

	i = 0;
	elem = 0;
	on = 0;
	while (s[i])
	{
		if (s[i] != c && on == 0)
		{
			on = 1;
			elem++;
		}
		if (s[i] == c && on == 1)
			on = 0;
		i++;
	}
	return (elem);
}

char	**ft_split(char const *s, char c)
{
	char	**pptr;
	int		i;
	int		j;
	int		k;

	pptr = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!pptr)
		return (NULL);
	i = 0;
	k = 0;
	while (k < ft_countwords(s, c))
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			j++;
		}
		pptr[k++] = ft_substr(&s[i - j], 0, j);
	}
	pptr[k] = 0;
	return (pptr);
}
