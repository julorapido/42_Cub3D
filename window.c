/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:06:06 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/20 16:10:14 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void	p_int_to_rgb(int color)
{
	unsigned int red   = (color & 0x00ff0000) >> 16;
	unsigned int green = (color & 0x0000ff00) >> 8;
	unsigned int blue  = (color & 0x000000ff);
	printf("(int)(%d) RGB=[R: %d, G: %d, B: %d] \n", color, red, green, blue);
}

unsigned int	get_texture_color(t_cub3d *f, int x, int y, t_image *texture)
{
	t_image *i = texture;

	if(x < 0 || y < 0)
		return (0);
	return (*(unsigned int *)(i->bfr
		+ (y * i->linelen)
		+ x * (i->bpp / 8)
		)
	);
}

void	set_pixel_color(t_window *w, long x, long y, unsigned int n)
{
	char	*dst;
	long	offset;

	if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
		return ;
	offset = (y * w->linelen + x * (w->bpp / 8));
	dst = w->buf + (offset);
	*(unsigned int *)dst = n;
}

//  =====================================================
//   				INIT A WINDOW
//  =====================================================
int	init_windows(t_cub3d *t)
{
	t->fps = malloc(sizeof(t_window));
	t->fps->mlx = mlx_init();
	if (!t->fps->mlx)
	    return (-1);
	t->fps->win = mlx_new_window(t->fps->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!t->fps->win)
        return (-1);
    t->fps->img = mlx_new_image(t->fps->mlx, WIDTH, HEIGHT);
	if (!(t->fps->img))
        return (-1);
	t->fps->buf = mlx_get_data_addr(t->fps->img, &t->fps->bpp,
        &t->fps->linelen, &t->fps->endian);
	return (1);
}



void render(t_cub3d *f)
{
    raycasting(f);
	//check_entities(f);
	//render_entities(f);
    draw_walls(f);
	draw_grid(f);
	draw_entities(f);
	render_gun(f);
    mlx_put_image_to_window(f->fps->mlx, f->fps->win, f->fps->img, 0, 0);
}