/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:52:12 by ksoto             #+#    #+#             */
/*   Updated: 2021/08/21 23:14:02 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>

# define BUFF_SIZE 36

/*
**	stdlib
*/

int		ft_atoi(char *str);

/*
**	stdio
*/

int		ft_putchar(char c);
int		ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);
int		ft_putstr_fd(const char *s, int fd);

/*
**	strings
*/

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memalloc(size_t size);
int		ft_chrcount(const char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_fstrjoin(char *s1, char *s2);
char	*ft_strnew(size_t size);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strcat(char *restrict s1, const char *restrict s2);

/*
**	others
*/
char	**ft_strsplit(char const *s, char c);
int		ft_rgbtoi(unsigned char r, unsigned char g, unsigned char b);
int		is_file(char *filename);
int		get_next_line(const int fd, char **line);

#endif
