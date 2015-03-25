
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

#ifndef NVFBC_TO_SYS_H_
#define NVFBC_TO_SYS_H_

#define NVFBC_TO_SYS (0x1203)

typedef enum
{
    NVFBC_TOSYS_ARGB       = 0,              /**< Output in 32-bit packed ARGB format .*/
    NVFBC_TOSYS_RGB           ,              /**< Output in 24-bit packed RGB format .*/
    NVFBC_TOSYS_YYYYUV420p    ,              /**< Output in Y, U, V separate planes. No subsampling for Luma(Y) data, Chroma (U, V) data subsampled 4:2:0, i.e. one U, V value pair for 4 Y values. */
    NVFBC_TOSYS_RGB_PLANAR    ,              /**< Output in separate R, G, B planes with no subsampling.*/
    NVFBC_TOSYS_XOR           ,              /**< Use for diffmap.*/
    NVFBC_TOSYS_YUV444p       ,              /**< Output in separate Y, U, V planes with no subsampling.*/
    NVFBC_TOSYS_BUF_FMT_LAST  ,              /**< Sentinel value. Do not use.*/
} NVFBCToSysBufferFormat;

typedef enum 
{
    NVFBC_TOSYS_SOURCEMODE_FULL  = 0,        /**< Grab full res */
    NVFBC_TOSYS_SOURCEMODE_SCALE    ,        /**< Will convert current res to supplied resolution (dwTargetWidth and dwTargetHeight) */
    NVFBC_TOSYS_SOURCEMODE_CROP     ,        /**< Native res, crops a subwindow, of dwTargetWidth and dwTargetHeight sizes, starting at dwStartX and dwStartY */
    NVFBC_TOSYS_SOURCEMODE_LAST     ,        /**< Sentinel value. Do not use. */
}NVFBCToSysGrabMode;

typedef enum 
{
    NVFBC_TOSYS_NOFLAGS = 0x0,               /**< Default, grabbing will wait for a new frame or HW mouse move */
    NVFBC_TOSYS_NOWAIT  = 0x1,               /**< Grabbing will not wait for a new frame nor a HW mouse move */
} NVFBC_TOSYS_GRAB_FLAGS;

typedef struct
{
    NvU32 dwVersion;                         /**< [in]: Struct version. Set to NVFBC_TOSYS_SETUP_PARAMS_VER.*/
    NvU32 bWithHWCursor :1;                  /**< [in]: The client should set this to 1 if it requires the HW cursor to be composited on the captured image.*/
    NvU32 bDiffMap      :1;                  /**< [in]: The client should set this to use the DiffMap feature.*/
    NvU32 bEnableMouseGrab : 1;              /**< [in]: The client should set this to 1 if it wants to enable mouse capture in separate stream.*/
    NvU32 bReservedBits :29;                 /**< [in]: Reserved. Set to 0.*/
    NVFBCToSysBufferFormat eMode;            /**< [in]: Output image format.*/
    NvU32 dwReserved1;                       /**< [in]: Reserved. Set to 0.*/
    void **ppBuffer;                         /**< [out]: Container to hold NvFBC output buffers.*/
    void **ppDiffMap;                        /**< [out]: Container to hold NvFBC output diffmap buffers.*/
    void  *mouseEventHandle;                 /**< [out]: Client should wait for mouseEventHandle event before calling MouseGrab function. */
    NvU32 dwReserved[58];                    /**< [in]: Reserved. Set to 0.*/
    void *pReserved[29];                     /**< [in]: Reserved. Set to 0.*/
} NVFBC_TOSYS_SETUP_PARAMS;
#define NVFBC_TOSYS_SETUP_PARAMS_VER NVFBC_STRUCT_VERSION(NVFBC_TOSYS_SETUP_PARAMS, 1)

