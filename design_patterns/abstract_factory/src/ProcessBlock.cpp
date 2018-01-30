#include "ProcessBlock.hpp"

using namespace std;

bool ProcessBlock::process()
{
  
  return true;
}

bool ProcessBlock::nextBlock(shared_ptr<ProcessBlock> block)
{
  if(canBeNextBlock(block.get()))
    nextBlocks().push_back(block);

  return true;
}

bool ProcessBlock::prevBlock(weak_ptr<ProcessBlock> block)
{
  if(canBePrevBlock(block.lock().get()))
    prevBlocks().push_back(block);

  return true;
}

unsigned ProcessBlock::roisInFrame(unsigned frameIndex) const
{
  if(frameIndex >= m_roisInFrameVec.size())
    throw "Frame Index out of bounds";

  return m_roisInFrameVec[frameIndex];
}

void ProcessBlock::clear()
{
  m_resultFrames.clear();
  m_resultRois.clear();
  m_roisInFrameVec.clear();
}

const std::vector<VideoFrame> ProcessBlock::inputFrames() const
{
  vector<VideoFrame> inputFramesVec;
  
  for(const weak_ptr<ProcessBlock>& block: prevBlocks())
    {
      const vector<VideoFrame>& outputFrames =
	block.lock()->outputFrames();
      inputFramesVec.insert(inputFramesVec.end(), outputFrames.begin(),
			    outputFrames.end());
    }
  
  return inputFramesVec;

}
