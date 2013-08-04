/*
 * Copyright (C) 2013. See COPYRIGHT in top-level directory.
 */

#ifndef HAVE_ARMCI_PROFILER_H
#define HAVE_ARMCI_PROFILER_H

enum ARMCI_Profiler_stats
{

};

typedef struct {
  int    total_count;
  double total_time;
} armci_profiler_stat_t;

extern global_state_t ARMCII_GLOBAL_STATE;
  
typedef struct {
  void *src;
  void *dst;
  int   stride_levels;

  int  *base_ptr;
  int  *src_stride_ar;
  int  *dst_stride_ar;
  int  *count;

  /* Iterator State */
  int   was_contiguous;
  int  *idx;
} armcii_iov_iter_t;

void ARMCII_Acc_type_translate(int armci_datatype, MPI_Datatype *type, int *type_size);

#endif /* HAVE_ARMCI_PROFILER_H */
