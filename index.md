# Video Player using C++ by Adrià Sellarés Salvador

Welcome! This is a small project created by a Videogame Development and Design student. I'll show you how I managed to create a Video Player using Visual Studio 2019 and C++. Notice this project may possibly not work on another OS. If you want to try running the code on iOS, keep in mind you may need to make some changes. Even so, the libraries used in this project are cross platform, so the code can be very likely transformed to work using the same libraries.

In the GitHub repository you'll find two folders, one containing an exercice and the other the solution to that exercice. If you are interested on checking the Github respoitory click [here](https://github.com/AdriaSeSa/VideoPlayerCpp).

Aside from the code, I'll also have a small essay about Video Players in videogame context, as well as an explanation on what were my reasons to choose the selected libraries and methodologies. Check the following index:

1. Market Study
2. Selected Approach
3. Possible Improvements
4. Examples
5. Exercises explanation
6. References

Making a Video Player is a hard task, and if you are a beginner programmer this may be a bit challenging for you (it was plenty of a challenge for me at least). I will try to explain what is the problem we are trying to explain, before starting the project's first chapter.

The main issue with creating a Video Player in videogames it's that it requires to decodify information on an already demanding context (video games are really demanding for the computer). So decodifying a video can affect our performance. On the other hand, decodifying a video is not an easy task. There are many ways a video can be codified, and it can be stored in a lot of formats (.mp4, .wav, .avi ...), which makes the task a lot harder. 
Of these two main issues, the second one is the only we can try to approach. Performance can hardly be improved.

## Market Study

Using Videos on videogames has been a common recurrent method to introduce a videogame narrative since a long time ago. An easy example of this is Final Fantasy VII's introduction, that had a 3 minute pre-rendered animation played at the beginning of the game to introduce us it's characters and location.

<iframe width="560" height="315" src="https://www.youtube.com/embed/JujtlsiqZ-E" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Nowadays this method is used a lot less, since animating characters and using the in-game camera can be an easier way to achieve this. Even so, there are videogames that still use videos for cutscenes, introductions and endings, so it is not an obsolete tool. However it is true that, when speaking of cutscenes, videogames have ceased to use pre-rendered videos to create them, and instead are now using the engine to do it. Here are the main reasons why:

First, and most important, it requires less space in disk. Pre-rendered videos can be very heavy, specially nowadays where the standard has a very high quality.

Second, there is not a noticable change of quality. This makes reference to two things. You can use the engine to create the cutscene with a very high quality, so there is no reason to make a pre-rendered video, and there won't be a change of graphics quality when changing between gameplay and cutscene, therefore improving player inmersion.

Third, reuse, always reuse. You can't reuse a cutscene to create another cutscene. But you can use the same elements you have in your engine to create multiple cutscenes. It is just more efficient.

So, if using video insted of engine cutscenes is just better, why would you still want to do it? Well, you certainly can avoid it, but video has a really important advantage still: it is limitless. You can create a video with any visual style. We can see a very clear example of this in the The Witcher 3's intro. In this intro, the art used for the video could not be used inside an engine because it does not share the same art style as the game. You could charge those sprites in your game to create the ctuscene inside the engine, but you would not use them again, so they would become a waste of storage. 

<iframe width="560" height="315" src="https://www.youtube.com/embed/dd2gz6AxYoA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

In summary, video is still a very optimal option if you want to create cutscene where you won't use elements of the gameplay, such as characters or locations, as used in-game. If that is not the case, you can always use an engine to run the cutscene in real time, and add inmersion to the player's experience.


## Selected Approach

Now that we understand the pros and cons of using videos in videogames, let's get into HOW to do it. Keep in mind we can't use any engines like Unity or Unreal, and we are using C++. I'm a Windows user, so I will be doing it with Visual Studio 2019. Another condition is, if able, using SDL2 as well. This is because SDL2 is the standard library used for games created without an engine in my university, so being able to reproduce video inside an SDL2 window is necessary if I ever intend to use any of the code in a future project.

Doing some research I've discovered two ways of solving this issue.

On the first one, I will NOT use SDL2, and I will reproduce video using another rendering library named OpenCV.

