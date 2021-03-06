/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:54:24 by ede-banv          #+#    #+#             */
/*   Updated: 2020/08/18 14:31:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
**structure to save the bmp file
*/
typedef struct	s_save
{
	int			fd;
	int			size;
	int			unused;
	int			offset_begin;
	int			header_bytes;
	short int	plane;
	short int	bpp;
}				t_save;

/*
**texture structures
*/
typedef struct	s_txtr
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*sp;
	int		tbpp[5];
	int		tsize_l[5];
	int		tendian[5];
}				t_txtr;

typedef struct	s_pars
{
	int		res[2];
	int		screenw;
	int		screenh;
	t_txtr	texture;
	t_txtr	textadd;
	int		f;
	int		c;
	int		**map;
	int		*w;
	int		sp;
}				t_pars;

/*
**image & widnow structures
*/
typedef struct	s_img
{
	void	*image;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;
	int		lineh;
	int		dstart;
	int		dend;
}				t_img;

typedef struct	s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		height;
	int		width;
	int		maxh;
	int		maxw;
}				t_win;

typedef	struct	s_mov
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		close;
	int		turnl;
	int		turnr;
	int		speed;
}				t_mov;

/*
**sprite structure
*/
typedef struct	s_spt
{
	double		x;
	double		y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			move_screen;
	int			spr_h;
	int			spr_w;
	int			screen_x;
	int			draw_sx;
	int			draw_ex;
	int			draw_sy;
	int			draw_ey;
	int			text_w;
	int			text_h;
	int			textx;
	int			texty;
	int			d;
	int			texture;
	int			i;
}				t_spt;

/*
**player structures
*/
typedef struct	s_vec
{
	double	x;
	double	y;
}				t_vec;

/*
**-p is the position of the player
**-dir is the direction vector of the player
**-plane is the plane vector (corresponds to half the plane)
**-raydir corresponds to the vector of the position of where the ray cuts
** the plane. so the vector of the direction w the ray
**-map has the current square of the map the ray is in
**-deltadist is the ray distance between one y(or x) coord and the other
**-pwd is the var taht has the dist of the wall
**-hit records if there was a wall
**-side records which side (NS/EW) was hit
**-sidedist is the dist from the ray start position to the first side (x or y)
**-step is to know whether the ray is going in a positive or negative dir.
**-mov is the structure to know if a key is being pressed
**-wallx, textx, texty are for textures
**-speed and rotspeed are for speed change
*/
typedef struct	s_play
{
	t_vec	p;
	t_vec	dir;
	t_vec	plane;
	t_vec	raydir;
	int		mapx;
	int		mapy;
	t_vec	deltadist;
	double	pwd;
	int		hit;
	int		side;
	t_vec	sidedist;
	int		stepx;
	int		stepy;
	t_mov	mov;
	double	wallx;
	int		textx;
	int		texty;
	double	speed;
	double	rotspeed;
}				t_play;

/*
**master structure
*/
typedef struct	s_all
{
	t_pars	pars;
	t_win	win;
	t_play	player;
	t_vec	sp[50];
	t_spt	spt;
	double	*zbuff;
	t_save	save;
	int		s;

}				t_all;

#endif
