/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:58:35 by ede-banv          #+#    #+#             */
/*   Updated: 2020/08/05 17:06:48 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
//pour le tracing jai besoin d'un wallx
//wallx = posy + pwd * raydiry (if side <1, else x) (real distance of wall)
//textx
//maybe change the draw vline function so for each direction instead of
void	ft_drawvline(t_all *all, int i)
{
	int		width;
	t_img	*img;
	int		j;

	j = 0;
	img = &all->win.img;
	width = all->pars.res[0];
	while (j < img->dstart)
		img->data[j++ * width + i] = all->pars.c;
	ft_texturedraw(all, i, j);
	j = img->dend;
	while (j < all->pars.res[1])
		img->data[j++ * width + i] = all->pars.f;
}

void	ft_init_text(t_all *all)
{
	if (!(all->pars.textadd.no = mlx_get_data_addr(all->pars.texture.no,
			&all->pars.texture.tbpp[0], &all->pars.texture.tsize_l[0],
			&all->pars.texture.tendian[0])))
		ft_exit(3, 0);
	if (!(all->pars.textadd.so = mlx_get_data_addr(all->pars.texture.so,
			&all->pars.texture.tbpp[1], &all->pars.texture.tsize_l[1],
			&all->pars.texture.tendian[1])))
		ft_exit(3, 0);
	if (!(all->pars.textadd.ea = mlx_get_data_addr(all->pars.texture.ea,
			&all->pars.texture.tbpp[2], &all->pars.texture.tsize_l[2],
			&all->pars.texture.tendian[2])))
		ft_exit(3, 0);
	if (!(all->pars.textadd.we = mlx_get_data_addr(all->pars.texture.we,
			&all->pars.texture.tbpp[3], &all->pars.texture.tsize_l[3],
			&all->pars.texture.tendian[3])))
		ft_exit(3, 0);
	if (!(all->pars.textadd.sp = mlx_get_data_addr(all->pars.texture.sp,
			&all->pars.texture.tbpp[4], &all->pars.texture.tsize_l[4],
			&all->pars.texture.tendian[4])))
		ft_exit(3, 0);
}


int		ft_draw_ns(int i, t_play *py, t_txtr *textadd, t_all *all, int j)
{
	if (py->raydir.y >= 0)
	{
		while (all->win.img.dstart < all->win.img.dend)   //sud
		{
			py->texty = abs((((all->win.img.dstart * 256 - all->pars.res[1]
			* 128 + all->win.img.lineh * 128) * 64) / all->win.img.lineh) / 256);
			ft_memcpy(&all->win.img.data[j++ * all->pars.res[0] + i],
			&textadd->so[py->texty % 64 * all->pars.texture.tsize_l[1] +
			(63 - py->textx % 64) * all->pars.texture.tbpp[1] / 8], sizeof(int));
			all->win.img.dstart++;
		}
	}
	else
	{
		while (all->win.img.dstart < all->win.img.dend) //nord
		{
			py->texty = abs((((all->win.img.dstart * 256 - all->pars.res[1]
			* 128 + all->win.img.lineh * 128) * 64) / all->win.img.lineh) / 256);
			ft_memcpy(&all->win.img.data[j++ * all->pars.res[0] + i],
			&textadd->no[py->texty % 64 * all->pars.texture.tsize_l[0] +
			(63 - py->textx % 64) * all->pars.texture.tbpp[0] / 8], sizeof(int));
			all->win.img.dstart++;
		}
	}
	return (1);
}

int		ft_draw_ew(int i, t_play *py, t_txtr *textadd, t_all *all, int j)
{
	if (py->raydir.x >= 0) //est
	{
		while (all->win.img.dstart < all->win.img.dend)
		{
			py->texty = abs((((all->win.img.dstart * 256 - all->pars.res[1]
			* 128 + all->win.img.lineh * 128) * 64) / all->win.img.lineh) / 256);
			ft_memcpy(&all->win.img.data[j++ * all->pars.res[0] + i],
			&(textadd->ea)[py->texty % 64 * all->pars.texture.tsize_l[2] +
			(63 - py->textx % 64) * all->pars.texture.tbpp[2] / 8], sizeof(int));
			all->win.img.dstart++;
		}
	}
	else
	{
		while (all->win.img.dstart < all->win.img.dend) //ouest
		{
			py->texty = abs((((all->win.img.dstart * 256 - all->pars.res[1]
			* 128 + all->win.img.lineh * 128) * 64) / all->win.img.lineh) / 256);
			ft_memcpy(&all->win.img.data[j++ * all->pars.res[0] + i],
			&textadd->we[py->texty % 64 * all->pars.texture.tsize_l[3] +
			(63 - py->textx % 64) * all->pars.texture.tbpp[3] / 8], sizeof(int));
			all->win.img.dstart++;
		}
	}
	return (1);
}

void	ft_texturecalc(t_all *all)
{
	t_play	*py;

	py = &all->player;
	if (py->side == 0)
		py->wallx = py->p.y + py->pwd * py->raydir.y;
	else
		py->wallx = py->p.x + py->pwd * py->raydir.x;
	py->wallx -= floor(py->wallx);
	py->textx = (int)(py->wallx * 64.0);
	if (py->side == 0 && py->raydir.x > 0)
		py->textx = 64.0 - py->textx - 1;
	if (py->side == 1 && py->raydir.y < 0)
		py->textx = 64.0 - py->textx - 1;
}

int		ft_texturedraw(t_all *all, int i, int j)
{
	ft_texturecalc(all);
	if (all->player.side == 1)
		ft_draw_ns(i, &all->player, &all->pars.textadd, all, j);
	else
		ft_draw_ew(i, &all->player, &all->pars.textadd, all, j);
	if (ft_draw_ns(i, &all->player, &all->pars.textadd, all, j) != 1 ||
		ft_draw_ew(i, &all->player, &all->pars.textadd, all, j) != 1)
		return (-1);
	return (1);
}
