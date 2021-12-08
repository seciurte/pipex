/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seciurte <seciurte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 01:45:52 by seciurte          #+#    #+#             */
/*   Updated: 2021/11/26 16:28:31 by seciurte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	while (*env != NULL && ft_strncmp("PATH", *env, 4) != 0)
		++env;
	if (ft_strncmp("PATH", *env, 4) != 0)
		return (NULL);
	return (ft_split(&env[0][5], ':'));
}

char	***get_cmds(char **av)
{
	int		i;
	char	***cmds;

	i = 2;
	while (av[i + 1] != NULL)
		++i;
	cmds = malloc(sizeof(char **) * (i - 1));
	if (cmds == NULL)
		return (NULL);
	cmds[i - 2] = NULL;
	while (--i - 1 > 0)
	{
		cmds[i - 2] = ft_split(av[i], ' ');
		if (cmds == NULL)
			return (NULL);
	}
	return (cmds);
}

char	*find_cmd_path(t_pipex *p, int c)
{
	int		i;
	char	*cmd;
	char	*tmp;

	i = 0;
	if (access(p->cmds[c][0], X_OK) == 0)
		return (p->cmds[c][0]);
	while (p->path[i])
	{
		tmp = ft_strjoin(p->path[i], "/");
		if (tmp == NULL)
			return (NULL);
		cmd = ft_strjoin(tmp, p->cmds[c][0]);
		free(tmp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			free(cmd);
		++i;
	}
	handle_cmd_not_found(p, c);
	return (NULL);
}
