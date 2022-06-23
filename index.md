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

Making a Video Player is a hard task, and if you are a beginner programmer this may be a bit challenging for you (it was plenty of a challenge for me at least). I will try to explain what is the problem we are trying to solve, before starting the project's first chapter.

The main issue with creating a Video Player in videogames it's that it requires to decodify information on an already demanding context (video games are really demanding for the computer). So decodifying a video can affect our performance. On the other hand, decodifying a video is not an easy task. There are many ways a video can be codified, and it can be stored in a lot of formats (.mp4, .wav, .avi ...), which makes the task a lot harder. 
Of these two main issues, the second one is the only we can try to approach. Performance can hardly be improved.

## Market Study

Using Videos on videogames has been a common method to introduce a videogame's narrative. An easy example of this is Final Fantasy VII's introduction, that had a 3 minute pre-rendered animation played at the beginning of the game to introduce us it's characters and location.

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

## Examples

I have created one code example for both approaches, and they are available inside the github [repository](https://github.com/AdriaSeSa/VideoPlayerCpp) linked to this page.

**WARNING: To use these examples you have to download [this](https://drive.google.com/drive/folders/1ssyBmUIr7sRFqAvcQhOaHOrgnxvEmQAu?usp=sharing) .dll file and place it inside the Game folder. This is a dynamic library for debugging OpenCV. It gets corrputed if uploaded with github for some reason I don't understand, so you have to download it manually.**

You can either check the Exercices folder, where I created a step-to-step exercice to write the code for both approaches, or the Solution folder, where you can find the completed code.

In both templates I created the same structure. There are two classes, one for each approach, with the code necessary to reproduce video inside them. You can either call one or the other inside main.cpp. These are:

* OpenCVVideoPlayer
* FfmpegVideoPlayer

**OpenCVVideoPlayer**

Here the strcuture is fairly simple. The constructor to this class containts all the code necesarry for loading and rendering the video you choose. Of course, this is just a sample code. You would want to separate the while loop for rendering the video into another function. 

**FfmpegVideoPlayer**

Inside this class the strcuture is:
* Constructor that calls LoadVIdeo() with a given file name
* LoadVideo() that load the AVFormatContext, AVCodecParameters, AVCodec and AVCodecCOntext variables, as well as getting the video stream index.
* GetFrame() that iterates through our video data to get the next frame.
* GetFPS() that calculates the video FPS.
* CleanUp() to free all allocated memory.

On main.cpp we can se a simple example on how to use this class correctly using SDL2. You basically need a renderer and a texture. Inside your application loop, update that texture with the YUV information inside the frame given by GetFrame(). When frame equals a nullptr, the video has ended (or an error has occured), and you can proceed as you want (in my case I just end the application).

## Exercises explanation

Now I will give a detailed explanation of every TODO written inside both approach's exercises.

### OpenCV approach

You can check the OpenCV API [here](https://docs.opencv.org/4.5.5/) in case you feel lost.

**TODO 1**
First we need our [VideoCapture](https://docs.opencv.org/4.5.5/d8/dfe/classcv_1_1VideoCapture.html) variable. This is a variable to store video data. Initialize it with the desired file name to reproduce.

**TODO 2**
For every step we make we need to make sure we are not makin a mistake. Create an if statement that used the class function isOpened() of our VideoCapture variable to see if we correctly opened the video. If not, you probably wrote the file name incorrectly, or the video is corrputed.

**TODO 3**
We need the Frames Per Second ratio to reproduce the video correctly. We can get this from our VideoCapture variable. Use the function .get() and fill it with cv::CAP_PROP_FPS.

**TODO 4**
Now we have to display our video. To do that, OpenCV has a class named [Mat](https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html), that stores image data and can be given to the window directly. Create a Mat Variable.

**TODO 5**
Now we have to store our video data inside the Mat variable. To do so, use the class function .read() inside our VideoCapture variable and fill it with our new Mat variable. This function returns a boolean. Check if it returns false and finish the process if so.

**TODO 6**
Lastly, we need to update our window with the new data stored in our Mat variable. Use imshow(windowName, Matvariable) to do this. imshow() is a function from the highui library inside OpenCV.

Now, if you are calling this class constructor inside main, and you have commented the FFmpeg part of the code, you should see your video reproduce when you compile.

### Ffmpeg approach

You can check the Ffmpeg API [here](http://www.ffmpeg.org/documentation.html) in case you feel lost.

**TODO 1**
First we need to allocate the necessary memory for our AVFormatContext variable. To do this, use the avformat_alloc_context() function and assign its result to the already declared variable named avFormatCtx. This variable is declared at the header file of this class.

**TODO 2**
Now we need to find our video stream. To do so, we must iterate over each stream inside our AvFormatContext variable. You will get the number of streams with the nb_streams variable inside our AvFormatContext variable, and you can get the streams data on an array named streams inside the AvFormatCOntext as well.
Once we have a for loop, we must get the stream data inside a variable to check it later. Store the current iteration stream data inside an auto variable using "auto stream = avFormatCtx->streams[i]"

**TODO 3**
Now we need to see if the stream we are currently iterating on is a video stream. We can check that using the Parameters inside the current stream. Assign the avCodecParams variable to our format context variable's codecpar.
Then assign our avCodec variable to the result of avcodec_find_decoder(avCodecParams->codec_id). We will use this later on.

**TODO 4**
Once we have an avCodec we need to see if it is actually filled with data. This tells us if there has been an error inside this stream. So, check if the avCodec variable is false. If it is, you should stop the process.
After that we need to see if our stream is a VIDEO stream. To see this, use the avCodecParams->codec_type variable and compare it to AVMediaType::AVMEDIA_TYPE_VIDEO.
If it returns true, assign the current iteration to our videoStreamIndex variable. We will use this in the future to access this stream.

**TODO 5**
You don't have to wirte the following code, just understanding what it does is enough. 
Here we are assigning the memory of the avCodeCtx variable (check header file)  and using the avCodecParams variable to fill it with the codified data. Afterwards, we open the Codified data into the avCodecCtx using the Codec we got in our previous for loop. On summary, we are using the parameters(avCodecParams) to fill the CodecContext(avCodecCtx), and we are using the Codec(avCodec) to interpret these parameters. Remember the reason we are doing this is because all data is Codified, an we must Decodifiy it before being able to use it

**TODO 6**
Now we have to get the frames. First we must iterate thorugh every packet inside our AvFormatContext variable, and see if it is related to the video stream we found at TODO 4. For starters, fill the while loop with the following check: "av_read_frame(avFormatCtx, avPacket) >= 0". If this returns false, it means there is no packets with frames left.

**TODO 7**
Once we know we are inside a video stream packet, we need to see if it contains any frames. We will use the avcodec_send_packet(avCodecCtx, avPacket) to see if our packet is valid first. If not, stop the process.
Then, we need to use avcodec_receive_frame(avCodecCtx, avFrame) to see if the packet contains any frames. This function can give us the following outputs:
* It returns AVERROR(EAGAIN), which indicates this frame has already been decoded.
* It returns AVERROR_EOF, which indicates this is the end of the file.
* It returns an integer minor than 0, which indicates an error ocurred.

If we get AVERROR(EAGAIN) or AVERROR_EOF, we use the keyword "continue" to go to the next frame (in case this one was already read) or end the process returning an empty frame (in case this was the end of the file).
If we get another error, we just stop the process.

**TODO 8**
Finally, we can render our frame. using the GetFrame() function we can now get the frame information and use it inside our SDL_Texture. Inside main.cpp there is already a texture prepared. We just have to use the SDL_UpdateYUVTexture() function to fill it with our frame data. The parameters should be:
* sdlTexture
* &sdlRect (check previous lines of code, this is just an SDL_Rect same size as the video)
* Y data
* Y linesize
* U data
* U linesize
* V data
* V linesize
To access Y, U and V data use videoFrame->data[0], videoFrame->data[1] and videoFrame->data[2] respectively.
To access Y, Y and V linesize use videoFrame->linesize[0], videoFrame->linesize[1] and, videoFrame->linesize[2] respectively.	 

If everything has been done correctly, and you have the OpenCV constructor call commented, you should be now seeing your video reproducing when compiling the code. 

## References

https://www.youtube.com/watch?v=W6Yx3injNZs&list=PL3tTRNNl2htmYsuodk4ycATQV84K63OPH&index=43&t=710s This has been my main reference! Thanks a lot to Bartholomew for this video, it was very illustrative.

https://www.youtube.com/watch?v=qMNr1Su-nR8&t=399s

https://programming.vip/docs/video-player-based-on-ffmpeg-and-sdl-sdl-video-display.html

https://joanvaliente.github.io/Video-Player-Research/

https://programmerclick.com/article/99852034665/

https://www.gamedev.net/forums/topic/348340-play-video-files-in-sdl/

https://stackoverflow.com/questions/13669346/libavcodec-get-video-duration-and-framerate

https://stackoverflow.com/questions/31116781/playing-a-video-file-in-opencv-c

https://discourse.libsdl.org/t/how-to-play-video-in-sdl2-0-1/20206
