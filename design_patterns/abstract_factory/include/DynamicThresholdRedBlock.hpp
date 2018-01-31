#ifndef DYNAMIC_THRESHOLD_RED_BLOCK_HPP
#define DYNAMIC_THRESHOLD_RED_BLOCK_HPP

#include "SegmentationForWarningAndProhibitionSignsBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki ostrzegawcze i znaki zakazu
 *
 * Wykorzystuje algorytm z dynamicznym progiem
 */
class DynamicThresholdRedBlock
  : public SegmentationForWarningAndProhibitionSignsBlock
{
public:
  /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
};


#endif // DYNAMIC_THRESHOLD_RED_BLOCK_HPP
