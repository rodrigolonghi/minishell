/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarneir <acarneir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 22:39:43 by rfelipe-          #+#    #+#             */
/*   Updated: 2022/06/24 00:30:34 by acarneir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_prompt(void)
{
	if (g_obj.input)
		free(g_obj.input);
	if (g_obj.envp)
		ft_free_matrix(g_obj.envp);
	rl_clear_history();
	exit(0);
}
