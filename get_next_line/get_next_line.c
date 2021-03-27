/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:43:01 by jyelena           #+#    #+#             */
/*   Updated: 2021/01/27 10:30:57 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_chkkeeper(char *keeper)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	if (!keeper)
		return (NULL);
	i = ft_substr_len(keeper, '\n');
	if (!keeper[i])
	{
		ft_free(&keeper);
		return (NULL);
	}
	if (!(result = malloc((ft_substr_len(keeper, 0) - i) + 1 * sizeof(char))))
		return (NULL);
	i++;
	while (keeper[i])
		result[j++] = keeper[i++];
	result[j] = '\0';
	ft_free(&keeper);
	return (result);
}

char	*ft_takeline(char *str)
{
	int		i;
	char	*tline;

	if (!str)
		return (NULL);
	i = ft_substr_len(str, '\n');
	tline = (char *)malloc(sizeof(char) * (i + 1));
	if (tline == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		tline[i] = str[i];
		i++;
	}
	tline[i] = '\0';
	return (tline);
}

int		ft_chksybmoln(char *str)
{
	char *runner;

	if (!str)
		return (0);
	runner = str;
	while (*runner)
		if (*runner++ == '\n')
			return (1);
	return (0);
}

void	ft_init(int *bytes, char **str)
{
	*bytes = 1;
	if (*str == NULL)
	{
		*str = (char *)malloc(sizeof(char));
		*str[0] = '\0';
	}
}

int		get_next_line(int fd, char **line)
{
	char		*buff;
	static char	*keeper;
	int			bytes;

	if (fd < 0 || !line || BUFFER_SIZE <= 0
	|| !(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ft_init(&bytes, &keeper);
	while (!ft_chksybmoln(keeper) && bytes != 0)
	{
		if ((bytes = read(fd, buff, BUFFER_SIZE)) < 0)
			break ;
		buff[bytes] = '\0';
		keeper = ft_strjoin_gnl(keeper, buff);
	}
	free(buff);
	if (bytes < 0)
		return (-1);
	*line = ft_takeline(keeper);
	keeper = ft_chkkeeper(keeper);
	if (bytes == 0)
		ft_free(&keeper);
	if (bytes == 0)
		return (0);
	return (1);
}
