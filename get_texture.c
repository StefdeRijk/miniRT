#include "miniRT.h"

t_vec3f	get_plane_texture(t_plane plane, t_vec3f plane_pos, t_ray r, t_hits hit)
{
	t_plane	texture_plane;
	int		bump_x;
	int		bump_y;
	int		base_index;

	bump_x = ((int)(fabsf(plane_pos.x) * plane.texture.width)) \
		% plane.texture.width;
	bump_y = ((int)(fabsf(plane_pos.y) * plane.texture.height)) \
		% plane.texture.height;
	base_index = bump_x * plane.bump_map.bytes_per_pixel + \
		bump_y * plane.bump_map.bytes_per_row;
	texture_plane = plane;
	texture_plane.color.x = (float)plane.texture.data[base_index] / 255;
	texture_plane.color.y = (float)plane.texture.data[base_index + 1] / 255.;
	texture_plane.color.z = (float)plane.texture.data[base_index + 2] / 255.;
	if (BONUS && plane.material == CHECKER)
		return (get_color_checkerboard_plane(texture_plane, r, hit.hit_min));
	return (texture_plane.color);
}
