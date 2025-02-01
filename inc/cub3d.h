/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:12:53 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/01 18:10:02 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libraries/Libft/libft.h"
# include "../libraries/get_next_line/get_next_line_bonus.h"
# include "cub3d_structs.h"

// Checks
int		check_file_extension(char *filename);
int		check_texture(char *path);
int		check_color(char **rgb);

// Utils map
int		check_newline(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		file_to_map(int fd, t_data *map, char *line);
void	free_2d_array(char **array);
int		save_texture(t_data *data, char *id, char *path);

// Utils
int		convert_rgb(int r, int g, int b, int a);
char	*skip_newline(int fd);
int		is_texture(char *line);
int		is_color(char *content);
int		is_rgb(char *str);

// Map check
int		char_position_check(t_data *data);
int		map_check(t_data *data);
int		check_valid_position(t_data *data, int x, int y);
int		is_map_complete(t_data *data);

// Parsing
int		map_parse(int fd, t_data *data, char *line);
int		texture_parse(char *content, t_data *data);
int		color_parse(char *content, t_data *data, char type);
int		save_content(char *content, t_data *data, int fd);

// Raycasting

t_ray	cast_ray(t_data *data, t_player *player, double ray_angle);
// void	draw_scene(t_data *data, t_player *player, mlx_image_t *img);
void	key_hook(void *param);
void	init_player(t_data *data);

//TESTINGWTFFISGOINGONNN

void	init_data(t_data *data);
void	game_loop(void *param);
void	draw_scene_wrapper(void *param);
void 	handle_keypress(mlx_key_data_t keydata, void *param);
void 	render_frame(void *param);
void 	draw_scene(t_data *data, mlx_image_t *img);

#endif
