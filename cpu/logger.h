struct log{

	char * title;
	char * log_contents;
	#define ERROR 0

	#define PROG_FLOW 1
	#define BUS_OPS 2
	#define CPU_STATE 3
	#define INFO 4

	int severity;
};
void add_log(struct log in);
void add_log(int severity,char *title,char* data);
