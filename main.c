/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:15 by habdella          #+#    #+#             */
/*   Updated: 2025/01/24 11:12:14 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

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
	p = NULL;
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
	initialize(p, ac, av, env);
	if (!p || ac != 5)
		puterror(p);
	set_up(p);
	while (wait(&state) > 0)
		;
	if (state >> 8 == 1)
		return (free_all(p), 1);
	err_code = error_code(p);
	free_all(p);
	return (err_code);
}
