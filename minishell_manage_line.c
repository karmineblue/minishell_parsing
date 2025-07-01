/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_manage_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/06/26 18:10:32 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_spacing_sep(t_data *data, t_index *in, int type)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(data->line) + 3));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	j = -1;
	while (++j < in->i)
		new[j] = data->line[j];
	new[j++] = ' ';
	i = in->i;
	new[j++] = data->line[i++];
	if (type == 1)
		new[j++] = data->line[i++];
	new[j++] = ' ';
	while (data->line[i])
		new[j++] = data->line[i++];
	new[j] = '\0';
	ft_free(data->line);
	data->line = new;
	in->i = in->i + type + 1;
}

void	mini_space_sep(t_data *data, char *str, t_index *in)
{
	if (in->m == 0 && ((str[in->i] == '<' && str[in->i + 1] != '<')
			|| (str[in->i] == '>' && str[in->i + 1] != '>')
			|| str[in->i] == '|'))
		mini_spacing_sep(data, in, 0);
	else if (in->m == 0 && ((str[in->i] == '<' && str[in->i + 1] == '<')
			|| (str[in->i] == '>' && str[in->i + 1] == '>')))
		mini_spacing_sep(data, in, 1);
}

void	mini_check_line(t_data *data, char *s, t_index *in)
{
	if (in->m == 0
		&& (s[in->i] == '|' && s[in->i + 1] == '|'))
		ft_free(data->line);
	else if (in->m == 0 && s[in->i + 1] != 0
		&& ((s[in->i] == '<' && s[in->i + 1] == '<' && s[in->i + 2] == '<')
			|| (s[in->i] == '>' && s[in->i + 1] == '>' && s[in->i + 2] == '>')))
		ft_free(data->line);
}

void	mini_line_set(t_data *data)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	if (!data->line)
		return ;
	while (data->line != NULL
		&& (mini_isspace(data->line[in.i]) == 1 || data->line[in.i] == 0))
		if (data->line[in.i++] == 0)
			return (mini_invalid_line(data->line, NULL));
	//if (data->story)
	//	ft_free(data->story);
	//data->story = ft_strdup(data->line);
	//if (!data->story)
	//	mini_liberate_all(data, "malloc failure", 1);
	in.i = -1;
	while (data->line && data->line[++in.i])
	{
		mini_mode_switch(data->line, &in, 0);
		mini_check_line(data, data->line, &in);
	}
	if (data->line && data->line != NULL && in.m == 0)
		mini_line_sep(data);
	else
		mini_invalid_line(data->line, "invalid line");
}
