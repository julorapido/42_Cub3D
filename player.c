/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:55:57 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/20 16:53:58 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void aff(float px, float py, t_cub3d *f)
{
    if (f->Ast_frm_player > f->Bst_frm_player2)
    {
        if(py > f->player->y)
            f->texture_x = TEXTURE_WIDTH - f->texture_x;
        if(px > f->player->x)
        {
            f->i = f->wall_textures[EAST];
        }
        else
            f->i = f->wall_textures[WEST];
    }else
    {
        if(px > f->player->x)
            f->texture_y = TEXTURE_HEIGHT - f->texture_y;
        if(py > f->player->y)
        {
            f->i = f->wall_textures[SUD];
        }
        else
            f->i = f->wall_textures[NORD];
    }
}

void raycasting(t_cub3d *f)
{
    int     x;
    float   a;

    a = 0.001;
    x = WIDTH - 1;
    f->beta = FOV/2;
    while (a < FOV)
    {
        init_ray_loop(f);
        throw_ray_loop(f, a);
        f->texture_x = (TEXTURE_WIDTH) * ((int)(f->px) % (WIDTH /f->map->width)) / (WIDTH / f->map->width);
        f->texture_y = (TEXTURE_HEIGHT) * ((int)(f->py) % (HEIGHT / f->map->height)) / (HEIGHT / f->map->height);
        aff(f->px, f->py, f);
        draw_fps_texturedRay(f->fps, 
            x, 
            (f->dst_to_wall * cos(degreesToRadians(f->beta))) * 0.5,
            terner(f),
            f,
            f->i,
            degreesToRadians(f->player->rot + a)
        );
        x--;
        a += (float)(FOV)/ (float)(WIDTH);
    }
}
void shoot(t_cub3d *f)
{
    f->shooting = true;
    f->gun_i = 0;
    float p = (f->player)->rot;
    init_projectile(f, f->player->x, f->player->y, p + 30);
}
void render_gun(t_cub3d *f)
{
    int y;
    int x;

    y = (4 * F_);
	while(y < 128 * F_)
	{
        x = 0;
		while(x < 128 * F_)
		{
            if (get_texture_color(f, (x/F_), (128 - (y/ F_)), f->gun[(f->gun_i)]) != -16777216)
            {
                set_pixel_color(f->fps,
                    (WIDTH / 2) - ((128 / 2) * F_ )+ x,
                    (HEIGHT - (y - (4 * F_))),
                    get_texture_color(f, (x / F_), (128 - (y / F_)), f->gun[f->gun_i])
                );
            }
            x++;
		}
        y++;
    }
}

int	close_hook(int k_code, t_cub3d *f)
{
    if(f->k_code == -1){
        return (0);
	}
    // Z
    if (k_code == 119)
        f->z = false;
    // S
    if (k_code == 115)
        f->s = false;
    // Q
    if (k_code == 97)
        f->q = false;
    // D
    if (k_code == 100)
        f->d = false;
    if(k_code == 113) // Q
        f->a = false;
    if(k_code == 101) // E
        f->e = false;
    return (0);
}
int open_hook(int k_code, t_cub3d *f)
{
    if(f->k_code == -1){
        return (0);
	}
    printf("open [%d] \n", k_code);
    // Z
    if (k_code == 119){
        f->z = true;
        printf("Z \n");
    }
    // S
    if (k_code == 115)
        f->s = true;
    // Q
    if (k_code == 97)
        f->q = true;
    // D
    if (k_code == 100)
        f->d = true;
    if(k_code == 113) // Q# define WIDTH 1000

        f->a = true;
    if(k_code == 101) // E
        f->e = true;
	return(0);
}
int	mouse(int x, int y, t_cub3d *f)
{
    if(f->last_mouse < x)
    {
        (f->player)->rot -= 1;
    }else if (f->last_mouse > x)
    {
        (f->player)->rot += 1;
    }    
}


int	hook_mousedown(int k_code, long x, long y, t_cub3d *f)
{
    (void)(x);
    (void)(y);
    if(k_code == 1)
        shoot(f);
}
int	keyboard(t_cub3d *f)
{
    if(f->k_code == -1){
        return (0);
	}
    if (f->k_code == K_ESC){
		exit(0);
    }else
	{
        // Z
        if (f->z)
        {
            if(position_to_map_tiles(
                (f->player)->x + 8 *(cos(degreesToRadians((f->player->rot + FOV/2 + 0)))),
                (f->player)->y - 8 *(sin(degreesToRadians((f->player->rot + FOV/2 + 0)))),
                f) != 1)
            {
                (f->player)->x += roundf(6 * (cos(degreesToRadians((f->player->rot + FOV/2 )))));
                (f->player)->y -= roundf(6 * (sin(degreesToRadians((f->player->rot + FOV/2 )))));
            }
        }
        // S
        if (f->s)
        {
            if(position_to_map_tiles(
                (f->player)->x + 8 * (cos(degreesToRadians((f->player->rot + FOV/2 + 180)))),
                (f->player)->y - 8 * (sin(degreesToRadians((f->player->rot + FOV/2 + 180)))),
                f) != 1)
            {
                (f->player)->x += roundf(6 * cos(degreesToRadians((float)(f->player->rot + FOV/2 + 180))));
                (f->player)->y -= roundf(6 * sin(degreesToRadians((float)(f->player->rot + FOV/2 + 180))));
            }
        }
        // Q
        if (f->d)
        {
            if(position_to_map_tiles(
                (f->player)->x + 8 * (cos(degreesToRadians(f->player->rot + FOV/2 - 90))),
                (f->player)->y - 8 * (sin(degreesToRadians((f->player->rot + FOV/2 - 90)))),
                f) != 1)
            {
                (f->player)->x += roundf(6 * (cos(degreesToRadians((f->player->rot + FOV/2 - 90)))));
                (f->player)->y -= roundf(6 * (sin(degreesToRadians((f->player->rot + FOV/2 - 90)))));
            }
        }
        // D
        if (f->q)
        {
            if(position_to_map_tiles(
                (f->player)->x + 8 * (cos(degreesToRadians((f->player->rot + FOV/2 + 90)))),
                (f->player)->y - 8 * (sin(degreesToRadians((f->player->rot + FOV/2 + 90)))),
                f) != 1)
            {
                (f->player)->x += roundf(6 * (cos(degreesToRadians((f->player->rot + FOV/2 + 90)))));
                (f->player)->y -= roundf(6 * (sin(degreesToRadians((f->player->rot + FOV/2 + 90)))));
            }
        }
        if(f->a) // A
            (f->player)->rot+= 4;
        if(f->e) // E11111111
            (f->player)->rot-= 4;
	}
	return (0);
}

void init_player(t_cub3d *f)
{
    (f->player)->rot= 0;
    (f->gun_i) = 0;
    (f->player)->health = 100;
    for(int i = 0; i < (f->map)->width; i ++)
    {
        for(int j = 0; j < (f->map)->height; j ++)
        {
            if((f->map)->map_matrix[i][j] == 'E')
            {
                (f->player)->x = (j * (WIDTH / (f->map)->width)) + (WIDTH / ((f->map)->width) / 2);
                (f->player)->y = (i * (HEIGHT / (f->map)->height)) + (HEIGHT / ((f->map)->height) / 2);
            }
        }
    }
}
