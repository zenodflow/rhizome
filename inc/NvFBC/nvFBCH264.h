
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


#ifndef _NVFBC_H264_H_
#define _NVFBC_H264_H_

#include "NvFBC.h"

#define NVFBC_TO_H264_HW_ENCODER (0x1403)
#define NVFBC_MAX_REF_FRAMES 0x10

typedef enum 
{
    NVFBC_TOH264_NOFLAGS  = 0x0,                                         /**< Default, grabbing will wait for a new frame or HW mouse move. */
    NVFBC_TOH264_NOWAIT   = 0x1,                                         /**< Grabbing will not wait for a new frame nor a HW mouse move. */
    NVFBC_TOH264_RESERVED = 0x2,                                         /**< Reserved. Do not use. */
} NVFBC_TO_H264_FLAGS;

typedef enum 
{
    NVFBC_TOH264_SOURCEMODE_FULL  = 0,                                  /**< Grab at full desktop resolution. */
    NVFBC_TOH264_SOURCEMODE_SCALE    ,                                  /**< Will convert current res to supplied resolution (NVFBC_H264_GRAB_FRAME_PARAMS::dwTargetWidth and NVFBC_H264_GRAB_FRAME_PARAMS::dwTargetHeight) */
    NVFBC_TOH264_SOURCEMODE_CROP     ,                                  /**< Native res, crops a subwindow, of NVFBC_H264_GRAB_FRAME_PARAMS::dwTargetWidth and NVFBC_H264_GRAB_FRAME_PARAMS::dwTargetHeight sizes, starting at NVFBC_H264_GRAB_FRAME_PARAMS::dwStartX and NVFBC_H264_GRAB_FRAME_PARAMS::dwStartY */
    NVFBC_TOH264_SOURCEMODE_LAST     ,                                  /**< Sentinel value. Do not use. */
} NVFBCH264GrabMode;

typedef enum
{
    NVFBC_H264_STEREO_NONE           =      0,                          /**< Mono grab. Default use case. */
    NVFBC_H264_STEREO_MVC                    ,                          /**< Full frames with MVC coding */
    NVFBC_H264_STEREO_TB                     ,                          /**< Top Bottom squeezed, with SEI inband message */
    NVFBC_H264_STEREO_LR                     ,                          /**< Left Right squeezed, with SEI inband message */
    NVFBC_H264_STEREO_SBS                    ,                          /**< Left Right squeezed, no SEI */
    NVFBC_H264_STEREO_LAST                   ,                          /**< Sentinel value. Do not use. */
} NVFBC_H264_STEREO_FORMAT;

typedef enum
{
    NVFBC_H264_PRESET_LOW_LATENCY_HP         = 0,                       /**< Use for Fastest encode, with suboptimal quality */
    NVFBC_H264_PRESET_LOW_LATENCY_HQ            ,                       /**< Use for better overall quality, compromising on encoding speed. */
    NVFBC_H264_PRESET_LOW_LATENCY_DEFAULT       ,                       /**< Use for better quality than NVFBC_H264_PRESET_LOW_LATENCY_HP and higher speed than NVFBC_H264_PRESET_LOW_LATENCY_HQ. */
    NVFBC_H264_PRESET_RESERVED                  ,                       /**< Reserved. Do not use. */
    NVFBC_H264_PRESET_LOSSLESS_HP               ,                       /**< Use for lossless encoding at higher performance. */
    NVFBC_H264_PRESET_LAST                      ,                       /**< Sentinel value. Do not use. */
} NVFBC_H264_PRESET;

typedef enum _NVFBC_H264_ENC_PARAMS_RC_MODE
{
    NVFBC_H264_ENC_PARAMS_RC_CONSTQP                = 0x0,              /**< Constant QP mode */
    NVFBC_H264_ENC_PARAMS_RC_VBR                    = 0x1,              /**< Variable bitrate mode */
    NVFBC_H264_ENC_PARAMS_RC_CBR                    = 0x2,              /**< Constant bitrate mode */
    NVFBC_H264_ENC_PARAMS_RC_2_PASS_QUALITY         = 0x8,              /**< Multi pass encoding optimized for image quality and works best with single frame VBV buffer size */
    NVFBC_H264_ENC_PARAMS_RC_2_PASS_FRAMESIZE_CAP   = 0x10,             /**< Multi pass encoding optimized for maintaining frame size and works best with single frame VBV buffer size */
    NVFBC_H264_ENC_PARAMS_RC_CBR_IFRAME_2PASS       = 0x20              /**< Constant bitrate mode using two pass only for IDR frame or I frame. */
} NVFBC_H264_ENC_PARAMS_RC_MODE;

