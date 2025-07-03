/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/06/30 18:00:19 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*mini_token_new(t_data *data, char **strs, int i)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		mini_liberate_all(data, "malloc failure", 1);
	new->str = ft_strdup(strs[i]);
	new->type = -1;
	if (!new->str)
		mini_liberate_all(data, "malloc failure", 1);
	new->next = NULL;
	return (new);
}

int	mini_token_assign(char *str, int prev_type)
{
	if (ft_strncmp(str, "|", 2) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (REDINFILE);
	else if (ft_strncmp(str, "<<", 3) == 0)
		return (REDHEREDOC);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (REDOUTFILE);
	else if (ft_strncmp(str, ">>", 3) == 0)
		return (REDAPPEND);
	else if (prev_type == REDINFILE)
		return (INFILE);
	else if (prev_type == REDHEREDOC)
		return (HEREDOC);
	else if (prev_type == REDOUTFILE)
		return (OUTFILE);
	else if (prev_type == REDAPPEND)
		return (APPEND);
	//else if (prev_type == PIPE || prev_type == INFILE || prev_type == HEREDOC)
	//	return (FONCTION);
	return (ARG);
}

void	mini_token_cleaning(t_data *data)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*cnext;

	cur = data->first;
	prev = NULL;
	while (cur)
	{
		cnext = cur->next;
		if (cur->type > 30)
		{
			if (cur == data->first && cnext)
				data->first = cnext;
			free(cur->str);
			free(cur);
			cur = cnext;
			if (prev)
				prev->next = cur;
		}
		prev = cur;
		if (cnext)
			cur = cur->next;
		else
			break ;
	}
}

void	mini_token_syntax(t_data *data)
{
	t_token	*cur;

	cur = data->first;
	while (cur)
	{
		if (!cur->next && (cur->type > 30 || cur->type == 2))
		{
			data->pipe = -1;
			return ;
		}
		if (cur->next && cur->type > 30 && cur->next->type > 30)
		{
			data->pipe = -1 * cur->next->type;
			data->error = 2;
			return ;
		}
		cur = cur->next;
	}
	mini_token_cleaning(data);
}

void	mini_tokenizer(t_data *data)
{
	t_token	*cur;
	int		i;
	int		prevtype;

	prevtype = 2;
	data->first = mini_token_new(data, data->ltab, 0);
	cur = data->first;
	cur->type = mini_token_assign(cur->str, prevtype);
	prevtype = cur->type;
	i = 0;
	while (data->ltab[++i])
	{
		cur->next = mini_token_new(data, data->ltab, i);
		cur = cur->next;
		cur->type = mini_token_assign(cur->str, prevtype);
		prevtype = cur->type;
	}
	mini_token_syntax(data);
}
