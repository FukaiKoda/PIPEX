/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:16:15 by habdella          #+#    #+#             */
/*   Updated: 2025/01/27 09:13:38 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_BONUS_H
# define PIPE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define BUFFER_SIZE 1337

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
	char	*limiter;
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
char	*command_check(t_pipe *p, char *cmd);
/*----------------- GNL functions ------------------*/
char	*get_container(char *contain, char *buff, int fd);
char	*ft_stjoin(const char *s1, const char *s2);
char	*f_strchr(const char *s, char c);
char	*ft_strdupnl(char *contain);
char	*ft_strdup(const char *s);
char	*update(char *contain);
char	*get_next_line(int fd, int flag);
/*--------------- Bonus functions 1 ---------------*/
void	first_bonus(t_pipe *p);
void	fill_the_file(t_pipe *p);
int		which_bonus(t_pipe *p);
/*--------------- Bonus functions 2 ---------------*/
void	second_bonus(t_pipe *p);
void	close_all(t_pipe *p);
int		error_code(t_pipe *p);

#endif