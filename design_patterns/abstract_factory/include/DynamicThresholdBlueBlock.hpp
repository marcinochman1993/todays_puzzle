#ifndef DYNAMIC_THRESHOLD_BLUE_BLOCK_HPP
#define DYNAMIC_THRESHOLD_BLUE_BLOCK_HPP

#include "SegmentationForInfoAndMandatorySignsBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki informacyjne i nakazu
 *
 * Wykorzystuje algorytm z dynamicznym progiem
 */
class DynamicThresholdBlueBlock
  : public SegmentationForInfoAndMandatorySignsBlock
{
public:
  /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
};


#endif // DYNAMIC_THRESHOLD_BLUE_BLOCK_HPP
