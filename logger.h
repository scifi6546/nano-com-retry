struct log{

	char * title;
	char * log_contents;
	#define ERROR 0
	#define BUS_IO 1
	#define BUS_DBG 2
	#define GPU_INFO 3 
	#define PROG_FLOW 4
	#define CPU_STATE 5
	#define INFO 5

	int severity;
};
void add_log(struct log in);
void add_log(int severity,char *title,char* data);
