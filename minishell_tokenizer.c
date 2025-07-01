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

int	mini_token_assign(char *str, int pt)
{
	if (ft_strncmp(str, "|", 5) == 0)
		return (2);
	else if (ft_strncmp(str, "<", 5) == 0)
		return (31);
	else if (ft_strncmp(str, "<<", 5) == 0)
		return (41);
	else if (ft_strncmp(str, ">", 5) == 0)
		return (51);
	else if (ft_strncmp(str, ">>", 5) == 0)
		return (61);
	else if (pt == 31)
		return (3);
	else if (pt == 41)
		return (4);
	else if (pt == 51)
		return (5);
	else if (pt == 61)
		return (6);
	else if (pt == 2 || pt == 3 || pt == 4)
		return (1);
	return (0);
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
		/*if (cur->type > 4 && cur->next != NULL && cur->next->type == 0)
		{
			cur->next = cnext->next;
			cnext->next = cur;
			prev->next = cnext;
		}*/
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
		if (cur->next && cur->type > 30 && cur->next->type > 30)
			mini_liberate_all(data, "unexpected token", 0);
		cur = cur->next;
	}
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
	mini_token_cleaning(data);
}
