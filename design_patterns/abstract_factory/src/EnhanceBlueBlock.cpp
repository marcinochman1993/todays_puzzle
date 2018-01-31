#include "EnhanceBlueBlock.hpp"

using namespace std;
using namespace cv;

bool EnhanceBlueBlock::process()
{
   for(weak_ptr<ProcessBlock> block: prevBlocks())
    {
      for(const VideoFrame& frame: block.lock()->outputFrames())
   	{
	  VideoFrame enhancedBlueFrame = frame.enhanceBlue();

	  vector<vector<Point>> contours = enhancedBlueFrame.findContours(0.001);
	  for(auto& contour: contours)
	    {
	      VideoFrame frameFromContour = frame.fromContour(contour);
	      m_resultFrames.push_back(frameFromContour);
	    }
   	}
    }
 
   return true;
}
