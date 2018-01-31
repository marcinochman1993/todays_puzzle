#include "EnhanceBlockFactory.hpp"
#include "EnhanceRedBlock.hpp"
#include "EnhanceBlueBlock.hpp"

EnhanceBlockFactory* EnhanceBlockFactory::m_instance = new EnhanceBlockFactory;

SegmentationForInfoAndMandatorySignsBlock* EnhanceBlockFactory::createInfoAndMandatorySignBlock() const
{
  return new EnhanceBlueBlock;
}


SegmentationForWarningAndProhibitionSignsBlock* EnhanceBlockFactory::createWarningAndProhibitionSignBlock() const
{
  return new EnhanceRedBlock;
}

SegmentationForRightOfWaySignBlock*  EnhanceBlockFactory::createRightOfWaySignBlock() const
{
  // todo zaimplementować
  return nullptr;
}
