struct log{

	char * title;
	char * log_contents;
	#define ERROR 0

	#define BUS_IO 1
	#define BUS_DBG 2
	#define BUS_OPS 4
	#define GPU_INFO 5 
	#define PROG_FLOW 6
	#define CPU_STATE 7
	#define INFO 8

	int severity;
};
void add_log(struct log in);
void add_log(int severity,char *title,char* data);
