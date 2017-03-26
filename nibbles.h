# ifndef __mdl__nibbles__h
# define __mdl__nibbles__h
# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <eint_t.h>
# define NIB_SUCCESS 0
# define NIB_FAILURE -1
# define NIB_COMPRESS 0
# define NIB_UCOMPRESS -1

# ifdef __cplusplus
extern "C" {
# endif

typedef struct {
	uint8_t *data;
	size_t data_len;
	uint8_t *buff;
	size_t buff_len;
	size_t size;
} nib_args_t;

size_t nibbles(uint8_t *, size_t, uint8_t *, size_t, size_t, int8_t);
void *nib_compress(void *);
void *nib_uncompress(void *);

# ifdef __cplusplus
}
# endif

# endif /*__mdl__nibbles__h*/
