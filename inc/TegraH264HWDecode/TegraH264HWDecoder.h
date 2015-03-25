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

//! The default size of an input buffer (4 MB).
#define MIN_INPUT_BUFFER_SIZE 0x400000u

namespace nv
{
    //! Forward declaration of the implementation class.
    class TegraH264HWDecoderImpl;

    //! Class that exposes a simple interface to the Tegra H.264 h/w decoder.
    class TegraH264HWDecoder
    {
        // Disallowed copy constructor and assignment operator.
        TegraH264HWDecoder(const TegraH264HWDecoder &);
        TegraH264HWDecoder &operator=(const TegraH264HWDecoder &);

      public:
        //! Class that obtains H.264 compressed bits when requested.
        struct Reader
        {
            //! Destructor
            virtual ~Reader() {}

            //! Load compressed bits into the provided buffer.
            /*!
              \param buffer Buffer into which the compressed data must be copied.
              \param allocLen Size of the input buffer in bytes.
              \param timeStamp Time stamp associated with the input buffer.
              \return
              The number of bytes written into the input buffer.  A return value
              of 0 indicates that the Reader has reached the end of stream.
              \remarks
              Behavior is undefined if the number of bytes written into the
              buffer exceeds its capacity.
            */
            virtual uint32_t read(void *buffer, uint32_t allocLen, uint64_t &timeStamp) = 0;
        };

        //! Class that receives notifications.
        struct Listener
        {
            //! Destructor
            virtual ~Listener() {}

            //! Invoked when a frame has been decoded and is about to be queued
            //! for rendering.
            /*! \param timeStamp The timestamp of the frame in question. */
            virtual void onFrameDecoded(uint64_t timeStamp) = 0;
        };

      public:
        //! Constructor.
        /*!
          \remarks The TegraH264HWDecoder must be initialize()d before use.
        */
        TegraH264HWDecoder();

        //! Destructor.
        /*!
          \remarks The TegraH264HWDecoder must be shutdown() before destruction.
        */
        ~TegraH264HWDecoder();

        //! Initialize a newly constructed TegraH264HWDecoder.
        /*!
          \param reader Object that obtains compressed bits.
          \param listener Object that receives notifications.  May be NULL.
          \param nativeVideoWindow The ANativeWindow associated with the Java Surface.
          \param inputBufferSize The size of allocated input buffers (in bytes).
          \return
          true if initialization succeeded, false otherwise.  See the Android
          log for more information on why initialization failed.
          \remarks
          The ANativeWindow reference can be obtained from the Java Surface
          (jobject) using ANativeWindow_fromSurface().  See native_window_jni.h.
          The ANativeWindow reference will be automatically released by calling
          ANativeWindow_Release().
        */
        bool initialize(Reader *reader,
                        Listener *listener,
                        ANativeWindow *nativeVideoWindow,
                        uint32_t inputBufferSize = MIN_INPUT_BUFFER_SIZE);

        //! Shutdown the TegraH264HWDecoder.
        void shutdown(void);

      private:
        //! The object that contains the actual implementation.
        TegraH264HWDecoderImpl *m_impl;
    };
}

