#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "option.h"

int getOption(char* ptrOpt){
	if(ptrOpt[0] == '-'){
		if(!strcmp(ptrOpt, "-c"))
			return CREATE;
		else if(!strcmp(ptrOpt, "-o"))
			return OPEN;
		else
			return ERROR;
	}
}
