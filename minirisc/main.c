#include <stdlib.h>
#include <stdio.h>
#include "platform.h"
#include "minirisc.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_binary_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

    platform_t *platform;
    minirisc_t *minirisc;
    int error_occured = 0;

    platform = platform_new();
    minirisc = minirisc_new(0x80000000, platform);

    if (platform_load_program(platform, argv[1])) {
    	error_occured = 1;
    	goto quit;
    }

    if (minirisc_run(minirisc)) {
    	error_occured = 1;
    }

quit:
    minirisc_free(minirisc);
    platform_free(platform);

    return error_occured ? EXIT_FAILURE : EXIT_SUCCESS;
}