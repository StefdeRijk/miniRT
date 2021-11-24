#include "vec.h"

t_vec2i	vec2i_trans(t_vec2i v, t_direction dir)
{
	t_vec2i	vr;

	vr = v;
	if (dir == UP)
		vr.y--;
	if (dir == DOWN)
		vr.y++;
	if (dir == LEFT)
		vr.x--;
	if (dir == RIGHT)
		vr.x++;
	return (vr);
}
