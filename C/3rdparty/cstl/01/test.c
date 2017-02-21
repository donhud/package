/*************************************************************************
* File Name: main.c
* Author: Don Hu
* Mail: hudeng@staff.sina.com.cn
* Create Time: 2015-10-10 03:04:50
* Last modified: 2015-10-10 04:56:54
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "cstl/cvector.h"

int main(int argc, char *argv)
{
	vector_t *pvec = create_vector(int);
	iterator_t it;
	size_t i = 0;

	if(pvec == NULL) {
		return -1;
	}

	vector_init(pvec);
	for(i = 0; i < 10; i++) {
		vector_push_back(pvec, i * 100);
	}

#if 0
	for(i = 0; i < vector_size(pvec); i++) {
		printf("%d, ", *(int *)vector_at(pvec, i));
	}
#else
	for(it = vector_begin(pvec); !iterator_equal(it, vector_end(pvec)); it = iterator_next(it)) {
		printf("%d, ", *(int *)iterator_get_pointer(it));
	}
#endif

	printf("\n");

	vector_destroy(pvec);

	return 0;
}

