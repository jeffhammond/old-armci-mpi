/*
 * profile.h
 *  <FILE_DESC>
 * 	
 *  Author: Min Si
 */

#ifndef PROFILE_H_
#define PROFILE_H_
#include "mpi.h"

#ifdef ENABLE_PROFILE
enum ARMCI_Profile_func {
    PROF_PARMCI_GetS,
    PROF_PARMCI_Get,
    PROF_PARMCI_AccS,
    PROF_PARMCI_Acc,
    PROF_PARMCI_Rmw,
    PROF_PARMCI_Barrier,
    PROF_PARMCI_AllFence,
    PROF_MAX_NUM_PROFILE_FUNC
};

extern int profile_global_var_nproc;
extern int *prof_counters;
extern double *prof_timings;

static void ARMCI_Profile_init()
{
    int nproc;
    MPI_Comm_size(MPI_COMM_WORLD, &profile_global_var_nproc);

    if (prof_counters == NULL)
        prof_counters = calloc(PROF_MAX_NUM_PROFILE_FUNC * profile_global_var_nproc, sizeof(int));
    if (prof_timings == NULL)
        prof_timings = calloc(PROF_MAX_NUM_PROFILE_FUNC, sizeof(double));
}

static void ARMCI_Profile_destroy()
{
    if (prof_counters)
        free(prof_counters);
    if (prof_timings)
        free(prof_timings);
}

#define ARMCI_PROFILE_INIT ARMCI_Profile_init
#define ARMCI_PROFILE_DESTROY ARMCI_Profile_destroy

#define ARMCI_FUNC_PROFILE_TIMING_START(func) double _profile_time_start = MPI_Wtime();
#define ARMCI_FUNC_PROFILE_TIMING_END(func) {   \
    if (!prof_timings) fprintf(stderr, "WARNING: prof_timings is not initialized\n");   \
    if (prof_timings && PROF_##func >= 0 && PROF_##func < PROF_MAX_NUM_PROFILE_FUNC) \
        prof_timings[PROF_##func] += MPI_Wtime() - _profile_time_start;   \
}

#define ARMCI_FUNC_PROFILE_COUNTER_INC(func, target) {  \
        if (!prof_counters) fprintf(stderr, "WARNING: prof_counters is not initialized\n"); \
        if (prof_counters && PROF_##func >= 0 && PROF_##func < PROF_MAX_NUM_PROFILE_FUNC) \
            prof_counters[target * PROF_MAX_NUM_PROFILE_FUNC + PROF_##func]++;   \
    }

#else
#define ARMCI_PROFILE_INIT()
#define ARMCI_PROFILE_DESTROY()
#define ARMCI_FUNC_PROFILE_TIMING_START(func)
#define ARMCI_FUNC_PROFILE_TIMING_END(func)
#define ARMCI_FUNC_PROFILE_COUNTER_INC(func, target)

#endif
#endif /* PROFILE_H_ */
