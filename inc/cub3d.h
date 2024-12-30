/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusic <ahusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:12:53 by ahusic            #+#    #+#             */
/*   Updated: 2024/12/30 22:59:06 by ahusic           ###   ########.fr       */
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

//Utils map
int		check_newline(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		file_to_map(int fd, t_data *map, char *line);

//utils
int		convert_rgb(int r, int g, int b);
char	*skip_newline(int fd);
int		is_texture(char *line);
int		is_color(char *content);
int		is_rgb(char *str);

#endif
