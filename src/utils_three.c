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

char	*change_dollar(char **mat, char *src)
{
	size_t	i;
	size_t	j;
	char	*tmp;
	char	*change;

	i = 0;
	j = dollar_size(mat, src);
	if (j == 0)
		return (NULL);
	change = ft_calloc(j + 1, sizeof(char));
	if (!change)
		ft_error(MALLOC, NULL);
	while (mat[i])
	{
		tmp = ft_get_env(mat[i]);
		if (tmp)
			ft_strlcat(change, tmp, j);
		i++;
	}
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
	str = change_dollar(mat, src);
	join = ft_strjoin(copy, str);
	free (str);
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
	return (str);
}
