#include "miniRT.h"

#define SPOT_BRIGHTNESS 70

t_vec3f spot_light(t_ray r, t_scene *scene)
{
	t_vec3f		spot_unit;
	t_vec3f		ray_unit;
	t_vec3f		spot_color;
    float       distance_sq;
	float		in_product;

    spot_unit = vec3f_sub(scene->light->pos, r.origin);
    distance_sq = vec3f_len_sq(spot_unit);
    spot_unit = vec3f_unit(spot_unit);
    ray_unit = vec3f_unit(r.dir);
    in_product = vec3f_dot(spot_unit, ray_unit);
    if (in_product < 0)
        in_product = 0;
    spot_color = vec3f_mul(scene->light->color, ((scene->light->brightness * in_product) / distance_sq) * SPOT_BRIGHTNESS);
    return (spot_color);
}
