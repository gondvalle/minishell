/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/09/23 21:20:31 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

size_t	ft_matlen(char **mat)
{
	size_t	size;

	size = 0;
	while (mat[size])
		size++;
	return (size);
}

char	*dollar_digit(char *str)
{
	int		i;
	int		j;
	char	*otmp;

	i = 0;
	j = -1;
	otmp = ft_calloc(ft_strlen(str), sizeof(char));
	if (!otmp)
		ft_error(MALLOC, NULL);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0)
		{
			while (str[i])
			{
				otmp[++j] = str[i];
				i++;
			}
			break ;
		}
		i++;
	}
	return (otmp);
}

char	*dollar_env(char *str)
{
	int		i;
	char	*var_env;
	char	*otmp;
	

	i = -1;
	otmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!otmp)
		ft_error(MALLOC, NULL);
	while (str[++i])
	{
		if (ft_isalnum(str[i]) == 0)
			break ;
		otmp[i] = str[i];
	}
	var_env = ft_get_env(otmp);
	free(otmp);
	return (var_env);
}

void	concat_env(char **mat, char *change, size_t j, char **matqoute)
{
	size_t i;
	char *tmp;
	char *otmp;

	i = -1;
	while (mat[++i])
	{
		if (matqoute[i][0] == 'n')
		{
			tmp = dollar_env(mat[i]);
			if (tmp)
				ft_strlcat(change, tmp, j);
			otmp = dollar_digit(mat[i]);
			if (otmp)
			{
				ft_strlcat(change, otmp, j);
				free(otmp);
			}
		}
		else
		{
			ft_strlcat(change, "$", j);
			ft_strlcat(change, mat[i], j);
		}
	}
}

char	*change_dollar(char **mat, char *src, char **matqoute)
{
	size_t j;
	char *change;

	j = dollar_size(mat, src, matqoute) + 1;
	if (j == 0)
		return (NULL);
	change = ft_calloc(j + 1, sizeof(char));
	if (!change)
		ft_error(MALLOC, NULL);
	concat_env(mat, change, j, matqoute);
	if (src[ft_strlen(src) - 1] == '$')
		ft_strlcat(change, "$", j + 1);
	return (change);
}

void	mini_qte_two(char *str, char *lit, int clsd, int clss)
{
	int i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && clsd == 1)
		{
			clss = clss * -1;
			lit[i] = 'c';
		}
		else if (str[i] == '\"' && clss == 1)
		{
			clsd = clsd * -1;
			lit[i] = 'c';
		}
		else if (str[i] == ' ' && clss == 1 && clsd == 1)
			lit[i] = ' ';
		else if (str[i] == '$')
			lit[i] = '$';
		else if (clss == -1)
			lit[i] = 's';
		else
			lit[i] = 'n';
	}
}

char	*quote_line_two(char *str)
{
	int     close_s;
	int     close_d;
	char    *lit;
	
	lit = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!lit)
		ft_error(MALLOC, NULL);
	close_s = 1;
	close_d = 1;
	mini_qte_two(str, lit, close_d, close_s);
	return (lit);
}

char	**qout_mat(char *src)
{
	char	**mat_qout;
	char	*qoute_str;
	char	*str;
	int		i;

	qoute_str = quote_line_two(src);
	i = -1;
	while (qoute_str[++i])
		if (qoute_str[i] == '$')
			break ;
	str = ft_substr(qoute_str, i, ft_strlen(qoute_str));
	mat_qout  = ft_split(str, '$');
	free(str);
	free(qoute_str);
	return(mat_qout);
}

char	**split_pointer(char *src)
{
	char	*point;
	char	**mat;

	point = ft_strchr(src, '$');
	mat = ft_split(point, '$');
	return (mat);
}

char	*mini_env_dollar(char *src)
{
	char	**mat;
	char	*str;
	char	*join;
	char	*copy;
	char	**matqoute;

	copy = copy_character(src, '$');
	mat = split_pointer(src);
	if (!mat)
		ft_error(MALLOC, NULL);
	matqoute = qout_mat(src);
	str = change_dollar(mat, src, matqoute);
	ft_free(matqoute);
	ft_free(mat);
	join = ft_strjoin(copy, str);
	free(copy);
	free(str);
	if (!join) 
		ft_error(MALLOC, NULL);
	return (join);
}

char	*env_dollar(char *src)
{
	char	**mat;
	char	*str;

	if (ft_strncmp(src, "$", 1) != 0)
	{
		str = mini_env_dollar(src);
		return (str);
	}
	mat = ft_split(src, '$');
	if (!mat)
		ft_error(MALLOC, NULL);
	char **matqoute = qout_mat(src); ///////////////////////////////
	str = change_dollar(mat, src, matqoute);
	ft_free(matqoute);//////////////////////////////////////////////////
	ft_free(mat);
	return (str);
}
