/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// Copyright (c) 1996-2014, Live Networks, Inc.  All rights reserved
// A program that converts a H.264 (Elementary Stream) video file into a Transport Stream file.
// main program

#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "liveMedia.hh"
#include "OnDemandServerMediaSubsession.hh"
#include "LiveSourceWithx264.h"
#include <string>
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"
#include "WindowsAudioInputDevice_noMixer.hh"

FramedSource* videoSource;
NvU32 NVH264::headerSize = 0;
unsigned char NVH264::ppssps_data[1024];

UsageEnvironment* env;
H264VideoRTPSink* videoSink;
RTPSink* audioSink;

int startMediaServer()
{
 OutPacketBuffer::maxSize = 500000;
  // Begin by setting up our usage environment:
  TaskScheduler* scheduler = BasicTaskScheduler::createNew();
  env = BasicUsageEnvironment::createNew(*scheduler);
  H264VideoRTPSink* videoSink;
  // Create 'groupsocks' for RTP and RTCP:
  struct in_addr destinationAddress;

  destinationAddress.s_addr = chooseRandomIPv4SSMAddress(*env);
  //destinationAddress.s_addr = our_inet_addr("96.49.249.165");
  // Note: This is a multicast address.  If you wish instead to stream
  // using unicast, then you should use the "testOnDemandRTSPServer"
  // test program - not this test program - as a model.

  const unsigned short rtpPortNum = 20000;
  const unsigned short rtcpPortNum = rtpPortNum+1;
  const unsigned char ttl = 255;

  const Port rtpPort(rtpPortNum);
  const Port rtcpPort(rtcpPortNum);

  Groupsock rtpGroupsock(*env, destinationAddress, rtpPort, ttl);
  rtpGroupsock.multicastSendOnly(); // we're a SSM source
  Groupsock rtcpGroupsock(*env, destinationAddress, rtcpPort, ttl);
  rtcpGroupsock.multicastSendOnly(); // we're a SSM source

  // Create a 'H264 Video RTP' sink from the RTP 'groupsock':

  videoSink = H264VideoRTPSink::createNew(*env, &rtpGroupsock, 96);
  //videoSink->setPacketSizes(1200,1200);
 increaseSendBufferTo(*env,rtpGroupsock.socketNum(),550*1024);
 

 //Audio
 int inputPortNumber = 0;
 int bitsPerSample = 16;
 int numChannels = 2;
 int samplingFrequency = 44100;
 int granularityInMS = 10;

 /*
  //AudioInputDevice* audioSource = WindowsAudioInputDevice::createNew(*env, inputPortNumber,bitsPerSample, numChannels,samplingFrequency, granularityInMS);
  WindowsAudioInputDevice* audioSource = (WindowsAudioInputDevice*)AudioInputDevice::createNew(*env, inputPortNumber,bitsPerSample, numChannels,samplingFrequency, granularityInMS);

  if (audioSource == NULL)
  {
	  *env << "audiSource null" << env->getResultMsg() << "\n";
	  return 0;
  }

 // audioSink = SimpleRTPSink::createNew(*env,&rtpGroupsock,10,samplingFrequency,"audio","L16",numChannels);
 //WindowsAudioInputDevice* audioSourceSwap =  (WindowsAudioInputDevice*)EndianSwap16::createNew(*env, audioSource);

 //
 */

  // Create (and start) a 'RTCP instance' for this RTP sink:
  const unsigned estimatedSessionBandwidth = 6000; // in kbps; for RTCP b/w share
  const unsigned maxCNAMElen = 100;
  unsigned char CNAME[maxCNAMElen+1];
  gethostname((char*)CNAME, maxCNAMElen);
  CNAME[maxCNAMElen] = '\0'; // just in case
  RTCPInstance* rtcp
  = RTCPInstance::createNew(*env, &rtcpGroupsock,
			    estimatedSessionBandwidth, CNAME,
			    videoSink, NULL /* we're a server */,
			    True /* we're a SSM source */);
  // Note: This starts RTCP running automatically
  RTSPServer* rtspServer = RTSPServer::createNew(*env, 8554);
  if (rtspServer == NULL) {
    *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
    exit(1);
  }


  ServerMediaSession* sms
    = ServerMediaSession::createNew(*env, "testStream", "",
		   "Session streamed by \"testH264VideoStreamer\"",
					   True /*SSM*/);
  sms->addSubsession(PassiveServerMediaSubsession::createNew(*videoSink, rtcp));
 //sms->addSubsession(PassiveServerMediaSubsession::createNew(*audioSink, rtcp));

  rtspServer->addServerMediaSession(sms);
  
  char* url = rtspServer->rtspURL(sms);
  *env << "Play this stream using the URL \"" << url << "\"\n";
  delete[] url;

  // Start the streaming:
  *env << "Beginning streaming...\n";



	LiveSourceWithx264 *source = LiveSourceWithx264::createNew(*env);

  // Create a framer for the Video Elementary Stream:
  H264VideoStreamDiscreteFramer* dSource = H264VideoStreamDiscreteFramer::createNew(*env, source);

  // Finally, start playing:
  *env << "Beginning to read from framer...\n";
  videoSink->startPlaying(*dSource, NULL, videoSink);
  //audioSink->startPlaying(*audioSourceSwap,NULL,audioSink);
  env->taskScheduler().doEventLoop(); // does not return

  return 0; // only to prevent compiler warning
}


int main(int argc, char** argv) {

    

	  startMediaServer();
	 return 0; // only to prevent compiler warning
}

