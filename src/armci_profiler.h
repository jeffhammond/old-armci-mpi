/*
 * Copyright (C) 2013. See COPYRIGHT in top-level directory.
 */

#ifndef HAVE_ARMCI_PROFILER_H
#define HAVE_ARMCI_PROFILER_H

#include <stdio.h>

enum ARMCI_Profiler_function_e
{
  FENCE = 0, ALLFENCE = 1, BARRIER = 2,
  TEST = 3, WAIT = 4, WAITPROC = 5, WAITALL = 6,
  MALLOC = 7, FREE = 8,
  RMW = 9,
  PUT  = 10, GET  = 11, ACC  = 12,
  PUTS = 13, GETS = 14, ACCS = 15,
  PUTV = 16, GETV = 17, ACCV = 18,
  NBPUT  = 19, NBGET  = 20, NBACC  = 21,
  NBPUTS = 22, NBGETS = 23, NBACCS = 24,
  NBPUTV = 25, NBGETV = 26, NBACCV = 27,
  LAST_FUNCTION = 28,
};

enum ARMCI_Profiler_key_e
{
  NAME,
  COUNT,
  TIME
};

typedef struct {
  char   name[12];
  int    total_count;
  double total_time;
} armci_profiler_stat_t;

armci_profiler_stat_t * armci_profiler_stats;

void ARMCI_Profiler_initialize(void);
void ARMCI_Profiler_finalize(void);
void ARMCI_Profiler_add(enum ARMCI_Profiler_function_e fn, enum ARMCI_Profiler_key_e key, void * value);

#endif /* HAVE_ARMCI_PROFILER_H */
