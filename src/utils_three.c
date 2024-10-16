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

void	concat_env(char **mat, char *change, size_t j)
{
	size_t i;
	char *tmp;
	char *otmp;

	i = -1;
	while (mat[++i])
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
}

char	*change_dollar(char **mat, char *src)
{
	size_t j;
	char *change;

	j = dollar_size(mat, src) + 1;
	if (j == 0)
		return (NULL);
	change = ft_calloc(j + 1, sizeof(char));
	if (!change)
		ft_error(MALLOC, NULL);
	concat_env(mat, change, j);
	if (src[ft_strlen(src) - 1] == '$')
		ft_strlcat(change, "$", j + 1);
	return (change);
}

char	*mini_env_dollar(char * src)
{
	char	**mat;
	char	*point;
	char	*str;
	char	*join;
	char	*copy;

	point = ft_strchr(src, '$');
	copy = copy_character(src, '$');
	mat = ft_split(point, '$');
	if (!mat)
		ft_error(MALLOC, NULL);
	printf("EL src es %s\nla matriz es \n", src);
	/* PONER ESTO PARA MIRAR COSAS echo hjdbbds'$PWD+'$HOME'g
	char **mq = prepare_split(src); ///////////////////////////////
	print_matrix(mq);
	ft_free(mq); //////////////////////////////////
	*/
	str = change_dollar(mat, src);
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
	str = change_dollar(mat, src);
	ft_free(mat);
	return (str);
}
