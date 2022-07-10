/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttomori <ttomori@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:28:42 by ttomori           #+#    #+#             */
/*   Updated: 2022/07/10 17:30:02 by ttomori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	convert_recursive(char *s, long long int n);
static int	count_digit(long long int n);

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*ft_itoa(int n)
{
	int				digit;
	char			*p;
	char			*head;
	long long int	nbr;

	nbr = (long long int)n;
	digit = count_digit(nbr);
	p = (char *)malloc(sizeof(char) * (digit + 1));
	if (p == NULL)
		return (NULL);
	head = p;
	p[digit] = '\0';
	if (nbr < 0)
	{
		*p++ = '-';
		nbr *= -1;
	}
	else if (nbr == 0)
	{
		*p++ = '0';
	}
	convert_recursive(head + digit - 1, nbr);
	return (head);
}

static void	convert_recursive(char *s, long long int n)
{
	if (n == 0)
		return ;
	convert_recursive(s - 1, n / 10);
	*s = (n % 10) + '0';
}

static int	count_digit(long long int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
	{
		n = -n;
		counter++;
	}
	while (n != 0)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}
