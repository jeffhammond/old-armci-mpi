/*
 * Copyright (C) 2010. See COPYRIGHT in top-level directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <armci.h>
#include <armci_internals.h>
#include <debug.h>
#include <gmr.h>


/* -- begin weak symbols block -- */
#if defined(HAVE_PRAGMA_WEAK)
#  pragma weak ARMCI_NbPutS = PARMCI_NbPutS
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#  pragma _HP_SECONDARY_DEF PARMCI_NbPutS ARMCI_NbPutS
#elif defined(HAVE_PRAGMA_CRI_DUP)
#  pragma _CRI duplicate ARMCI_NbPutS as PARMCI_NbPutS
#endif
/* -- end weak symbols block -- */

/** Non-blocking operation that transfers data from the calling process to the
  * memory of the remote process.  The data transfer is strided and blocking.
  *
  * @param[in] src_ptr         Source starting address of the data block to put.
  * @param[in] src_stride_arr  Source array of stride distances in bytes.
  * @param[in] dst_ptr         Destination starting address to put data.
  * @param[in] dst_stride_ar   Destination array of stride distances in bytes.
  * @param[in] count           Block size in each dimension. count[0] should be the
  *                            number of bytes of contiguous data in leading dimension.
  * @param[in] stride_levels   The level of strides.
  * @param[in] proc            Remote process ID (destination).
  *
  * @return                    Zero on success, error code otherwise.
  */
int PARMCI_NbPutS(void *src_ptr, int src_stride_ar[/*stride_levels*/],
               void *dst_ptr, int dst_stride_ar[/*stride_levels*/], 
               int count[/*stride_levels+1*/], int stride_levels, int proc, armci_hdl_t *hdl) {

  return PARMCI_PutS(src_ptr, src_stride_ar, dst_ptr, dst_stride_ar, count, stride_levels, proc);
}


/* -- begin weak symbols block -- */
#if defined(HAVE_PRAGMA_WEAK)
#  pragma weak ARMCI_NbGetS = PARMCI_NbGetS
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#  pragma _HP_SECONDARY_DEF PARMCI_NbGetS ARMCI_NbGetS
#elif defined(HAVE_PRAGMA_CRI_DUP)
#  pragma _CRI duplicate ARMCI_NbGetS as PARMCI_NbGetS
#endif
/* -- end weak symbols block -- */

/** Non-blocking operation that transfers data from the remote process to the
  * memory of the calling process.  The data transfer is strided and blocking.
  *
  * @param[in] src_ptr         Source starting address of the data block to put.
  * @param[in] src_stride_arr  Source array of stride distances in bytes.
  * @param[in] dst_ptr         Destination starting address to put data.
  * @param[in] dst_stride_ar   Destination array of stride distances in bytes.
  * @param[in] count           Block size in each dimension. count[0] should be the
  *                            number of bytes of contiguous data in leading dimension.
  * @param[in] stride_levels   The level of strides.
  * @param[in] proc            Remote process ID (destination).
  *
  * @return                    Zero on success, error code otherwise.
  */
int PARMCI_NbGetS(void *src_ptr, int src_stride_ar[/*stride_levels*/],
               void *dst_ptr, int dst_stride_ar[/*stride_levels*/], 
               int count[/*stride_levels+1*/], int stride_levels, int proc, armci_hdl_t *hdl) {

  return PARMCI_GetS(src_ptr, src_stride_ar, dst_ptr, dst_stride_ar, count, stride_levels, proc);
}


/* -- begin weak symbols block -- */
#if defined(HAVE_PRAGMA_WEAK)
#  pragma weak ARMCI_NbAccS = PARMCI_NbAccS
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#  pragma _HP_SECONDARY_DEF PARMCI_NbAccS ARMCI_NbAccS
#elif defined(HAVE_PRAGMA_CRI_DUP)
#  pragma _CRI duplicate ARMCI_NbAccS as PARMCI_NbAccS
#endif
/* -- end weak symbols block -- */

/** Non-blocking operation that accumulates data from the local process into the
  * memory of the remote process.  The data transfer is strided and blocking.
  *
  * @param[in] datatype        Type of data to be transferred.
  * @param[in] scale           Pointer to the value that input data should be scaled by.
  * @param[in] src_ptr         Source starting address of the data block to put.
  * @param[in] src_stride_arr  Source array of stride distances in bytes.
  * @param[in] dst_ptr         Destination starting address to put data.
  * @param[in] dst_stride_ar   Destination array of stride distances in bytes.
  * @param[in] count           Block size in each dimension. count[0] should be the
  *                            number of bytes of contiguous data in leading dimension.
  * @param[in] stride_levels   The level of strides.
  * @param[in] proc            Remote process ID (destination).
  *
  * @return                    Zero on success, error code otherwise.
  */
int PARMCI_NbAccS(int datatype, void *scale,
               void *src_ptr, int src_stride_ar[/*stride_levels*/],
               void *dst_ptr, int dst_stride_ar[/*stride_levels*/],
               int count[/*stride_levels+1*/], int stride_levels, int proc, armci_hdl_t *hdl) {

  return PARMCI_AccS(datatype, scale, src_ptr, src_stride_ar, dst_ptr, dst_stride_ar, count, stride_levels, proc);
}
