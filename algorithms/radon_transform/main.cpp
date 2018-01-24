//g++ main.cpp  -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -o radon

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <cmath>

const double PI = 3.14159265359;

cv::Mat radonTransform(cv::Mat& img)
{
  cv::Point center(img.cols/2, img.rows/2);
  cv::Rect boundBox = cv::RotatedRect(center, img.size(), 45).boundingRect();

  const int sinogramHeight = std::max(boundBox.height, boundBox.width);

  cv::Mat greyImg;
  cv::cvtColor(img, greyImg, cv::COLOR_BGR2GRAY);

  cv::Mat sinogram(180, sinogramHeight, CV_32F);

  for(int angle = 0; angle < 180; ++angle)
  {
    cv::Mat rotationMatrix = getRotationMatrix2D(center, angle, 1), rotated;
    rotationMatrix.at<double>(0,2) += boundBox.width/2.0 - center.x;
    rotationMatrix.at<double>(1,2) += boundBox.height/2.0 - center.y;

    cv::warpAffine(greyImg, rotated, rotationMatrix, boundBox.size());
    cv::Rect rectSlice(0, angle, sinogramHeight, 1);
    cv::Mat slice;
    cv::reduce(rotated, slice, 0, CV_REDUCE_SUM, CV_32F);

    slice.copyTo(sinogram(rectSlice));
  }

  cv::normalize(sinogram, sinogram, 1, 0, cv::NORM_MINMAX);

  cv::Mat rotation90Matrix = getRotationMatrix2D(cv::Point(sinogramHeight/2, 180/2), 90, 1);
  rotation90Matrix.at<double>(0,2) += boundBox.width/2.0 - sinogramHeight/2;
  rotation90Matrix.at<double>(1,2) += boundBox.height/2.0 - 180/2;

  cv::warpAffine(sinogram, sinogram, rotation90Matrix, cv::Size(sinogramHeight, sinogramHeight));

  return sinogram;
}

int main(int argc, char* argv[])
{
  cv::Mat originalImage = cv::imread(argv[1]);
  cv::Mat sinogram = radonTransform(originalImage), colorMap;
  double min, max;

  cv::minMaxLoc(sinogram, &min, &max);

  sinogram.convertTo(sinogram,CV_8UC1, 255.0/(max-min));

  applyColorMap(sinogram, colorMap, cv::COLORMAP_HOT);

  cv::imshow("Original image", originalImage);
  cv::waitKey(0);

  cv::imshow("Sinogram", colorMap);
  cv::waitKey(0);

}
