#ifndef DYNAMIC_THRESHOLD_BLOCK_FACTORY_HPP
#define DYNAMIC_THRESHOLD_BLOCK_FACTORY_HPP

#include "SegmentationForSignBlockAbstractFactory.hpp"

/*!
 * \brief Klasa definiująca fabrykę, dla bloków wykrywających znaki drogowe na podstawie algorytmu z dynamicznym progiem
 */
class DynamicThresholdBlockFactory
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
   * \brief Tworzy blok, który wykrywa znak drogi z pierwszeństwem
   */
  SegmentationForRightOfWaySignBlock* createRightOfWaySignBlock() const override;

  /*!
   * \brief Metoda pozwalająca otrzymać jedyny obiekt fabryki tego typu
   */
  static DynamicThresholdBlockFactory* getInstance() { return m_instance; }
private:

  /*!
   * \brief Ukryty domyślny kontruktor
   */
  DynamicThresholdBlockFactory() { }

  /*!
   * \brief Pole przechowujące instancję obiektu fabryki
   */
  static DynamicThresholdBlockFactory* m_instance;
};


#endif // DYNAMIC_THRESHOLD_BLOCK_FACTORY_HPP
