/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 23:27:40 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/05/16 22:48:43 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path(char *command, char **envp)
{
	char	**env_path;
	char	*temp_path;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	env_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (env_path[i])
	{
		temp_path = ft_strjoin(env_path[i], "/");
		path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

static int	check_envp(t_data *obj, char **args)
{
	int	fd[2];
	int	pid;
	int	response;

	response = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
		response = execve(get_path(args[0], obj->envp), args, obj->envp);
	waitpid(pid, NULL, 0);
	close(fd[0]);
	close(fd[1]);
	if (response == -1)
		return (0);
	return (1);
}

static int	check_builtin(t_data *obj, char **args)
{
	if (ft_memcmp(args[0], "exit", ft_strlen(args[0])) == 0)
		exit_prompt(obj);
	if (ft_memcmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (pwd_prompt());
	return (0);
}

void	check_input(t_data *obj)
{
	char	**args;

	args = tokenizer(obj);
	if (args && !check_builtin(obj, args))
	{
		if (get_path(args[0], obj->envp))
		{
			if (!check_envp(obj, args))
				printf("Error -> Command not found: %s\n", obj->input);
				//ver no futuro
		}
		else
			printf("Command not found: %s\n", obj->input);
	}
}