/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:11 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 15:09:41 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	while_back_slash(char *str)
{
	int	len;
	int	cnt;

	len = ft_strlen(str);
	cnt = 0;
	while (len > 0 && str[len - 1] == '\\')
	{
		cnt++;
		len--;
	}
	if (cnt % 2 == 1)
		return (0);
	return (1);
}

int	validate_basic(t_shell *shell, char *str)
{
	if (is_only_backslashes_or_backtick(str))
	{
		if (str[0] == '\\')
			err_backslash();
		else if (str[0] == '`')
			err_backtick();
		return (1);
	}
	if (!is_only_backslashes_or_backtick(str))
	{
		if (str[0] == '\\')
			error_message(&str);
		else if (str[0] == '`')
			error_message(&str);
	}
	if (check_error_token(str))
	{
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

char	*ft_parse_input(char *in, t_shell *shell)
{
	if (validate_syntax(shell, in))
	{
		return (ft_strdup(""));
	}
	return (parse_cmd(in));
}

int	validate_quotes(t_shell *shell, char *str)
{
	if (!all_quotes_closed(str))
	{
		ft_putstr_fd("Unclosed quotes\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	if (is_only_quotes(str))
	{
		ft_putstr_fd("Command '' not found\n", 2);
		shell->exit_code = 127;
		return (1);
	}
	return (0);
}

int	validate_syntax(t_shell *shell, char *str)
{
	if (find_first(str).which == 2 && !while_back_slash(str))
		if (check_backslash_tick(str))
			return (2);
	if (validate_basic(shell, str))
		return (1);
	if (validate_quotes(shell, str))
		return (1);
	return (0);
}
