/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:12:53 by ahusic            #+#    #+#             */
/*   Updated: 2025/02/12 19:13:35 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libraries/Libft/libft.h"
# include "../libraries/get_next_line/get_next_line_bonus.h"
# include "cub3d_structs.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Checks
int				check_file_extension(char *filename);
int				check_texture(char *path);
int				check_color(char **rgb);

// Utils map
int				check_newline(char *str);
char			*ft_strjoin_gnl(char *s1, char *s2);
int				file_to_map(int fd, t_data *map, char *line);
void			free_2d_array(char **array);
int				save_texture(t_data *data, char *id, char *path);

// Utils
int				convert_rgb(int r, int g, int b, int a);
char			*skip_newline(int fd);
int				is_texture(char *line);
int				is_color(char *content);
int				is_rgb(char *str);

// Map check
int				char_position_check(t_data *data);
int				map_check(t_data *data);
int				check_valid_position(t_data *data, int x, int y);
int				is_map_complete(t_data *data);

// Parsing
int				map_parse(int fd, t_data *data, char *line);
int				texture_parse(char *content, t_data *data);
int				color_parse(char *content, t_data *data, char type);
int				save_content(char *content, t_data *data, int fd);

// Raycasting

t_ray			cast_ray(t_data *data, t_player *player, double ray_angle);
void			draw_scene(t_data *data, mlx_image_t *img);
void			key_hook(void *param);
void			init_player(t_data *data);

// Minimap and other

void			draw_minimap(t_data *data);
void			init_data(t_data *data);
void			game_loop(void *param);
void			draw_scene_wrapper(void *param);
void			handle_keypress(void *param);
void			render_frame(void *param);
void			render_walls(t_data *data);
void			init_ray(t_data *data, int x, t_ray *ray);
int				set_player_pos(t_data *data, int i, int j);
void			cleanup_textures(t_data *data);
void			draw_square(t_data *data, t_pos pos, int size, uint32_t color);
int				is_valid_pos(t_data *data, int map_x, int map_y);
void			handle_rotation(t_data *data);
int				calc_tex_x(t_ray *ray, t_data *data, mlx_texture_t *texture,
					int side);
mlx_texture_t	*select_texture(t_data *data, t_ray *ray, int side);
void			calc_wall_height(t_wall *wall, t_ray *ray, t_data *data,
					int side);
void			calc_ray_values(t_ray *ray, t_player *player, double ray_angle);
void			calc_step_y(t_ray *ray, t_player *player);
void			handle_input(void *param);
void			draw_textured_line(t_data *data, t_wall *wall, t_ray *ray,
					int x);
bool			load_textures(t_data *data);
mlx_texture_t	*scale_texture(mlx_texture_t *texture, int new_width,
					int new_height);
char			*join_strings(char *s1, char *s2, int should_free_s1);
int				line_process(char **map_str, char *line, t_data *map);
int				set_texture_path(char **texture_path, char *path);
void			set_wall_color(t_ray *ray, t_wall *wall, int side);
void			copy_pixel(uint8_t *dst, uint8_t *src);
void			scale_pixels(mlx_texture_t *scaled, mlx_texture_t *texture,
					int new_width, int new_height);
int				init_game(t_data *data, char *map_path);

void			cleanup_map(t_data *data);
void			cleanup_texture_paths(t_data *data);
void			draw_tile(t_data *data, t_pos pos, char tile, int square_size);
uint32_t		get_tile_color(char tile);
int				get_max_width(t_data *data);
void			handle_minimap(t_data *data, int *cooldown,
					bool *minimap_toggle);

#endif
