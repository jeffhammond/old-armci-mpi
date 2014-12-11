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
#define MAX_NPROC 4000
enum ARMCI_Profile_func {
    PROF_PARMCI_GetS,
    PROF_PARMCI_Get,
    PROF_PARMCI_AccS,
    PROF_PARMCI_Acc,
    PROF_PARMCI_NbGetS,
    PROF_PARMCI_NbGet,
    PROF_PARMCI_Rmw,
    PROF_PARMCI_Barrier,
    PROF_PARMCI_AllFence,
    PROF_PARMCI_WaitAll,
    PROF_PARMCI_Wait,
    PROF_gmr_create,
    PROF_gmr_destroy,
    PROF_gmr_flushall,
    PROF_MAX_NUM_PROFILE_FUNC
};

extern int profile_global_var_nproc;
extern int prof_counters[MAX_NPROC * PROF_MAX_NUM_PROFILE_FUNC];
extern double prof_timings[PROF_MAX_NUM_PROFILE_FUNC];

extern void ARMCI_Profile_destroy();
extern void ARMCI_Profile_init();

#define ARMCI_PROFILE_INIT ARMCI_Profile_init
#define ARMCI_PROFILE_DESTROY ARMCI_Profile_destroy

#define ARMCI_FUNC_PROFILE_TIMING_START(func) double _profile_time_start = MPI_Wtime();
#define ARMCI_FUNC_PROFILE_TIMING_END(func) {   \
    ARMCII_Assert(PROF_##func < MAX_NPROC);	\
    if (PROF_##func >= 0 && PROF_##func < PROF_MAX_NUM_PROFILE_FUNC) \
        prof_timings[PROF_##func] += MPI_Wtime() - _profile_time_start;   \
}

#define ARMCI_FUNC_PROFILE_COUNTER_INC(func, target) {  \
    	ARMCII_Assert(target * PROF_MAX_NUM_PROFILE_FUNC + PROF_##func < MAX_NPROC * PROF_MAX_NUM_PROFILE_FUNC);	\
        if (PROF_##func >= 0 && PROF_##func < PROF_MAX_NUM_PROFILE_FUNC) \
            prof_counters[target * PROF_MAX_NUM_PROFILE_FUNC + PROF_##func]++;   \
    }

extern void ARMCI_Profile_reset_counter();
extern void ARMCI_Profile_reset_timing();
extern void ARMCI_Profile_print_timing(char *name);
extern void ARMCI_Profile_print_counter(char *name);
#else
#define ARMCI_PROFILE_INIT()
#define ARMCI_PROFILE_DESTROY()
#define ARMCI_FUNC_PROFILE_TIMING_START(func)
#define ARMCI_FUNC_PROFILE_TIMING_END(func)
#define ARMCI_FUNC_PROFILE_COUNTER_INC(func, target)

#endif
#endif /* PROFILE_H_ */
