/*
 * The original developers of the TAU-ARMCI interface were
 * Jeff Hammond, Sriram Krishnamoorthy and Sameer Shende.
 *
 * Copyright (C) 2010. Argonne National Laboratory.
 * Copyright (C) 2010. Pacific Northwest National Laboratory.
 * Copyright (C) 2010. University of Oregon.
 * Copyright (C) 2010. Paratools, Inc.
 */

/*
 * Copyright (C) 2013. See COPYRIGHT in top-level directory.
 */

#include <stdio.h>
#include "armci.h"

#ifdef USE_TAU
#include <TAU.h>
#else
#define TAU_TRACE_SENDMSG
#endif

#ifdef USE_ARMCI_PROFILER
#include "armci_profiler.h"

static inline void armci_profiler_get_name(int fn, char * p)
{
  switch(fn) {
    case(FENCE):    p = "FENCE";    break;
    case(ALLFENCE): p = "ALLFENCE"; break;
    case(BARRIER):  p = "BARRIER";  break;
    case(TEST):     p = "TEST";     break;
    case(WAIT):     p = "WAIT";     break;
    case(WAITPROC): p = "WAITPROC"; break;
    case(WAITALL):  p = "WAITALL";  break;
    case(MALLOC):   p = "MALLOC";   break;
    case(FREE):     p = "FREE";     break;
    case(RMW):      p = "RMW";      break;
    case(PUT):      p = "PUT";      break;
    case(GET):      p = "GET";      break;
    case(ACC):      p = "ACC";      break;
    case(PUTS):     p = "PUTS";     break;
    case(GETS):     p = "GETS";     break;
    case(ACCS):     p = "ACCS";     break;
    case(PUTV):     p = "PUTV";     break;
    case(GETV):     p = "GETV";     break;
    case(ACCV):     p = "ACCV";     break;
    case(NBPUT):    p = "NBPUT";    break;
    case(NBGET):    p = "NBGET";    break;
    case(NBACC):    p = "NBACC";    break;
    case(NBPUTS):   p = "NBPUTS";   break;
    case(NBGETS):   p = "NBGETS";   break;
    case(NBACCS):   p = "NBACCS";   break;
    case(NBPUTV):   p = "NBPUTV";   break;
    case(NBGETV):   p = "NBGETV";   break;
    case(NBACCV):   p = "NBACCV";   break;
  }
  return;
}

void ARMCI_Profiler_initialize(void)
{
  armci_profiler_stats = (armci_profiler_stat_t *) malloc( LAST_FUNCTION * sizeof(armci_profiler_stat_t) );
  if (armci_profiler_stats==NULL)
    fprintf(stderr, "ARMCI_Profiler_init: malloc failed \n");

  for (int fn=0; fn<LAST_FUNCTION; fn++) {
      memset( &(armci_profiler_stats[fn][NAME]), '\0', 12);
      armci_profiler_get_name(fn, &(armci_profiler_stats[fn][NAME]));
      armci_profiler_stats[fn][COUNT] = 0;
      armci_profiler_stats[fn][TIME]  = 0.0;
  }

  return;
}

void ARMCI_Profiler_finalize(void)
{
  for (int fn=0; fn<LAST_FUNCTION; fn++) {
     fprintf(stderr, "name = %12c %d %lf \n",
         armci_profiler_stats[fn][NAME],
         armci_profiler_stats[fn][COUNT],
         armci_profiler_stats[fn][TIME]);
  }

  free(armci_profiler_stats);

  return;
}

void ARMCI_Profiler_add(enum ARMCI_Profiler_function_e fn, enum ARMCI_Profiler_key_e key, void * value)
{
  if (fn<LAST_FUNCTION) {
    switch(key) {
      case(COUNT):
        int i = (int)(*value);
        armci_profiler_stats[fn][COUNT] += i;
        break;
      case(TIME):
        double d = (double)(*value);
        armci_profiler_stats[fn][COUNT] += (double)(*value);
        break;
      default:
        fprintf(stderr, "ARMCI_Profiler_add: unsupported key %d \n", key);
    }
  }

  return;
}
#else
void ARMCI_Profiler_add(enum ARMCI_Profiler_function_e fn, enum ARMCI_Profiler_key_e key, void * value) {};
void ARMCI_Profiler_init(void) {};
void ARMCI_Profiler_init(void) {};
#endif

