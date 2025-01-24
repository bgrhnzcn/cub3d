/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:20:28 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/20 20:13:07 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INPUTS_H
# define FT_INPUTS_H

# ifdef __linux__

#  define ESC_KEY 0xff1b
#  define X_KEY 0x0078
#  define Z_KEY 0x007a
#  define O_KEY 0x006f
#  define Q_KEY 0x0071
#  define W_KEY 0x0077
#  define E_KEY 0x0065
#  define R_KEY 0x0072
#  define A_KEY 0x0061
#  define S_KEY 0x0073
#  define D_KEY 0x0064
#  define F_KEY 0x0066
#  define P_KEY 0x0070
#  define RIGHT_KEY 0xff53
#  define LEFT_KEY 0xff51
#  define UP_KEY 0xff52
#  define DOWN_KEY 0xff54

# else

#  define ESC_KEY 53
#  define X_KEY 7
#  define Z_KEY 6
#  define O_KEY 31
#  define Q_KEY 12
#  define W_KEY 13
#  define E_KEY 14
#  define R_KEY 15
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define F_KEY 3
#  define P_KEY 35
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define UP_KEY 126
#  define DOWN_KEY 125

# endif

typedef enum e_mlx_event
{
	KeyPress = 2,
	KeyRelease = 3,
	ButtonPress = 4,
	ButtonRelease = 5,
	MotionNotify = 6,
	Expose = 12,
	Destroy = 17
}	t_mlx_event;

#endif
