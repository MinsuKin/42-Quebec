/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:17:58 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 14:34:58 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

# define WIDTH 1200
# define HEIGHT 900
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.1
# define X 1
# define Y 0

// Enum for key codes
enum {
	W_KEY = 13,
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	L_KEY = 123,
	R_KEY = 124,
	ESC_KEY = 53
};

// Enum for MLX functions
enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// Enum for map values
enum {
	EMPTY = 0,
	WALL = 1,
	PLAYER = 2,
	SPACE = 3
};

enum {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

#endif // CUB3D_DEFINES_H
