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

const char *ARMCI_Profile_func_names[PROF_MAX_NUM_PROFILE_FUNC] = {
    "PARMCI_GetS",
    "PARMCI_Get",
    "PARMCI_AccS",
    "PARMCI_Acc",
    "PARMCI_Rmw",
    "PARMCI_Barrier",
    "PARMCI_AllFence",
};

int profile_global_var_nproc = 0;
int *prof_counters = NULL;
double *prof_timings = NULL;

void ARMCI_Profile_reset_counter()
{
    int i;
    if (prof_counters == NULL)
        fprintf(stderr, "WARNING: prof_timings is not initialized\n");

    if (prof_counters != NULL)
        for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC * profile_global_var_nproc; i++)
            prof_counters[i] = 0;
}

void ARMCI_Profile_reset_timing()
{
    int i;
    if (prof_timings == NULL)
        fprintf(stderr, "WARNING: prof_timings is not initialized\n");

    if (prof_timings != NULL)
        for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++)
            prof_timings[i] = 0.0;
}

void ARMCI_Profile_print_timing()
{
    int i;
    if (!prof_timings)
        return;
    for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++) {
        if (prof_timings[i] > 0.0)
            printf("Timing %s : %lf\n", ARMCI_Profile_func_names[i], prof_timings[i]);
    }
    fflush(stdout);
}

void ARMCI_Profile_print_counters()
{
    int i, dst;
    if (!prof_timings)
        return;
    for (i = 0; i < PROF_MAX_NUM_PROFILE_FUNC; i++) {
        printf("Counter %s : ", ARMCI_Profile_func_names[i]);
        for (dst = 0; dst < profile_global_var_nproc; dst++)
            printf("%d ", prof_counters[dst * PROF_MAX_NUM_PROFILE_FUNC + i]);
        printf("\n");
    }
    fflush(stdout);
}

#endif
