/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:25:11 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

void	expand_herdoc_data(char *str, int fd)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			tmp = key_value(str + i);
			len = key_len(str + i, 0);
			if (*tmp)
				write(fd, tmp, ft_strlen(tmp));
			i += len;
		}
		else
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

char	*here_doc_reader(char *str, bool mode, int i)
{
	char	*input;
	int		fds[2];

	if (mode)
		safe_pipe(fds);
	*process_status() = HERDOC_READ;
	input = ft_readline();
	while (1)
	{
		if (*process_status() == INTERRUPTED
			|| !input || !ft_strncmp(input, str, ft_strlen(input) + 1))
			break ;
		if (mode)
			here_doc_util(input, fds[1]);
		free(input);
		input = ft_readline();
	}
	if (mode)
	{
		close(fds[1]);
		util()->ports[i] = fds[0];
		return (ft_itoa(fds[0]));
	}
	return (NULL);
}

void	herdoc_job(void)
{
	int		i;
	t_data	*tmp;
	int		ind;

	ind = 0;
	tmp = *box();
	while (tmp)
	{
		i = 0;
		while (tmp->file.infile && tmp->file.infile[i])
		{
			if (tmp->file.i_type[i] == HERDOC && tmp->file.infile[i + 1])
				here_doc_reader(tmp->file.infile[i], false, ind);
			else if (tmp->file.i_type[i] == HERDOC)
			{
				replace_fd(tmp,
					here_doc_reader(tmp->file.infile[i], true, ind), i);
				ind++;
			}
			if (*process_status() == INTERRUPTED)
				return (close_herdoc_ports());
			i++;
		}
		tmp = tmp->next;
	}
}
