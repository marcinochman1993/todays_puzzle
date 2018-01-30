#ifndef SEGMENTATION_FOR_SIGN_BLOCK_ABSTRACT_FATORY_HPP
#define SEGMENTATION_FOR_SIGN_BLOCK_ABSTRACT_FATORY_HPP

#include "SegmentationForWarningAndProhibitionSignsBlock.hpp"
#include "SegmentationForInfoAndMandatorySignsBlock.hpp"
#include "SegmentationForRightOfWaySignBlock.hpp"

/*!
 * \brief Klasa definiująca fabrykę, dla bloków wykrywających znaki drogowe
 */
class SegmentationForSignBlockAbstractFactory
{
public:
  /*
   * \brief Tworzy blok, który wykrywa znaki informacyjne oraz nakazu
   */
  virtual SegmentationForInfoAndMandatorySignsBlock* createInfoAndMandatorySignBlock() const  = 0;

  /*
   * \brief Tworzy blok, który wykrywa znaki ostrzegawczne oraz zakazu
   */
  virtual SegmentationForWarningAndProhibitionSignsBlock* createWarningAndProhibitionSignBlock() const = 0;

  /*
   * \brief Tworzy blok, który wykrywa znaki informacyjne oraz nakazu
   */
  virtual  SegmentationForRightOfWaySignBlock* createRightOfWaySignBlock() const = 0;
};


#endif
