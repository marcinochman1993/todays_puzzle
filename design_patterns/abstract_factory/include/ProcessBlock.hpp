#ifndef VIDEO_FRAME_PROCESS_BLOCK_HPP
#define VIDEO_FRAME_PROCESS_BLOCK_HPP

#include <list>
#include "VideoFrame.hpp"
#include <memory>

/*!
 * \brief Bazowa klasa dla bloków przetwarzania obrazu
 */
class ProcessBlock
{
public:

  /*!
   * \brief Wirtualna metoda definiująca operacje bloku
   *
   * \retval true - operacje zakończone powodzeniem
   * \retval false - w.p.p.
   */
  virtual bool process();

  /*!
   * \brief Pozwala otrzymać obrazy, będące wynikiem operacji bloku
   */
  virtual const std::vector<VideoFrame>& outputFrames() const { return m_resultFrames; }

  /*!
   * \brief Pozwala otrzymać informacje o podobrazach (rois), będące wynikiem operacji bloku
   */
  virtual std::vector<cv::Rect> resultRoi() const { return {}; }

  /*!
   * \brief Pozwala ustawić następnika bloku
   *
   * \param block - blok, który ma zostać utawiony jako następnik
   *
   * \returns czy operacja się powiodła
   */
  virtual bool nextBlock(std::shared_ptr<ProcessBlock> block);

  /*!
   * \brief Pozwala ustawić poprzednik bloku
   *
   * \param block - blok, który ma zostać utawiony jako poprzednik
   *
   * \returns czy operacja się powiodła
   */
  virtual bool prevBlock(std::weak_ptr<ProcessBlock> block);

  /*!
   * \brief Pozwala pobrać wszystkie bloki będące następnikami
   */
  const std::vector<std::shared_ptr<ProcessBlock>>& nextBlocks() const { return m_nextBlocks; }

  /*!
   * \brief Pozwala pobrać wszystkie bloki będące poprzednikami
   */
  const std::vector<std::weak_ptr<ProcessBlock>>& prevBlocks() const { return m_prevBlocks; }

  /*!
   * \brief Pozwala pobrać wszystkie bloki będące następnikami
   */
  std::vector<std::shared_ptr<ProcessBlock>>& nextBlocks() { return m_nextBlocks; }

  /*!
   * \brief Pozwala pobrać wszystkie bloki będące poprzednikami
   */
  std::vector<std::weak_ptr<ProcessBlock>>& prevBlocks() { return m_prevBlocks; }

  /*!
   * \brief Określa ile obrazów wynikowych generuje na podstawie jednego obrazu wejściowego
   */
  virtual unsigned outputFramesCountPerFrame() const { return 1; }

  /*!
   * \brief Określa ile obszarów wynikowych generuje na podstawie jednego obrazu wejściowego
   */
  virtual unsigned outputRoisCountPerFrame() const { return 0; }

  /*!
   * \brief Określa czy podany blok może być następnikiem
   *
   * \param block - badany blok
   *
   * \returns czy podany blok może być następnikiem
   */
  virtual bool canBePrevBlock(const ProcessBlock* block ) { return block != nullptr; }

  /*!
   * \brief Określa czy podany blok może być poprzednikiem
   *
   * \param block - badany blok
   *
   * \returns czy podany blok może być poprzednikiem
   */
  virtual bool canBeNextBlock(const ProcessBlock* block ) { return block != nullptr; }

  /*!
   * \brief Pozwala sprawdzić, ile roi wygenerowano na podstawie jednej ramki
   *
   * \param frameIndex - indeks ramki
   */
  virtual unsigned roisInFrame(unsigned frameIndex = 0) const;

  /*!
   * \brief Pozwala otrzymać wejściowe obrazy
   */
  virtual const std::vector<VideoFrame> inputFrames() const;
protected:

  /*!
   * \brief Przechowuje obrazy będące wynikiem działania bloku
   */
  std::vector<VideoFrame> m_resultFrames;

  /*!
   * \brief Przechowuje ROI będące wynikiem działania bloku
   */
  std::vector<cv::Rect> m_resultRois;

  /*!
   * \brief Przechowuje ilość ROI dla każdej z ramek
   */
  std::vector<unsigned> m_roisInFrameVec;

  /*!
   * \brief Usuwa wszystkie wyniki bloku
   */
  void clear();
private:

  /*!
   * \brief Przechowuje poprzednie bloki
   */
  std::vector<std::weak_ptr<ProcessBlock>> m_prevBlocks;

  /*!
   * \brief Przechowuje następniki
   */
  std::vector<std::shared_ptr<ProcessBlock>> m_nextBlocks;
};


#endif
