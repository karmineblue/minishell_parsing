/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main_parsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:18:35 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/01 12:58:11 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_fonction_parse(t_token *cur)
{
	if (cur->type == FONCTION && ft_strncmp(cur->str, "echo", 5) == 0)
		printf("buil-tin: ");
	else if (cur->type == FONCTION && ft_strncmp(cur->str, "cd", 3) == 0)
		printf("buil-tin: ");
	else if (cur->type == FONCTION && ft_strncmp(cur->str, "pwd", 4) == 0)
		printf("buil-tin: ");
	else if (cur->type == FONCTION && ft_strncmp(cur->str, "export", 7) == 0)
		printf("buil-tin: ");
	else if (cur->type == FONCTION && ft_strncmp(cur->str, "unset", 6) == 0)
		printf("buil-tin: ");
	else if (cur->type == FONCTION && ft_strncmp(cur->str, "env", 4) == 0)
		printf("buil-tin: ");
	else if (cur->type == FONCTION && ft_strncmp(cur->str, "exit", 5) == 0)
		printf("buil-tin: ");
	else if (cur->type == FONCTION)
		printf("execve: ");
}

void	mini_print_envp(t_data *data)
{
	t_envlist	*cur;

	if (data->start && data->start->str != NULL)
	{
		cur = data->start;
		while (cur != NULL)
		{
			printf("%s\n", cur->str);
			cur = cur->next;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_token	*cur;

	(void)argv;
	if (argc > 1)
	{
		write(2, "Error : no argument please\n", 27);
		return (0);
	}
	ft_bzero(&data, sizeof(t_data));
	mini_get_envp(&data, envp);
	while (1)
	{
		data.line = readline("ask > ");
		if (data.line && data.line != NULL)
			mini_line_set(&data);
		if (data.end && data.end->str != NULL)
			printf("und = %s\n", data.end->str);
		if (data.first && data.first != NULL)
		{
			cur = data.first;
			while (cur)
			{
				mini_fonction_parse(cur);
				printf("%s (%d)\n", cur->str, cur->type);
				cur = cur->next;
			}
			if (ft_strncmp(data.first->str, "exit", 5) == 0)
			{
				mini_free_envlist(data.start);
				mini_free_token(data.first);
				exit (0);
			}
			else if (data.pipe == -1)
				printf("minishell: syntax error near unexpected token 'newline' error: %d\n", data.error);
			else if (data.pipe < -1)
				printf("minishell: syntax error near unexpected token '%d' error: %d\n", data.pipe, data.error);
			mini_free_token(data.first);
			data.first = NULL;
		}
	}
	return (0);
}
