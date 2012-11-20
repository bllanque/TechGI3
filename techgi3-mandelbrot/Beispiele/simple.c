/******************************************
 * An example source module to accompany...
 * "Using POSIX Threads:
 *     Programming with Pthreads"
 * Brad nichols, Dick Buttlar, Jackie Farrell
 * O'Reilly & Associates, Inc.
 ******************************************
 * simple.c
 *
 * Simple serial example. Calls three procedures.
 */

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap_up(int, int);

int r1 = 0, r2 = 0;
int v1 = 0;
main()
{
  
  do_one_thing(&r1);
  
  do_another_thing(&r2);

  do_wrap_up(r1, r2);
  
}

void do_one_thing(int *pnum_times)
{
  int i, j, x;
  static int v2=0;
  
  for (i = 0;  i < 4; i++) {
    v1++; v2++; printf("%d: v1=%d,v2=%d ",getpid(),v1,v2);
    sleep(1);
    printf("doing one thing\n");
    for (j = 0; j < 10000; j++) x = x + i;
    (*pnum_times)++;
  }

}

void do_another_thing(int *pnum_times)
{
  int i, j, x;
  static int v2=0;
  
  for (i = 0;  i < 4; i++) {
    v1++; v2++; printf("%d: v1=%d,v2=%d ",getpid(),v1,v2);
    sleep(1);
    printf("doing another \n"); 
    for (j = 0; j < 10000; j++) x = x + i;
    (*pnum_times)++;
  }

}

void do_wrap_up(int one_times, int another_times)
{
  int total;

  total = one_times + another_times;
  printf("All done, one thing %d, another %d for a total of %d\n",
	one_times, another_times, total);
}
