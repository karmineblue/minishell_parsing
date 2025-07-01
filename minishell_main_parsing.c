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

void	mini_fonction_parse(t_data *data)
{
	t_token	*cur;

	cur = data->first;
	if (cur->type == 1 && ft_strncmp(cur->str, "echo", 5) == 0)
		printf("(buil-tin : exit)");
	else if (cur->type == 1 && ft_strncmp(cur->str, "cd", 5) == 0)
		printf("(buil-tin : exit)");
	else if (cur->type == 1 && ft_strncmp(cur->str, "pwd", 5) == 0)
		printf("(buil-tin : exit)");
	else if (cur->type == 1 && ft_strncmp(cur->str, "export", 5) == 0)
		printf("(buil-tin : exit)");
	else if (cur->type == 1 && ft_strncmp(cur->str, "unset", 5) == 0)
		printf("(buil-tin : exit)");
	else if (cur->type == 1 && ft_strncmp(cur->str, "env", 5) == 0)
		printf("(buil-tin : exit)");
	else if (cur->type == 1 && ft_strncmp(cur->str, "exit", 5) == 0)
		printf("(buil-tin : exit)");
	else if (cur->type == 1)
		printf("(execve : %s)", cur->str);
}

void	mini_print_envp(t_data *data)
{
	t_envlist	*cur;

	if (data->start && data->start->at != NULL)
	{
		cur = data->start;
		while (cur != NULL)
		{
			printf("%s\n", cur->at);
			cur = cur->next;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_token	*cur;
//	int		i;

	(void)argv;
//	(void)argc;
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
		if (data.end && data.end->at != NULL)
			printf("und = %s\n", data.end->at);
		if (data.first)
		{
			cur = data.first;
			while (cur)
			{
				printf("%s (%d)\n", cur->str, cur->type);
				cur = cur->next;
			}
			if (ft_strncmp(data.first->str, "exit", 5) == 0)
			{
                //mini_liberate_all(&data, NULL, 0);
                mini_free_envlist(data.start);
				mini_free_token(data.first);
				exit (0);
            }
            mini_free_token(data.first);
			data.first = NULL;
		}
	}
	return (0);
}