typedef struct
{
    NvU32 dwVersion;                         /**< [in]: Struct version. Set to NVFBC_MOUSE_GRAB_INFO_VER.*/
    NvU32 dwWidth;                           /**< [out]: Width of mouse glyph captured.*/
    NvU32 dwHeight;                          /**< [out]: Height of mouse glyph captured.*/
    NvU32 dwPitch;                           /**< [out]: Pitch of mouse glyph captured.*/
    NvU32 bIsHwCursor :1;                    /**< [out]: tells if cursor is HW cursor or SW cursor. If set to 0, ignore height, width, pitch and pBits.*/
    NvU32 Reserved :31;                      /**< [in]: Reserved.*/
    NvU32 dwReserved;                        /**< [in]: Reserved.*/
    void * pBits;                            /**< [out]: pointer to mouse buffer.*/
    NvU32 dwReservedA[58];                   /**< [in]: Reserved. Set to 0.*/
    void * pReserved[31];                    /**< [in]: Reserved. Set to 0.*/
}NVFBC_TOSYS_GRAB_MOUSE_PARAMS;
#define NVFBC_TOSYS_GRAB_MOUSE_PARAMS_VER NVFBC_STRUCT_VERSION(NVFBC_TOSYS_GRAB_MOUSE_PARAMS, 1)

typedef struct
{
    NvU32 dwVersion;                         /**< [in]: Struct version. Set to NVFBC_TOSYS_GRAB_FRAME_PARAMS_VER.*/
    NvU32 dwFlags;                           /**< [in]: Special grabbing requests. This should be a bit-mask of NVFBC_TOSYS_GRAB_FLAGS values.*/
    NvU32 dwTargetWidth;                     /**< [in]: Target image width. NvFBC will scale the captured image to fit taret width and height. Used with NVFBC_TOSYS_SOURCEMODE_SCALE and NVFBC_TOSYS_SOURCEMODE_CROP. */
    NvU32 dwTargetHeight;                    /**< [in]: Target image height. NvFBC will scale the captured image to fit taret width and height. Used with NVFBC_TOSYS_SOURCEMODE_SCALE and NVFBC_TOSYS_SOURCEMODE_CROP. */
    NvU32 dwStartX;                          /**< [in]: x-coordinate of starting pixel for cropping. Used with NVFBC_TOSYS_SOURCEMODE_CROP. */
    NvU32 dwStartY;                          /**< [in]: y-coordinate of starting pixel for cropping. Used with NVFBC_TOSYS_SOURCEMODE_CROP. .*/
    NVFBCToSysGrabMode eGMode;               /**< [in]: Frame grab mode.*/
    NvU32 dwReserved1;                       /**< [in]: Reserved. Set to 0.*/
    NvFBCFrameGrabInfo *pNvFBCFrameGrabInfo; /**< [in/out]: Frame grab information and feedback from NvFBC driver.*/
    NvU32 dwReserved[56];                    /**< [in]: Reserved. Set to 0.*/
    void *pReserved[31];                     /**< [in]: Reserved. Set to NULL.*/
} NVFBC_TOSYS_GRAB_FRAME_PARAMS;
#define NVFBC_TOSYS_GRAB_FRAME_PARAMS_VER NVFBC_STRUCT_VERSION(NVFBC_TOSYS_GRAB_FRAME_PARAMS, 1)

class INvFBCToSys_v2
{
public:
    /**
     * Set up NVFBC System Memory capture according to the provided parameters.
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCToSysSetUp              (NVFBC_TOSYS_SETUP_PARAMS *pParam) = 0;
    /**
     * Capture the desktop and dump the captured data to a System memory buffer
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCToSysGrabFrame          (NVFBC_TOSYS_GRAB_FRAME_PARAMS *pParam) = 0;
    /**
     * Capture mouse bitmap whenever shape of mouse is changed
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCToSysGrabMouse          (NVFBC_TOSYS_GRAB_MOUSE_PARAMS *pParam) = 0;
    /**
     * A high precision implementation of Sleep(). Can provide sub quantum (usually 16ms) sleep that does not burn CPU cycles
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCToSysGPUBasedCPUSleep   (__int64 qwMicroSeconds) = 0;
    /**
     * Release the NVFBC interface.
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCToSysRelease            () = 0;
};


typedef INvFBCToSys_v2 NvFBCToSys;

#endif // NVFBC_TO_SYS_H_
