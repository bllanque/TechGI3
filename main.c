#include <stdio.h>
#include "strip.h"


int main()
{
	puts((test_strip() == OK)? "OK" : "NOT_OK");
}
