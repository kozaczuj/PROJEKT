#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>

typedef struct {
		int n;		// liczba punktów
		double *x;	// x punktów
		double *y;	// y punktów
} points_t;

int read_pts_failed ( FILE* inf, points_t *pts);

#endif
