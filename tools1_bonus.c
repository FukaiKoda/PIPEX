/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:22:12 by habdella          #+#    #+#             */
/*   Updated: 2025/01/27 09:14:17 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

static void	handle_commands(t_pipe *p, int index)
{
	p->cmd = ft_split(p->av[index], ' ');
	if (p->cmd)
		p->path = command_check(p, p->cmd[0]);
	if (!p->cmd)
		return ;
	if (!p->path)
		ft_printf("command not found: %s\n", p->av[index]);
}

static void	handle_out_fd(t_pipe *p)
{
	if (access(p->av[5], F_OK) == 0)
	{
		if (access(p->av[5], W_OK) == -1)
		{
			ft_printf("permission denied: %s\n", p->av[5]);
			free(p);
			exit(1);
		}
	}
	p->out_fd = open(p->av[5], O_CREAT | O_WRONLY | O_APPEND, 0644);
}

static void	child_process(t_pipe *p, int index, int flag)
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
		(free(p->av[2]), free_all(p), exit(0));
	execve(p->path, p->cmd, p->env);
}

void	fill_the_file(t_pipe *p)
{
	char	*line;
	int		fake[2];
	int		flag;

	pipe(fake);
	flag = 0;
	ft_printf("heredoc> ");
	line = get_next_line(0, flag);
	while (line != NULL)
	{
		if (!ft_strncmp(line, p->limiter, ft_strlen(p->limiter)))
			flag = 1;
		if (!flag)
		{
			ft_printf("heredoc> ");
			write(fake[1], line, ft_strlen(line));
		}
		free(line);
		line = get_next_line(0, flag);
	}
	free(line);
	line = NULL;
	dup2(fake[0], 0);
	close(fake[0]);
	close(fake[1]);
}

void	first_bonus(t_pipe *p)
{
	pid_t	pid;
	int		i;
	int		flag;

	flag = 0;
	i = 2;
	fill_the_file(p);
	while (i <= 3)
	{
		pipe(p->fds);
		pid = fork();
		if (i == 3)
			flag = 1;
		if (pid == 0)
			child_process(p, i + 1, flag);
		dup2(p->fds[0], 0);
		close_all(p);
		i++;
	}
	free(p->av[2]);
}
