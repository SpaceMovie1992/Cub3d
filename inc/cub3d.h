/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:12:53 by ahusic            #+#    #+#             */
/*   Updated: 2025/01/05 17:49:39 by ahusic           ###   ########.fr       */
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

// Parsing
int		map_parse(int fd, t_data *data, char *line);
int		texture_parse(char *content, t_data *data);
int		color_parse(char *content, t_data *data, char type);
int		save_content(char *content, t_data *data, int fd);

#endif