On the second one, I will use SDL2, and I will decodify the video data using FFmpeg's libraries avcodec and avformat.

On the first approach, using OpenCV is the easiest way to go around this task. OpenCV is an open source library that is ready to reproduce video in an extreamly easy way. This library already has a decodifying feature to read video data, and so you don't need any extra libraries to do it.

On the second approach, we find ourselves with the problem that SDL2 has no way of reading video data. So, in order to render a video, we must use a decodifying library to read and decodify video data, and give that data to SDL2 to render. The library I choosed is Ffmpeg's libavcodec and libavformat. These are responsible of opening the video file, finding its components and frames, and storing that information in a way SDL2 can understand.

### Using OpenCV

Because OpenCV is ready to reproduce video already, this becomes a really easy task. I will not explain here how to set up a Visual Studio project with OpenCV libraries, because I think it's a little off topic, but I will leave some links on the References part in case you need some help with that.

Once we have OpenCV in our project, we can start reproducing video right away. Just follow these steps:

_Here is the code I used. If you are planning to make a serious application please consider to modularize this code into parts first._

1. Create a VideoCapture variable to store your video data

```
  VideoCapture cap("video.mp4");
    // cap is the object of class video capture that tries to capture Bumpy.mp4
    if (!cap.isOpened())  // isOpened() returns true if capturing has been initialized.
    {
        cout << "Cannot open the video file. \n";
        return;
    }
```
2. Get the video FPS
```
 double fps = cap.get(cv::CAP_PROP_FPS);
```
3. Create a window
```
 namedWindow("A_good_name", WINDOW_AUTOSIZE);
```
4. Inside your application loop, create a Mat variable (this is basically an image)
```
Mat frame;
```
5. Use your VideoCapture variable to read the frame information into your Mat variable
```
  if (!cap.read(frame)) // if not success, break loop
        // read() decodes and captures the next frame.
        {
            cout << "\n Cannot read the video file. \n";
            break;
        }
```
6. Update your window with your Mat variable

```
 imshow("A_good_name", frame);
```

As simple as that! If you have your video file inside the right directory you should able to create a window that reproduces your video and closes after finishing.

### Using Ffmpeg and SDL2

To be able to reproduce video, we must find every frame inside the video we choose and render it into an SDL_Texture. This seems fairly simple, but getting a frame from a video is where the challenge is met. To see how to accomplish this, we must first understand how video data is stored. 

Libavocdec and libavformat are libraries that help us to open and decode video information. But what does that mean? 

All video data is encrypted, and in order to read it we must first decrypt it. Although these libraries do this exact task, they do not do it automatically, so we must understand (at least on a basic level) how video is encrypted. I will make an over-simplified verison step-to-step of this approach in order to explain both how video data is stored and how to read it.

1. First we have an AVFormatContext variable, which contains all the data on that video file.
```
avFormatCtx = avformat_alloc_context(); // Create Context
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
```
2. Inside our AVFormatContext we can find multiple streams. Streams can have all sorts of information, but only one of them has the video data. We must find which one of those streams contains video data and store it.
```
for (int i = 0; i < avFormatCtx->nb_streams; i++)
	{
		auto stream = avFormatCtx->streams[i];
		avCodecParams = avFormatCtx->streams[i]->codecpar;
		avCodec = avcodec_find_decoder(avCodecParams->codec_id);

		if (!avCodec) //  If there is no codec we look for the next stream. This should never happen on a normal video file.
		{
			continue;
		}

		if (avCodecParams->codec_type == AVMediaType::AVMEDIA_TYPE_VIDEO) // If this is the video stream, we save its index
		{
			videoStreamIndex = i;
			break;
		}
	}
```
3. Once we have our video stream, we must create a Codec and CodecContext variable to store the stream codification and decrypt it. 
```
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
```

4. With the video stream data decrypted, we must find our frames. It's our lucky day, because Ffmpeg has a way to tell which frames we have already read, so we won't have to pay attention to that. 

5. To find those frames, we must learn about Packets. These are small pieces of data that the AVFormatContext contains. We must find those that are related with the video stream, and read them looking for a frame.

