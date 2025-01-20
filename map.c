/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:17:45 by jsaintho          #+#    #+#             */
/*   Updated: 2025/01/20 16:11:30 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int position_to_map_tiles(int px, int py, t_cub3d *f)
{
	if(px > WIDTH || py > HEIGHT || px < 0 || py < 0)
		return (1);
	if((int) (px / (WIDTH / (f->map)->width)) >= (f->map)->width
		|| (int)((py / (HEIGHT / (f->map)->height))) >= (f->map)->height )
		return (1);
	if(  (f->map)->map_matrix[(int)(
			(py / (HEIGHT / (f->map)->height))
		)][(int)(
			(px / (WIDTH / (f->map)->width))
		)] == '1')
	{
		return (1);
	}else
	{
		return (0);
	}
}

void	nxt_horz_inter(float alpha, float *p_x, float *p_y, t_cub3d *f)
{
	float	AY;
	float	AX;
	int		h_tick;
	
	h_tick = (HEIGHT / (f->map)->height);
	if(sin(degreesToRadians(alpha)) > 0 )
	{
		AY = (float)((*p_y) - (int)(*p_y) % h_tick) - 0.1;
	}
	else
	{
		AY = (*p_y) + (float)(h_tick - ((int)(*p_y) % h_tick));
	}
	AX = (*p_x) + (*p_y - AY)/(float)(tan(degreesToRadians(alpha)));
	*p_x = AX;
	*p_y = AY;

}

void	nxt_vert_inter(float alpha, float *p_x, float *p_y, t_cub3d *f)
{
	float	AY;
	float	AX;
	int		v_tick;

	v_tick = (WIDTH / (f->map)->width);
	if(cos(degreesToRadians(alpha)) < 0)
	{
		AX = (float)((*p_x) - (int)(*p_x) % v_tick) - 0.1;
	}else
	{
		AX = (*p_x) + (float)((v_tick - ((int)(*p_x) % v_tick)));
	}
	AY = (*p_y) + (*p_x - AX)*tan(degreesToRadians(alpha));
	*p_x = AX;
	*p_y = AY;
}

void    init_map(t_cub3d *t)
{
    // t->map = malloc(sizeof(t_map));
    // if (!t->map)
    //     return ;
    // (t->map)->width = 10;
    // (t->map)->height = 10;
    // (t->map)->v = malloc((t->map)->height * sizeof(int *));
    // for(int i = 0; i < (t->map)->height; i++)
    // {
    //     (t->map)->v[i] = (int *) malloc(sizeof(int) * ((t->map)->width + 1));
    //     for(int j = 0; j < (t->map)->width; j ++)
    //     {
    //         (t->map)->v[i][j] = map[i][j];
    //     }
    // }
}