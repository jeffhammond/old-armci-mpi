/*
 * profile.c
 *  <FILE_DESC>
 * 	
 *  Author: Min Si
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#include <armci.h>
#include <armci_internals.h>
#include <debug.h>
#include <gmr.h>
#include "profile.h"

#ifdef ENABLE_PROFILE

#ifdef ENABLE_MTCORE_PROFILE
extern void MTCORE_Profile_reset_flush_counter(MPI_Win win);
extern void MTCORE_Profile_print_flush_counter(MPI_Win win);
#endif

const char *ARMCI_Profile_func_names[PROF_MAX_NUM_PROFILE_FUNC] = {
    "PARMCI_GetS",
    "PARMCI_Get",
    "PARMCI_AccS",
    "PARMCI_Acc",
    "PARMCI_NbGetS",
    "PARMCI_NbGet",
    "PARMCI_Rmw",
    "PARMCI_Barrier",
    "PARMCI_AllFence",
    "PARMCI_WaitAll",
    "PARMCI_Wait",
    "gmr_create",
    "gmr_destroy",
    "gmr_flushall",
};

int profile_global_var_nproc = 0;
int prof_counters[MAX_NPROC * PROF_MAX_NUM_PROFILE_FUNC];
double prof_timings[PROF_MAX_NUM_PROFILE_FUNC];
static int env_print_per_rank = -1;

static inline void read_tpi_env()
{
    /* only read from environment once */
    if (env_print_per_rank < 0) {
        char *envval = 0;
        envval = getenv("ARMCI_PROF_PRINT_PER_RANK");
        if (envval && strlen(envval)) {
            env_print_per_rank = 1;
        }
        else {
            env_print_per_rank = 0;
        }
    }
}

void ARMCI_Profile_init()
{
    int rank, i;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &profile_global_var_nproc);
    if (profile_global_var_nproc > MAX_NPROC) {
        fprintf(stderr, "nproc %d > max profile nproc %d\n", profile_global_var_nproc, MAX_NPROC);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    read_tpi_env();

    for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC * profile_global_var_nproc; i++)
        prof_counters[i] = 0;
    for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++)
        prof_timings[i] = 0.0;

    if (rank == 0)
        fprintf(stdout, "ARMCI PROFILE initialized\n");
}

void ARMCI_Profile_destroy()
{
}

void ARMCI_Profile_reset_counter()
{
    int i;

    for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC * profile_global_var_nproc; i++)
        prof_counters[i] = 0;

#ifdef ENABLE_MTCORE_PROFILE
    gmr_t *cur_mreg = gmr_list;
    while (cur_mreg) {
        MTCORE_Profile_reset_flush_counter(cur_mreg->window);
        cur_mreg = cur_mreg->next;
    }
#endif
}

void ARMCI_Profile_reset_timing()
{
    int i;

    for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++)
        prof_timings[i] = 0.0;
}

void ARMCI_Profile_print_timing(char *name)
{
    int i, rank, size;
    double timers_avg[PROF_MAX_NUM_PROFILE_FUNC];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (env_print_per_rank == 1) {
        for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++) {
            if (prof_timings[i] > 0.0) {
                fprintf(stderr, "rank %d, %s %s : %lf\n", rank, name, ARMCI_Profile_func_names[i],
                        prof_timings[i]);
            }
        }
        fflush(stderr);
    }

    MPI_Reduce(prof_timings, timers_avg, PROF_MAX_NUM_PROFILE_FUNC, MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++) {
            if (timers_avg[i] > 0.0) {
                timers_avg[i] = timers_avg[i] / size;
                fprintf(stderr, "%s %s : %lf\n", name, ARMCI_Profile_func_names[i], timers_avg[i]);
            }
        }
        fflush(stderr);
    }
}

void ARMCI_Profile_print_counter(char *name)
{
    int i, dst, rank;
    int counters_total[PROF_MAX_NUM_PROFILE_FUNC], counters_total_avg[PROF_MAX_NUM_PROFILE_FUNC];

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    memset(counters_total, 0, sizeof(int) * PROF_MAX_NUM_PROFILE_FUNC);
    memset(counters_total_avg, 0, sizeof(int) * PROF_MAX_NUM_PROFILE_FUNC);

    for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++) {
        for (dst = 0; dst < profile_global_var_nproc; dst++)
            counters_total[i] += prof_counters[dst * PROF_MAX_NUM_PROFILE_FUNC + i];
    }

    if (env_print_per_rank == 1) {
        for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++) {
#if PROFILE_LEVEL == 2
            for (dst = 0; dst < profile_global_var_nproc; dst++)
                if (prof_counters[dst * PROF_MAX_NUM_PROFILE_FUNC + i] > 0)
                    fprintf(stderr, "%d:%d ", dst,
                            prof_counters[dst * PROF_MAX_NUM_PROFILE_FUNC + i]);
            fprintf(stderr, "\n");
            fflush(stderr);
#else
            if (counters_total[i] > 0) {
                fprintf(stderr, "rank %d, %s %s : %d\n", rank, name, ARMCI_Profile_func_names[i],
                        counters_total[i]);
                fflush(stderr);
            }
#endif
        }
    }

    MPI_Reduce(counters_total, counters_total_avg, PROF_MAX_NUM_PROFILE_FUNC, MPI_INT, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (rank == 0) {
        for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++) {
            if (counters_total_avg[i] > 0) {
                fprintf(stderr, "%s %s : %d\n", name, ARMCI_Profile_func_names[i],
                        counters_total_avg[i]);
                fflush(stderr);
            }
        }

#ifdef ENABLE_MTCORE_PROFILE
        gmr_t *cur_mreg = gmr_list;
        while (cur_mreg) {
            MTCORE_Profile_print_flush_counter(cur_mreg->window);
            cur_mreg = cur_mreg->next;
        }
#endif
    }
    fflush(stdout);
}

#endif
