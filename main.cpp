# include <nibbles.h>
# include <string.h>
# include <cstdio>

// most basic form of compression
int main() {
	uint8_t my_string[] = "IIIIIIIIIJJJJJJJJDDODKDKLDKDKKKPKKPJOIJ";
	uint8_t buff[128] = {0x0};

	nib_args_t nib_args = {
		.data = my_string,
		.data_len = 18,
		.buff = buff,
		.buff_len = 128
	};

	nib_compress(&nib_args);
	printf("new size: %d, old: 18\n", nib_args.size);
}
