/*
 * profile_f.c
 *  <FILE_DESC>
 * 	
 *  Author: Min Si
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "profile.h"

#ifdef ENABLE_PROFILE

void armci_profile_reset_counter_(){
    ARMCI_Profile_reset_counter();
}

void armci_profile_reset_timing_(){
    ARMCI_Profile_reset_timing();
}

void armci_profile_print_timing_(){
    ARMCI_Profile_print_timing();
}

void armci_profile_print_counter_(){
    ARMCI_Profile_print_counter();
}

#endif
