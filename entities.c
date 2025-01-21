/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:41:23 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/21 13:28:23 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_entities(t_cub3d *f)
{
	f->game_entities = calloc(100, sizeof(t_entity));
	f->game_entities[0].x = WIDTH / 2;
	f->game_entities[0].y = HEIGHT / 2;
	// f->game_entities[0].sprite = f->sprites[0];
	f->game_entities[0].destroyed = false;
	f->game_entities[0].seen = false;
	f->game_entities[0].type = 1;
	f->game_entities[1].x = WIDTH / 4;
	f->game_entities[1].y = HEIGHT / 3;
	// f->game_entities[1].sprite = f->sprites[0];
	f->game_entities[1].destroyed = false;
	f->game_entities[1].seen = false;
	f->game_entities[1].type = 1;
	f->entities_n = 2;
}

void	init_projectile(t_cub3d *f, int x, int y, float dir)
{
	int	n;

	n = f->entities_n;
	f->game_entities[n].dir = dir;
	f->game_entities[n].destroyed = false;
	f->game_entities[n].seen = false;
	f->game_entities[n].type = 2;
	f->game_entities[n].x = x;
	f->game_entities[n].y = y;
	f->game_entities[n].sprite = f->sprites[1];
	f->entities_n++;
}

static int	aa(int ll, int px, int py, t_cub3d *f)
{
	if (ll != -1)
	{
		draw_line(f->fps,
			f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
			px / MINIMAP_RATIO, py / MINIMAP_RATIO,
			0xFFF000
			);
	}
	else
	{
		draw_line(f->fps,
			f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
			px / MINIMAP_RATIO, py / MINIMAP_RATIO,
			0xFF00FF
			);
	}
}

static void	wawer(t_cub3d *f, int px, int py)
{
	int	l;

	l = 0;
	while (l < f->entities_n)
	{
		if (f->game_entities[l].destroyed)
		{
			l++;
			continue ;
		}
		if ((px < f->game_entities[l].x + 5
				&& px > f->game_entities[l].x - 5)
			&& (py < f->game_entities[l].y + 5
				&& py > f->game_entities[l].y - 5))
		{
			f->game_entities[l].seen = true;
			f->ht = true;
			f->ll = l;
			break ;
		}
		l++;
	}
}

void	check_entities(t_cub3d *f)
{
	float	px;
	float	py;
	float	a;

	a = 0.001;
	for(int i = 0; i < f->entities_n; i++)
		f->game_entities[i].seen = false;
	while (a < FOV)
	{
		f->ht = false;
		px = (float)(f->player->x);
		py = (float)(f->player->y);
		f->ll = -1;
		while (1)
		{
			if ((int)(px) > WIDTH || (int)(py) > HEIGHT || position_to_map_tiles((px), (py), f) == 1)
				break ;
			px += (cos(degreesToRadians(((a - f->player->rot) - 60))));
			py += (sin(degreesToRadians(((a - f->player->rot) - 60))));
			wawer(f, px, py);
			aa(f->ll, px, py, f);
		}
		a += ((float)(FOV) / (float)(WIDTH)) * 20;
	}
}

void	render_entities(t_cub3d *f)
{
	int		l;
	float	dst;

	l = 0;
	while (l < f->entities_n)
	{
		if (f->game_entities[l].seen)
		{
			dst = (sqrt(pow((float)(f->game_entities[l].x)
							- (float)(f->player->x), 2)
						+ pow((float)(f->game_entities[l].y)
							- (float)(f->player->y), 2)));
			if (dst > 3.0)
			{
				draw_sprite(f->game_entities[l].sprite, dst,
					f->game_entities[l].y, f->game_entities[l].x,
					f, f->game_entities[l].type == 1 ? 0.4 : 1,
						f->game_entities[l].type
					);
			}
		}
		l++;
	}
}
