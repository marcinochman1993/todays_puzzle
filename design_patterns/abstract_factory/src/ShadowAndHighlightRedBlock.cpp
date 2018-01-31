#include "ShadowAndHighlightRedBlock.hpp"

using namespace std;
using namespace cv;

bool ShadowAndHighlightRedBlock::process()
{	  cout << "WCHODZI DO YR\n";
  for(weak_ptr<ProcessBlock> block: prevBlocks())
    {
      for(const VideoFrame& frame: block.lock()->outputFrames())
   	{
	  VideoFrame filterFrame = frame.shadowAndHighlightInvariantFilter(Color::RED);

	  vector<vector<Point>> contours = filterFrame.findContours(0.001);
	  for(auto& contour: contours)
	    {
	      VideoFrame frameFromContour = frame.fromContour(contour);
	      m_resultFrames.push_back(frameFromContour);
	    }	  
   	}
    }

  return true;
}
