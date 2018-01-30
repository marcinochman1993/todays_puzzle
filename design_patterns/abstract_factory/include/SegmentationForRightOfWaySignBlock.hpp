#ifndef SEGMENTATION_FOR_RIGHT_OF_WAY_SIGN_BLOCK_HPP
#define SEGMENTATION_FOR_RIGHT_OF_WAY_SIGN_BLOCK_HPP

#include "SegmentationForSignBlock.hpp"

/*!
 *  \brief Blok przetwarzania obrazu, wyszukujący znak drogi z pierwszeństwem
 */
class SegmentationForRightOfWaySignBlock
  : public SegmentationForSignBlock
{
public:
  /*!
   * \brief Określa typ wyszukiwanych znaków drogowych
   */
  TrafficSignTypeForBlocks trafficSignType() const override {return TrafficSignTypeForBlocks::RIGHT_OF_WAY; }
};

#endif // SEGMENTATION_FOR_RIGHT_OF_WAY_SIGN_BLOCK_HPP
