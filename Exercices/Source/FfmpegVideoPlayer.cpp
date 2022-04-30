#include "FfmpegVideoPlayer.h"

FfmpegVideoPlayer::FfmpegVideoPlayer(const char* filename)
{
	LoadVideo(filename);
}

bool FfmpegVideoPlayer::LoadVideo(const char* filename)
{
	// TODO 1 FFMPEG: Assign the memory of our AVFormatContext variable (avFormatCtx) using avformat_alloc_context()
	
	//First we need to create a context to store the video data in
	//avFormatCtx = avformat_alloc_context(); // Create Context <------------
	if (!avFormatCtx)
	{
		printf("Couldn't format context\n");
		return 0;
	}
	if (avformat_open_input(&avFormatCtx, filename, NULL, NULL)) // fill context with video data
	{
		printf("Couldn't open video\n");
		return 0;
	}


	// TODO 2 FFMPEG: We must find the VIDEO stream inside our Format Context. To do so, we must iterate through every stream until
	// we find the VIDEO stream. Once we find it, we store its index inside our videoStreamIndex variable (check header file)
	// To do so, we must iterate over every stream in avFormatCtx using avFormatCtx->nb_streams.
	// For now we will only get a reference to the current stream using "auto stream = avFormatCtx->streams[currentIteration]"
	
	// We must find the stream that contains the video data
	for (int i = 0; i < /*number of streams*/; i++)
	{
		/*Get a reference to the current stream*/

		// TODO 3 FFMPEG: Now that we have the current stream, we must see if it is a video stream. 
		// To do so, we must access its Parameters. Assign the avCodecParams (check header file) to avFormatCtx->streams[i]->codecpar
		// Then assign avCodec (check header file) to the decoder of these parameters using avCodec = avcodec_find_decoder(avCodecParams->codec_id)
		// This allows us to decode the current information codificated into the stream.


		// TODO 4 FFMPEG: If you made it this far you should have the following:
		// -> a stream variable
		// -> a codec parameters variable
		// -> a codec variable
		// If you don't have one of these in your for loop, check previous TODO
		// Now we must first check if our avCodec variable is false. That would mean the current stream has no codec, therefore we are not interested in it.
		// if that is the case, we continue to the next iteration (use keyword "continue;")
		// After we checked if our codec variable is true, we must check if the codec type is a VIDEO. Remember, the purpose of this loop is to see
		// if we are in a VIDEO stream.
		// To check this, use avCodecParams->codec_type and compare it to AVMediaType::AVMEDIA_TYPE_VIDEO.
		// If true, save the current iteraion number into videoStreamIndex and call "break;" to stop iterating
	}

	// If video stream index is still -1, we didn't find a video stream index. Therefore, there is no video.
	if (videoStreamIndex == -1)
	{
		printf("Couldn't find video stream\n");
		return false;
	}


	// TODO 5 FFMPEG: You don't have to write code in this TODO. Instead, check the following code until the end of the LoadVideo() function.
	// Here we are assigning the memory of the avCodeCtx variable (check header file)  and using the avCodecParams variable to fill it with the codified data
	// Afterwards, we open the Codified data into the avCodecCtx using the Codec we got in our previous for loop
	// On summary, we are using the parameters(avCodecParams) to fill the CodecContext(avCodecCtx), and we are using the Codec(avCodec) to interpret these parameters.
	// Remember the reason we are doing this is because all data is Codified, an we must Decodifiy it before being able to use it
	
	// Set up a codec context for the decoder
	avCodecCtx = avcodec_alloc_context3(avCodec); // Allocate an avCodecContext to store params data
	if (!avCodecCtx)
	{
		printf("Couldn't create AvCodecContext\n");
		return false;
	}

	// Set AvCodecContext parameters 
	if (avcodec_parameters_to_context(avCodecCtx, avCodecParams) < 0)
	{
		printf("Couldn't initialize AvCodecContext\n");
		return false;
	}
	// Open Codec
	if (avcodec_open2(avCodecCtx, avCodec, NULL) < 0)
	{
		printf("Couldn't open codec\n");
		return false;
	}
	return true;
}

AVFrame* FfmpegVideoPlayer::GetFrame()
{
	avFrame = av_frame_alloc();
	if (!avFrame)
	{
		printf("Couldn't allocate frame\n");
		return 0;
	}
	avPacket = av_packet_alloc();

	// TODO 6 FFMPEG: Now that our video is been loaded and decodified, we must read its frames.
	// To do this, first we have to iterate through every packet into our AVFormatContext and find the ones inside our VIDEO stream
	// Fill the following while loop checking if av_read_frame(avFormatCtx, avPacket) is greater or equal to 0.
	
	int result;
	while (/*fill*/)
	{
		// If this is not the video stream, we skip this packet
		if (avPacket->stream_index != videoStreamIndex)
		{
			continue;
		}
		
		// TODO 7 FFMPEG: Now that we have a packet inside our VIDEO stream, we must see if it contains any frames.
		// Packets can contain all sorts of different data, and frames are only some of it. 
		// First, we assign the result variable to avcodec_send_packet(avCodecCtx, avPacket), to see if our packet is valid.
		// If this is minor than 0, stop the function using return 0 and print "Failed to decode packet"
		// Then, assign result to avcodec_receive_frame(avCodecCtx, avFrame)
		// Here there's 3 options:
		// 1. result equals AVERROR(EAGAIN), which indicates this frame has already been decoded.
		// 2. result equals AVERROR_EOF, which indicates this is the end of the file.
		// 3. result is minor than 0, which indicates an error ocurred.
		// In cases 1 and 2, we go to the next iterarion using the keyword "continue;"
		// In case 3, we return 0;

		// This is a hard code! If you are not making it, here is the solution to keep you from guessing. Use the code below if you don't want
		// to do this TODO and prefer to go to the next one.

		/*result = avcodec_send_packet(avCodecCtx, avPacket);
		if (result < 0)
		{
			printf("Failed to decode packet\n");
			return 0;
		}
		result = avcodec_receive_frame(avCodecCtx, avFrame);
		if (result == AVERROR(EAGAIN) || result == AVERROR_EOF) // If this frame has already been decoded or it is the end of the file
		{
			continue;
		}
		else if (result < 0)
		{
			printf("Faild to decode packet\n");
			return 0;
		}
		*/

		// If no error is given on this point, we successfully recieved a frame
		return avFrame;
	}

	// If we don go into the while loop, we return nullptr to notice there is no frame available
	return nullptr;
}

double FfmpegVideoPlayer::GetFPS()
{
	auto stream = avFormatCtx->streams[videoStreamIndex];
	const double FPS = (double)stream->r_frame_rate.num / (double)stream->r_frame_rate.den;
	return FPS;
}

void FfmpegVideoPlayer::CleanUp()
{
	av_packet_unref(avPacket);
	av_packet_free(&avPacket);
	av_frame_free(&avFrame);
	avformat_close_input(&avFormatCtx);
	avformat_free_context(avFormatCtx);
	avcodec_free_context(&avCodecCtx);
}