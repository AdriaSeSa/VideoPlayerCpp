#pragma once
extern "C"
{
#include "libavcodec/avcodec.h"  
#include "libavformat/avformat.h"  
#include "libswscale/swscale.h"  
#include "libavutil/imgutils.h" 
}

class FfmpegVideoPlayer
{
public:
	FfmpegVideoPlayer(const char* filename);
	void CleanUp();
	AVFrame* GetFrame();
	double GetFPS();
private:
	bool LoadVideo(const char* filename);

private:
	// TODO 0 FFMPEG: Check all the necessary variables. These will be created and destroyed with the instance of this class
	// You must not destroy them before finishing the video.
	// The already get destroyed on CleanUp() function, called at the end of main.cpp

	AVFormatContext* avFormatCtx = nullptr; // Context information about the video
	int videoStreamIndex = -1; // The index of the video stream of our AvFormatContext
	AVCodecParameters* avCodecParams = nullptr; // The parameters of our video stream
	const AVCodec* avCodec = nullptr; // The codification of our video stream
	AVCodecContext* avCodecCtx = nullptr; // The context of our video stream codification
	AVFrame* avFrame = nullptr; // Our frame
	AVPacket* avPacket = nullptr; // Our vide stream package
};

