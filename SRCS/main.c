/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:40:29 by vgauther          #+#    #+#             */
/*   Updated: 2019/04/17 12:24:08 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/mlx_img.h"

#define D_BLUE 255
#define D_RED 16711680
#define D_GREEN 65280
#define D_YELLOW 16776960
#define D_PURPLE 16711935
#define D_BLACK 0
#define D_WHITE 16777215

#define WIN_LEN 1000
#define WIN_HEIGHT 1000



void	put_pixel_image(t_pixel pixel, char *str, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int len;

	len = WIN_LEN;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	str[(pixel.x * 4) + (len * 4 * pixel.y)] = b;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 1] = g;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 2] = r;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 3] = 0;
}

/*
** In this function we just have 'whiles' to create the square patern. The important
** things are in the put_pixel_image function
*/

void			print_square(int left_corner_x, int left_corner_y, int len_in_pixels, t_data *data)
{
	t_pixel		pix;
	int			y_stop;
	int			x_stop;

	x_stop = left_corner_x + len_in_pixels;
	y_stop = left_corner_y + len_in_pixels;
	pix.y = left_corner_y;

	while (pix.y != y_stop)
	{
		pix.x = left_corner_x;
		while (pix.x != x_stop)
		{
			put_pixel_image(pix, data->image.img_str, D_RED);
			pix.x++;
		}
		pix.y++;
	}
}

int				ft_key_pressed(int k, void *param)
{
	if (k == 53) /* on a qwerty macbook keyboard the esc keyboard key number is 53 */
		exit(0);
	return (0);
	(void)param;
}

int				main(void)
{
	t_data data;

	data.mlx = mlx_init(); /* initialization of mlx */
	data.win = mlx_new_window(data.mlx, WIN_LEN, WIN_HEIGHT, "MLX_IMG"); /* window's creation */

	data.image.img = mlx_new_image(data.mlx, WIN_LEN, WIN_HEIGHT);
	data.image.img_str = mlx_get_data_addr(data.image.img, &data.image.bits, &data.image.size_line, &data.image.endian);

	mlx_hook(data.win, 2, 0, ft_key_pressed, &data); /* it looks if a key is pressed then she launch a function (here: ft_key_pressed)*/

	print_square(0, 0, 500, &data); /* print a square look for it to understand how to put pixel in image */

	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0); /* print the image you created on the window */
	mlx_destroy_image(data.mlx, data.image.img); /* to avoid leaks you have to destroy the image before creating an other */

	mlx_loop(data.mlx); /* mlx_loop allow the program to keep looking for user's actions */

	return (0);
}
