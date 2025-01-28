/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:22:21 by habdella          #+#    #+#             */
/*   Updated: 2025/01/24 11:12:03 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	close_all(t_pipe *p)
{
	close(p->fds[0]);
	close(p->fds[1]);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == 0)
		return ((char *)(s + i));
	return (NULL);
}

void	puterror(t_pipe *p)
{
	ft_printf("Enter: <file1> <cmd1> <cmd2> <file2>\n");
	free_all(p);
	exit(1);
}

int	error_code(t_pipe *p)
{
	char	*path;

	path = NULL;
	if (access(p->av[p->ac - 1], F_OK) == 0)
	{
		if (access(p->av[p->ac - 1], W_OK) == -1)
			return (1);
	}
	p->cmd = ft_split(p->av[p->ac - 2], ' ');
	if (p->cmd)
		path = command_check(p, p->cmd[0]);
	if (!p->cmd)
		return (0);
	if (path == NULL)
		return (127);
	return (0);
}
