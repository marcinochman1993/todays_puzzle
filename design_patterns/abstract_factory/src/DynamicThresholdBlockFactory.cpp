#include "DynamicThresholdBlockFactory.hpp"
#include "DynamicThresholdRedBlock.hpp"
#include "DynamicThresholdBlueBlock.hpp"

DynamicThresholdBlockFactory* DynamicThresholdBlockFactory::m_instance = new DynamicThresholdBlockFactory;


SegmentationForInfoAndMandatorySignsBlock* DynamicThresholdBlockFactory::createInfoAndMandatorySignBlock() const
{
  return new DynamicThresholdBlueBlock;
}

SegmentationForWarningAndProhibitionSignsBlock* DynamicThresholdBlockFactory::createWarningAndProhibitionSignBlock() const
{

  return new DynamicThresholdRedBlock;
}
  
SegmentationForRightOfWaySignBlock* DynamicThresholdBlockFactory::createRightOfWaySignBlock() const
{

  return nullptr;
}
