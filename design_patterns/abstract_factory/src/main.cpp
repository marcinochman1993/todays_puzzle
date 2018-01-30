#include <iostream>
#include "DynamicThresholdBlockFactory.hpp"
#include "HsvBlockFactory.hpp"
#include "EnhanceBlockFactory.hpp"
#include <memory>

SegmentationForSignBlockAbstractFactory* getFactory(int factoryId)
{
  switch(factoryId)
    {
    case 0: return DynamicThresholdBlockFactory::getInstance();
    case 1: return HsvBlockFactory::getInstance();
    default:
      return EnhanceBlockFactory::getInstance();
    }
}

int main(int argc, char* argv[])
{
  std::cout << "Type num 1 - 3: ";

  int factoryId = 0;
  std::cin >> factoryId;

  SegmentationForSignBlockAbstractFactory* factory = getFactory(factoryId);

  std::unique_ptr<SegmentationForInfoAndMandatorySignsBlock> infoAndMandatoryAlgorithm{factory->createInfoAndMandatorySignBlock()};
  std::unique_ptr<SegmentationForWarningAndProhibitionSignsBlock> warningProhibitionAlgorithm{factory->createWarningAndProhibitionSignBlock()};
  std::unique_ptr<SegmentationForRightOfWaySignBlock> rightOfWay{factory->createRightOfWaySignBlock()};

  // further processing
}
