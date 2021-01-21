#include "piv_gs_solver.h"
#include <stdlib.h>

int piv_gs_solver (matrix_t * eqs)
{
	if (eqs != NULL) {
		pivot_gs_in_situ_matrix (eqs);
		if (bs_matrix (eqs) == 0) {
			return 0;
		} else {
			return 1;
		}
	} else return 1;
}
