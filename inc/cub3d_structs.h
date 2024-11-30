/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:09:48 by ahusic            #+#    #+#             */
/*   Updated: 2024/11/30 21:27:31 by ahusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 800
# define FOV 60
# define TILE_SIZE 64
# define SPEED 5
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define M_PI 3.14159265358979323846
# define NORTH 4.7123889804 // 3 * PI / 2
# define SOUTH 1.5707963268 // PI / 2
# define WEST 3.1415926535 // PI
# define EAST 0

typedef struct s_player
{
	int		player_x;
	int		player_y;
	double	angle;
	float	fov;
	int		rotation;
	int		l_r; // left and right flag
	int		u_d; // up and down flag
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
	// need to add more
}	t_ray;

#endif
