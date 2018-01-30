#include "ShadowAndHighlightBlockFactory.hpp"
#include "ShadowAndHighlightRedBlock.hpp"
#include "ShadowAndHighlightBlueBlock.hpp"

ShadowAndHighlightBlockFactory* ShadowAndHighlightBlockFactory::m_instance = new ShadowAndHighlightBlockFactory;

SegmentationForInfoAndMandatorySignsBlock* ShadowAndHighlightBlockFactory::createInfoAndMandatorySignBlock() const
{
  // TODO implement
  return new ShadowAndHighlightBlueBlock;
}

SegmentationForWarningAndProhibitionSignsBlock* ShadowAndHighlightBlockFactory::createWarningAndProhibitionSignBlock() const
{
  // TODO implement
  return new ShadowAndHighlightRedBlock;
}
  
SegmentationForRightOfWaySignBlock* ShadowAndHighlightBlockFactory::createRightOfWaySignBlock() const
{
  // TODO implement
  return nullptr;
}
