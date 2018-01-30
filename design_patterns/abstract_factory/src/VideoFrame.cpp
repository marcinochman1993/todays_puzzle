#include "VideoFrame.hpp"
#include <utility>
#include <set>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include <cstdlib>

using namespace cv;
using namespace std;



VideoFrame VideoFrame::scaleToWidth(unsigned int width) const
{
  Mat result;
  resize(mat(), result, Size(width, height() * width / this->width()));


  return fromMat(result, format());
}

VideoFrame VideoFrame::sobel(unsigned maskSize) const
{
  std::set<unsigned> maskSizeTab = {1, 3, 5 ,7};

  if(maskSizeTab.find(maskSize) == maskSizeTab.end())
    throw "maskSize should be one of the following value: 1, 3, 5, 7";

  Mat gradXMat, gradYMat, absGradX, absGradY, resultMat,
    inputMat = toGrayScale().mat();

  Sobel(inputMat, gradXMat, CV_16S, 1, 0, 3,
	1, 0, BORDER_DEFAULT );
  convertScaleAbs( gradXMat, absGradX );

  Sobel(inputMat, gradYMat, CV_16S, 0, 1, 3,
	1, 0, BORDER_DEFAULT );
  convertScaleAbs( gradYMat, absGradY );

  addWeighted(absGradX, 0.5, absGradY, 0.5, 0, resultMat);

  return fromMat(resultMat, VideoFrameFormat::GRAY_SCALE);
}

VideoFrame VideoFrame::laplace(unsigned kernelSize) const
{
  Mat resultMat, laplacianMat;

  Laplacian(toGrayScale().gaussianBlur().mat(),
	    laplacianMat, CV_16S, kernelSize, 1, 0, BORDER_DEFAULT);
  convertScaleAbs(laplacianMat, resultMat );

  return fromMat( resultMat, VideoFrameFormat::GRAY_SCALE);
}

cv::Moments VideoFrame::moments() const
{
  Mat normalizedMat;
  normalize(toGrayScale().mat(), normalizedMat, 0.0, 1.0, NORM_MINMAX, CV_32FC1);

  return cv::moments(normalizedMat);
}

std::vector<double> VideoFrame::huMoments() const
{
  Moments moments = this->moments();
  vector<double> huMomentsVec;

  HuMoments(moments, huMomentsVec);

  return huMomentsVec;
}


