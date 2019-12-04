#include "logger.h"
#include <stdio.h>
const int MAX_LOG=BUS_OPS;
const char INTERACTIVE=1;
void add_log(int severity,char *title,char* data){
	struct log l;
	l.title=title;
	l.log_contents=data;
	l.severity=severity;
	add_log(l);

}
void add_log(struct log in){
	if(in.severity<=MAX_LOG){
		if(in.severity==ERROR){
			printf("\e[31mERROR! %i %s %s\n\e[0m ",in.severity,in.title,in.log_contents);
		}else{
			printf("%i %s %s\n",in.severity,in.title,in.log_contents);
		}
		if(INTERACTIVE==1){
			char f=getchar();
		}
	}
}