int
ARMCI_Init ()
{
  int rval;
  rval = PARMCI_Init ();
  return rval;
}

int
ARMCI_Init_args (int *argc, char ***argv)
{
  int rval;
  rval = PARMCI_Init_args (argc, argv);
  return rval;
}

void
ARMCI_Finalize ()
{
  PARMCI_Finalize ();
}

/* memory ops */

int
ARMCI_Malloc (void **ptr_arr, armci_size_t bytes)
{
  int rval;
  rval = PARMCI_Malloc (ptr_arr, bytes);
  return rval;
}

int
ARMCI_Free (void *ptr)
{
  int rval;
  rval = PARMCI_Free (ptr);
  return rval;
}

void *
ARMCI_Malloc_local (armci_size_t bytes)
{
  void *rval;
  rval = PARMCI_Malloc_local (bytes);
  return rval;
}

int
ARMCI_Free_local (void *ptr)
{
  int rval;
  rval = PARMCI_Free_local (ptr);
  return rval;
}

/* bulk sync ops */

void
ARMCI_Fence (int proc)
{
  PARMCI_Fence (proc);
}

void
ARMCI_AllFence ()
{
  PARMCI_AllFence ();
}

void
ARMCI_Barrier ()
{
  PARMCI_Barrier ();
}

/* nonblocking sync ops */

int
ARMCI_Test (armci_hdl_t * nb_handle)
{
  int rval;
  rval = PARMCI_Test (nb_handle);
  return rval;
}

int
ARMCI_Wait (armci_hdl_t * nb_handle)
{
  int rval;
  rval = PARMCI_Wait (nb_handle);
  return rval;
}

int
ARMCI_WaitProc (int proc)
{
  int rval;
  rval = PARMCI_WaitProc (proc);
  return rval;
}

int
ARMCI_WaitAll ()
{
  int rval;
  rval = PARMCI_WaitAll ();
  return rval;
}

/* mutex ops */

int
ARMCI_Create_mutexes (int num)
{
  int rval;
  rval = PARMCI_Create_mutexes (num);
  return rval;
}

int
ARMCI_Destroy_mutexes ()
{
  int rval;
  rval = PARMCI_Destroy_mutexes ();
  return rval;
}

void
ARMCI_Lock (int mutex, int proc)
{
  PARMCI_Lock (mutex, proc);
}

void
ARMCI_Unlock (int mutex, int proc)
{
  PARMCI_Unlock (mutex, proc);
}

/* atomic ops */

int
ARMCI_Rmw (int op, void *ploc, void *prem, int extra, int proc)
{
  int rval;
  int size = (op == ARMCI_SWAP_LONG || op == ARMCI_FETCH_AND_ADD_LONG) ? 8 : 4;
  TAU_TRACE_SENDMSG (1, proc, size);
  rval = PARMCI_Rmw (op, ploc, prem, extra, proc);
  return rval;
}

/* blocking ops */

int
ARMCI_Put (void *src, void *dst, int bytes, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, bytes);
  rval = PARMCI_Put (src, dst, bytes, proc);
  return rval;
}

int
ARMCI_Get (void *src, void *dst, int bytes, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, bytes);
  rval = PARMCI_Get (src, dst, bytes, proc);
  return rval;
}

int
ARMCI_Acc (int optype, void *scale, void *src, void *dst, int bytes, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, bytes);
  rval = PARMCI_Acc (optype, scale, src, dst, bytes, proc);
  return rval;
}

