/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:13:50 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 11:28:52 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_backslash_tick(char *s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] && s[i] == '\\')
		{
			j++;
			i++;
		}
		if (j % 2 != 0 && s[0] == '\\')
		{
			err_backslash();
			return (2);
		}
		else if (j % 2 != 0 && s[0] == '`')
		{
			err_backtick();
			return (2);
		}
		i++;
	}
	return (0);
}

t_quote	find_first(char *str)
{
	t_quote	idx;
	int		i;

	i = 0;
	idx.first = 0;
	idx.which = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			idx.first = i;
			idx.which = 1;
			return (idx);
		}
		if (str[i] == '"')
		{
			idx.first = i;
			idx.which = 2;
			return (idx);
		}
		i++;
	}
	return (idx);
}
