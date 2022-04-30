#include <papi.h>
#include <stdio.h>
#include <stdlib.h>

int EventSet=PAPI_NULL;

int handle_error(int i) {
  printf("PAPI API error %d\n", i);
  exit(i);
}

void test1() {
  if (PAPI_reset(EventSet) != PAPI_OK)
      handle_error(1);

  if (PAPI_start(EventSet) != PAPI_OK)
      handle_error(1);

  // No memory accessed: no LLC refs or misses
  for (unsigned i=0; i<10000000; i++);

  long_long values[3];
  if (PAPI_stop(EventSet, values) != PAPI_OK)
      handle_error(1);

  printf("test1: instructions-completed: %lld, total-cycle: %lld, L3-cache-misses: %lld\n",
    values[0], values[1], values[2]);
}

void test2(int *buf) {
  if (PAPI_reset(EventSet) != PAPI_OK)
      handle_error(1);

  if (PAPI_start(EventSet) != PAPI_OK)
      handle_error(1);

  // Memory heavily accessed, however, not randomly
  for (unsigned i=0; i<1000000; ++i) {
    *(buf+i) = 0xdeadbeef;
  }

  long_long values[3];
  if (PAPI_stop(EventSet, values) != PAPI_OK)
      handle_error(1);

  printf("test2: instructions-completed: %lld, total-cycle: %lld, L3-cache-misses: %lld\n",
    values[0], values[1], values[2]);
}

void test3(int *buf) {
  if (PAPI_reset(EventSet) != PAPI_OK)
      handle_error(1);

  if (PAPI_start(EventSet) != PAPI_OK)
      handle_error(1);

  // Memory heavily accessed randomly
  for (unsigned i=0; i<1000000; ++i) {
    long idx = random() % 1000000;
    *(buf+idx) = 0xdeadbeef;
  }

  long_long values[3];
  if (PAPI_stop(EventSet, values) != PAPI_OK)
      handle_error(1);

  printf("test3: instructions-completed: %lld, total-cycle: %lld, L3-cache-misses: %lld\n",
    values[0], values[1], values[2]);
}

int main(int argc, char **argv)
{
  int *buf = (int*)malloc(sizeof(int)*1000000);

  /* Initialize the PAPI library */
  int retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT) {
    fprintf(stderr, "PAPI library init error!\n");
    exit(1);
  }

  /* Create the Event Set */
  if (PAPI_create_eventset(&EventSet) != PAPI_OK)
    handle_error(1);

  /* Instructions completed */
  if (PAPI_add_event(EventSet, PAPI_TOT_INS) != PAPI_OK)
      handle_error(1);

  /* Total Cycles */
  if (PAPI_add_event(EventSet, PAPI_TOT_CYC) != PAPI_OK)
      handle_error(1);

  /* Level 3 cache misses */
  if (PAPI_add_event(EventSet, PAPI_L3_TCM) != PAPI_OK)
      handle_error(1);

  test1();
  test2(buf);
  test3(buf);

  return 0;
}
