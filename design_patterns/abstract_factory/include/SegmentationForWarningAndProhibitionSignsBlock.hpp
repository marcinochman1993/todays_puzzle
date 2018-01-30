#ifndef SEGMENTATION_FOR_WARNING_AND_PROHIBITION_SIGNS_BLOCK_HPP
#define SEGMENTATION_FOR_WARNING_AND_PROHIBITION_SIGNS_BLOCK_HPP

#include "SegmentationForSignBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki ostrzegawcze i zakazu
 */
class SegmentationForWarningAndProhibitionSignsBlock: public SegmentationForSignBlock
{
public:
  /*!
   * \brief Określa typ wyszukiwanych znaków drogowych
   */
  TrafficSignTypeForBlocks trafficSignType() const override;
    
};

#endif
