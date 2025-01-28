/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:22:47 by habdella          #+#    #+#             */
/*   Updated: 2025/01/11 14:22:49 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		flag = 1;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (flag)
				count++;
			flag = 0;
			i++;
		}
	}
	return (count);
}

static int	ft_len(const char *s, int i, char c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static char	*ft_strduplen(char *s, int len)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	free_split(char ***p)
{
	int	i;

	i = 0;
	if (!p || !*p || !**p)
		return ;
	while ((*p)[i])
	{
		free((*p)[i]);
		(*p)[i] = NULL;
		i++;
	}
	free(*p);
	*p = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**p;
	int		k;
	int		i;

	if (!s || count_words(s, c) == 0)
		return (NULL);
	p = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!p)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			p[k++] = ft_strduplen(&s[i], ft_len(s, i, c));
			i += ft_len(s, i, c);
		}
	}
	p[k] = NULL;
	return (p);
}
