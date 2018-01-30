#ifndef HSV_BLUE_BLOCK_HPP
#define HSV_BLUE_BLOCK_HPP

#include "SegmentationForInfoAndMandatorySignsBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki informacyjne i nakazu
 *
 * Wykorzystuje algorytm analizujący odcień
 */
class HsvBlueBlock
  : public SegmentationForInfoAndMandatorySignsBlock
{
public:

  /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
  
};

#endif // HSV_BLUE_BLOCK_HPP
