/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:58:53 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/22 12:03:24 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void fixedUpdate(t_cub3d *f, clock_t currentTime)
{
    for(int l = 0; l < f->entities_n; l ++)
    {
        if (f->game_entities[l].destroyed || f->game_entities[l].x == 0)
            continue;
        if(f->game_entities[l].type == 2)
        {
            f->game_entities[l].x += (12) * (cos(degreesToRadians((f->game_entities[l].dir))));
            f->game_entities[l].y -= (12) * (sin(degreesToRadians((f->game_entities[l].dir))));
            if(position_to_map_tiles(f->game_entities[l].x, f->game_entities[l].y, f) == 1)
                f->game_entities[l].destroyed = true;
            for(int m = 0; m < f->entities_n; m ++)
            {
                if(f->game_entities[m].type == 1 && !f->game_entities[m].killed)
                {
                    if( ((f->game_entities[l].x < f->game_entities[m].x + 15) && (f->game_entities[l].x > f->game_entities[m].x - 15) )
                        && ((f->game_entities[l].y < f->game_entities[m].y + 15) && (f->game_entities[l].y > f->game_entities[m].y - 15))
                    )
                    {
                        f->game_entities[l].destroyed = true;
                        f->game_entities[m].killed = true;
                    }
                }
            } 
        }
    }
    f->lastFixedTime = currentTime;
}
static void Update(t_cub3d *f, clock_t currentTime)
{
    double  fps;
    
    fps = (double)f->fps_counter / f->elapsedTime;
    f->fps_v = (int)(fps);
    f->fps_counter = 0;
    f->lastTime = currentTime;
    if(f->bob_left < -1)
        f->bob_left += 1;
    else if (f->bob_left > 1)
        f->bob_left -= 1;
    else
        f->bob_left = 0;
    for(int m = 0; m < f->entities_n; m ++)
    {
        if(f->game_entities[m].type == 1)
            f->game_entities[m].sprite = f->enemy[f->game_entities[m].en_i];
        if(f->game_entities[m].type == 1 && f->game_entities[m].killed)
        {
            if(f->game_entities[m].en_i < 4)
                f->game_entities[m].en_i++;
            // else
            //     f->game_entities[m].destroyed = true;
        }
    }
    if(f->shooting)
    {
        if(f->gun_i < 3)
        {
            f->gun_i++;
        }else
        {
            f->gun_i = 0;
            f->shooting = false;
        }
    }
}

int	render_next_frame(t_cub3d *f)
{

    f->fps_counter++;
    keyboard(f);
    render(f);
    clock_t currentTime = clock();
    f->elapsedTime = (double)(currentTime - f->lastTime) / CLOCKS_PER_SEC;
    f->elapsedFixedTime = (double)(currentTime - f->lastFixedTime) / CLOCKS_PER_SEC;
    // fixedupdate
    if(f->elapsedFixedTime >= 0.008)
    {
        fixedUpdate(f, currentTime);
    }
    if (f->elapsedTime >= 0.12)
    {
        Update(f, currentTime);
    }
    char a [40];
    sprintf(a,"%d",(int)(f->fps_v));
    mlx_string_put(f->fps->mlx, f->fps->win, WIDTH/2, 30, 0xFFFFFF, "CUB3D");
    mlx_string_put(f->fps->mlx, f->fps->win, WIDTH/2, 45, 0xFFFFFF, a);
    mlx_string_put(f->fps->mlx, f->fps->win, WIDTH/2 + 15, 45, 0xFFFFFF, "FPS");
    return(0);
}

const char *a[4] = {
    "./textures/01.xpm",
    "./textures/02.xpm",
    "./textures/01.xpm",
    "./textures/texture_03.xpm"
};
const char *b[2] = {
    "./textures/enemy.xpm",
    "./textures/BULLET.xpm"
};
const char *c[4] = {
    "./textures/t0.xpm",
    "./textures/t1.xpm",
    "./textures/t2.xpm",
    "./textures/t3.xpm",
};
const char *d[5] = {
    "./textures/ea.xpm",
    "./textures/eb.xpm",
    "./textures/ec.xpm",
    "./textures/ed.xpm",
    "./textures/ee.xpm"
};


