#include "HsvBlueBlock.hpp"

using namespace std;
using namespace cv;

bool HsvBlueBlock::process()
{

  for(weak_ptr<ProcessBlock>& block: prevBlocks())
    {
      for(const VideoFrame& frame: block.lock()->outputFrames())
   	{
	  VideoFrame hsvRedFrame = frame.hsvColorFilter(Color::BLUE);
	  
	  vector<vector<Point>> contours = hsvRedFrame.findContours(0.001);

	  for(auto& contour: contours)
	    {
	      VideoFrame frameFromContour = frame.fromContour(contour);
	      m_resultFrames.push_back(frameFromContour);
	    }	  
   	}
    }

  return true;
  
}
