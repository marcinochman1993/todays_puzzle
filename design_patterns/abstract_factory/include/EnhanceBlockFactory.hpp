#ifndef SEGMENTATION_FOR_SIGN_BLOCK_ABSTRACT_FACTORY_HPP
#define SEGMENTATION_FOR_SIGN_BLOCK_ABSTRACT_FACTORY_HPP

#include "SegmentationForSignBlockAbstractFactory.hpp"

/*!
 * \brief Klasa definiująca fabrykę, dla bloków wykrywających znaki drogowe na podstawie algorytmu z dynamicznym progiem
 */
class EnhanceBlockFactory
  : public SegmentationForSignBlockAbstractFactory
{
public:

  /*
   * \brief Tworzy blok, który wykrywa znaki informacyjne oraz nakazu
   */
  SegmentationForInfoAndMandatorySignsBlock* createInfoAndMandatorySignBlock() const  override;

  /*
   * \brief Tworzy blok, który wykrywa znaki ostrzegawczne oraz zakazu
   */
  SegmentationForWarningAndProhibitionSignsBlock* createWarningAndProhibitionSignBlock() const override;

  /*
   * \brief Tworzy blok, który wykrywa znak drogi z pierwszeństwem
   */  
  SegmentationForRightOfWaySignBlock* createRightOfWaySignBlock() const override;

  /*!
   * \brief Metoda pozwalająca otrzymać jedyny obiekt fabryki tego typu
   */
  static EnhanceBlockFactory* getInstance() { return m_instance; }
private:

  /*!
   * \brief Ukryty domyślny kontruktor
   */
  EnhanceBlockFactory() { }

  /*!
   * \brief Pole przechowujące instancję obiektu fabryki
   */
  static EnhanceBlockFactory* m_instance;
};

#endif
