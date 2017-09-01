# include <nibbles.h>
# include <string.h>
# include <cstdio>
// most basic form of compression
int main() {
/*
	uint8_t buff[12288] = {0x0};

	nib_args_t nib_args = {
		.data = gimp_image.pixel_data,
		.data_len = (gimp_image.width * gimp_image.height) * 3,
		.buff = buff,
		.buff_len = sizeof(buff)
	};
	nib_compress(&nib_args);
	printf("new size: %d, old: %d\n", nib_args.size, (gimp_image.width * gimp_image.height) * 3);

	uint8_t _buff[12288] = {0x0};
	nib_args_t _nib_args = {
		.data = buff,
		.data_len = nib_args.size,
		.buff = _buff,
		.buff_len = sizeof(_buff)
	};

	nib_uncompress(&_nib_args);
	printf("new size: %d\n", _nib_args.size);
*/

	uint8_t my_string[] = "XXXXXYYYYYAAAAA";
	uint8_t buff[21299] = {'\0'};

	nib_args_t nib_args = {
		.data = my_string,
		.data_len = strlen((char *)my_string),
		.buff = buff,
		.buff_len = sizeof(buff)
	};

	nib_compress(&nib_args);
	printf("new size: %d, old: %d\n", nib_args.size, strlen((char *)my_string));

	printf("%d - %d\n", buff[0], buff[2]);

	uint8_t _buff[21299] = {'\0'};
	nib_args_t _nib_args = {
		.data = buff,
		.data_len = nib_args.size,
		.buff = _buff,
		.buff_len = sizeof(_buff)
	};

	nib_uncompress(&_nib_args);
	printf("%d\n", _nib_args.size);

	printf("%s\n%s\n", my_string, _buff);

}
