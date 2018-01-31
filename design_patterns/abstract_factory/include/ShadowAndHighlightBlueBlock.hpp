#ifndef SHADOW_AND_HIGHLIGHT_BLUE_BLOCK_HPP
#define SHADOW_AND_HIGHLIGHT_BLUE_BLOCK_HPP

#include "SegmentationForInfoAndMandatorySignsBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki informacyjne i nakazu
 *
 * Wykorzystuje algorytm odporny na cienie i odbicia
 */
class ShadowAndHighlightBlueBlock
  : public SegmentationForInfoAndMandatorySignsBlock
{
public:

  /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
};


#endif // SHADOW_AND_HIGHLIGHT_BLUE_BLOCK_HPP
