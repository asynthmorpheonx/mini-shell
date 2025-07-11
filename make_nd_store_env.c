/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_nd_store_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:00 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

void	set_path(void)
{
	char	*path;
	t_env	*tmp;

	path = key_value("PATH");
	if (!*path)
	{
		tmp = safe_alloc(sizeof(t_env), 0);
		if (!tmp)
			ult_exit();
		tmp->key = safe_substr("PATH", 0, 4);
		tmp->value = safe_substr(DFLPATH, 0, 61);
		add_to_envp(envp(), tmp);
	}
}

t_env	*last_env(t_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_to_envp(t_env **lst, t_env *tmp)
{
	if (!*lst)
		*lst = tmp;
	else
		last_env(*lst)->next = tmp;
}

void	make_env(char **env, t_env **lst, int i, int j)
{
	int		toggle;
	t_env	*tmp;

	while (env[i])
	{
		j = 0;
		toggle = 1;
		tmp = safe_alloc(sizeof(t_env), 0);
		if (!tmp)
			exit (EXIT_FAILURE);
		while (env[i][j])
		{
			if (env[i][j] == '=' && toggle)
			{
				tmp->key = safe_substr(env[i], 0, j);
				tmp->value = safe_substr
					(env[i], j + 1, ft_strlen(env[i] + j + 1));
				toggle = 0;
			}
			j++;
		}
		add_to_envp(lst, tmp);
		i++;
	}
	set_path();
}
