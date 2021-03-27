/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyelena <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 18:43:23 by jyelena           #+#    #+#             */
/*   Updated: 2021/03/02 19:56:48 by dmikhaylov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# define BUFFER_SIZE 1

int				get_next_line(int fd, char **line);
char			*ft_strjoin_gnl(char *s1, char *s2);
int				ft_substr_len(char const *s, char c);
void			ft_free(char **str);

#endif