int
ARMCI_PutS (void *src_ptr, int *src_stride_arr, void *dst_ptr,
	    int *dst_stride_arr, int *count, int stride_levels, int proc)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_PutS (src_ptr, src_stride_arr, dst_ptr, dst_stride_arr, count,
		 stride_levels, proc);
  return rval;
}

int
ARMCI_GetS (void *src_ptr, int *src_stride_arr, void *dst_ptr,
	    int *dst_stride_arr, int *count, int stride_levels, int proc)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_GetS (src_ptr, src_stride_arr, dst_ptr, dst_stride_arr, count,
		 stride_levels, proc);
  return rval;
}

int
ARMCI_AccS (int optype, void *scale, void *src_ptr, int *src_stride_arr,
	    void *dst_ptr, int *dst_stride_arr, int *count, int stride_levels,
	    int proc)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_AccS (optype, scale, src_ptr, src_stride_arr, dst_ptr,
		 dst_stride_arr, count, stride_levels, proc);
  return rval;
}

int
ARMCI_PutV (armci_giov_t * darr, int len, int proc)
{
  int rval;
  {
    int i, bytes = 0;
    for (i = 0; i < len; i++)
      bytes += darr[i].ptr_array_len * darr[i].bytes;
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval = PARMCI_PutV (darr, len, proc);
  return rval;
}

int
ARMCI_GetV (armci_giov_t * darr, int len, int proc)
{
  int rval;
  {
    int i, bytes = 0;
    for (i = 0; i < len; i++)
      bytes += darr[i].ptr_array_len * darr[i].bytes;
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval = PARMCI_GetV (darr, len, proc);
  return rval;
}

int
ARMCI_AccV (int op, void *scale, armci_giov_t * darr, int len, int proc)
{
  int rval;
  {
    int i, bytes = 0;
    for (i = 0; i < len; i++)
      bytes += darr[i].ptr_array_len * darr[i].bytes;
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval = PARMCI_AccV (op, scale, darr, len, proc);
  return rval;
}

/* nonblocking ops */

int
ARMCI_NbPut (void *src, void *dst, int bytes, int proc,
	     armci_hdl_t * nb_handle)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, bytes);
  rval = PARMCI_NbPut (src, dst, bytes, proc, nb_handle);
  return rval;
}

int
ARMCI_NbGet (void *src, void *dst, int bytes, int proc,
	     armci_hdl_t * nb_handle)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, bytes);
  rval = PARMCI_NbGet (src, dst, bytes, proc, nb_handle);
  return rval;
}

int
ARMCI_NbAcc (int optype, void *scale, void *src, void *dst, int bytes, int proc,
             armci_hdl_t * nb_handle)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, bytes);
  rval = PARMCI_NbAcc (optype, scale, src, dst, bytes, proc, nb_handle);
  return rval;
}

int
ARMCI_NbPutS (void *src_ptr, int *src_stride_arr, void *dst_ptr,
              int *dst_stride_arr, int *count, int stride_levels, int proc,
              armci_hdl_t * nb_handle)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_NbPutS (src_ptr, src_stride_arr, dst_ptr, dst_stride_arr, count,
                   stride_levels, proc, nb_handle);
  return rval;
}

int
ARMCI_NbGetS (void *src_ptr, int *src_stride_arr, void *dst_ptr,
	      int *dst_stride_arr, int *count, int stride_levels, int proc,
	      armci_hdl_t * nb_handle)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_NbGetS (src_ptr, src_stride_arr, dst_ptr, dst_stride_arr, count,
		   stride_levels, proc, nb_handle);
  return rval;
}

int
ARMCI_NbAccS (int optype, void *scale, void *src_ptr, int *src_stride_arr,
	      void *dst_ptr, int *dst_stride_arr, int *count,
	      int stride_levels, int proc, armci_hdl_t * nb_handle)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_NbAccS (optype, scale, src_ptr, src_stride_arr, dst_ptr,
		   dst_stride_arr, count, stride_levels, proc, nb_handle);
  return rval;
}

