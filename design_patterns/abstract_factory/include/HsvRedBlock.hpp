#ifndef HSV_RED_BLOCK_HPP
#define HSV_RED_BLOCK_HPP

#include "SegmentationForWarningAndProhibitionSignsBlock.hpp"


/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki ostrzegawcze i zakazu
 *
 * Wykorzystuje algorytm analizujący odcień
 */
class HsvRedBlock
  : public SegmentationForWarningAndProhibitionSignsBlock
{
public:

  /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
  
};

#endif // HSV_RED_BLOCK_HPP
