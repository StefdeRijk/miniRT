#include "miniRT.h"
#include <math.h>

float   hit_plane(t_plane plane, t_ray r)
{
    t_vec3f p_min_l;
    float   dot_plane_orientation;
    float   dot_l_n;

    p_min_l = vec3f_sub(plane.pos, r.origin);
    dot_plane_orientation = vec3f_dot(p_min_l, plane.dir);
    dot_l_n = vec3f_dot(r.dir, plane.dir);
    return (dot_plane_orientation / dot_l_n);
}
