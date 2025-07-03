/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:07:19 by ledupont          #+#    #+#             */
/*   Updated: 2025/07/01 12:08:56 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include "libft/libft.h"

# define ARG 0
# define FONCTION 1
# define PIPE 2
# define INFILE 3
# define HEREDOC 4
# define OUTFILE 5
# define APPEND 6
# define REDINFILE 31
# define REDHEREDOC 41
# define REDOUTFILE 51
# define REDAPPEND 61

/*enum e_token_type
{
	HEREDOC,
};*/

typedef struct s_index
{
	int	i;
	int	w;
	int	m;
	int	h;
}	t_index;

typedef struct s_token
{
	struct s_token		*next;
	char				*str;
	int					type;
}	t_token;

typedef struct s_envlist
{
	struct s_envlist	*next;
	char				*str;
}	t_envlist;

typedef struct s_data
{
	struct s_envlist	*start;
	struct s_envlist	*end;
	struct s_token		*first;
	char				**ltab;
	char				**sptr;
	char				*line;
	char				*ex;
	char				*tmp;
	int					len;
	int					pipe;
	int					error;
}	t_data;

void		free2dstr(char **strs);
void		ft_free(void *ptr);
void		mini_check_line(t_data *data, char *s, t_index *in);
void		mini_clean_line(t_data *data, t_token *cur, t_token *prev);
void		mini_clean_quote(char *str, int i);
int			mini_countwords(char *str);
int			mini_empty_expanding(t_data *data, char *s, int i, int l);
t_envlist	*mini_envlist_new(t_data *data, char **envp, int i);
int			mini_error_expanding(t_data *data, char *s, int i);
int			mini_exp_strcmp(char *envp, char *expand, int l);
int			mini_expand(t_data *data, char *s, int i);
int			mini_expand_nutcase(t_data *data, char *s, int i);
int			mini_expanding(t_data *data, char *cur, char *s, int i);
void		mini_free_envlist(t_envlist *start);
void		mini_free_token(t_token *first);
void		mini_get_envp(t_data *data, char **envp);
int			mini_get_envp_check(char **envp, int i);
void		mini_invalid_line(char *str, char *msg);
int			mini_isquote(char c);
int			mini_isredir(char *str, int i);
int			mini_isspace(char c);
void		mini_liberate_all(t_data *data, char *msg, int err);
void		mini_line_sep(t_data *data);
void		mini_line_set(t_data *data);
void		mini_manage_expand_redir(t_data *data, t_token *cur, t_token *prev);
void		mini_manage_expand_arg(t_data *data, t_token *cur, t_token *prev);
void		mini_mode_switch(char *str, t_index *in, int type);
int			mini_redircheck(char *str);
void		mini_redirection_switch(char **str, t_index *in, int i);
void		mini_sizeword(t_data *data);
void		mini_space_sep(t_data *data, char *str, t_index *in);
void		mini_spacing_sep(t_data *data, t_index *in, int type);
void		mini_split_line(t_data *data);
void		mini_to_clean(t_data *data);
int			mini_to_expand(t_data *data, char *s, int i);
int			mini_token_assign(char *str, int pt);
void		mini_token_cleaning(t_data *data);
t_token		*mini_token_new(t_data *data, char **strs, int i);
void		mini_tokenizer(t_data *data);

#endif