static int load_imgs(t_cub3d *f)
{
    // walls
    for(int i = 0; i < 4; i ++)
    {
        f->wall_textures[i] = calloc(1, sizeof(t_image));
        if(!f->wall_textures[i])
            return (-1);
        f->wall_textures[i]->img = mlx_xpm_file_to_image(f->fps->mlx, (char *)(a[i]),
            &f->wall_textures[i]->width, &f->wall_textures[i]->height);
        if(!f->wall_textures[i]->img)
            return (-1);
        f->wall_textures[i]->bfr = mlx_get_data_addr(f->wall_textures[i]->img, &f->wall_textures[i]->bpp,
            &f->wall_textures[i]->linelen, &f->wall_textures[i]->endiant);
        //printf("f->wall_->img[%d] [%dx%d] {%d:%d} \n", i, f->wall_textures[i]->width, f->wall_textures[i]->height,
        //    f->wall_textures[i]->linelen, f->wall_textures[i]->bpp);
    }
    // sprites
    for(int i = 0; i < 2; i ++)
    {
        f->sprites[i] = calloc(1, sizeof(t_image));
        if(!f->sprites[i])
            return (-2);
        f->sprites[i]->img = mlx_xpm_file_to_image(f->fps->mlx, (char *)(b[i]),
            &f->sprites[i]->width, &f->sprites[i]->height);
        // printf("f->sprites->img[%d] [%dx%d] \n", i, f->sprites[i]->width, f->sprites[i]->height);
        if(!f->sprites[i]->img)
            return (-2);
        f->sprites[i]->bfr = mlx_get_data_addr(f->sprites[i]->img, &f->sprites[i]->bpp,
            &f->sprites[i]->linelen, &f->sprites[i]->endiant);
    }
    // gun
     for(int i = 0; i < 4; i ++)
    {
        f->gun[i] = malloc( sizeof(t_image));
        if(!f->gun[i])
            return (-3);
        f->gun[i]->img = mlx_xpm_file_to_image(f->fps->mlx, (char *)(c[i]),
            &f->gun[i]->width, &f->gun[i]->height);
        if(!f->gun[i]->img)
            return (-3);
        f->gun[i]->bfr = mlx_get_data_addr(f->gun[i]->img, &f->gun[i]->bpp,
            &f->gun[i]->linelen, &f->gun[i]->endiant);
        //printf("f->gun->img[%d] [%dx%d] {%d:%d} \n", i, f->gun[i]->width, f->gun[i]->height, f->gun[i]->linelen, f->gun[i]->bpp);
        //p_int_to_rgb( (get_texture_color(f, 10, 10, f->gun[i])));
    }
    // enemy
    for(int i = 0; i < 5; i ++)
    {
        f->enemy[i] = malloc( sizeof(t_image));
        if(!f->enemy[i])
            return (-3);
        f->enemy[i]->img = mlx_xpm_file_to_image(f->fps->mlx, (char *)(d[i]),
            &f->enemy[i]->width, &f->enemy[i]->height);
        if(!f->enemy[i]->img)
            return (-3);
        f->enemy[i]->bfr = mlx_get_data_addr(f->enemy[i]->img, &f->enemy[i]->bpp,
            &f->enemy[i]->linelen, &f->enemy[i]->endiant);
        //printf("f->gun->img[%d] [%dx%d] {%d:%d} \n", i, f->gun[i]->width, f->gun[i]->height, f->gun[i]->linelen, f->gun[i]->bpp);
        //p_int_to_rgb( (get_texture_color(f, 10, 10, f->gun[i])));
    }
    return (1);
}


int	main(int argc, char **argv)
{
	int			c;
    t_cub3d     *f;

    (void)(argc);
    (void)(argv);
    f = malloc(sizeof(t_cub3d));
    f->map = malloc(sizeof(t_mapdata));
	if (!f->map)
		return (1);
	f->map = cub_parser(argc, argv);
    f->lastTime = clock();
    f->player = malloc(sizeof(t_player));
    f->last_mouse = -1;
    if(!f || !(f->player) || !f->map)
    {
        return (EXIT_FAILURE);
    }
    // int a = f->map->width;
    // f->map->width = f->map->height;
    // f->map->height = a;
	c = init_windows(f);
	if (!c)
	{
		return (EXIT_FAILURE);
	}
	(f->player)->rot= 0;

	if(load_imgs(f) != 1)
    {
        printf("LOADING TEXTURES ERRROR AT %d \n", load_imgs(f));
	    return (EXIT_FAILURE);
    }
    printf("(f->map)->height): %d (f->map)->width: %d \n", (f->map)->height, (f->map)->width);
    if((f->map)->height > (f->map)->width)
    {
        //f->map->saved_width = f->map->height;
        f->map->width = f->map->height;
    }
    else
    {
        // f->map->saved_width = f->map->width;
        f->map->height = f->map->width;
    }
    printf("(f->map)->height): %d (f->map)->width: %d \n", (f->map)->height, (f->map)->width);
    //p_int_to_rgb(*(unsigned int *)f->wall_image->bfr);
    //init_map(f);
    init_player(f);
    init_entities(f);
    mlx_mouse_hide(f->fps->mlx, f->fps->win);
    mlx_hook(f->fps->win, 6, 1L << 6, mouse, f);
    mlx_hook(f->fps->win, 2, 1L << 0, open_hook, f);
    mlx_hook(f->fps->win, 3, 1L << 1, close_hook, f);
    mlx_hook(f->fps->win, 4, 1L << 2, hook_mousedown, f);
    mlx_loop_hook(f->fps->mlx, render_next_frame, f);
	mlx_loop(f->fps->mlx);
	return (0);
}