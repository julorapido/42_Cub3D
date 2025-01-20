/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:06:05 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/20 15:15:09 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_walls(t_cub3d *f)
{
    int y;
    int x;
    y = 0;
    while(y < (f->map)->height)
    {
        x = 0;
        while (x < (f->map)->width)
        {
            if((f->map)->map_matrix[y][x] == '1')
            {
                draw_rect(f->fps,
                    (x * (WIDTH / (f->map)->width)) / MINIMAP_RATIO,
                    (y * (HEIGHT / (f->map)->height)) / MINIMAP_RATIO,
                    (((x + 1) * (WIDTH / (f->map)->width))) / MINIMAP_RATIO,
                    (((y + 1) * (HEIGHT / (f->map)->height))) / MINIMAP_RATIO,
                    0XFFFFFF
                );
            }
            x++;
        }
        y++;
    }
}

void draw_grid(t_cub3d *f)
{
    int y;
    int x;
    y = 0;

    return;
    while(y < (f->map)->saved_width)
    {
        x = 0;
        while (x < (f->map)->saved_width)
        {
            draw_line(f->fps,
                ((x) * (WIDTH / (f->map)->width)) / MINIMAP_RATIO,
                (y * (HEIGHT / (f->map)->height)) / MINIMAP_RATIO,
                (((x + 1) * (WIDTH / (f->map)->width))) / MINIMAP_RATIO,
                (((y) * (HEIGHT / (f->map)->height))) / MINIMAP_RATIO,
                0x444444
            );
            draw_line(f->fps,
                ((x + 1) * (WIDTH / (f->map)->width)) / MINIMAP_RATIO,
                (y * (HEIGHT / (f->map)->height)) / MINIMAP_RATIO,
                (((x + 1) * (WIDTH / (f->map)->width))) / MINIMAP_RATIO,
                (((y + 1) * (HEIGHT / (f->map)->height))) / MINIMAP_RATIO,
                0x444444
            );
            x++;
        }
        y++;
    }
}


void draw_entities(t_cub3d *f)
{
    draw_rect(f->fps, (f->player)->x / MINIMAP_RATIO, (f->player)->y / MINIMAP_RATIO,
       ((f->player)->x / MINIMAP_RATIO) + 4, ((f->player)->y / MINIMAP_RATIO) + 4, 0x00FFFF);

    for(int i = 0; i < f->entities_n; i++)
    {
        t_entity *e = &(f->game_entities[i]);
        int color = e->type == 2 ? 0x222222 : 0xFFFF00;
        int sz = e->type == 2 ? 3: 5;
        draw_rect(f->fps, (int)((e)->x) / MINIMAP_RATIO, (int)((e)->y) / MINIMAP_RATIO,
            ((int)((e)->x) / MINIMAP_RATIO) + sz, ((int)((e)->y) / MINIMAP_RATIO) + sz, color);
    }
}
