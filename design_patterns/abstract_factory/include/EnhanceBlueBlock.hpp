#ifndef ENHANCE_BLUE_BLOCK_HPP
#define ENHANCE_BLUE_BLOCK_HPP

#include "SegmentationForInfoAndMandatorySignsBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki informacyjne i nakazu
 *
 * Wykorzystuje algorytm korzystający z różnic RGB
 */
class EnhanceBlueBlock
  : public SegmentationForInfoAndMandatorySignsBlock
{
public:

  /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
};


#endif //ENHANCE_BLUE_BLOCK_HPP
