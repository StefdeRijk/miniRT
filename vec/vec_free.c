#include "vec.h"
#include <stdlib.h>

void	vec_free(t_vec vec)
{
	free(vec.data);
}