// NVFBC_H264_ENC_PARAM_FLAGS is depricated from SDK 2.3, use bit wise flags in NvFBC_H264HWEncoder_EncodeParams

typedef enum
{
    NVFBC_H264_ENC_SLICE_TYPE_DEFAULT         = 0x0,                    /**< Slice type is same as picture type */
    NVFBC_H264_ENC_SLICE_TYPE_I               = 0x02,                   /**< Intra predicted slice */
    NVFBC_H264_ENC_SLICE_TYPE_UNKNOWN         = 0xFF                    /**< Slice type unknown */
} NVFBC_H264_ENC_SLICE_TYPE;

typedef enum
{
	NVFBC_H264_ENC_SLICING_MODE_DISABLED          = -1,                 /**< Disable slicing mode. */
    NVFBC_H264_ENC_SLICING_MODE_FIXED_NUM_MBS     =  0,                 /**< Picture will be divided into slices of n MBs, where n = dwSlicingModeParam. */
    NVFBC_H264_ENC_SLICING_MODE_FIXED_NUM_BYTES       ,                 /**< Picture will be divided into slices of n Bytes, where n = dwSlicingModeParam. */
    NVFBC_H264_ENC_SLICING_MODE_FIXED_NUM_MB_ROWS     ,                 /**< Picture will be divided into slices of n rows of MBs, where n = dwSlicingModeParam. */
    NVFBC_H264_ENC_SLICING_MODE_FIXED_NUM_SLICES      ,                 /**< Picture will be divided into n+1 slices, where n = dwSlicingModeParam. */
    NVFBC_H264_ENC_SLICING_MODE_LAST                  ,                 /**< Sentinel value. Do not use. */
} NVFBC_H264_ENC_SLICING_MODE;

