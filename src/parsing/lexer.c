/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:31:30 by adam              #+#    #+#             */
/*   Updated: 2024/08/18 11:49:24 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_count_spaces_bonus(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '&' || input[i] == '(' || input[i] == '|'
			|| input[i] == ')')
			count++;
		if (input[i + 1] && ((input[i] == '&' && input[i + 1] == '&')
				|| (input[i] == '|' && input[i + 1] == '|')))
			count--;
		i++;
	}
	return (count);
}

int	ft_count_spaces(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>' || input[i] == '|')
			count++;
		if (input[i + 1] && ((input[i] == '<' && input[i + 1] == '<')
				|| (input[i] == '>' && input[i + 1] == '>') || (input[i] == '|'
					&& input[i + 1] == '|')))
			count--;
		i++;
	}
	return (count);
}

char	*ft_add_spaces_bonus(char *input, int j)
{
	int		i;
	char	*tmp;

	i = ft_count_spaces_bonus(input) * 2;
	if (!i)
		return (ft_strdup(input));
	tmp = malloc(ft_strlen(input) + (i + 1));
	i = 0;
	while (input[j])
	{
		if ((input[j] == '&' || input[j] == '(' || input[j] == '|')
			&& !check_quote(input, j))
		{
			tmp[i] = ' ';
			tmp[++i] = input[j++];
			if (input[j - 1] != '(' && ((input[j] == '&' && input[j - 1] != '|')
					|| input[j] == '|'))
				tmp[++i] = input[j++];
			tmp[++i] = ' ';
			i++;
		}
		else
			tmp[i++] = input[j++];
	}
	return (tmp[i] = '\0', tmp);
}

char	*ft_add_spaces(char *input, int j)
{
	int		i;
	char	*tmp;

	i = ft_count_spaces(input) * 2;
	if (!i)
		return (ft_strdup(input));
	tmp = malloc(ft_strlen(input) + (i + 1));
	i = 0;
	while (input[j])
	{
		if ((input[j] == '<' || input[j] == '>' || input[j] == ')')
			&& !check_quote(input, j))
		{
			tmp[i] = ' ';
			tmp[++i] = input[j++];
			if (input[j - 1] != '|' && input[j - 1] != ')' && (input[j] == '<'
					|| input[j] == '>'))
				tmp[++i] = input[j++];
			tmp[++i] = ' ';
			i++;
		}
		else
			tmp[i++] = input[j++];
	}
	return (tmp[i] = '\0', tmp);
}

char	**ft_lexer(char *input)
{
	char	**split_input;
	char	*input_spaces;
	char	*input_spaces_b;

	input_spaces = ft_add_spaces(input, 0);
	input_spaces_b = ft_add_spaces_bonus(input_spaces, 0);
	split_input = ft_split(input_spaces_b, " \n\t\v\f\r");
	free(input_spaces);
	free(input_spaces_b);
	return (split_input);
}
