#include "HsvBlockFactory.hpp"

HsvBlockFactory* HsvBlockFactory::m_instance = new HsvBlockFactory;

SegmentationForInfoAndMandatorySignsBlock* HsvBlockFactory::createInfoAndMandatorySignBlock() const 
{
  // todo implement
  return nullptr;
}


SegmentationForWarningAndProhibitionSignsBlock* HsvBlockFactory::createWarningAndProhibitionSignBlock() const 
{
  // todo implement
  return nullptr;
}

SegmentationForRightOfWaySignBlock* HsvBlockFactory::createRightOfWaySignBlock() const 
{
  // todo implement
  return nullptr;
}
