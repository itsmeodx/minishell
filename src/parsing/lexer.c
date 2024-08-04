/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:31:30 by adam              #+#    #+#             */
/*   Updated: 2024/08/05 00:42:38 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

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
				|| (input[i] == '>' && input[i + 1] == '>')))
			count--;
		i++;
	}
	return (count);
}
// this ft should be optimized to add spaces to
// || and && operators plus parenthesis

char	*ft_add_spaces_bonus(char *input, int j)
{
	int		i;
	char	*tmp;

	i = ft_count_spaces(input) * 2;
	tmp = malloc(ft_strlen(input) + i + 1);
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
			{
				tmp[++i] = input[j++];
			}
			tmp[++i] = ' ';
			i++;
		}
		else
			tmp[i++] = input[j++];
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_add_spaces(char *input, int j)
{
	int		i;
	char	*tmp;

	i = ft_count_spaces(input) * 2;
	tmp = malloc(ft_strlen(input) + i + 1);
	i = 0;
	while (input[j])
	{
		if ((input[j] == '<' || input[j] == '>' || input[j] == '|')
			&& !check_quote(input, j))
		{
			tmp[i] = ' ';
			tmp[++i] = input[j++];
			if (input[j - 1] != '|' && (input[j] == '<' || input[j] == '>'))
			{
				tmp[++i] = input[j++];
			}
			tmp[++i] = ' ';
			i++;
		}
		else
			tmp[i++] = input[j++];
	}
	tmp[i] = '\0';
	return (tmp);
}

char	**ft_lexer(char *input)
{
	char	**split_input;
	char	**output;
	char	**split_input_b;
	char	*input_spaces;
	char	*input_spaces_b;

	input_spaces = ft_add_spaces(input, 0);
	input_spaces_b = ft_add_spaces_bonus(input, 0);
    printf("input_spaces_b: %s\n", input_spaces_b);
	split_input = ft_split(input_spaces, " \n\t\v\f\r");
	split_input_b = ft_split(input_spaces_b, " \n\t\v\f\r");
    output = ft_strjoin_pro(split_input, split_input_b);
    free_str(split_input, ft_count_strs(split_input));
	free(input_spaces);
	free(input_spaces_b);
	return (output);
}
