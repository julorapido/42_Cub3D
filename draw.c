/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:56:23 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/20 16:43:23 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_line(t_window *w, int x0, int y0, int x1, int y1, int color)
{
	int	err;
	int	e2;

	int dx = abs(x1 - x0);
	int sx = SNS(x0, x1);
	int dy = -abs(y1 - y0);
	int sy = SNS(y0, y1);
	err = dx + dy;
	while (1)
	{
		set_pixel_color(w, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
    	e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_rect(t_window *w, int x0, int y0, int x1, int y1, int color)
{
    if (x1 < x0 || y1 < y0)
        return ;
    while(y0 < y1)
    {
        draw_line(w, x0, y0, x1, y0, color);
        y0++;
    }
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void draw_fps_texturedRay(t_window *w, int x, float dist_to_wall, int texture_x, t_cub3d *f, t_image *texture, float a)
{
	float wall_height = (float)(HEIGHT) / (float)dist_to_wall;

	wall_height *= (float)(HEIGHT * (f->map->height *  (0.004) ));
	for(int y = 0; y < HEIGHT; y ++)
	{
		if(y <= (HEIGHT / 2) - (wall_height / (2))) // sky
		{
			set_pixel_color(w, x, y, 0xDDDDDD);
			//set_pixel_color(w, x, y, 0x222222);
		}
		else if(y >= (HEIGHT / 2) + (wall_height / (2))) // ground
		{
			set_pixel_color(w, x, y, get_texture_color(f, 0, 0, f->wall_textures[0]));
			//set_pixel_color(w, x, y, 0x000044);
		}
		else
		{
			int y_y = y - ((HEIGHT / 2) - (wall_height / 2));
			// 150/300 = 0.50
			float f_texture_y = ((float)(y_y) / (float)((wall_height)));
			int texture_y = f_texture_y * TEXTURE_HEIGHT;
			unsigned int color = (get_texture_color(f, texture_x, texture_y, texture));

			int red = (color >> 16) & 0xFF; // Extract the red component
			int green = (color >> 8) & 0xFF; // Extract the green component
			int blue = color & 0xFF;        // Extract the blue component

			float factor = dist_to_wall / 500;
			red = MIN(255, red + ((float)(255 - red) * factor));
			green = MIN(255, green + ((float)(255 - green) * factor));
			blue = MIN(255, blue + ((float)(255 - blue) * factor));

			int n_color = (red << 16) | (green << 8) | blue;
			color = color + (0xFFFFFF * (dist_to_wall / 100));
			set_pixel_color(w, x, y, n_color);
		}
	}
}

void draw_sprite(t_image *i, float dst_to_sprite, float sprite_y, float sprite_x, t_cub3d *f, float size_factor)
{
	int real_y = 0;
    int aax = 0;
	int hitler = -1;
	for(float a = 0.001; a < FOV && hitler == -1; a += (float)(FOV)/ (float)(WIDTH) )
	{
		float px = (float)(f->player->x);
		float py = (float)(f->player->y);
		while (1)
		{
			if(px < 0.0 || (int)(px) > WIDTH || (int)(py) > HEIGHT || py < 0.0)
				break;
			if((px < sprite_x + 2 && px > sprite_x - 2) && (py < sprite_y + 2 && py > sprite_y - 2))
			{
				hitler = aax;
				break;
			}
			px += (cos(degreesToRadians(((a - f->player->rot) - 60))));
            py += (sin(degreesToRadians(((a - f->player->rot) - 60))));
		}
		aax ++;
	}
	for(float y = 0; y < i->height; y += (dst_to_sprite / 100) * size_factor)
	{
		int real_x = 0;
		for (float x = 0; x < i->width; x+= (dst_to_sprite / 100) * size_factor)
		{
			int offset = (i->width / (dst_to_sprite / 100));
			int offset_y = (i->height / (dst_to_sprite / 100));
			if(get_texture_color(f, (int)(x), (int)(y), i) != -16777216)
			{
				set_pixel_color(f->fps, (hitler) + (real_x) - (offset / 3),  (HEIGHT /2) + real_y - (offset_y / 3),
					get_texture_color(f, (int)(x), (int)(y), i)
				);
			}
			real_x++;
		}
		real_y++;
	}

}