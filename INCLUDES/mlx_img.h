/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 14:33:49 by vgauther          #+#    #+#             */
/*   Updated: 2019/04/17 11:30:39 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_img
{
	void 	*img;
	char 	*img_str;
	int		bits;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_data
{
	void 	*mlx;
	void 	*win;
	t_img 	image;
}				t_data;

typedef struct	s_pixel
{
	int x;
	int y;
}				t_pixel;

#endif
