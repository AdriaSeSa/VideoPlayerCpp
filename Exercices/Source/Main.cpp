#include "OpenCVVideoPlayer.h"
#include "FfmpegVideoPlayer.h"

#include "SDL.h"  
#include "Timer.h"

#include <memory>
#include <stdint.h>
#include <Windows.h>

int main(int argc, char** argv)
{
	// Uncomment this code if you want to do the OpenCV Video Player
	// Run code to play a video using OpenCV
	//OpenCVVideoPlayer(); // Go into this constructor to see the OpenCV Video Player code

	// Run code to play a video using Ffmpeg and SDL2
	//Uncomment this code if you want to do the FFmpeg and SDL Video Player

	// Create an instance of an ffmpegVideoPlayer
	FfmpegVideoPlayer ffmpegVP = FfmpegVideoPlayer("video.mp4");

	// Get the current video frame
	AVFrame* videoFrame = ffmpegVP.GetFrame();

	// Convert to total milliseconds per frame
	double framesPerSecond = ffmpegVP.GetFPS();
	double milisecondsPerFrame = 1000 / framesPerSecond;

	// Create a timer to control fps
	Timer timer;

	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		printf("Could not initialize SDL - %s\n", SDL_GetError());
		return -1;
	}

	//Create SDL Window
	SDL_Window* screen = SDL_CreateWindow("SDL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		videoFrame->width, videoFrame->height,
		SDL_WINDOW_OPENGL
	);

	if (!screen)
	{
		printf("SDL: could not create window - exiting:%s\n", SDL_GetError());
		return -1;
	}

	// Create Renderer
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
	// Set pixel format to IYUV
	//IYUV: Y + U + V  (3 planes)  
	SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer,
		SDL_PIXELFORMAT_IYUV,
		SDL_TEXTUREACCESS_STREAMING,
		videoFrame->width,
		videoFrame->height
	);
	// Texture rect, same size as video
	SDL_Rect sdlRect;
	sdlRect.x = 0;
	sdlRect.y = 0;
	sdlRect.w = videoFrame->width;
	sdlRect.h = videoFrame->height;

	while (1)
	{
		// If our video frame is nullptr, it means there is no more frames to render (or video loading failed)
		if (videoFrame == nullptr) break;

		// TODO 8 FFMPEG: Final TODO! Now that we have the current frame of our video, we must print it using SDL.
		// To do so, we must update the already created texture using SDL_UpdateYUVTexture().
		// The parameters should be as it follows:
		// sdlTexture
		// &sdlRect (check previous lines of code, this is just an SDL_Rect same size as the video)
		// Y data
		// Y linesize
		// U data
		// U linesize
		// V data
		// V linesize
		// To access Y, U and V data use videoFrame->data[0], videoFrame->data[1] and videoFrame->data[2] respectively.
		// to access Y, Y and V linesize use videoFrame->linesize[0], videoFrame->linesize[1] and, videoFrame->linesize[2] respectively.
		
		// Update our texture with video Frame YUV data
	
		// Update renderer
		SDL_RenderClear(sdlRenderer);
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
		SDL_RenderPresent(sdlRenderer);

		// Get next frame
		videoFrame = ffmpegVP.GetFrame();

		// Control our FPS 
		timer.Update();
		int deltaTime = timer.getDeltaTime();
		if (timer.getDeltaTime() < milisecondsPerFrame)
		{
			Sleep(milisecondsPerFrame - deltaTime);
		}
	}

	// When the application is done, we have to deallocate all memory
	ffmpegVP.CleanUp();
	
	return 0;
}