VideoFrame VideoFrame::drawConvexHull() const
{
  Mat result = Mat::zeros(height(), width(), CV_8UC1);
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  cv::findContours( mat(), contours, hierarchy, CV_RETR_TREE,
		CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  vector<vector<Point> >hull( contours.size() );
  for(unsigned i = 0; i < contours.size(); i++ )
    {
      convexHull( Mat(contours[i]), hull[i]);
      cv::drawContours( result, hull, i, 255, CV_FILLED, 8);
    }


  return fromMat(result, VideoFrameFormat::GRAY_SCALE);
}


double VideoFrame::affineMomentInvariant() const
{
  Moments moments = this->moments();
  double denominator = moments.m00 * moments.m00;
  denominator *= denominator;

  return (moments.mu20 * moments.mu02 - moments.mu11 * moments.mu11) / denominator;
}

double VideoFrame::triangularity() const
{
  double affineMomentInv = affineMomentInvariant();

  if(affineMomentInv <= 0.009259259) // 1/108
    return 108 * affineMomentInv;

  return 1/(108 * affineMomentInv);
}

double VideoFrame::rectangularity() const
{
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  cv::findContours(toGrayScale().mat(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

  if(contours.size() != 1)
    return 0.0;

  double area = contourArea(contours[0]);
  Rect boundingRect = cv::boundingRect(contours[0]);

  return area / (boundingRect.width * boundingRect.height);
}

double VideoFrame::ellipticity() const
{
  double affineMomentInv = affineMomentInvariant();
  const double coeff = 157.913670417; // 16pi^2

  if(affineMomentInv <= 1 / coeff)
    return coeff * affineMomentInv;

  return 1 / (coeff * affineMomentInv);
}

vector<double> VideoFrame::horizontalHsvSumReduce(unsigned intervalsCount, unsigned channelIndex) const
{
  Mat reducedMat;
  vector<double> resultVec;
  vector<Mat> channels;

  split(mat(), channels);

  if(channelIndex < channels.size())
    {
      reduce(channels[channelIndex], reducedMat, 1, CV_REDUCE_SUM, CV_64FC1);

      Mat resultMat;
      resize(reducedMat, resultMat, Size(intervalsCount, 1));

      resultMat.copyTo(resultVec);
    }

  return resultVec;

}

vector<double> VideoFrame::verticalHsvSumReduce(unsigned intervalsCount, unsigned channelIndex) const
{
  Mat reducedMat;
  vector<double> resultVec;
  vector<Mat> channels;

  split(mat(), channels);

  if(channelIndex < channels.size())
    {
      reduce(channels[channelIndex], reducedMat, 0, CV_REDUCE_SUM, CV_64FC1);

      Mat resultMat;
      resize(reducedMat, resultMat, Size(1, intervalsCount));

      resultMat.copyTo(resultVec);
    }

  return resultVec;
}

VideoFrame VideoFrame::roi(const cv::Rect& rectangle) const
{
  Mat roiImage(mat(), rectangle);
  return fromMat(roiImage, format(), true);
}

std::vector<VideoFrame> VideoFrame::rois(const std::vector<cv::Rect>& rectangles) const
{
  vector<VideoFrame> resultRois;

  for(const Rect& rect: rectangles)
    {
      Mat roiImage(mat(), rect);
      resultRois.push_back(fromMat(roiImage, format(), true));
    }

  return resultRois;
}

VideoFrame VideoFrame::loadFromFile(std::string fileName)
{
  Mat mat;
  mat = imread(fileName, CV_LOAD_IMAGE_COLOR);

  return fromMat(mat, VideoFrameFormat::BGR);
}


VideoFrame VideoFrame::fromMat(Mat& mat, VideoFrameFormat format, bool clone)
{
  VideoFrame frame;

  if(clone)
    frame.m_mat = mat.clone();
  else
    frame.m_mat = mat;

  frame.m_format = format;

  return frame;
}

VideoFrame VideoFrame::toGrayScale() const
{
  int convertFlagTable[] = {CV_BGR2GRAY, CV_RGB2GRAY, 0, 0, 0 }; // 0 means no action no implemented yet

  //todo implement HLS -> GRAY conversion

  if(format() == VideoFrameFormat::HSV)
    {
      vector<Mat> hsvChannels;
      split(mat(), hsvChannels);
      return fromMat(hsvChannels[2], VideoFrameFormat::GRAY_SCALE);
    }

  return convertFormat(VideoFrameFormat::GRAY_SCALE, convertFlagTable);
}


VideoFrame VideoFrame::toRgb() const
{
  int convertFlagTable[] = { CV_BGR2RGB, 0, CV_GRAY2RGB, CV_HSV2RGB, CV_HLS2RGB };

  return convertFormat(VideoFrameFormat::RGB, convertFlagTable);
}

VideoFrame VideoFrame::toBgr() const
{
  int convertFlagTable[] = {0, CV_RGB2BGR, CV_GRAY2BGR, CV_HSV2BGR, CV_HLS2BGR };

  return convertFormat(VideoFrameFormat::BGR, convertFlagTable);
}

VideoFrame  VideoFrame::toHsv() const
{
  int convertFlagTable[] = {CV_BGR2HSV, CV_RGB2HSV, 0, 0, 0 }; // 0 means no action or no implemented yet

  //todo implement gray -> hsv and hsl -> hsv

  return convertFormat(VideoFrameFormat::HSV, convertFlagTable);
}

VideoFrame VideoFrame::toHls() const
{
  int convertFlagTable[] = {CV_BGR2HLS, CV_RGB2HLS, 0, 0, 0 }; // 0 means no action or no implemented yet

  //todo implement gray -> hsv and hsl -> hsv

  return convertFormat(VideoFrameFormat::HLS, convertFlagTable);
}


VideoFrame VideoFrame::toIHls() const
{
  VideoFrame bgrFrame = toBgr(), hsvFrame = toHsv();
  Mat bgrMat, hsvMat;

  bgrMat = bgrFrame.mat();
  hsvMat = hsvFrame.mat();

  Mat ihls = Mat::zeros(height(), width(), CV_8UC3);

  bgrFrame.forEach(ihls,
		   [](unsigned x, unsigned y,
		      unsigned char* dataPtr, const unsigned char* orgPtr)
		   {

		     unsigned char red = orgPtr[2], green = orgPtr[1],
		       blue = orgPtr[0];
		     unsigned char &hue = dataPtr[0], &luminance = dataPtr[1],
		       &saturation = dataPtr[2];

		     double theta = acos( (red - green / 2.0 - blue / 2.0)
					  / sqrt(pow(red + green + blue,2.0) - 3*(red*green + red*blue + green*blue))) / M_PI * 180.0;

		     if(blue <= green)
		       hue = theta / 2.0; // because overflow may occur
		     else
		       hue = 180.0 - theta / 2.0;

		     saturation = max(red, max(blue, green)) - min(red, min(blue, green));

		     luminance = 0.2126 * red + 0.7152 * green + 0.0722 * blue;

		   });

  return fromMat(ihls);
}

VideoFrame VideoFrame::canny(double min, double max, int maskSize) const
{
  Mat edgesMat = toGrayScale().histogramEqualize().mat();
  blur(edgesMat,edgesMat,Size(5,5));
  Canny(m_mat,edgesMat,min,max,maskSize);
  return fromMat(edgesMat, VideoFrameFormat::GRAY_SCALE);
}

VideoFrame VideoFrame::drawContours() const
{
  Mat edgesMat = canny().mat();
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  cv::findContours(edgesMat, contours, hierarchy,
		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  Mat drawing = Mat::zeros( edgesMat.size(), CV_8UC3 );
  for(unsigned i = 0; i< contours.size(); i++ )
    {
      Scalar color = Scalar(255,255,255); // white color
      cv::drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );
    }

  return fromMat(drawing);
}


vector<vector<Point>> VideoFrame::findContours(double minAreaRatio) const
{
  vector<vector<Point> > contours, result;
  vector<Vec4i> hierarchy;
  cv::findContours(m_mat.clone(), contours, hierarchy,
		   CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  double minArea = height() * width() * minAreaRatio;

  for(auto& contour: contours)
    {
      if(contourArea(contour) >= minArea)
	result.push_back(contour);
    }

  return result;
}

VideoFrame VideoFrame::fromContour(const std::vector<cv::Point> contour) const
{
  Rect boundRect = boundingRect(contour);
  Mat mask = Mat::zeros(height(), width(), CV_8UC1);
  vector<vector<Point>>  contours = { contour };
  cv::drawContours(mask, contours, 0, 255, CV_FILLED, 8);

  Mat result;
  mat().copyTo(result, mask);

  result = result(boundRect);

  return fromMat(result, format());
}


VideoFrame VideoFrame::histogramEqualize() const
{
  Mat resultMat;
  equalizeHist(mat(), resultMat);
  return fromMat(resultMat);
}


VideoFrame VideoFrame::gaussianBlur(unsigned kernelWidth, unsigned kernelHeight) const
{
  Mat resultMat;

  GaussianBlur( mat(), resultMat, Size( kernelWidth, kernelHeight ), 0, 0 );

  return fromMat(resultMat, format());
}


VideoFrame VideoFrame::hsvColorFilter(Color color) const
{
  Mat hsvMat = toHsv().mat();
  Mat resultMat = Mat::zeros(mat().rows, mat().cols, CV_8UC1);

  for(int y = 0;y < hsvMat.rows;y++)
    {
      unsigned char* p = hsvMat.ptr<unsigned char>(y);
      unsigned char* p2 = resultMat.ptr<unsigned char>(y);
      for(int x = 0, x_index = 0; x < hsvMat.cols*hsvMat.channels();x = x + 3, x_index++)
	{

	  unsigned char hValueImg = p[x], sValueImg = p[x + 1],
	    vValueImg = p[x + 2];

	  bool filterCondition =
	    getHsvFunctionByColor(color)(hValueImg, sValueImg, vValueImg);

	  if(filterCondition)
	      p2[x_index] = 255;
	}
    }

  return fromMat(resultMat, VideoFrameFormat::GRAY_SCALE);
}

VideoFrame VideoFrame::detectTriangles() const
{
  Mat resultMat = mat().clone();

  for(const auto& boundRect: detectTrianglesBoundingRect())
    rectangle(resultMat, boundRect.tl(), boundRect.br(), Scalar(33,24,204));

  return fromMat(resultMat);
}

std::vector<cv::Rect> VideoFrame::detectTrianglesBoundingRect() const
{
   Mat cannyMat = canny().mat(), resultMat = mat().clone(),
    trianglesMat(cannyMat.size(), CV_8U, Scalar(0,0,0));
  vector<vector<Point> > contours, contoursTriangles;
  vector<Point> contoursOut;
  vector<Vec4i> hierarchy;
  cv::findContours(cannyMat, contours, hierarchy,
  		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  for(unsigned i = 0; i< contours.size(); i++ )
    {
      approxPolyDP(contours[i], contoursOut, 20, true);
      if(contoursOut.size() == 3) // is triangle
  	contoursTriangles.push_back(contoursOut);
    }

  vector<Rect> boundingRectVec;

  for(unsigned i = 0;i < contoursTriangles.size();i++)
    {
      Point points[3];
      for(unsigned j =0; j<3;j++)
	points[j] = contoursTriangles[i][j];

      Rect boundRect = boundingRect(contoursTriangles[i]);
      boundingRectVec.push_back(boundRect);

   }

  return boundingRectVec;
}

VideoFrame VideoFrame::detectQuads() const
{
  Mat resultMat = mat().clone();

  for(const auto& boundRect: detectQuadsBoundingRect())
    rectangle(resultMat, boundRect.tl(), boundRect.br(), Scalar(33,24,204));

  return fromMat(resultMat);
}

std::vector<cv::Rect> VideoFrame::detectQuadsBoundingRect() const
{
  Mat cannyMat = canny().mat(), resultMat = mat().clone(),
    trianglesMat(cannyMat.size(), CV_8U, Scalar(0,0,0));
  vector<vector<Point> > contours, contoursQuads;
  vector<Point> contoursOut;
  vector<Vec4i> hierarchy;
  cv::findContours(cannyMat, contours, hierarchy,
  		CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  for(unsigned i = 0; i< contours.size(); i++ )
    {
      approxPolyDP(contours[i], contoursOut, 45, true);
      if(contoursOut.size() == 4) // is quad
  	contoursQuads.push_back(contoursOut);
    }

  vector<Rect> boundingRectVec;

  for(unsigned i = 0;i < contoursQuads.size();i++)
    {
      Point points[3];
      for(unsigned j =0; j<3;j++)
	points[j] = contoursQuads[i][j];

      Rect boundRect = boundingRect(contoursQuads[i]);
      boundingRectVec.push_back(boundRect);
   }

  return boundingRectVec;
}


VideoFrame VideoFrame::detectCirclesHough() const
{
  Mat resultMat = toBgr().mat().clone();

  for(const auto& boundRect: detectCirclesHoughBoundingRect())
    rectangle(resultMat, boundRect.tl(), boundRect.br(), Scalar(33,24,204), 10);

  return fromMat(resultMat);
}

vector<Rect> VideoFrame::detectCirclesHoughBoundingRect() const
{
  vector<Rect> boundingRectVec;
  vector<Vec3f> circles;
  Mat cannyMat = toGrayScale().mat();

  HoughCircles(cannyMat, circles, CV_HOUGH_GRADIENT, 1,
	       cannyMat.rows/8, 200, 50, 0, 0 );

  for(const auto& circle: circles)
    {
      float x = circle[0], y = circle[1],
	radius = circle[2];
      Point topLeft(x - radius, y - radius),
	bottomRight(x + radius, y + radius);
      Rect boundingRect(topLeft, bottomRight);
      if(topLeft.x >= 0 && topLeft.y >=0 &&
	 bottomRight.x > topLeft.x && bottomRight.y > topLeft.y &&
	 bottomRight.x <= width() && bottomRight.y <= height())
	boundingRectVec.push_back(boundingRect);
    }

  return boundingRectVec;
}

std::vector<cv::Rect> VideoFrame::detectCirclesBoundingRect() const
{
  Mat cannyMat = canny().mat(), resultMat = mat().clone(),
    trianglesMat(cannyMat.size(), CV_8U, Scalar(0,0,0));
  vector<vector<Point> > contours, contoursQuads;
  vector<Point> contoursOut;
  vector<Vec4i> hierarchy;
  vector<Rect> boundingRectVec;
  const double MIN_AREA = 100.0;
  const double ERROR = 0.2,
    MAX_ERROR_RATIO = 1.0 + ERROR,
    MIN_ERROR_RATIO = 1.0 - ERROR;

  cv::findContours(cannyMat, contours, hierarchy,
  		CV_RETR_TREE, CV_CHAIN_APPROX_TC89_L1, Point(0, 0));

  for(unsigned i = 0; i< contours.size(); i++ )
    {
      double area = contourArea(contours[i]),
	perimeter = arcLength(contours[i], true);
      Rect boundRect = boundingRect(contours[i]);
      double a = boundRect.width / 2.0,
	b = boundRect.height / 2.0,
	reqArea = M_PI * a * b,
	areaRatio = area / reqArea;
      if(areaRatio >= MIN_ERROR_RATIO && areaRatio <= MAX_ERROR_RATIO)
	boundingRectVec.push_back(boundRect);
    }

  return boundingRectVec;
}

VideoFrame VideoFrame::dynamicThresholdFilter(Color color) const
{

  Mat hlsFrame = toIHls().mat();

  Mat hlsChannels[3];
  Mat filteredMat = Mat::zeros(height(), width(), CV_8UC1);
  split(hlsFrame, hlsChannels);
  double dynamicThreshold = exp(-mean(hlsChannels[1])[0] / 255.0);
  for(int y = 0;y < hlsFrame.rows;y++)
    {
      unsigned char* p = hlsFrame.ptr<unsigned char>(y),
	*p2 = filteredMat.ptr<unsigned char>(y);
      for(int x = 0, x_index = 0; x < hlsFrame.cols*hlsFrame.channels();x += channels(), x_index++)
	{
	  double hValue = 2*p[x] / 180.0 * M_PI, sValue=p[x+2]/255.0,
	    hReqValue = getReqHueValueForDynamicThreshold(color),
	    sReqValue = getReqSaturationValueForDynamicThreshold(color);
	  // performance issue possible
	  double d = sqrt(pow(sValue*cos(hValue) - sReqValue*cos(hReqValue), 2.0)
			  + pow(sValue*sin(hValue) - sReqValue*sin(hReqValue), 2.0));

	  if(d <= dynamicThreshold)
	    {
	      p2[x_index] = 255;
	    }
	}
    }

  return fromMat(filteredMat, VideoFrameFormat::GRAY_SCALE);
}


double VideoFrame::countBlackPixelsAreaInPercent() const
{
  VideoFrame grayFrame = toGrayScale();
  Mat resultMat;
  inRange(grayFrame.mat(), 0, 50, resultMat);

  return static_cast<double>(countNonZero(resultMat)) / (width() * height());
}

double VideoFrame::countWhitePixelsAreaInPercent() const
{
  VideoFrame grayFrame = toGrayScale();
  Mat resultMat;
  inRange(grayFrame.mat(), 200, 255, resultMat);

  return static_cast<double>(countNonZero(resultMat)) / (width() * height());
}


VideoFrame VideoFrame::shadowAndHighlightInvariantFilter(Color color) const
{
  Mat hsvMat = toHsv().mat();

  function<bool(uchar, uchar, uchar)> conditionalFun =
    getSaHIFunctionByColor(color);

  forEach(hsvMat, [&conditionalFun](unsigned x, unsigned y,
		     unsigned char* dataPtr, const unsigned char* orgPtr)
  	  {
  	    unsigned char& hue = dataPtr[0], &saturation = dataPtr[1],
  	      &value = dataPtr[2];

	    if(conditionalFun(hue,saturation,value))
		hue = 255;
	    else
	      hue = 0;
  	  });

  Mat hsvChannels[3];
  Mat result;
  split(hsvMat, hsvChannels);
  Mat hueChannel = hsvChannels[0];

  subRegionFilter(hueChannel).convertTo(result, CV_8UC1);

  return fromMat(result, VideoFrameFormat::GRAY_SCALE);
}


VideoFrame VideoFrame::enhanceRed() const
{
  Mat redChannel = Mat::zeros(height(), width(), CV_8UC1);
  VideoFrameFormat imgFormat = format();
  forEach(redChannel, [imgFormat](unsigned x, unsigned y, unsigned char* resultPtr,
				  const unsigned char* orgPtr){
	    float  redChannel = imgFormat == VideoFrameFormat::BGR? orgPtr[2]:orgPtr[0],
	      greenChannel = orgPtr[1],
	      blueChannel = imgFormat == VideoFrameFormat::BGR? orgPtr[0]:orgPtr[2],
	      sum = redChannel + greenChannel + blueChannel,
	      fr = min(redChannel - greenChannel,
				 redChannel - blueChannel)/sum;

	    *resultPtr = fr < 0.25f? 0 : 255;
    });

  return fromMat(redChannel, VideoFrameFormat::GRAY_SCALE);
}


VideoFrame VideoFrame::enhanceBlue() const
{
  Mat redChannel = Mat::zeros(height(), width(), CV_8UC1);
  VideoFrameFormat imgFormat = format();
  forEach(redChannel, [imgFormat](unsigned x, unsigned y, unsigned char* resultPtr,
				  const unsigned char* orgPtr){
	    float  redChannel = imgFormat == VideoFrameFormat::BGR? orgPtr[2]:orgPtr[0],
	      greenChannel = orgPtr[1],
	      blueChannel = imgFormat == VideoFrameFormat::BGR? orgPtr[0]:orgPtr[2],
	      sum = redChannel + greenChannel + blueChannel,
	      fr = min(blueChannel - greenChannel,
		       blueChannel - redChannel)/sum;

	    *resultPtr = fr < .1f? 0 : 255;
	  });

  return VideoFrame::fromMat(redChannel, VideoFrameFormat::GRAY_SCALE);
}

VideoFrame VideoFrame::whitePixelsFilter() const
{
  VideoFrame grayFrame = toGrayScale();
  Mat resultMat;

  threshold(grayFrame.mat(), resultMat, 200,
	     255, THRESH_BINARY);

  return fromMat(resultMat, VideoFrameFormat::GRAY_SCALE);
}

VideoFrame VideoFrame::grayWorld() const
{
  Mat channels[3]; // bgr
  Mat matToSplit;
  mat().copyTo(matToSplit);
  split(matToSplit, channels);

  Scalar averageValues = mean(mat());

  double avgRedChannel = averageValues[2],
    avgGreenChannel = averageValues[1],
    avgBlueChannel = averageValues[0],
    maxAvgPerChannel = max(avgRedChannel, max(avgGreenChannel, avgBlueChannel)),
    scaleFactorRedChannel = maxAvgPerChannel / avgRedChannel,
    scaleFactorGreenChannel = maxAvgPerChannel / avgGreenChannel,
    scaleFactorBlueChannel = maxAvgPerChannel / avgBlueChannel;

  Mat resultMat = Mat::zeros(height(), width(), CV_8UC3);

  VideoFrameFormat imgFormat = format();

  forEach(resultMat,[imgFormat, scaleFactorBlueChannel, scaleFactorGreenChannel, scaleFactorRedChannel]
	  (unsigned x, unsigned y, unsigned char* resultPtr,
	   const unsigned char* orgPtr)
	  {
	    unsigned char  redChannel = imgFormat == VideoFrameFormat::BGR? orgPtr[2]:orgPtr[0],
	      greenChannel = orgPtr[1],
	      blueChannel = imgFormat == VideoFrameFormat::BGR? orgPtr[0]:orgPtr[2];

	    unsigned char &redChannelResult = resultPtr[2],
	      &greenChannelResult = resultPtr[1],
	      &blueChannelResult = resultPtr[0];

	    redChannelResult = saturate_cast<uchar>(redChannel / scaleFactorRedChannel);
	    greenChannelResult = saturate_cast<uchar>(greenChannel / scaleFactorGreenChannel);
	    blueChannelResult = saturate_cast<uchar>(blueChannel / scaleFactorBlueChannel);

	  });

  return fromMat(resultMat);
}

template<typename T>
void VideoFrame::forEach(Mat& result, T fun) const
{
  Mat mat;
  m_mat.copyTo(mat);
  for(int y = 0; y < result.rows; y++)
    {
      unsigned char* ptrResult = result.ptr<unsigned char>(y);
      const unsigned char* ptrOrg = mat.ptr<unsigned char>(y);
      for(int xResult = 0, xOrg = 0, x_index = 0; x_index < result.cols;
	  xResult += result.channels(), xOrg += channels(), x_index++)
	fun(x_index, y, ptrResult + xResult, ptrOrg + xOrg);
    }
}

function<bool(uchar, uchar, uchar)> VideoFrame::getSaHIFunctionByColor(Color color) const
{
  switch(color)
    {
      case Color::RED:
	return [](uchar hue, uchar saturation, uchar value) -> bool
	{
	  return (hue >= 169 || hue <= 9) &&
	    !(saturation < 40 || value < 30 || value > 230);
	};

    case Color::BLUE:
      return [](uchar hue, uchar saturation, uchar value) -> bool
	{
	  return (hue >= 96 && hue <= 112) &&
	    !(saturation < 40 || value < 30 || value > 230);
	};

    default:
      return [](uchar hue, uchar saturation, uchar value) -> bool
	{
	  return false;
	};
    }
}


std::function<bool(uchar, uchar, uchar)> VideoFrame::getHsvFunctionByColor(Color color) const
{
   switch(color)
    {
      case Color::RED:
	return [](uchar hue, uchar saturation, uchar value) -> bool
	{
	  return hue <=5 || hue >= 175;
	};

    case Color::BLUE:
      return [](uchar hue, uchar saturation, uchar value) -> bool
	{
	  return hue >= 105 && hue <= 130;
	};

    default:
      return [](uchar hue, uchar saturation, uchar value) -> bool
	{
	  return false;
	};
    }
}


double VideoFrame::getReqHueValueForDynamicThreshold(Color color) const
{
  switch(color)
    {
    case Color::RED:
      return 6.1599;
    case Color::BLUE:
      return 3.942390781;
    case Color::YELLOW:
      return 0.911215686;
    default:
      return 0.0;
    }
}

double VideoFrame::getReqSaturationValueForDynamicThreshold(Color color) const
{
    switch(color)
    {
    case Color::RED:
      return 0.811764706; // 207/255.0;
    case Color::BLUE:
      return   0.921568627; //
    case Color::YELLOW:
      return 0.901960784;
    default :
      return 0.0;
    }
}


Mat VideoFrame::subRegionFilter(cv::Mat& hueChannel) const
{
  Mat resultMat = Mat::zeros(height(), width(), CV_16UC1);
  vector<Point> seedPoints, allSeedPoints;
  const float subRegionSize = 16.0;
  unsigned subRegionsVerCount = ceil(height()/ subRegionSize),
    subRegionsHorCount = ceil(width() / subRegionSize);
  for(unsigned y = 0; y < subRegionsVerCount; y++)
    {
      for(unsigned x = 0; x < subRegionsHorCount; x++)
  	{
	  unsigned subRegionX = subRegionSize * x,
	    subRegionY = subRegionSize * y,
	    subRegionWidth = subRegionX + subRegionSize < width()? subRegionSize:width() - subRegionX,
							  subRegionHeight = subRegionY + subRegionSize
							  < height()? subRegionSize:height() - subRegionY,
							    subRegionCenterX = subRegionX + subRegionWidth/2,
							    subRegionCenterY = subRegionY + subRegionHeight/2;
	  Mat subRegion = hueChannel(Rect(subRegionX, subRegionY,
					  subRegionWidth, subRegionHeight));

	  unsigned whitePixels = countNonZero(subRegion);
	  if(whitePixels >= 60 && hueChannel.ptr<const unsigned char>(subRegionCenterY)[subRegionCenterX] == 255)
	    {
	      Point top(subRegionCenterX, subRegionCenterY - subRegionSize),
		topLeft(subRegionCenterX - subRegionSize, subRegionCenterY - subRegionSize),
		topRight(subRegionCenterX + subRegionSize, subRegionCenterY - subRegionSize),
		botttom(subRegionCenterX, subRegionCenterY + subRegionSize),
		bottomLeft(subRegionCenterX - subRegionSize, subRegionCenterY + subRegionSize),
		bottomRight(subRegionCenterX + subRegionSize, subRegionCenterY + subRegionSize),
		left(subRegionCenterX - subRegionSize, subRegionCenterY),
		right(subRegionCenterX + subRegionSize, subRegionCenterY);

	      bool addToVector = true;
	      for(const Point& point: allSeedPoints)
		if(point == top || point == botttom || point == left || point == right || point == topLeft
		   || point == topRight || point == bottomLeft || point == bottomRight)
		  addToVector = false;

	      allSeedPoints.push_back(Point(subRegionCenterX, subRegionCenterY));

	      if(addToVector)
		seedPoints.push_back(Point(subRegionCenterX, subRegionCenterY));
	    }
  	}
    }
  unsigned colorValue = 125;
  for(auto& point: seedPoints)
    {
      Mat copyHueChannel, mask, whiteMat = Mat::ones(height(), width(), CV_16UC1);
      hueChannel.copyTo(copyHueChannel);
      floodFill(copyHueChannel, point, colorValue);

      inRange(copyHueChannel, colorValue - 1, colorValue + 1, copyHueChannel);

      copyHueChannel.convertTo(copyHueChannel, CV_16UC1);
      resultMat += copyHueChannel;
    }

  return resultMat;
}

VideoFrame VideoFrame::convertFormat(VideoFrameFormat destFormat, int convertArray[]) const
{
  Mat resultMat;
  if(destFormat == format())
    resultMat = mat();
  else
    cvtColor(mat(),resultMat,convertArray[static_cast<int>(format())]);

  return fromMat(resultMat,destFormat);
}

VideoCapture& operator>>(VideoCapture& vc, VideoFrame& frame)
{
  Mat mat;
  vc >> mat;
  frame.mat(mat);
  return vc;
}
