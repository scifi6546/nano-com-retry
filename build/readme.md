# Build System

## Component structure:
each component will have a simmilar structor
```
COMP_NAME/
	COMP_NAME.h
	Makefile
	lib/
		{COMP_SOURCE FILES}
	build/
		{COMP_NAME}.so
```
## The COMP_NAME.h file has the following format

```
int {COMP_NAME}_boot();
void {COMP_NAME}_tick(struct bus *sys_bus,struct ram_bus *mem_bus);
```
## Makefile
The Makefile then generates a {COMP_NAME}.so file and places it into build

## Build Config
```
comps=[
	{
		name:"foo"
		directory:"~/foo"
	}
]
```
