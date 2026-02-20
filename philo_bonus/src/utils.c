/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:20:46 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/19 18:22:15 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

char	*ft_strjoin_wich(char *s1, char *s2, size_t size_s1)
{
	size_t	size_s2;
	char	*dest;
	int		i;
	int		j;

	size_s2 = 0;
	while (s2[size_s2])
		size_s2++;
	dest = ft_calloc(size_s1 + size_s2 + 1, sizeof(char));
	if (dest)
	{
		i = -1;
		while (++i < (int)size_s1)
			dest[i] = s1[i];
		j = -1;
		while (++j < (int)size_s2)
		{
			dest[i] = s2[j];
			i++;
		}
	}
	free(s2);
	return (dest);
}

char	*ft_itoa_wich(int n)
{
	int		len;
	int		nbr;
	char	*s;

	nbr = n;
	len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	if (nbr == 0)
		s[0] = '0';
	while (nbr > 0)
	{
		len--;
		s[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (s);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi_wich(char *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;

	if (size == 0 || nmemb == 0)
	{
		tmp = malloc(0);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	if (nmemb != 0 && size > ((size_t) - 1) / nmemb)
		return (NULL);
	tmp = malloc(size * nmemb);
	if (!tmp)
		return (NULL);
	memset(tmp, 0, nmemb * size);
	return (tmp);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