int
ARMCI_NbPutV (armci_giov_t * darr, int len, int proc, armci_hdl_t * nb_handle)
{
  int rval;
  {
    int i, bytes = 0;
    for (i = 0; i < len; i++)
      bytes += darr[i].ptr_array_len * darr[i].bytes;
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval = PARMCI_NbPutV (darr, len, proc, nb_handle);
  return rval;
}

int
ARMCI_NbGetV (armci_giov_t * darr, int len, int proc, armci_hdl_t * nb_handle)
{
  int rval;
  {
    int i, bytes = 0;
    for (i = 0; i < len; i++)
      bytes += darr[i].ptr_array_len * darr[i].bytes;
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval = PARMCI_NbGetV (darr, len, proc, nb_handle);
  return rval;
}

int
ARMCI_NbAccV (int op, void *scale, armci_giov_t * darr, int len, int proc,
	      armci_hdl_t * nb_handle)
{
  int rval;
  {
    int i, bytes = 0;
    for (i = 0; i < len; i++)
      bytes += darr[i].ptr_array_len * darr[i].bytes;
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval = PARMCI_NbAccV (op, scale, darr, len, proc, nb_handle);
  return rval;
}

/* flag ops */

int
ARMCI_Put_flag (void *src, void *dst, int bytes, int *f, int v, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, bytes);
  rval = PARMCI_Put_flag (src, dst, bytes, f, v, proc);
  return rval;
}

int
ARMCI_PutS_flag (void *src_ptr, int *src_stride_arr, void *dst_ptr,
		 int *dst_stride_arr, int *count, int stride_levels,
		 int *flag, int val, int proc)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_PutS_flag (src_ptr, src_stride_arr, dst_ptr, dst_stride_arr, count,
		      stride_levels, flag, val, proc);
  return rval;
}

int
ARMCI_PutS_flag_dir (void *src_ptr, int *src_stride_arr, void *dst_ptr,
		     int *dst_stride_arr, int *count, int stride_levels,
		     int *flag, int val, int proc)
{
  int rval;
  {
    int i, bytes = 1;
    for (i = 0; i < stride_levels + 1; i++)
      bytes *= count[i];
    TAU_TRACE_SENDMSG (1, proc, bytes);
  }
  rval =
    PARMCI_PutS_flag_dir (src_ptr, src_stride_arr, dst_ptr, dst_stride_arr,
			  count, stride_levels, flag, val, proc);
  return rval;
}

/* value ops */

int
ARMCI_PutValueInt (int src, void *dst, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, 4);
  rval = PARMCI_PutValueInt (src, dst, proc);
  return rval;
}

int
ARMCI_GetValueInt (void *src, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, 4);
  rval = PARMCI_GetValueInt (src, proc);
  return rval;
}

int
ARMCI_PutValueLong (long src, void *dst, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, 8);
  rval = PARMCI_PutValueLong (src, dst, proc);
  return rval;
}

long
ARMCI_GetValueLong (void *src, int proc)
{
  long rval;
  TAU_TRACE_SENDMSG (1, proc, 8);
  rval = PARMCI_GetValueLong (src, proc);
  return rval;
}

int
ARMCI_PutValueFloat (float src, void *dst, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, 4);
  rval = PARMCI_PutValueFloat (src, dst, proc);
  return rval;
}

float
ARMCI_GetValueFloat (void *src, int proc)
{
  float rval;
  TAU_TRACE_SENDMSG (1, proc, 4);
  rval = PARMCI_GetValueFloat (src, proc);
  return rval;
}

int
ARMCI_PutValueDouble (double src, void *dst, int proc)
{
  int rval;
  TAU_TRACE_SENDMSG (1, proc, 8);
  rval = PARMCI_PutValueDouble (src, dst, proc);
  return rval;
}

double
ARMCI_GetValueDouble (void *src, int proc)
{
  double rval;
  TAU_TRACE_SENDMSG (1, proc, 8);
  rval = PARMCI_GetValueDouble (src, proc);
  return rval;
}
