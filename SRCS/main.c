/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgauther <vgauther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 15:40:29 by vgauther          #+#    #+#             */
/*   Updated: 2019/04/10 21:42:31 by vgauther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/fdf.h"

void	put_pixel_image(t_pixel pixel, t_data win1, char *str, int color)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int len;

	len = 1000;

	pixel.color = color;
	r = (pixel.color >> 16) & 0xff;
	g = (pixel.color >> 8) & 0xff;
	b = pixel.color & 0xff;
	str[(pixel.x * 4) + (len * 4 * pixel.y)] = b;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 1] = g;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 2] = r;
	str[(pixel.x * 4) + (len * 4 * pixel.y) + 3] = 0;
	(void)win1;
}

void				recup_data_from_the_file(char *file_name)
{
	char *gnl_ret;
	int fd;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &gnl_ret) == 1)
	{
		ft_putstr(gnl_ret);
		ft_putstr("\n");
		free(gnl_ret);
	}
}

int				ft_key_pressed(int k, void *param)
{
	if (k == 53)
	{
		exit(0);
	}
	return (0);
	(void)param;
}

int				main(int ac, char **av)
{
	t_data data;
	int i1;
	int i2;
	int i3;
	t_pixel pix;

	pix.x = 20;
	pix.y = 20;
	pix.color = 400000;

	if (ac != 2)
	{
		ft_putstr("Usage : ./fdf <filename>\n");
		return (0);
	}


	recup_data_from_the_file(av[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1000, 1000, "FDF");
	data.image.img = mlx_new_image(data.mlx, 1000, 1000);
	data.image.img_str = mlx_get_data_addr(data.image.img, &i1, &i2, &i3);
	mlx_hook(data.win, 2, 0, ft_key_pressed, &data);
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 21;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 22;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 23;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 24;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 25;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 26;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 27;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	pix.y = 28;
	put_pixel_image(pix,data,data.image.img_str,4000000);
	mlx_put_image_to_window(data.mlx, data.win, data.image.img, 0, 0);
	mlx_destroy_image(data.mlx, data.image.img);

	mlx_loop(data.mlx);
	(void)av;
	return (0);
}
