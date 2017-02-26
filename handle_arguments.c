#include <stdlib.h>
#include "handle_arguments.h"

// Program title and version
const char *argp_program_version = "ARGHANDLER EXTREME 9000.0";
// Who to contact if bugs are found
const char *argp_program_bug_address = "donotrepy@no.absolutelynot";

// Documentation string.
char doc[] = "Who needs documentation with arg handles like these";

// Description of the required arguments we accept.
char args_doc[] = "";

// This option struct is for any optional arguments.
struct argp_option options[] = {
	{"height",	'h',	"LENGTH",	  0,	"Argument for height" },
	{"width",	  'w',	"WIDTH",	  0,	"Argument for width" },
	{"square",	's',	"SQUARE",		0,	"Argument for square board" },
	{"connect", 'c',  "CONNECT",  0, "Argument for connect requirement"},
	{"load",	  'l',	"FILE", 	  0, 	"Load file" },
	{ 0 }
};

// Argp requires us to pass these values in via the argp struct
struct argp argp = { options, parse_opt, args_doc, doc };

// Declare a variable called arguments that is also an
// arguments struct.  Remeber - we can't use the struct
// by just describing it.  We also need to make one.  Sort
// of similar to how we instantiate an object in Java.
struct arguments arguments;

// Our custom function for setting up values once they
// have been parsed from the command line args.
error_t parse_opt(int key, char* arg, struct argp_state *state){
	struct arguments *arguments = state->input;
	switch(key){
		case 's':
			arguments->width = atoi(arg);
			arguments->height = atoi(arg);
			break;
		case 'w':
			arguments->width = atoi(arg);
			break;
		case 'h':
			arguments->height = atoi(arg);
			break;
		case 'c':
			arguments->connect = atoi(arg);
			break;
		case 'l':
			arguments->load_file = arg;
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

// Here we setup some default values and override them
// if we get new values from the commandline.
void setup(int argc, char** argv, struct arguments *args){

	// Call argp to do its thing.
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	args->width = arguments.width;
	args->height = arguments.height;
	args->connect = arguments.connect;
	args->load_file = arguments.load_file;

}
