/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cleanline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/06/26 18:06:47 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_redirection_switch(char **str, t_index *in, int i)
{
	if (in->m == 0 && i > 0 && mini_redircheck(str[i]) == 0
		&& ft_strncmp("<<", str[i - 1], 2) == 0)
		in->h = 1;
	else if (in->m == 0 && i == 0 && mini_redircheck(str[i]) == 1)
		in->h = -1;
	else if (in->m == 0 && mini_redircheck(str[i]) > 0
		&& (!str[i + 1] || str[i + 1] == NULL))
		in->h = -1;
	else
		in->h = 0;
}

void	mini_clean_quote(char *str, int i)
{
	int	l;

	l = ft_strlen(str);
	while (i < l)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = 0;
}

void	mini_mode_switch(char *str, t_index *in, int type)
{
	if (in->m == 0 && str[in->i] == '"')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 2;
	}
	else if (in->m == 2 && str[in->i] == '"')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 0;
	}
	else if (in->m == 0 && str[in->i] == '\'')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 1;
	}
	else if (in->m == 1 && str[in->i] == '\'')
	{
		if (type == 1 && in->h == 0)
			mini_clean_quote(str, in->i--);
		in->m = 0;
	}
}

void	mini_clean_line(t_data *data, char *str, int pt)
{
	t_index	in;

	ft_bzero(&in, sizeof(t_index));
	//data->sptr = &str;
	//data->ind = i;
	//mini_redirection_switch(data->ltab, &in, i);
	while (str && str != NULL && str[in.i])
	{
		if (in.i >= 0 && in.m != 1 && in.h == 0 && str
			&& str[in.i] == '$'
			&& (ft_isalnum(str[in.i + 1]) == 1
			|| str[in.i + 1] == '?'
			|| str[in.i + 1] == '_')
            && pt != 4)
			in.i = mini_expand(data, str, in.i);
		mini_mode_switch(str, &in, 1);
		in.i++;
	}
}
