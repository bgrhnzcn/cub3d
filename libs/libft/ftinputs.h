#ifndef FTINPUTS_H
# define FTINPUTS_H

# ifdef __linux__

#  include <X11/keysym.h>
#  define ESC_KEY XK_Escape
#  define X_KEY XK_x
#  define Z_KEY XK_z
#  define O_KEY XK_o
#  define Q_KEY XK_q
#  define W_KEY XK_w
#  define E_KEY XK_e
#  define R_KEY XK_r
#  define A_KEY XK_a
#  define S_KEY XK_s
#  define D_KEY XK_d
#  define F_KEY XK_f
#  define P_KEY XK_p

# else

#  define ESC_KEY 53
#  define X_KEY 7
#  define Z_KEY 6
#  define O_KEY 31
#  define P_KEY 35

# endif

#endif