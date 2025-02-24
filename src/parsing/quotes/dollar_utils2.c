/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:51:28 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 23:51:28 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_count_occurrences(char *str, char *old)
{
	size_t	i;
	size_t	count;
	size_t	old_len;

	old_len = ft_strlen(old);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], old, old_len) == 0)
		{
			count++;
			i += old_len - 1;
		}
		i++;
	}
	return (count);
}

char	*ft_allocate_result(size_t i, size_t count, size_t new_len,
		size_t old_len)
{
	(void)i;
	(void)count;
	(void)new_len;
	(void)old_len;
	return (ft_calloc(5000, sizeof(char *)));
}

char	*ft_process_replacement(char *str, char *old, char *new, t_replace *r)
{
	size_t	old_len;
	size_t	new_len;

	old_len = ft_strlen(old);
	new_len = ft_strlen(new);
	while (*str)
	{
		if (ft_strncmp(str, old, old_len) == 0)
		{
			ft_memcpy(&r->res[r->idx], new, new_len);
			r->idx += new_len;
			str += old_len;
		}
		else
		{
			r->res[r->idx++] = *str;
			str++;
		}
	}
	r->res[r->idx] = '\0';
	return (r->res);
}

char	*ft_strreplace(char *str, char *old, char *new)
{
	char		*result;
	size_t		old_len;
	size_t		new_len;
	size_t		count;
	t_replace	r;

	old_len = ft_strlen(old);
	new_len = ft_strlen(new);
	count = ft_count_occurrences(str, old);
	r.idx = 0;
	result = ft_allocate_result(r.idx, count, new_len, old_len);
	if (!result)
		return (NULL);
	r.res = result;
	return (ft_process_replacement(str, old, new, &r));
}

char	*expand_variables_in_token(char *token, t_shell *shell)
{
	char	*expanded;
	int		pos;

	pos = 0;
	expanded = ft_parse_word(token, &pos, shell);
	expanded = remove_quotes(expanded);
	free(token);
	return (expanded);
}
