#ifndef SHADOW_AND_HIGHLIGHT_RED_BLOCK_HPP
#define SHADOW_AND_HIGHLIGHT_RED_BLOCK_HPP

#include "SegmentationForWarningAndProhibitionSignsBlock.hpp"

/*!
 * \brief Blok przetwarzania obrazu, wyszukujący znaki ostrzegawcze i zakazu
 *
 * Wykorzystuje algorytm odporny na cienie i odbicia
 */
class ShadowAndHighlightRedBlock
  : public SegmentationForWarningAndProhibitionSignsBlock
{
public:

  /*!
   * \brief Przeciążona metoda wykonująca przetwarzanie
   */
  bool process() override;
};


#endif // SHADOW_AND_HIGHLIGHT_RED_BLOCK_HPP