typedef struct
{
    NvU32                               dwVersion;                      /**< [in]: Set to NVFBC_H264HWENC_CONFIG_VER. */
    NvU32                               dwProfile;                      /**< [in]: H.264 profile that the HW encoder should use for video encoding. Overridden to 244 if client is using NVFBC_H264_PRESET_LOSSLESS_HP. */
    NvU32                               dwFrameRateNum;                 /**< [in]: Frame rate numerator. Encoding frame rate = dwFrameRateNum/dwFrameRateDen. This is not related to rate at which frames are grabbed. */
    NvU32                               dwFrameRateDen;                 /**< [in]: Frame rate denominator. Encoding frame rate = dwFrameRateNum/dwFrameRateDen. This is not related to rate at which frames are grabbed. */
    NvU32                               dwAvgBitRate;                   /**< [in]: Target Average bitrate. HW Encoder will try to achieve this bitrate during video encoding. This is the only bitrate setting useful for Constant Bit Rate RateControl mode. This is ignored for NVFBC_H264_ENC_PARAMS_RC_CONSTQP mode. */
    NvU32                               dwPeakBitRate;                  /**< [in]: Maximum bitrate that the HW encoder can hit while encoding video in VBR [variable bit rate mode]. This is ignored for NVFBC_H264_ENC_PARAMS_RC_CONSTQP mode. */
    NvU32                               dwGOPLength;                    /**< [in]: Number of pictures in a GOP. every GOP beigins with an I frame, so this is the same as I-frame interval. */
    NvU32                               dwQP;                           /**< [in]: QP value to be used for rate control in ConstQP mode. Overridden to 0 if client is using NVFBC_H264_PRESET_LOSSLESS_HP. */
    NVFBC_H264_ENC_PARAMS_RC_MODE       eRateControl;                   /**< [in]: Rate Control Mode to be used by the HW encoder. Should be set to NVFBC_H264_ENC_PARAMS_RC_CONSTQP for using NVFBC_H264_PRESET_LOSSLESS_HP preset. */
    NVFBC_H264_PRESET                   ePresetConfig;                  /**< [in]: Specifies the encoding preset used for fine tuning for encoding parameters */
    NvU32                               bOutBandSPSPPS          :1;     /**< [in]: Set this to 1, for enabling out of band generation of SPS, PPS headers. */
    NvU32                               bRecordTimeStamps       :1;     /**< [in]: Set this to 1, if client wants timestamp information to be preserved. Client should send timestamps as input. */
    NvU32                               bIntraFrameOnRequest    :1;     /**< [in]: Reserved. Set to 0. */
    NvU32                               bUseMaxRCQP             :1;     /**< [in]: Set this to 1, if client wants to specify maxRCQP[] */
    NvU32                               bEnableSubframeEncoding    :1;  /**< [in]: Unsupported. Set this to 0. */
    NvU32                               bEnableIntraRefresh        :1;  /**< [in]: Set to 1, to enable gradual decoder refresh or intra-refresh. If the GOP structure uses B frames this will be ignored. */
    NvU32                               bEnableConstrainedEncoding :1;  /**< [in]: Unsupported. Set this to 0. */
    NvU32                               bEnableMSE                 :1;  /**< [in]: Set this to 1 to enable returning MSE per channel in :: NVFBC_H264_GRAB_FRAME_PARAMS NOTE: Enabling this bit will have affect performance severly, Set this bit only if Client wants to evaluate quality of encoder.*/
    NvU32                               bEnableYUV444Encoding      :1;  /**< [in]: Set this to 1 to enable YUV444 encoding. */
    NvU32                               bReservedBits              :23; /**< [in]: Reserved. Set to 0. */
    NVFBC_H264_ENC_SLICING_MODE         dwSlicingMode;                  /**< [in]: Refer to enum NVFBC_H264_ENC_SLICING_MODE for usage. */
    NvU32                               dwSlicingModeParam;             /**< [in]: Refer to enum NVFBC_H264_ENC_SLICING_MODE for usage. */
    NvU32                               dwVBVBufferSize;                /**< [in]: VBV buffer size can be used to cap the frame size of encoded bitstream, reducing the need for buffering at decoder end.
                                                                                   For lowest latency, VBV buffersize = single frame size = channel bitrate/frame rate.
                                                                                   I-frame size may be larger than P or B frames.
                                                                                   Overridden by NvFBC in case of NVFBC_H264_ENC_PARAMS_RC_2_PASS_QUALITY or NVFBC_H264_ENC_PARAMS_RC_2_PASS_FRAMESIZE_CAP rate control modes. */
    NvU32                               dwVBVInitialDelay;              /**< [in]: No. of bits to buffer at the decoder end. For lowest latency, set to be equal to dwVBVBufferSize. 
                                                                                   Overridden by NvFBC in case of NVFBC_H264_ENC_PARAMS_RC_2_PASS_QUALITY or NVFBC_H264_ENC_PARAMS_RC_2_PASS_FRAMESIZE_CAP rate control modes.*/
    NvU32                               maxRCQP[3];                     /**< [in]: maxQP[0] = max QP for P frame, maxRCQP[1] = max QP for B frame, maxRCQP[2] = max QP for I frame respectively. */
    NvU32                               dwMaxNumRefFrames;              /**< [in]: This is used to specify the DPB size used for encoding. Setting this to 0 will allow encoder to use the default DPB size.
                                                                                   Low latency applications are recommended to use a large DPB size(recommended size is 16) so that it allows clients to invalidate
                                                                                   corrupt frames and use older frames for reference to improve error resiliency */
    NVFBC_H264_STEREO_FORMAT            stereoFormat;                   /**< [in]: Stereo packing format required in the encoded bitstream. Only valid for MVC content. dwProfile == 128. */
    NvU32                               dwReserved[44];                 /**< [in]: Reserved.Set to 0. */
    void*                               pReserved[32];                  /**< [in]: Reserved. Set to NULL. */
} NvFBC_H264HWEncoder_Config;
#define NVFBC_H264HWENC_CONFIG_VER NVFBC_STRUCT_VERSION(NvFBC_H264HWEncoder_Config, 1)

