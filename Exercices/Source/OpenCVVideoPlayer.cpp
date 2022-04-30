#include "OpenCVVideoPlayer.h"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;


OpenCVVideoPlayer::OpenCVVideoPlayer()
{
    // TODO 1 OCV: Create a VideoCapture variable and initialize it with the name of the file you want to reproduce.
    // Use VideoCapture variableName("VideoName") // Remember to add the extension on the name (.mp4, .wav, .avi...)
 
    // TODO 2 OCV: Fill the next if statement using the function isOpened() on the VideoCapture variable.
    // This way we can be sure the given file was found and opened successfully.
    /*if (*!variableName.isOpened()*)  // isOpened() returns true if capturing has been initialized.
    {
        cout << "Cannot open the video file. \n";
        return;
    }*/

    // TODO 3 OCV: Get the fps of the video using variableName.get(cv::CAP_PROP_FPS)
    double fps;
    //fps = *fill this gap*

    // We create a window using OpenCV
    namedWindow("VideoPlayer with OpenCV!", WINDOW_AUTOSIZE); 
    // first argument: name of the window.
    // second argument: flag- types: 
    // WINDOW_NORMAL : The user can resize the window.
    // WINDOW_AUTOSIZE : The window size is automatically adjusted to fit the displayed image, and you cannot change the window size manually.
    
    while (1)
    {
        // TODO 4 OCV: Create a Mat object to store the current frame data into it.
        // Mat object is a basic image container. frame is an object of Mat.

        // TODO 5 OCV: Fill the next if statement with VideoCapture.read(Mat), using the variables you made for your VideoCapture and Mat
        /*if (VideoCapture.read(Mat)) // if not success, break loop
        {
            cout << "\n Cannot read the video file. \n";
            break;
        }*/

        // TODO 6 OCV: Update the created window with a name and an image. The image is the Mat variable we created before. Use imshow(name, Mat)
        //imshow(name, Mat)
        // first argument: name of the window.
        // second argument: image to be shown(Mat object).

        if (waitKey(30) == 27) // Wait for 'esc' key press to exit
        {
            break;
        }
    }
}
