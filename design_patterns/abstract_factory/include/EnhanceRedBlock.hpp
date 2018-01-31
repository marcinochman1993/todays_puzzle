#ifndef ENHANCE_RED_BLOCK_HPP
#define ENHANCE_RED_BLOCK_HPP

#include "SegmentationForWarningAndProhibitionSignsBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki ostrzegawcze i zakazu 
 *
 * Wykorzystuje algorytm korzystający z różnic RGB
 */
class EnhanceRedBlock
  : public SegmentationForWarningAndProhibitionSignsBlock
{
public:
    /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
};


#endif // ENHANCE_RED_BLOCK_HPP
