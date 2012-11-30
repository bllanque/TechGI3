#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int   glob1 = 6;   /* external variable in initialized data */
char  buf[] = "a write to stdout\n";
int
main()
{
  int	var;	/* automatic variable on the stack */
  pid_t	pid;
  var = 88;
  if (write(1, buf, sizeof(buf)-1) != sizeof(buf)-1) exit(-1);
  printf("before fork\n");
  if ( (pid = fork()) < 0)
  	exit(-2);
  else if (pid == 0) {	/* child */
  	glob1++;		/* modify variables */
  	var++;
  } else
  	sleep(2);	/* parent */
  printf("pid = %d, glob1 = %d, var = %d\n", getpid(), glob1, var);
  exit(0);
}