typedef struct 
{
    NvU32                               dwVersion;                                      /**< [in]: Set to NVFBC_H264HWENC_ENCODE_PARAMS_VER. */
    NvU32                               dwNewAvgBitRate;                                /**< [in]: Specifies the new average bit rate to be used from this frame onwards. */
    NvU32                               dwNewPeakBitRate;                               /**< [in]: Specifies the new peak bit rate to be used from this frame onwards. */
    NvU32                               dwNewVBVBufferSize;                             /**< [in]: Specifies the new VBV buffer size to be used from this frame onwards. */
    NvU32                               dwNewVBVInitialDelay;                           /**< [in]: Specifies the new VBV initial delay to be used from this frame onwards. */
    NvU64                               ulCaptureTimeStamp;                             /**< [in]: Input timestamp to be associated with this input picture. */
    NvU64                               ulInvalidFrameTimeStamp[NVFBC_MAX_REF_FRAMES];  /**< [in]: This specifies an array of timestamps of the encoder references which the clients wants to invalidate*/
    NvU32                               dwRecoveryFrameCnt;                             /**< [in]: Unused. Set to 0. */ 
    NvU32                               bInvalidateRefrenceFrames   : 1;                /**< [in]: Set this to 1 if client wants encoder references to be invalidated. Ignored if Intra-Refresh is enabled for the session. */
    NvU32                               bForceIDRFrame              : 1;                /**< [in]: Replaces dwEncodeParamFlags. Set this to 1 if client wants the current frame to be encoded as an IDR frame. */
    NvU32                               bConstrainedFrame           : 1;                /**< [in]: Reserved. Set to 0. */
    NvU32                               bStartIntraRefresh          : 1;                /**< [in]: Set this to 1 if it wants to force Intra Refresh with intra refresh period dwIntraRefreshCnt*/
    NvU32                               bDynamicBitRate             : 1;                /**< [in]: Set this to 1 if client wants to change bit rate from current frame*/
    NvU32                               bEnableAdaptiveQuantization : 1;                /**< [in]: Set this to 1 if client wants to enable adaptive quantization to encode*/
    NvU32                               bReservedBits               : 26;               /**< [in]: Reserved. Set to 0. */
    NvU32                               dwNumRefFramesToInvalidate;                     /**< [in]: This specifies number of encoder references which the clients wants to invalidate*/
    NvU32                               dwIntraRefreshCnt;                              /**< [in]: Specifies the number of frames over which intra refresh will happen, if bStartIntraRefresh is set. */
    NvU32                               dwReserved[45];                                 /**< [in]: Reserved.Set to 0. */
    void*                               pReserved[32];                                  /**< [in]: Reserved. Set to NULL. */
} NvFBC_H264HWEncoder_EncodeParams;
#define NVFBC_H264HWENC_ENCODE_PARAMS_VER NVFBC_STRUCT_VERSION(NvFBC_H264HWEncoder_EncodeParams, 2);

typedef struct 
{
    NvU32                               bIsIFrame     : 1;                              /**< [out]: Is set if the current frame is an I frame */
    NvU32                               bReservedBits : 31;                             /**< [in]: Reserved for future use */
    NvU32                               dwByteSize;                                     /**< [out]: Size of bitstream produced, in bytes. */
    NvU64                               ulTimeStamp;                                    /**< [out]: Timestamp associated with the encoded frame. */
    NvU32                               dwReserved[60];                                 /**< [in]: Reserved. Set to 0. */
    void*                               pReserved[32];                                  /**< [in]: Reserved. Set to NULL. */
} NvFBC_H264HWEncoder_FrameInfo;
#define NVFBC_H264HWENC_FRAME_INFO_VER NVFBC_STRUCT_VERSION(NvFBC_H264HWEncoder_FrameInfo, 1)

typedef struct
{
    NvU32 dwVersion;                                                                    /**< [in]: Struct version. Set this to NVFBC_H264_SETUP_PARAMS_VER. */
    NvU32 bWithHWCursor :1;                                                             /**< [in]: Set this to 1 for capturing mouse cursor with each grab. */
    NvU32 bIsCustomYUV444:1;                                                            /**< [out]: NvFBC will set this to 1 if the client has requested YUV444 capture,
                                                                                                     and NvFBC needed to use custom YUV444 representation.  */
    NvU32 bReservedBits :30;                                                            /**< [in]: Reserved. Set to 0. */
    NvFBC_H264HWEncoder_Config *pEncodeConfig;                                          /**< [in]: H.264 HW Encoder initial configuration parameters.       */
    NvU32 dwReserved[62];                                                               /**< [in]: Reserved. Set to 0. */
    void *pReserved[31];                                                                /**< [in]: Reserved. Set to NULL. */
} NVFBC_H264_SETUP_PARAMS;
#define NVFBC_H264_SETUP_PARAMS_VER NVFBC_STRUCT_VERSION(NVFBC_H264_SETUP_PARAMS, 1)

