#ifndef SEGMENTATION_FOR_SIGN_BLOCK
#define SEGMENTATION_FOR_SIGN_BLOCK

#include "ProcessBlock.hpp"

/*!
 * \brief Typ wyliczeniowy określający typ znaków drogowych
 */
enum class TrafficSignTypeForBlocks
{
  MANDATORY = 0x1, //! Znaki nakazu
    WARNING = 0x2, //! Znaki ostrzegawcze
    INFO = 0x4, //! Znaki informacyjne
    RIGHT_OF_WAY = 0x8, //! Znak drogi z pierwszeństwem
    PROHIBITION = 0x10, //! Znaki zakazu
    ALL = 0x1F //! Wszystkie znaki
};

/*!
 * \brief Przeciążony operator sumy logicznej dla typów znaku
 * \param a - pierwszy operand
 * \param b - drugi operand
 */
TrafficSignTypeForBlocks operator|(TrafficSignTypeForBlocks a, TrafficSignTypeForBlocks b);

/*!
 * \brief Klasa określająca blok, który wykrywa znaki drogowe
 */
class SegmentationForSignBlock: public ProcessBlock
{
public:
  /*!
   * \brief Określa jaki typ znaków jest wykrywany przez blok
   */
  virtual TrafficSignTypeForBlocks trafficSignType() const { return  TrafficSignTypeForBlocks::ALL; }
};

#endif // SEGMENTATION_FOR_SIGN_BLOCK
