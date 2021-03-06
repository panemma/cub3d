/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afficher_inttab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 14:33:30 by user42            #+#    #+#             */
/*   Updated: 2020/08/18 14:33:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/utils/utils.h"

void	affiche_inttab(int **map, t_pars pars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (j < pars.w[i])
		{
			ft_putnbr_fd(map[i][j], 1);
			j++;
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}
