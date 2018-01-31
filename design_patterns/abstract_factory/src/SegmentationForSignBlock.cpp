#include "SegmentationForSignBlock.hpp"



 TrafficSignTypeForBlocks operator|(TrafficSignTypeForBlocks a, TrafficSignTypeForBlocks b)
{
  return static_cast<TrafficSignTypeForBlocks>(static_cast<int>(a) | static_cast<int>(b));
}
