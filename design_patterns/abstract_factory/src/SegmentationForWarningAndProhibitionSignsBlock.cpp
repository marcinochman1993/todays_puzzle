#include "SegmentationForWarningAndProhibitionSignsBlock.hpp"


TrafficSignTypeForBlocks SegmentationForWarningAndProhibitionSignsBlock::trafficSignType() const
{
  return TrafficSignTypeForBlocks::PROHIBITION | TrafficSignTypeForBlocks::WARNING;
}

