# include <stdio.h>
# include <unistd.h>
# include <mdl/nibbles.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <string.h>
int main(int __argc, char const *__argv[]) {
	if (__argc < 4) {
		printf("usage: ./ {-c,-u}, {src}, {dest}\n");
		return -1;
	}
	char const *conv = __argv[1];
	char const *src_file = __argv[2];
	char const *dst_file = __argv[3];

	int in_fd, out_fd;
	if ((in_fd = open(src_file, O_RDONLY)) < 0) {
		return -1;
	}

	if ((out_fd = open(dst_file, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0) {
		return -1;
	}

	struct stat st;
	stat(src_file, &st);

	mdl_uint_t buff_size = 0;
	void*(*func)(void*) = NULL;

	if (!strcmp(conv, "-c")) {
		func = &nib_compress;
		buff_size = st.st_size+(st.st_size*2);
	} else if (!strcmp(conv, "-u")) {
		func = &nib_uncompress;
		buff_size = st.st_size+(st.st_size*0xFF);
	} else {
		close(out_fd);
		return -1;
	}

	mdl_u8_t *in = (mdl_u8_t*)malloc(st.st_size);
	mdl_u8_t *out = (mdl_u8_t*)malloc(buff_size);

	read(in_fd, in, st.st_size);
	close(in_fd);

	nib_args_t nib_args = {
		.data = in,
		.data_bc = st.st_size,
		.buff = out,
		.buff_bc = buff_size
	};

	func((void*)&nib_args);

	write(out_fd, out, nib_args.size);
	free(in);
	free(out);
	close(out_fd);
	printf("done.\n");
	return 0;
}
