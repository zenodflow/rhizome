
/*!
 * \copyright
 * Copyright 1993-2014 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO LICENSEE:
 *
 * This source code and/or documentation ("Licensed Deliverables") are
 * subject to NVIDIA intellectual property rights under U.S. and
 * international Copyright laws.
 *
 * These Licensed Deliverables contained herein is PROPRIETARY and
 * CONFIDENTIAL to NVIDIA and is being provided under the terms and
 * conditions of a form of NVIDIA software license agreement by and
 * between NVIDIA and Licensee ("License Agreement") or electronically
 * accepted by Licensee.  Notwithstanding any terms or conditions to
 * the contrary in the License Agreement, reproduction or disclosure
 * of the Licensed Deliverables to any third party without the express
 * written consent of NVIDIA is prohibited.
 *
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, NVIDIA MAKES NO REPRESENTATION ABOUT THE
 * SUITABILITY OF THESE LICENSED DELIVERABLES FOR ANY PURPOSE.  IT IS
 * PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.
 * NVIDIA DISCLAIMS ALL WARRANTIES WITH REGARD TO THESE LICENSED
 * DELIVERABLES, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * NOTWITHSTANDING ANY TERMS OR CONDITIONS TO THE CONTRARY IN THE
 * LICENSE AGREEMENT, IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY
 * SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THESE LICENSED DELIVERABLES.
 *
 * U.S. Government End Users.  These Licensed Deliverables are a
 * "commercial item" as that term is defined at 48 C.F.R. 2.101 (OCT
 * 1995), consisting of "commercial computer software" and "commercial
 * computer software documentation" as such terms are used in 48
 * C.F.R. 12.212 (SEPT 1995) and is provided to the U.S. Government
 * only as a commercial end item.  Consistent with 48 C.F.R.12.212 and
 * 48 C.F.R. 227.7202-1 through 227.7202-4 (JUNE 1995), all
 * U.S. Government End Users acquire the Licensed Deliverables with
 * only those rights set forth herein.
 *
 * Any use of the Licensed Deliverables in individual and commercial
 * software must include, in the user documentation and internal
 * comments to the code, the above Disclaimer and U.S. Government End
 * Users Notice.
*/

#ifndef _NVFBC_CUDA_H_
#define _NVFBC_CUDA_H_

#define NVFBC_SHARED_CUDA (0x1003)
#define NVFBC_SHARED_CUDA_YUV420P (0x1004)

typedef enum 
{
    NVFBC_TOCUDA_NOFLAGS   =        0x0,       /**< Default, grabbing will wait for a new frame or HW mouse move */
    NVFBC_TOCUDA_NOWAIT    =        0x1,       /**< Grabbing will not wait for a new frame nor a HW mouse move */
    NVFBC_TOCUDA_CPU_SYNC  =        0x2,       /**< Does a cpu event signal when grab is complete */
    NVFBC_TOCUDA_WITH_HWCURSOR =    0x4,       /**< Grabs the HW cursor if any visible */
} NVFBC_CUDA_FLAGS;

typedef struct
{
    NvU32 dwVersion;                           /**< [in]: Struct version. Set to NVFBC_CUDA_GRAB_FRAME_PARAMS_VER. */
    NvU32 dwFlags;                             /**< [in]: Flags for grab frame.*/
    void *pCUDADeviceBuffer;                   /**< [in]: Output buffer.*/
    NvFBCFrameGrabInfo *pNvFBCFrameGrabInfo;   /**< [in/out]: Frame grab configuration and feedback from NvFBC driver.*/
    NvU32 dwReserved[62];                      /**< [in]: Reserved. Set to 0.*/
    void *pReserved[30];                       /**< [in]: Reserved. Set to NULL.*/
} NVFBC_CUDA_GRAB_FRAME_PARAMS;
#define NVFBC_CUDA_GRAB_FRAME_PARAMS_VER NVFBC_STRUCT_VERSION(NVFBC_CUDA_GRAB_FRAME_PARAMS, 1)

class INvFBCCuda_v1
{
    // First Release
public:
    /**
     * Returns the maximum buffer size, in bytes for allocating a CUDA buffer
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCCudaGetMaxBufferSize (NvU32 *pdwMaxBufSize) = 0;
    
    /**
     * Capture the desktop and dump to a CUDA buffer provided by the client.
     * If the API returns a failure, the client should check whether it needs to recreate the sessino by checking the bMustRecreate field of pNvFBCFrameGrabInfo, 
     * or whether there is protected content on the screen, by checking the bProtectedContent field.
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCCudaGrabFrame        (NVFBC_CUDA_GRAB_FRAME_PARAMS *pParams) = 0;        // pCUDADeviceBuffer has been allocated
      
    /**
     * A high precision implementation of Sleep(). Can provide sub quantum (usually 16ms) sleep that does not burn CPU cycles
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCCudaGPUBasedCPUSleep (__int64 qwMicroSeconds) = 0;	// to provide sub quantum (usually 16ms) sleep that does not burn CPU cycles
     
    /**
     * Release NVFBC interface
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCCudaRelease          () = 0;
};

typedef INvFBCCuda_v1 NvFBCCuda;

#endif _NVFBC_CUDA_H_