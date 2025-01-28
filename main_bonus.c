/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:42:10 by habdella          #+#    #+#             */
/*   Updated: 2025/01/27 09:14:32 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"

void	free_all(t_pipe *p)
{
	if (p->cmd)
		free_split(&p->cmd);
	if (p->paths)
		free_split(&p->paths);
	if (p->path)
		free(p->path);
	if (p)
		free(p);
}

int	which_bonus(t_pipe *p)
{
	if (!ft_strncmp("here_doc", p->av[1], 8))
	{
		if (p->ac != 6)
		{
			ft_printf("please enter the folowing structure:\n");
			ft_printf("./pipex here_doc LIMITER cmd cmd1 file\n");
			(free(p), exit(1));
		}
		p->av[2] = ft_stjoin(p->av[2], "\n");
		p->limiter = p->av[2];
		return (1);
	}
	return (0);
}

void	initialize(t_pipe *p, int ac, char **av, char **env)
{
	p->ac = ac;
	p->av = av;
	p->env = env;
	p->in_fd = 0;
	p->out_fd = 0;
	p->cmd = NULL;
	p->paths = NULL;
	p->path = 0;
	p->flag = 0;
}

int	main(int ac, char **av, char **env)
{
	t_pipe	*p;
	int		err_code;
	int		state;

	p = malloc(sizeof(t_pipe));
	if (!p || ac < 5)
		return (ft_printf("not enough args!\n"), free(p), 1);
	initialize(p, ac, av, env);
	if (which_bonus(p))
		first_bonus(p);
	else
		second_bonus(p);
	while (wait(&state) > 0)
		;
	if (state >> 8 == 1)
		return (free_all(p), 1);
	err_code = error_code(p);
	free_all(p);
	return (err_code);
}
