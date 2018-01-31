#ifndef SHADOW_AND_HIGHLIGHT_BLOCK_FACTORY_HPP
#define SHADOW_AND_HIGHLIGHT_BLOCK_FACTORY_HPP

#include "SegmentationForSignBlockAbstractFactory.hpp"

/*!
 * \brief Klasa definiująca fabrykę, dla bloków wykrywających znaki drogowe na podstawie algorytmu z dynamicznym progiem
 */
class ShadowAndHighlightBlockFactory
  : public SegmentationForSignBlockAbstractFactory
{
public:
  /*
   * \brief Tworzy blok, który wykrywa znaki informacyjne oraz nakazu
   */
  SegmentationForInfoAndMandatorySignsBlock* createInfoAndMandatorySignBlock() const override;

  /*
   * \brief Tworzy blok, który wykrywa znaki ostrzegawczne oraz zakazu
   */
  SegmentationForWarningAndProhibitionSignsBlock* createWarningAndProhibitionSignBlock() const override;

  /*
   * \brief Tworzy blok, który wykrywa znaki informacyjne oraz nakazu
   * 
   */
  SegmentationForRightOfWaySignBlock* createRightOfWaySignBlock() const override;

  /*!
   * \brief Metoda pozwalająca otrzymać jedyny obiekt fabryki tego typu
   */
  static ShadowAndHighlightBlockFactory* getInstance() { return m_instance; }
private:

  /*!
   * \brief Ukryty domyślny kontruktor
   */
  static ShadowAndHighlightBlockFactory* m_instance;

  /*!
   * \brief Pole przechowujące instancję obiektu fabryki
   */
  ShadowAndHighlightBlockFactory() { }
};


#endif // SHADOW_AND_HIGHLIGHT_BLOCK_FACTORY_HPP
