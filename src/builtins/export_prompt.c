/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfelipe- <rfelipe-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:15:19 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/06/18 01:21:52 by rfelipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	define_var(t_data *obj, char *var)
{
	int		i;
	int		len;
	char	**aux;

	len = 0;
	while (obj->envp[len])
		len++;
	aux = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (i < len)
	{
		aux[i] = ft_strdup(obj->envp[i]);
		i++;
	}
	aux[i] = ft_strdup(var);
	ft_free_matrix(obj->envp);
	obj->envp = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (i < (len + 1))
	{
		obj->envp[i] = ft_strdup(aux[i]);
		i++;
	}
	ft_free_matrix(aux);
}

static void	update_var(t_data *obj, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_chrpos(var, '=');
	while (obj->envp[i])
	{
		if (ft_memcmp(var, obj->envp[i], len) == 0 && obj->envp[i][len] == '=')
		{
			free(obj->envp[i]);
			obj->envp[i] = ft_strdup(var);
			break ;
		}
		i++;
	}
}

static int	already_has_env_var(t_data *obj, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_chrpos(var, '=');
	while (obj->envp[i])
	{
		if (ft_memcmp(var, obj->envp[i], len) == 0 && obj->envp[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	is_valid_attribution(char *arg, char *next)
{
	int	i;
	int	j;

	i = 0;
	j = ft_chrpos(arg, '=');
	if (j == -1)
		return (0);
	while (i < j)
	{
		if (!(ft_isalpha(arg[i]) || ft_isdigit(arg[i]))
			|| ft_is_all_digit(arg, j))
		{
			printf("export '%s': not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	if (!arg[j + 1] && next)
	{
		printf("export '%s': not a valid identifier\n", next);
		return (-1);
	}
	return (1);
}

int	export_prompt(t_data *obj, char **args)
{
	int		i;
	int		j;
	char	*temp;

	i = 1;
	while (args[i])
	{
		temp = ft_strtrim(args[i], " \t");
		j = is_valid_attribution(temp, args[i + 1]);
		if (j == 1 || j == -1)
		{
			if (already_has_env_var(obj, temp))
				update_var(obj, temp);
			else
				define_var(obj, temp);
			if (j == -1)
				i++;
		}
		free(temp);
		i++;
	}
	return (1);
}