```
while (av_read_frame(avFormatCtx, avPacket) >= 0)
	{
		// If this is not the video stream, we skip this packet
		if (avPacket->stream_index != videoStreamIndex)
		{
			continue;
		}
		// Check for every possible error on this step
		result = avcodec_send_packet(avCodecCtx, avPacket);
		if (result < 0)
		{
			printf("Faild to decode packet\n");
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

		// If no error is given on this point, we successfully recieved a frame
		return avFrame;
	}
```

If we find a frame, we can store it to render it later (and stop looking for more frames).

Steps 1 to 4 must be done once per video, and step once per frame.

Now, before getting to SDL2 and how to render our frame (remember for now we only accomplished to get the frame data), lets look a little bit deeper into how this data encryption works.

As you have read, there are many data structures inside a video that contain important data. The ones we are paying more attention to are:
1. Our Video Context, which contains all data
2. Our Video Stream, which contains all video related data
3. Packets, that can contain frame data
4. Frames, that contain the actual frame data we are looking for.

The Video Context conatins all the data, and it can be accessed to get the streams and packets. Check the [AVFormatContext](https://ffmpeg.org/doxygen/trunk/structAVFormatContext.html) API for more information.

The video [Streams](https://ffmpeg.org/doxygen/trunk/structAVStream.html#details) contain the data of specific parts of the video. It could be video, audio or metadata like subtitles. 

[Packets](https://ffmpeg.org/doxygen/trunk/structAVPacket.html) are similar to streams, but in a smaller scale. They can contains almost any kind of data, and some of them conatin one or multiple frames.

Lastly, [frames](https://ffmpeg.org/doxygen/trunk/structAVFrame.html), contain the raw video information. We are mainly interested in the color and size data, but they contain many more information. There is a very important feature about frames inside video, and that is they are not stored as RGB, but as YUV.

So, now that we understand what data we are getting, let's render those frames.

As I wrote before, Frames are stored using YUV data instead of RGB. This is not a problem for us, because SDL2 contains a function we can use to update an already existing texture with YUV data. This is just perfect, because it allows us to create an empty texture and fill it with data any time we need it.

The process is as simple as:
1. Create an empty texture, and create an empty SDL_Rect which size is the video size (we will use this rect to render our texture). The texture must be set with the correct flags in order to edit it using YUV data.
```
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
	}
```
2. Get the AVFrame variable from the code created before, and update our texture with YUV information.
```
// Update our texture with video Frame YUV data
		SDL_UpdateYUVTexture(sdlTexture, &sdlRect,
			videoFrame->data[0], videoFrame->linesize[0],
			videoFrame->data[1], videoFrame->linesize[1],
			videoFrame->data[2], videoFrame->linesize[2]
		);
```
3. Render the texture using usual SDL2 code.
```
// Update renderer
		SDL_RenderClear(sdlRenderer);
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
		SDL_RenderPresent(sdlRenderer);
```
4. Extra Step! Make sure to have a way to control how often you call for the next frame. You should be calling for the next frame at the same ratio as the original video frame rate. Fortunately, we can get the video FPS pretty easily. We will have to acces our video stream first. 
```
const double FPS = (double)stream->r_frame_rate.num / (double)stream->r_frame_rate.den;
```

If everything has been done correctly, this should be enough to charge, read, decrypt, and render a frame using FFmpeg and SDL2!

## Possible Improvements

Creating a Video Player is a hard task, and the approches I have explained are far form perfect. 

The OpenCV approach is fairly simple, and can only be improved in a defined context. If you were to use this approach, you should try to break it down to controllable steps. Also, it has no option for multiple windows.

The Ffmpeg and SDL2 approach has many flaws. First, it has no audio, so you should look into how to reproduce audio using SDL's audio library SDL_Mixer, and see how to use the audio stream data with said library. Also, this is a fairly tasking code for your game performance. In my Visual Studio code only reproducing a 10 second video costed almost 100 MB of RAM. Using an already existing library to decode the video most likely made the performance better, but it is still a problem. Finally, we can't reproduce more than one video simultaneously using the given code. It could be transformed into multiple textures getting data from multiple frames.
