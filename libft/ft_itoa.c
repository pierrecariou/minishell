/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcariou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:46:26 by pcariou           #+#    #+#             */
/*   Updated: 2020/10/01 10:25:45 by pcariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		size(long int nb)
{
	int size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*fill_str(long int nblong, char *str, int neg)
{
	int	i;

	i = 0;
	while (nblong > 0)
	{
		str[i] = nblong % 10 + '0';
		nblong /= 10;
		i++;
	}
	if (neg == 1)
	{
		str[i] = '-';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_rev(char *str)
{
	int		i;
	int		count;
	char	a;

	i = 0;
	count = 0;
	while (str[count])
		count++;
	while (i < count)
	{
		a = str[i];
		str[i] = str[count - 1];
		str[count - 1] = a;
		i++;
		count--;
	}
	return (str);
}

char	*ft_itoa(int nb)
{
	int			neg;
	char		*str;
	long int	nblong;

	neg = 0;
	nblong = (long int)nb;
	if (!(str = malloc(sizeof(char) * size(nblong) + 1)))
		return (0);
	if (nblong < 0)
	{
		neg = 1;
		nblong *= -1;
	}
	if (nblong == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = fill_str(nblong, str, neg);
	return (ft_rev(str));
}
