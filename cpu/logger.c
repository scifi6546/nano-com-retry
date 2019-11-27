#include "logger.h"
#include <stdio.h>
void add_log(int severity,char *title,char* data){
	struct log l;
	l.title=title;
	l.log_contents=data;
	l.severity=severity;
	add_log(l);

}
void add_log(struct log in){
	printf("%i %s %s\n",in.severity,in.title,in.log_contents);
}
