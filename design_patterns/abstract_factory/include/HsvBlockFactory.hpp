#ifndef HSV_BLOCK_FACTORY_HPP
#define HSV_BLOCK_FACTORY_HPP

#include "SegmentationForSignBlockAbstractFactory.hpp"

/*!
 * \brief Klasa definiująca fabrykę dla bloków wykrywających znaki drogowe metodą analizy odcienia
 */
class HsvBlockFactory
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
   */
  SegmentationForRightOfWaySignBlock* createRightOfWaySignBlock() const override;

  /*!
   * \brief Metoda pozwalająca otrzymać jedyny obiekt fabryki tego typu
   */
  static HsvBlockFactory* getInstance() { return m_instance; }
private:
  /*!
   * \brief Ukryty domyślny kontruktor
   */  
  HsvBlockFactory() { }

  /*!
   * \brief Pole przechowujące instancję obiektu fabryki
   */
  static HsvBlockFactory* m_instance;
};

#endif // HSV_BLOCK_FACTORY_HPP
