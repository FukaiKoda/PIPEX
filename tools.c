/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:54:57 by habdella          #+#    #+#             */
/*   Updated: 2025/01/25 15:20:37 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	handle_commands(t_pipe *p, int index)
{
	p->cmd = ft_split(p->av[index], ' ');
	if (p->cmd)
		p->path = command_check(p, p->cmd[0]);
	if (!p->cmd)
		return ;
	if (!p->path)
		ft_printf("command not found: %s\n", p->av[index]);
}

void	handle_out_fd(t_pipe *p)
{
	if (access(p->av[p->ac - 1], F_OK) == 0)
	{
		if (access(p->av[p->ac - 1], W_OK) == -1)
		{
			ft_printf("permission denied: %s\n", p->av[p->ac - 1]);
			free(p);
			exit(1);
		}
	}
	p->out_fd = open(p->av[p->ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

void	child_process(t_pipe *p, int index, int flag)
{
	if (flag == 0)
		dup2(p->fds[1], 1);
	else
	{
		handle_out_fd(p);
		dup2(p->out_fd, 1);
		close(p->out_fd);
	}
	close_all(p);
	handle_commands(p, index);
	if (p->flag == 2 || !p->cmd)
		(free_all(p), exit(0));
	execve(p->path, p->cmd, p->env);
}

int	handle_in_fd(t_pipe *p)
{
	if (access(p->av[1], F_OK) == -1)
	{
		p->in_fd = open("/dev/null", O_RDONLY);
		ft_printf("no such file or directory: %s\n", p->av[1]);
		return (2);
	}
	else if (access(p->av[1], R_OK) == -1)
	{
		p->in_fd = open("/dev/null", O_RDONLY);
		ft_printf("permission denied: %s\n", p->av[1]);
		return (2);
	}
	else
		p->in_fd = open(p->av[1], O_RDONLY);
	return (1);
}

void	set_up(t_pipe *p)
{
	pid_t	pid;
	int		i;
	int		flag;

	flag = 0;
	i = handle_in_fd(p);
	dup2(p->in_fd, 0);
	close(p->in_fd);
	while (i <= 2)
	{
		pipe(p->fds);
		pid = fork();
		if (i == 2)
			flag = 1;
		if (pid == 0)
			child_process(p, i + 1, flag);
		dup2(p->fds[0], 0);
		close_all(p);
		i++;
	}
}
