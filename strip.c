#include <string.h>
#include "strip.h"


char* strip(char* str)
{
	// insert your code here
	
	return str;
}


TestResult test_strip()
{
	char str[] = "/usr//bin///env";	//example string
	char* p = strip(str);
	return (strcmp("/usr/bin/env", p)? NOT_OK : OK);
}