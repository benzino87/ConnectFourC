/**
 * Argument handler provided by Mr. Woodring
 */
#ifndef H_HANDLE_ARGUMENTS
#define H_HANDLE_ARGUMENTS

#include <argp.h>

// Define the arguments struct that will hold the values
// for flags that provide arguments.

struct arguments {
	int height;
	int width;
	int connect;
	char *load_file;
};

// Function to setup values once they are parsed.
error_t parse_opt(int key, char* arg, struct argp_state *state);

// Function to begin the parsing process.
void setup(int argc, char** argv, struct arguments *args);

#endif
