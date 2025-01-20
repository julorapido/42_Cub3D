/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:41:23 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/20 12:12:22 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void    init_entities(t_cub3d *f)
{
    f->game_entities = calloc(100, sizeof(t_entity));

    f->game_entities[0].x = WIDTH / 2;
    f->game_entities[0].y = HEIGHT / 2;
    f->game_entities[0].sprite = f->sprites[0];
    f->game_entities[0].destroyed = false;
    f->game_entities[0].seen = false;
    f->game_entities[0].type = 1;


    f->game_entities[1].x = WIDTH / 4;
    f->game_entities[1].y = HEIGHT / 2;
    f->game_entities[1].sprite = f->sprites[0];
    f->game_entities[1].destroyed = false;
    f->game_entities[1].seen = false;
    f->game_entities[1].type = 1;

    f->entities_n = 2;
}

void    init_projectile(t_cub3d *f, int x, int y, float dir)
{
    int n = f->entities_n;
    f->game_entities[n].dir = dir;
    f->game_entities[n].destroyed = false;
    f->game_entities[n].seen = false;
    f->game_entities[n].type = 2;
    f->game_entities[n].x = x;
    f->game_entities[n].y = y;
    f->game_entities[n].sprite = f->sprites[1];
    f->entities_n++;
}

void    check_entities(t_cub3d *f)
{
    int x = 0;
    float px;
    float py;
    for(int l = 0; l < f->entities_n; l ++)
        f->game_entities[l].seen = false;
    for(float a = 0.001; a < FOV; a += (float)(FOV)/ (float)(WIDTH) * 20)
    {
        bool ht = false;
        px = (float)(f->player->x);
        py = (float)(f->player->y);
        int ll = -1;
        while (1)
        {
            if(px < 0.0 || (int)(px) > WIDTH || (int)(py) > HEIGHT || py < 0.0 || position_to_map_tiles((px), (py), f) == 1)
            {
                break;
            }
            px += (cos(degreesToRadians(((a - f->player->rot)- 60))));
            py += (sin(degreesToRadians(((a - f->player->rot) - 60))));
            for(int l = 0; l < f->entities_n; l ++)
            {
                if (f->game_entities[l].destroyed)
                    continue;
                if((px < f->game_entities[l].x + 5 && px > f->game_entities[l].x - 5)
                    && (py < f->game_entities[l].y + 5 && py > f->game_entities[l].y - 5))
                {
                    f->game_entities[l].seen = true;
                    ht = true;
                    ll = l;
                    break;
                }
            }
        }
        if(ll != -1)
        {
            draw_line(f->fps,
                f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
                px / MINIMAP_RATIO, py / MINIMAP_RATIO,
                0xFFF000
            );
        }else
        {
            draw_line(f->fps,
                f->player->x / MINIMAP_RATIO, f->player->y / MINIMAP_RATIO,
                px / MINIMAP_RATIO, py / MINIMAP_RATIO,
                0xFF00FF
            );
        }
        x += 10;
    }
}

void    render_entities(t_cub3d *f)
{
    for(int l = 0; l < f->entities_n; l ++)
    {
        if (f->game_entities[l].seen)
        {
            float dst = (sqrt(pow((float)(f->game_entities[l].x) - (float)(f->player->x), 2)
                        + pow((float)(f->game_entities[l].y) - (float)(f->player->y), 2)));
            if(dst > 3.0)
            {
                draw_sprite(f->game_entities[l].sprite, dst, f->game_entities[l].y, f->game_entities[l].x, f, f->game_entities[l].type == 1 ? 0.2 : 1);
            }
        }
    }
}