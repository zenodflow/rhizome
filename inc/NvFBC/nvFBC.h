
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

#pragma once
#include <Windows.h>

#define NVFBC_DLL_VERSION 0x22
#define MAX_NUMBER_OF_SLICES 16

#define NVFBC_STRUCT_VERSION(typeName, ver) (NvU32)(sizeof(typeName) | ((ver)<<16) | (NVFBC_DLL_VERSION << 24))

#define NVFBCAPI __stdcall

typedef unsigned char NvU8;
typedef unsigned long NvU32;
typedef unsigned long long NvU64;

typedef enum
{
    NVFBC_SUCCESS = 0,
    NVFBC_ERROR_GENERIC = -1,                 // Unexpected failure in NVFBC
    NVFBC_ERROR_INVALID_PARAM = -2,           // One or more of the paramteres passed to NvFBC are invalid [This include NULL pointers]
    NVFBC_ERROR_INVALIDATED_SESSION = -3,     // NvFBC session is invalid. Client needs to recreate session.
    NVFBC_ERROR_PROTECTED_CONTENT = -4,       // Protected content detected. Capture failed.
    NVFBC_ERROR_DRIVER_FAILURE = -5,          // GPU driver returned failure to process NvFBC command.
    NVFBC_ERROR_CUDA_FAILURE   = -6,          // CUDA driver returned failure to process NvFBC command.
    NVFBC_ERROR_UNSUPPORTED    = -7,          // API Unsupported on this version of NvFBC.
    NVFBC_ERROR_HWENC_FAILURE  = -8,          // HW Encoder returned failure to process NVFBC command.
    NVFBC_ERROR_INCOMPATIBLE_DRIVER = -9,     // NVFBC is not compatible with this version of the GPU driver.
    NVFBC_ERROR_UNSUPPORTED_PLATFORM = -10,   // NVFBC is not supported on this platform.
    NVFBC_ERROR_OUT_OF_MEMORY  = -11,         // Failed to allocate memory
    NVFBC_ERROR_INVALID_PTR    = -12,         // A NULL pointer was passed
    NVFBC_ERROR_INCOMPATIBLE_VERSION = -13,   // An API was called with a parameter struct that has an incompatible version. Check dwVersion field of paramter struct.
} NVFBCRESULT;

typedef struct 
{
    // Deprecated. Do Not Use.
    DWORD   dwWidth;                // OUT, current res
    DWORD   dwHeight;               // OUT, current res
    DWORD   dwBufferWidth;          // OUT, current width of the pixel buffer  
    DWORD   dwCurrentFrame;         // OUT, current frame number
    BOOL    bOverlayActive;         // OUT, if overlay was active
    BOOL    bMustRecreate;          // OUT, if the compressor must call NvBFC_Create again
    BOOL    bFirstBuffer;           // OUT, relevant to XOR and diff modes only (valid for ToSYS interface only)
    BOOL    bHWMouseVisible;        // OUT, tells if HW mouse was on or not at the time of the grab (valid for ToSYS interface only)
    BOOL    bProtectedContent;      // OUT, if protected content was active (DXVA encryption Session)
    DWORD   dwDriverInternalError;  // OUT, driver ran out of resources while grabbing frames, 0 if success
    BOOL    bStereoOn;              // OUT, if stereo was on
    UINT32  dwSliceOffsets[MAX_NUMBER_OF_SLICES]; // OUT, slice offsets
} NvFBCFrameGrabInfo;

typedef struct 
{
    NvU32  dwVersion;              // IN, Struct version. Set to NVFBC_STATUS_VER.
    NvU32  bIsCapturePossible :1;  // OUT, tells if driver supports the NvFBC feature
    NvU32  bCurrentlyCapturing:1;  // OUT, tells if NVFBC is currently capturing
    NvU32  bCanCreateNow      :1;  // OUT, can NvFBC_Create be called now?
    NvU32  bReservedBits      :29; // Reserved.
    NvU32  dwNvFBCVersion;         // OUT, get NvFBC interface version
    NvU32  dwAdapterIdx;           // Adapter Ordinal corresponding to the display to be grabbed
    NvU32  dwReserved[60];         // Reserved. Set to 0.
    void*  pReserved[32];          // Reserved. Set to NULL.
} NvFBCStatusEx;
#define NVFBC_STATUS_VER NVFBC_STRUCT_VERSION(NvFBCStatusEx, 1)

typedef struct
{
    NvU32  dwVersion;              // IN, Struct version. Set to NVFBC_CREATE_PARAMS_VER.
    NvU32  dwInterfaceType;        // IN, Capture Type.
    NvU32  dwMaxDisplayWidth;      // OUT, Max. display width allowed.
    NvU32  dwMaxDisplayHeight;     // OUT, Max. display height allowed.
    void*  pDevice;                // IN, Device pointer.
    void*  pPrivateData;           // IN, Private data [optional]
    NvU32  dwPrivateDataSize;      // IN, Size of private data
    NvU32  dwInterfaceVersion;     // IN, Version of the capture interface.
    void*  pNvFBC;                 // OUT, pointer to the requested NVFBC object.
    NvU32  dwAdapterIdx;           // IN, Adapter Ordinal corresponding to the display to be grabbed.
                                   // This replaces the use of NVFBC_TARGET_ADAPTER environment variable.
                                   // If pDevice is set, this parameter is ignored.
                                   // to IDirect3D9::CreateDevice() for creating the d3d9 device.
    NvU32  dwNvFBCVersion;         // OUT, Version
    void*  cudaCtx;                // IN, CUDA context created using cuD3D9CtxCreate with the D3D9 device passed as pDevice. Only used for NvFBCCuda interface.
                                   // It is mandatory to pass a valid D3D9 device if cudaCtx is passed. The call will fail otherwise.
                                   // Client must release NvFBCCuda object before destroying the cudaCtx
    NvU32  dwReserved[56];         // Reserved. Set to 0.
    void*  pReserved[28];          // Reserved. Set to NULL.
}NvFBCCreateParams;
#define NVFBC_CREATE_PARAMS_VER NVFBC_STRUCT_VERSION(NvFBCCreateParams, 1)

#define NVFBC_GLOBAL_FLAGS_NONE                     0x00000000
#define NVFBC_GLOBAL_FLAGS_STEREO_BUFFER            0x00000001
#define NVFBC_GLOBAL_FLAGS_NO_INITIAL_REFRESH       0x00000002

typedef void   (NVFBCAPI * NvFBC_SetGlobalFlagsType) (DWORD dwFlags);
typedef NVFBCRESULT (NVFBCAPI * NvFBC_CreateFunctionExType)  (void * pCreateParams);
typedef NVFBCRESULT (NVFBCAPI * NvFBC_GetStatusExFunctionType) (void * pNvFBCStatus);
