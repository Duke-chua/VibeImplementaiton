#include <iostream>
#include<opencv2/highgui.hpp>
#include<opencv/cv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/video.hpp>
#include<libvibe++/src/libvibe++/ViBe.h>
#include<libvibe++/src/libvibe++/distances/Manhattan.h>
#include<libvibe++/src/libvibe++/system/types.h>
using namespace cv;
using namespace ViBe;
int main()
{
Mat image;
VideoCapture cap;

namedWindow("win",1);
cap.open(0);
typedef ViBeSequential<1, Manhattan<1> > ViBe;
Mat mat_array[20];
 srand(time(NULL));
 int32_t height = cap.get(CAP_PROP_FRAME_HEIGHT);
 int32_t width  = cap.get(CAP_PROP_FRAME_WIDTH);
  ViBe* vibe = NULL;
  Mat bwFrame(height, width, CV_8UC1);
  Mat segmentationMap(height, width, CV_8UC1);
  bool firstFrame = true;
while(1)
{
//int z=0;
cap>>image;
//std::cout<<image.rows<<" "<<image.cols<<std::endl;
Mat OutputArray;
cvtColor(image,bwFrame,CV_RGB2GRAY);
imshow("win2",bwFrame);
//bwFrame=OutputArray;
if (firstFrame) {
  /* Instantiation of ViBe. */
  vibe = new ViBe(height, width, bwFrame.data);
  firstFrame = false;
}
/* Segmentation and update. */
vibe->segmentation(bwFrame.data, segmentationMap.data);
vibe->update(bwFrame.data, segmentationMap.data);

/* Post-processing: 3x3 median filter. */
medianBlur(segmentationMap, segmentationMap, 3);



imshow("win",bwFrame);


/*for(int i=0;i<image.rows;i++){
    for(int j=0;j<image.cols;j++){
 //   if(OutputArray.at<uchar>(i,j)==255){
        if(OutputArray.at<uchar>(i,j)>=200)
        {
                OutputArray.at<uchar>(i,j)=0;

        }

        else
        {
            OutputArray.at<uchar>(i,j)=255;
        }

    }
/*for(int k=0;k<20;k++)
{
    for(i=0;i<image.rows;i++)
    {
        for(int j=0;j<image.cols;j++)
        {
            //if(mat_array[k].at<uchar>(i,j)>OutputArray.at<uchar>(i,j)
        }
    }
}*/

//mat_array[i]=OutputArray;
//}
imshow("win",OutputArray);


waitKey(33);

}

}
