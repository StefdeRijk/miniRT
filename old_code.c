
// ray_color different materials, s = smooth, m = matt
if (sphere.material == 's')
{
	// norm_dir = vec3f_unit(vec3f_sub(at(r, hit_min), sphere.pos));
	// reflection = vec3f_sub(r.dir, (vec3f_mul(norm_dir, 2 * vec3f_dot(r.dir, norm_dir))));
	norm_dir = get_normal_sphere(at(r, hit_min), sphere.pos);
	reflection = f_reflection(r.dir, norm_dir);
	r.origin = at(r, hit_min);
	r.dir = reflection;
}
else if (sphere.material == 'm')
{}