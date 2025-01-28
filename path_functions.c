/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:41 by habdella          #+#    #+#             */
/*   Updated: 2025/01/22 10:08:07 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	size_t	len;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(len + 2);
	if (!p)
		return (NULL);
	(1) && (i = 0, j = 0);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i++] = '/';
	while (s2[j])
	{
		p[i++] = s2[j];
		j++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (n == i)
		return (0);
	return (s1[i] - s2[i]);
}

char	*command_check(t_pipe *p, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (p->env[i])
	{
		if (!ft_strncmp("PATH=", p->env[i], 5))
		{
			p->paths = ft_split(&p->env[i][5], ':');
			break ;
		}
		i++;
	}
	i = 0;
	while (p->paths[i])
	{
		tmp = p->paths[i];
		p->paths[i] = ft_strjoin(p->paths[i], cmd);
		free(tmp);
		if (access(p->paths[i], X_OK) != -1)
			return (p->paths[i]);
		i++;
	}
	(1) && (free_split(&p->paths), p->flag = 2);
	return (NULL);
}
