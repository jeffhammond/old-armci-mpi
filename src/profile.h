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
    PROF_gmr_create,
    PROF_gmr_destroy,
    PROF_MAX_NUM_PROFILE_FUNC
};

extern int profile_global_var_nproc;
extern int prof_counters[MAX_NPROC*PROF_MAX_NUM_PROFILE_FUNC];
extern double prof_timings[MAX_NPROC];

static void ARMCI_Profile_init()
{
    int rank, i;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &profile_global_var_nproc);
    if(profile_global_var_nproc > MAX_NPROC){
	fprintf(stderr, "nproc %d > max profile nproc %d\n", 
			profile_global_var_nproc, MAX_NPROC);
	MPI_Abort(MPI_COMM_WORLD, 1);
    }
    
for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC * profile_global_var_nproc; i++)
    prof_counters[i] = 0;
for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++)
            prof_timings[i] = 0.0;
/*
    if (prof_counters == NULL)
        prof_counters = calloc(PROF_MAX_NUM_PROFILE_FUNC * profile_global_var_nproc, sizeof(int));
    if (prof_timings == NULL)
        prof_timings = calloc(PROF_MAX_NUM_PROFILE_FUNC, sizeof(double));
*/
    if(rank == 0) fprintf(stdout, "ARMCI PROFILE initialized\n");
}

static void ARMCI_Profile_destroy()
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
/*
    if (prof_counters)
        free(prof_counters);
    if (prof_timings)
        free(prof_timings);
*/
    if(rank == 0) fprintf(stdout, "ARMCI PROFILE destroied\n");
}

#define ARMCI_PROFILE_INIT ARMCI_Profile_init
#define ARMCI_PROFILE_DESTROY ARMCI_Profile_destroy

#define ARMCI_FUNC_PROFILE_TIMING_START(func) double _profile_time_start = MPI_Wtime();
#define ARMCI_FUNC_PROFILE_TIMING_END(func) {   \
    if (!prof_timings) fprintf(stderr, "WARNING: prof_timings is not initialized\n");   \
    ARMCII_Assert(PROF_##func < MAX_NPROC);	\
    if (prof_timings && PROF_##func >= 0 && PROF_##func < PROF_MAX_NUM_PROFILE_FUNC) \
        prof_timings[PROF_##func] += MPI_Wtime() - _profile_time_start;   \
}

#define ARMCI_FUNC_PROFILE_COUNTER_INC(func, target) {  \
        if (!prof_counters) fprintf(stderr, "WARNING: prof_counters is not initialized\n"); \
    	ARMCII_Assert(target * PROF_MAX_NUM_PROFILE_FUNC + PROF_##func < MAX_NPROC * PROF_MAX_NUM_PROFILE_FUNC);	\
        if (prof_counters && PROF_##func >= 0 && PROF_##func < PROF_MAX_NUM_PROFILE_FUNC) \
            prof_counters[target * PROF_MAX_NUM_PROFILE_FUNC + PROF_##func]++;   \
    }

extern void ARMCI_Profile_reset_counter();
extern void ARMCI_Profile_reset_timing();
extern void ARMCI_Profile_print_timing();
extern void ARMCI_Profile_print_counter();
#else
#define ARMCI_PROFILE_INIT()
#define ARMCI_PROFILE_DESTROY()
#define ARMCI_FUNC_PROFILE_TIMING_START(func)
#define ARMCI_FUNC_PROFILE_TIMING_END(func)
#define ARMCI_FUNC_PROFILE_COUNTER_INC(func, target)

#endif
#endif /* PROFILE_H_ */
