#include "matrix.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

void
pivot_ge_in_situ_matrix (matrix_t * c)
{
  int i, j, k;
  int cn = c->cn;	// liczba kolumn 
  int rn = c->rn;	// liczba wierszy
  double *e = c->e;	// macierz w postaci ciagu
  for (k = 0; k < rn - 1; k++) {        /* eliminujemy (zerujemy) kolumnę nr k */
    int piv = k;                /* wybór elementu dominującego - maks. z k-tej kol., poniżej diag */
    for (i = k + 1; i < rn; i++)
      if (fabs (*(e + i * cn + k)) > fabs (*(e + piv * cn + k)))
        piv = i;
    if (piv != k) {             /* jeśli diag. nie jest pivtem - wymień wiersze */
      xchg_rows (c, piv, k);
    }
    for (i = k + 1; i < rn; i++) {      /* pętla po kolejnych
                                           wierszach poniżej diagonalii k,k */
      double d = *(e + i * cn + k) / *(e + k * cn + k);
      for (j = k; j < cn; j++)
        *(e + i * cn + j) -= d * *(e + k * cn + j);
    }
  }
}

void
pivot_gs_in_situ_matrix (matrix_t * c)
{
	int i, j, t;		// zmienne pomocnicze
	int cn = c->cn;		// liczba kolumn
	int rn = c->rn;		// liczba wierszy
	double *e = c->e;	// macierz w postaci ciagu
	double tol = 0.1;	// tolerancja
	double x;
	int maxit = 1000; 	// liczba iteracji
	double *xp = malloc(rn * sizeof *xp); // ciag wynikow zmiennych
	memset (xp, 0.0, rn);

	for ( t = 0; t < maxit; t++ ) {
		for(i = 0; i < rn; i++) {
			x = 0.0;
			for (j = 0; j < cn - 1; j++) {
				x -= ( e[i*cn + j] * xp[j] );
			}
			x += ( e[i*cn + i] * xp[i] );
			x += e[(i+1)*cn - 1];
			xp[i] = x / e[i*cn + i];
		}
	}
	
	for (i = 0; i < rn; i++) {
		for (j = 0; j < (cn - 1); j++) {
			if (i == j) { 
				e[j+i*cn] = 1;
			} else {
				e[j+i*cn] = 0;
			}
		}
		e[(i+1)*cn - 1] = xp[i];
	}
}
