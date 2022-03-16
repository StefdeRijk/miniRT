#include "miniRT.h"

t_vec3f read_bump(t_bmp bump_map, int x, int y)
{
	int index;
	t_vec3f bump_normal;

	index = x * bump_map.bytes_per_pixel
		+ y * bump_map.bytes_per_row;
	bump_normal.x = (float)bump_map.data[index] / 128. - 1.;
	bump_normal.y = (float)bump_map.data[index + 1] / 128. - 1.;
	bump_normal.z = (float)bump_map.data[index + 2] / 128. - 1.;
	return (bump_normal);
}
