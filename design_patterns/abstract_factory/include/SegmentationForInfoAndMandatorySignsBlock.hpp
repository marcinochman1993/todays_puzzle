#ifndef SEGMENTATION_FOR_INFO_AND_MANDATORY_SIGNS_BLOCK_HPP
#define SEGMENTATION_FOR_INFO_AND_MANDATORY_SIGNS_BLOCK_HPP

#include "SegmentationForSignBlock.hpp"


/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki informacyjne i nakazu
 */
class SegmentationForInfoAndMandatorySignsBlock
  : public SegmentationForSignBlock
{
public:
  /*!
   * \brief Określa typ wyszukiwanych znaków drogowych
   */
  TrafficSignTypeForBlocks trafficSignType() const override
  { return TrafficSignTypeForBlocks::INFO | TrafficSignTypeForBlocks::MANDATORY; }
};

#endif
