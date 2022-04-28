#include "opencv2/highgui/highgui.hpp"

#include "libavcodec/avcodec.h"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    VideoCapture cap("video.mp4");
    // cap is the object of class video capture that tries to capture Bumpy.mp4
    if (!cap.isOpened())  // isOpened() returns true if capturing has been initialized.
    {
        cout << "Cannot open the video file. \n";
        return -1;
    }

    double fps = cap.get(cv::CAP_PROP_FPS); //get the frames per seconds of the video
    // The function get is used to derive a property from the element.
    // Example:
    // CV_CAP_PROP_POS_MSEC :  Current Video capture timestamp.
    // CV_CAP_PROP_POS_FRAMES : Index of the next frame.

    namedWindow("A_good_name", WINDOW_AUTOSIZE); //create a window called "MyVideo"
    // first argument: name of the window.
    // second argument: flag- types: 
    // WINDOW_NORMAL : The user can resize the window.
    // WINDOW_AUTOSIZE : The window size is automatically adjusted to fitvthe displayed image() ), and you cannot change the window size manually.
    // WINDOW_OPENGL : The window will be created with OpenGL support.

    while (1)
    {
        Mat frame;
        // Mat object is a basic image container. frame is an object of Mat.

        if (!cap.read(frame)) // if not success, break loop
        // read() decodes and captures the next frame.
        {
            cout << "\n Cannot read the video file. \n";
            break;
        }

        imshow("A_good_name", frame);
        // first argument: name of the window.
        // second argument: image to be shown(Mat object).

        if (waitKey(30) == 27) // Wait for 'esc' key press to exit
        {
            break;
        }
    }

    return 0;
}