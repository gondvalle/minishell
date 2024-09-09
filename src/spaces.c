/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes(char **input, char **temp, int *doubl, int *single)
{
	if (**input == '\"')
	{
		*doubl = !(*doubl);
		*(*temp)++ = *(*input)++;
	}
	else if (**input == '\'')
	{
		*single = !(*single);
		*(*temp)++ = *(*input)++;
	}
}

void	handle_operators(char **ipt, char **temp)
{
	if (ft_strncmp(*ipt, "<<", 2) == 0 || ft_strncmp(*ipt, ">>", 2) == 0)
	{
		*(*temp)++ = ' ';
		*(*temp)++ = *(*ipt)++;
		*(*temp)++ = *(*ipt)++;
		*(*temp)++ = ' ';
	}
	else if (**ipt == '<' || **ipt == '>' || **ipt == '|')
	{
		*(*temp)++ = ' ';
		*(*temp)++ = *(*ipt)++;
		*(*temp)++ = ' ';
	}
}

char	*add_spaces(char *input)
{
	char *result;
	char *temp;
	size_t len;
	int in_double_quotes;
	int in_single_quotes;

	len = ft_strlen(input);
	result = (char *)malloc((len * 2 + 1) * sizeof(char));
	if (!result)
		ft_error(MALLOC, NULL);
	in_double_quotes = 0;
	in_single_quotes = 0;
	temp = result;
	while (*input)
	{
		handle_quotes(&input, &temp, &in_double_quotes, &in_single_quotes);
		if (!in_double_quotes && !in_single_quotes)
			handle_operators(&input, &temp);
		if (*input)
			*temp++ = *input++;
	}
	*temp = '\0';
	return (result);
}