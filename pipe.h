/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:21:55 by habdella          #+#    #+#             */
/*   Updated: 2025/01/27 08:59:01 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipe
{
	int		in_fd;
	int		out_fd;
	int		fds[2];
	int		flag;
	int		ac;
	char	**av;
	char	**env;
	char	**cmd;
	char	**paths;
	char	*path;

}	t_pipe;

/*------------------- initialize ------------------- */
void	free_all(t_pipe *p);
void	puterror(t_pipe *p);
void	initialize(t_pipe *p, int ac, char **av, char **env);
/*------------------- helpers -------------------*/
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_printf(const char *format, ...);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
void	free_split(char ***p);
/*------------------- commands ------------------*/
void	handle_commands(t_pipe *p, int index);
char	*command_check(t_pipe *p, char *cmd);
/*------------------- executes -------------------*/
void	set_up(t_pipe *p);
void	close_all(t_pipe *p);
int		error_code(t_pipe *p);

#endif
