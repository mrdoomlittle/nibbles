# include "nibbles.h"

void *nib_compress(void *__nib_args) {
	nib_args_t *nib_args = (nib_args_t *)__nib_args;

	uint8_t sme_count = 0;
	uint_t cmp_size = 0, data_point = 0;
	uint8_t bypass = 0;
	do {
		if (*nib_args-> data == *(nib_args-> data + 1)) {
			if (sme_count == 233)
				bypass = 1;
			else
				sme_count++;
		}

		if (*nib_args-> data != *(nib_args-> data + 1) || bypass) {
			*nib_args-> buff = sme_count == 0? 1 : sme_count + 1;
			*(nib_args-> buff + 1) = *nib_args-> data;
			nib_args-> buff += 2;
			cmp_size += 2;
			sme_count = 0;
			bypass = 0;
		}
		++ nib_args-> data;
		data_point ++;
	} while(data_point < nib_args-> data_len);
	nib_args-> size = cmp_size;
}

void *nib_uncompress(void *__nib_args) {
	nib_args_t *nib_args = (nib_args_t *)__nib_args;

	uint_t ucmp_size = 0, data_point = 0;
	do {
		if (*nib_args-> data == 1) {
			*nib_args-> buff = *(nib_args-> data + 1);
			++ nib_args-> buff;
			ucmp_size++;
		} else {
			for (uint8_t o = 0; o != *nib_args-> data; o ++) {
				*nib_args-> buff = *(nib_args-> data + 1);
				++ nib_args-> buff;
				ucmp_size++;
			}
		}

		nib_args-> data += 2;
		data_point += 2;
	} while(data_point < nib_args-> data_len);
	nib_args-> size = ucmp_size;
}
