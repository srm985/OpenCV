#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main()
{    
    // load the image
    IplImage* img = cvLoadImage("boom.jpg");
    
    // create a place for images we'll be working with
    IplImage* blurImg = cvCreateImage(cvSize(img->width,img->height), img->depth, img->nChannels);
    IplImage* hsvImg = cvCreateImage(cvSize(img->width,img->height), img->depth, img->nChannels);
    IplImage* blurHsvImg = cvCreateImage(cvSize(img->width,img->height), img->depth, img->nChannels);
    IplImage* blurOutImg = cvCreateImage(cvSize(img->width,img->height), img->depth, img->nChannels);
    IplImage* outImg = cvCreateImage(cvSize(img->width,img->height), img->depth, img->nChannels);
    
    // blur the image
    cvSmooth(img, blurImg, CV_GAUSSIAN, 11, 11);
    
    // convert to HSV
    cvCvtColor(img, hsvImg, CV_RGB2HSV);
    cvCvtColor(blurImg, blurHsvImg, CV_RGB2HSV);
    
    // iterate through all the pixels, filter
    int step = img->widthStep;
    int channels = img->nChannels;
    for(int i=0; i < img->height; i++)
    {
        for(int j=0; j < img->width; j++)
        {
            if(hsvImg->imageData[i*step+j*channels] < 100 and hsvImg->imageData[i*step+j*channels] > 50)
            {
               hsvImg->imageData[i*step+j*channels] = 0;
               hsvImg->imageData[i*step+j*channels+1] = 0;
               hsvImg->imageData[i*step+j*channels+2] = 0;
            }
            if(blurHsvImg->imageData[i*step+j*channels] < 100 and blurHsvImg->imageData[i*step+j*channels] > 50)
            {
               blurHsvImg->imageData[i*step+j*channels] = 0;
               blurHsvImg->imageData[i*step+j*channels+1] = 0;
               blurHsvImg->imageData[i*step+j*channels+2] = 0;
            }
        }
    }
    
    cvCvtColor(hsvImg, outImg, CV_HSV2RGB);
    cvCvtColor(blurHsvImg, blurOutImg, CV_HSV2RGB);
    
    cvNamedWindow("Output", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Output - blurred", CV_WINDOW_AUTOSIZE);
    cvShowImage("Output", outImg);
    cvShowImage("Output - blurred", blurOutImg);
    
    // wait for the user to press a key
    cvWaitKey();
    
    cvDestroyWindow("Output");
    cvDestroyWindow("Output - blurred");
    
    cvReleaseImage(&img);
    cvReleaseImage(&blurImg);
    cvReleaseImage(&hsvImg);
    cvReleaseImage(&blurHsvImg);
    cvReleaseImage(&blurOutImg);
    cvReleaseImage(&outImg);
}
