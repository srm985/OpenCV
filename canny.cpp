#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{    
    // load the image
    IplImage* img = cvLoadImage("boom.jpg");
    
    // create a place for images we'll be working with
    IplImage* grayImg = cvCreateImage(cvSize(img->width,img->height), img->depth, 1);
    IplImage* outImg = cvCreateImage(cvSize(img->width,img->height), img->depth, 1);
    
    // convert to grayscale
    cvCvtColor(img, grayImg, CV_RGB2GRAY);
    
    cvCanny(grayImg, outImg, 0, 255);
    
    cvNamedWindow("Output", CV_WINDOW_AUTOSIZE);
    cvShowImage("Output", outImg);
    
    // wait for the user to press a key
    cvWaitKey();
    
    cvDestroyWindow("Output");
    
    cvReleaseImage(&img);
    cvReleaseImage(&grayImg);
    cvReleaseImage(&outImg);
}
