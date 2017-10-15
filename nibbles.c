# include "nibbles.h"
# include <string.h>
# include <stdio.h>
void static print_bin(mdl_u8_t __byte) {
	for (mdl_u8_t i = 0; i != 8; i++)
		printf("%u", __byte>>(7-i)&0x1);
	printf("\n");
}

void *nib_compress(void *__nib_args) {
	nib_args_t *nib_args = (nib_args_t*)__nib_args;

	mdl_u8_t *buff_itr = nib_args->buff;
	mdl_u8_t *data_itr = nib_args->data;

	mdl_u8_t *flag_buff = (mdl_u8_t*)malloc(1<<4);
	memset(flag_buff, 0x0, 1<<4);
	mdl_u8_t *flag_itr = flag_buff;

	memset(nib_args->buff, 0x0, nib_args->buff_bc);
	mdl_u8_t off = 0;
	do {
		if (*data_itr == *(data_itr+1) && *buff_itr < 0xF) {
			if (!((*buff_itr)++)) *(buff_itr+1) = *data_itr;
			continue;
		}

		if (*buff_itr > 0)
			printf("blk_size: %u\n", *buff_itr);

		if (off == 8) {
	//		print_bin(*flag_itr);
			mdl_uint_t fbi_off = flag_itr-flag_buff;
//			printf("----> %u - %u\n", ((fbi_off>>4)+1)*(1<<4), fbi_off);
			if (fbi_off+1 > (((fbi_off>>4)+1)*(1<<4))-1) {
				printf("Hello %u\n\n", fbi_off);
				flag_buff = (mdl_u8_t*)realloc(flag_buff, (fbi_off+1)+(1<<4));
				memset(flag_buff+(fbi_off+1), 0x0, 1<<4);
				flag_itr = flag_buff+fbi_off;
			}
			flag_itr++;
			off = 0;
		}

		if (!*(buff_itr++)) {
			*flag_itr |= 1<<off;
			*(buff_itr-1) = *data_itr;
		} else
			buff_itr++;
		off++;
/*
		if (!*(buff_itr++)) {
			*buff_itr = 0;
			*(buff_itr++) = *data_itr;
		} else buff_itr++;
*/
	} while((++data_itr) < nib_args->data+nib_args->data_bc-1);

	buff_itr+=(flag_itr-flag_buff)+1;
	printf("%u\n", flag_itr-flag_buff);
	mdl_u8_t i = 0;
	mdl_u8_t *end = buff_itr-((flag_itr-flag_buff)+1);
	while(buff_itr != end) {
		print_bin(*(flag_buff+i));
		*(buff_itr--) = *(flag_buff+(i++));
	}

	nib_args->size = (buff_itr-nib_args->buff)+(i+1);
}

void *nib_uncompress(void *__nib_args) {
	nib_args_t *nib_args = (nib_args_t*)__nib_args;

	mdl_u8_t *buff_itr = nib_args->buff;
	mdl_u8_t *data_itr = nib_args->data;
	mdl_u8_t *flag_itr = nib_args->data+(nib_args->data_bc-1);
	mdl_u8_t off = 0;
	printf("----> %u\n", nib_args->data_bc);

	do {
		print_bin(*flag_itr);

		if (off == 8) {
			off = 0;
			flag_itr--;
		}

		if (!((*flag_itr)>>off&0x1)) {
			printf("----|> %c\n", *(buff_itr+1));
			_again:
			if (((*data_itr)--) != 0) {
				*(buff_itr++) = *(data_itr+1);
				goto _again;
			}
			data_itr++;
		}

		*(buff_itr++) = *data_itr;

		off++;
	} while((++data_itr) < nib_args->data+(nib_args->data_bc-(((nib_args->data+nib_args->data_bc)-flag_itr)+1)));

	nib_args->size = buff_itr-nib_args->buff;
}