typedef struct
{
    NvU32 dwVersion;                                                                    /**< [in]: Struct version. Set to NVFBC_H264_GRAB_FRAME_PARAMS_VER.*/
    NvU32 dwFlags;                                                                      /**< [in]: Set this to one of NVFBC_TO_H264_FLAGS values. Default = NVFBC_TOH264_NOFLAGS. */
    NVFBCH264GrabMode eGMode;                                                           /**< [in]: Set this to one of NVFBCH264GrabMode values. Default = NVFBC_TOH264_SOURCEMODE_FULL. */
    NvU32 dwTargetWidth;                                                                /**< [in]: Set this to indicate the target width in case of eGMode = NVFNC_TOH264_SOURCEMODE_SCALE and in case of eGMode = NVFNC_TOH264_SOURCEMODE_CROP. */
    NvU32 dwTargetHeight;                                                               /**< [in]: Set this to indicate the target height in case of eGMode = NVFNC_TOH264_SOURCEMODE_SCALE and in case of eGMode = NVFNC_TOH264_SOURCEMODE_CROP. */
    NvU32 dwStartX;                                                                     /**< [in]: Set this to indicate the starting x-coordinate of cropping rect in case of in case of eGMode = NVFNC_TOH264_SOURCEMODE_CROP. Cropping rect = {dwStartX, dwStartY, dwStartX+dwTargetWidth, dwStartY+dwTargetHeight} */
    NvU32 dwStartY;                                                                     /**< [in]: Set this to indicate the starting y-coordinate of cropping rect in case of in case of eGMode = NVFNC_TOH264_SOURCEMODE_CROP. Cropping rect = {dwStartX, dwStartY, dwStartX+dwTargetWidth, dwStartY+dwTargetHeight} */
    NvU32 bReserved1;                                                                   /**< [in]: Reserved . Set to 0.*/
    NvFBCFrameGrabInfo* pNvFBCFrameGrabInfo;                                            /**< [in/out]: Pointer to NvFBCFrameGrabInfo struct, used to communicate miscellaneous information. */
    NvU8* pBitStreamBuffer;                                                             /**< [out]: Pointer to a buffer, provided by the client. NvFBC will write encoded H.264 bitstream data in the buffer.*/
    NvFBC_H264HWEncoder_EncodeParams * pEncodeParams;                                   /**< [in]: Pointer to a structure containing per-frame configuration paramters for the H.264 encoder. */
    NvFBC_H264HWEncoder_FrameInfo * pFrameInfo;                                         /**< [out]: Pointer to a structure containing data about the captured frame. The client allocates this struct. */
    NvU32 dwFrameInfoVer;                                                               /**< [in]: Struct version for NvFBC_H264HWEncoder_FrameInfo. Set to NVFBC_H264HWENC_FRAME_INFO_VER.*/
    NvU32 dwMSE[3];                                                                     /**< [out]: Mean square error used to evaluate Quality. Set flag in  NvFBC_H264HWEncoder_Config to enable getting MSE values per channel(Y, U, V) */
    NvU32 dwBitStreamBufferSize;                                                        /**< [in]: Size of the buffer passed in pBitStreamBuffer.*/
    NvU32 dwReserved[51];                                                               /**< [in]: Reserved. Set to 0. */
    void *pReserved[28];                                                                /**< [in]: Reserved. Set to NULL. */
} NVFBC_H264_GRAB_FRAME_PARAMS;
#define NVFBC_H264_GRAB_FRAME_PARAMS_VER NVFBC_STRUCT_VERSION(NVFBC_H264_GRAB_FRAME_PARAMS, 2)

typedef struct
{
    NvU32 dwVersion;                                                                    /**< [in]: Struct version. Set to NVFBC_H264_GET_HEADER_PARAMS_VER. */
    NvU32 dwReserved1;                                                                  /**< [in]: Reserved. Set to 0. */
    NvU32 *pSize;                                                                       /**< [out]: Contains size of the SPS\PPs header data written by the H.264 HW encoder. */
    NvU8  *pBuffer;                                                                     /**< [out]: Pointer to a client allocated buffer. NvFBC H.264 HW encoder writes SPS\PPS data to this buffer. */
    NvU32 dwReserved[62];                                                               /**< [in]: Reserved. Set to 0. */
    void *pReserved[30];                                                                /**< [in]: Reserved. Set to NULL. */
} NVFBC_H264_GET_HEADER_PARAMS;
#define NVFBC_H264_GET_HEADER_PARAMS_VER NVFBC_STRUCT_VERSION(NVFBC_H264_GET_HEADER_PARAMS, 1)

class INvFBCH264HWEncoder_v2
{
    /* First Release */
public:
    /**
     * Setup the NvFBC interface to capture and encode the desktop contents to h.264 bitstream
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCH264SetUp(NVFBC_H264_SETUP_PARAMS *pParam) = 0;
    
    /**
     * Capture the desktop contents and encode as h.264 bitstream
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCH264GrabFrame(NVFBC_H264_GRAB_FRAME_PARAMS *pParam) = 0;
    
    /**
     * Fetch Sequence Parameter and Picture Parameter set header
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCH264GetHeader(NVFBC_H264_GET_HEADER_PARAMS *pParams) = 0;
    
    /**
     * Release NVFBC interface
     */
    virtual NVFBCRESULT NVFBCAPI NvFBCH264Release() = 0;
};

typedef INvFBCH264HWEncoder_v2 NvFBCToH264HWEncoder;
typedef NvFBCToH264HWEncoder NvFBCH264;

#endif // _NVFBC_H264_H_
