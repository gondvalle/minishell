/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/09/25 23:02:02 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

char	**change_mat(char **mat, char *line)
{
	char	**src;
	int		i;

	src = ft_calloc(ft_matlen(mat) + 1, sizeof(char *));
	i = -1;
	src = mini_change_mat(mat, i, src, line);
	return (src);
}

char **prepare_split(char *str)
{
	char	*quotes;
	char	**qte_split;

	quotes = clean_other(str);
	if (!quotes)
		ft_error(MALLOC, NULL);
	qte_split = ft_split(quotes, ' ');
	free(quotes);
	if (!qte_split)
		ft_error(MALLOC, NULL);
	return (qte_split);
}

char	**quote_split(char *str, char **qte_split)
{
	char	**mat;
	char	*tmp;
	int		i;
	int		j;

	mat = ft_calloc(ft_matlen(qte_split) + 1, sizeof(char *));
	if (!mat)
		ft_error(MALLOC, NULL);
	tmp = clean_qt(str);
	if (!tmp)
		ft_error(MALLOC, NULL);
	i = -1;
	j = 0;
	while (qte_split[++i])
	{
		mat[i] = ft_substr(tmp, j, ft_strlen(qte_split[i]));
		if (!mat[i])
		{
			free (tmp);
			return (ft_free(mat), ft_free(qte_split), NULL);
		}
		j += ft_strlen(qte_split[i]) + 1;
	}
	free(tmp);
	return (mat);
}

char	**ft_quotesplit(char *str)
{
	char **qte_split;
	char **mat;

	qte_split = prepare_split(str);
	if (!qte_split)
		ft_error(MALLOC, NULL);
	mat = quote_split(str, qte_split);
	ft_free(qte_split);
	return (mat);
}

char	**quote_split_first(char *src)
{
	char	*quote;
	char	**qte_split;
	char	**mat;
	int		i;
	int		j;

	quote = quote_line(src);
	qte_split = ft_split(quote, ' ');
	free(quote);
	if (!qte_split)
		ft_error(MALLOC, NULL);
	mat = ft_calloc(ft_matlen(qte_split) + 1, sizeof(char *));
	if (!mat)
		ft_error(MALLOC, NULL);
	i = -1;
	j = 0;
	while (qte_split[++i])
	{
		mat[i] = ft_substr(src, j, ft_strlen(qte_split[i]));
		if (!mat[i])
			return (ft_free(mat), ft_free(qte_split), NULL);
		j += ft_strlen(qte_split[i]) + 1;
	}
	ft_free(qte_split);
	return (mat);
}

char	*mat_to_line(char **mat)
{
	char	*result;
	int		total_len;
	int		i;
	int		j;
	int		k;

	total_len = 0;
	i = -1;
	while (mat[++i])
		total_len += ft_strlen(mat[i]);
	result = ft_calloc((total_len + ft_matlen(mat) + 1), sizeof(char));
	if (!result)
		ft_error(MALLOC, NULL);
	i = -1;
	k = -1;
	while (mat[++i])
	{
		j = -1;
		while (mat[i][++j])
			result[++k] = mat[i][j];
		if (mat[i + 1])
			result[++k] = ' ';
	}
	result[++k] = '\0';
	return (result);
}


char	*dollar_line(char	*src)
{
	char	**dollar;
	char	**dol;
	char	*line;

	dol = quote_split_first(src);
	dollar = change_mat(dol, src);
	free(src);
	ft_free(dol);
	line = mat_to_line(dollar);
	ft_free(dollar);
	return (line);
}

char	**line_split(char *line)
{
	char	*clean;
	char	**mat;
	char	*dol_line;

	clean = clean_line(line);
	dol_line = dollar_line(clean);
	mat = ft_quotesplit(dol_line);
	free(dol_line);
	return (mat);
}
