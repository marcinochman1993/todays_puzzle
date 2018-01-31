#ifndef VIDEOFRAME_HPP
#define VIDEOFRAME_HPP

#include <opencv2/opencv.hpp>
#include <functional>


/*!
 * \brief Typ wyliczeniowy określający format obrazu
 */
enum class  VideoFrameFormat
{
  BGR = 0, //! Format BGR
    RGB, //! Format RGB
    GRAY_SCALE, //! Format z odcieniami szarości
    HSV, //! Format HSV
    HLS // Format HLS
};

/*!
 * \brief Typ wyliczeniowy określający kolor
 */
enum class Color
{
  RED, //! \brief Kolor czerwony
    YELLOW, //! \brief Kolor żółty
    BLUE //! \brief Kolor niebieski
};


 /*!
  * \brief Klasa reprezentująca obraz, w szczególności również obraz z kamery
  */
class VideoFrame
{
public:
  /*!
   * \brief Domyślny konstruktor klasy VideoFrame
   * Inicjuje pusty obraz w formacie BGR
   */
  VideoFrame(): m_format(VideoFrameFormat::BGR) { }

  /*!
   * \brief Metoda pozwalająca pobrać szerokość obrazu
   */
  unsigned width() const { return mat().cols; }

  /*!
   * \brief Metoda pozwalająca pobrać wysokość obrazu
   */
  unsigned height() const { return mat().rows; }

  VideoFrame scaleToWidth(unsigned width) const;

  /*!
   * \brief Metoda pozwalająca na pobranie ilości kanałów obrazu
  */
  unsigned channels() const { return mat().channels(); }


  /*!
   * \brief Pozwala otrzymać macierz obrazu
   */
  const cv::Mat& mat() const { return m_mat; }

  /*!
   * \brief Pozwala ustawić macierz obrazu
   */
  void mat(cv::Mat& newMat)  { m_mat = newMat; }

  /*!
   * \brief Określa format przechowywanego obrazu
   *
   * \returns Format obrazu
   */
  VideoFrameFormat format() const { return m_format; }

  /*!
   * \brief Pozwala przekonwertować obraz na obraz w odcieniach szarości
   *
   * \returns Obraz w odcieniach szarości
   */
  VideoFrame toGrayScale() const;

  /*!
   * \brief Pozwala przekonwertować obraz do przestrzeni kolorów RGB
   *
   * \returns Obraz zapisany w przestrzeni RGB
   */
  VideoFrame toRgb() const;

  /*!
   * \brief Pozwala przekonwertować obraz do przestrzeni kolorów BGR
   *
   * \returns Obraz zapisany w przestrzeni BGR
   */
  VideoFrame toBgr() const;

  /*!
   * \brief Pozwala przekonwertować obraz do przestrzeni kolorów HSV
   *
   * \returns Obraz zapisany w przestrzeni HSV
   */
  VideoFrame toHsv() const;

  /*!
   * \brief Pozwala przekonwertować obraz do przestrzeni kolorów HLS
   *
   * \returns Obraz zapisany w przestrzeni HLS
   */
  VideoFrame toHls() const;


  /*!
   * \brief Pozwala przekonwertować obraz do przestrzeni kolorów HLS
   *
   * \returns Obraz zapisany w przestrzeni HLS
   */
  VideoFrame toIHls() const;

  /*!
   * \brief Sprawdza czy obraz ma tylko jeden kanał
   *
   * \retval true - obraz ma tylko jeden kanał
   * \retval false - obraz ma 0 lub więcej niż jeden kanał
   */
  bool isGrayScale() const { return m_mat.channels() == 1; }

  /*!
   * \brief Funkcja realizuje operator canny
   *
   * \param min - minimalny próg dla operatora Canny
   * \param max - maksymalny próg dla operatora Canny
   * \param maskSize - rozmiar maski dla filtru dolnoprzepustowegoa Gaussa
   */
  VideoFrame canny(double min = 60, double max = 130, int maskSize = 3) const;

  /*!
   * \brief Wyszukuje i zaznacza kontury na obrazie
   *
   * \returns Obraz z zaznaczonymi konturami
   */
  VideoFrame drawContours() const;

  /*!
   * \brief Wyszukuje kontury
   *
   * \param minAreaRatio - stosunek pola kontury do pola obrazu, określa jaki kontur ma być brany pod uwagę
   *  \returns kontury
   */
  std::vector<std::vector<cv::Point>> findContours(double minAreaRatio = 0.01) const;

  /*!
   * \brief Metoda potrafi stworzyć nowy obraz, na którym znajduje się podany kontur
   *
   * Metoda określa roi na podstawie wielkości konturu i
   * tworzy nowy obraz.
   *
   * \param contour - kontur, który ma zostać wycięty
   *
   * \returns obraz z konturem
   */
  VideoFrame fromContour(const std::vector<cv::Point> contour) const;

  /*!
   * \brief Wykonuje operacje wyrównuje histogram
   *
   * \returns Obraz będący wynikiem wyrównania histogramu
   */
  VideoFrame histogramEqualize() const;

  /*!
   * \brief Metoda realizuje operator Sobela
   *
   *  \param maskSize - rozmiar maski
   *
   * \returns wynik operatora Sobela na obrazie
   */
  VideoFrame sobel(unsigned maskSize = 3) const;

  /*!
   * \brief Metoda realizuje operator Laplace'a
   *
   * \param kernelSize - rozmiar jądra
   * \returns wynik operatora Laplaca na obrazie
   */
  VideoFrame laplace(unsigned kernelSize = 7) const;

  /*!
   * \brief Oblicza momenty obrazu
   *
   * \returns momenty obrazu
   */
  cv::Moments moments() const;

  /*!
   * \brief Oblicza momentu Hu obrazu
   *
   * \returns wektor 7 liczba, będących kolejno następnymi momentami Hu
   */
  std::vector<double> huMoments() const;

  /*!
   * \brief Znajduje wszystkie kontury i rysuje otoczkę wypukłą
   *
   * \returns Obraz z narysowanymi otoczkami wypukłymi, dla każdego obrazu
   */
  VideoFrame drawConvexHull() const;

  /*!
   * \brief Oblicza niezmiennik przekształceń afinicznych
   *
   * \returns niezmiennik przekształceń afinicznych
   */
  double affineMomentInvariant() const;

  /*!
   * \brief Oblicza współczynnik podobieństwa do trójkąta
   *
   * \returns współczynnik podobieństwa do trójkąta
   */
  double triangularity() const;

  /*!
   * \brief Oblicza współczynnik podobieństwa do prostokąta
   *
   * \returns współczynnik podobieństwa do prostokąta
   */
  double rectangularity() const;

  /*!
   * \brief Oblicza współczynnik podobieństwa do okręgu
   *
   * \returns współczynnik podobieństwa do okręgu
   */
  double ellipticity() const;

  /*!
   * \brief
   */
  std::vector<double> horizontalHsvSumReduce(unsigned intervalsCount, unsigned channelIndex = 0) const;
  std::vector<double> verticalHsvSumReduce(unsigned intervalsCount, unsigned channelIndex) const;

  /*!
   * \brief Realizuje filtr dolnoprzepustowy Gaussa
   *
   * \param kernelWidth - szerokość jądra, musi być nieparzysta
   * \param kernelHeight - wysokość jądra, musi być nieparzysta
   *
   * \returns wynik filtru Gaussa
   */
  VideoFrame gaussianBlur(unsigned kernelWidth = 3, unsigned kernelHeight = 3) const;

  /*!
   * \brief Wykrywa trójkąty na obrazie i je zaznacza
   *
   * \returns Obraz z zaznaczonymi trójkątami
   */
  VideoFrame detectTriangles() const;

  /*!
   * \brief Wykrywa trójkąty na obrazie
   *
   * \returns Wektor z obszarami obrazu, gdzie znajdują się trójkąty
   */
  std::vector<cv::Rect> detectTrianglesBoundingRect() const;

  /*!
   * \brief Wykrywa okręgi przy pomocy transformata Hougha
   *
   * \returns Obraz z zaznaczonymi okręgami
   */
  VideoFrame detectCirclesHough() const;

  /*!
   * \brief Wykrywa okręgi przy pomocy transformaty Hougha
   *
   * \returns Wektor z obszarami obrazu, gdzie znajdują się okręgi
   */
  std::vector<cv::Rect> detectCirclesHoughBoundingRect() const;

  /*!
   * \brief Wykrywa okręgi
   *
   * Wykrycie okręgów polega na wykryciu konturów i
   * sprawdzeniu pola powierzchni i długości konturu.
   * Na tej podstawie określane jest czy jest to okrąg.
   *
   * \returns Wektor z obszarami obrazu, gdzie znajdują się okręgi
   */
  std::vector<cv::Rect> detectCirclesBoundingRect() const;

  /*!
   * \brief Wykrywa czworokąty na obrazie i je zaznacza
   *
   * \returns Obraz z zaznaczonymi czworokątami
   */
  VideoFrame detectQuads() const;

  /*!
   * \brief Wykrywa czworokąty na obrazie
   *
   * \returns Wektor z obszarami obrazu, gdzie znajdują się czworokąty
   */
  std::vector<cv::Rect> detectQuadsBoundingRect() const;

  /*!
   * \brief Zaznacza obszary obrazu o okręslonym odcieniu
   *
   * \param color - poszukiwany kolor
   * \returns obraz binarny, białe piksele oznaczają kolor o poszukiwanym odcieniu
   */
  VideoFrame hsvColorFilter(Color color = Color::RED) const;

  /*!
   * \brief Zaznacza obszary obrazu o określonym kolorze wykorzystując algorytm z dynamicznym progiem
   *
   * \returns obraz binarny, białe piksele oznaczają znaleziony kolor
   */
  VideoFrame dynamicThresholdFilter(Color color = Color::RED) const;

  /*!
   * \brief Zlicza czarne piksele na obrazie
   *
   * Obraz najpierw jest konwertowany do skali szarości.
   *
   * \returns Procentowa zawartość czarnych pikseli na obrazie
   */
  double countBlackPixelsAreaInPercent() const;

  /*!
   * \brief Zlicza białe piksele na obrazie
   *
   * Obraz najpierw jest konwertowany do skali szarości.
   *
   * \returns Procentowa zawartość białych pikseli na obrazie
   */
  double countWhitePixelsAreaInPercent() const;

  /*!
   * \brief Zaznacza obszary obrazu o określonym kolorze wykorzystując algorytm odporny na cienie i odbicia
   *
   * \returns obraz binarny, białe piksele oznaczają znaleziony kolor
   */
  VideoFrame shadowAndHighlightInvariantFilter(Color color = Color::RED) const;

  /*!
   * \brief Zaznacza obszary obrazu o kolorze czerwonym wykorzystując algorytm operujący na różnicach RGB
   *
   * \returns obraz binarny, białe piksele oznaczają znaleziony kolor
   */
  VideoFrame enhanceRed() const;

  /*!
   * \brief Zaznacza obszary obrazu o kolorze czerwonym wykorzystując algorytm operujący na różnicach RGB
   *
   * \returns obraz binarny, białe piksele oznaczają znaleziony kolor
   */
  VideoFrame enhanceBlue() const;

  VideoFrame whitePixelsFilter() const;

  /*!
   * \brief Poprawia oświetlenie na scenie wykorzystując algorytm gray world
   *
   * \returns wynik algorytmu gray world
   */
  VideoFrame grayWorld() const;

  /*!
   * \brief Potrafi stworzyć nowy obraz z podanego obszaru
   *
   * \param rectangle -  obszar, z którego ma powstać nowy obraz
   */
  VideoFrame roi(const cv::Rect& rectangle) const;

  /*!
   * \brief Potrafi stworzyć nowe obrazy z podanych obszarów
   *
   * \param rectangles - wektor obszarów, z których mają powstać nowe obrazy
   */
  std::vector<VideoFrame> rois(const std::vector<cv::Rect>& rectangles) const;

  /*!
   * \brief Pozwala załadować obraz z pliku
   *
   * \param fileName - ścieżka do pliku z obrazem
   *
   * \returns Załadowany obraz z pliku
   */
  static VideoFrame loadFromFile(std::string fileName);

  /*!
   * \brief Pozwala skontruować obraz z macierzy o określonym formacie
   *
   * \param mat - macierz obrazu
   * \param format - format obrazu
   * \param clone - czy macierz obrazu powinna zostać skopiowana
   *
   * \returns obraz powstały z macierzy
   */
  static VideoFrame fromMat(cv::Mat& mat, VideoFrameFormat format = VideoFrameFormat::BGR, bool clone = true);

protected:

  /*!
   * \brief Umożliwia przekonwertowanie formatu obrazu
   *
   * \param destFormat - format obrazu wynikowego
   * \param convertArray - flagi dla funkcji z biblioteki OpenCV
   *
   * \returns obraz o określonym obrazie
   */
  VideoFrame convertFormat(VideoFrameFormat destFormat, int convertArray[]) const;

  /*!
   * \brief Pozwala wykonać pewną operację dla każdego piksela obrazu
   *
   * \param result - macierz wynikowa
   * \param fun - obiekt, który zostanie wywołany
   */
  template<typename T>
  void forEach(cv::Mat& result, T fun) const;

  /*!
   * \brief Pozwala pobrać funkcję określająca czy piksel spełnia warunki dla algorytmu odpornego na cienie i odbicia
   */
  virtual std::function<bool(uchar, uchar, uchar)> getSaHIFunctionByColor(Color color) const;

  /*!
   * \brief Pozwala pobrać funkcję określająca czy piksel spełnia warunki dla algorytmu segmentacji na podstawie odcienia
   */
  virtual std::function<bool(uchar, uchar, uchar)> getHsvFunctionByColor(Color color) const;

  /*!
   * \brief Pozwala pobrać wymagany odcień w zależności od koloru dla algorytmu z dynamicznym progiem
   *
   * \param color - poszukiwany kolor przez algorytm
   * \returns wartość odcienia
   */
  double getReqHueValueForDynamicThreshold(Color color) const;

  /*!
   * \brief Pozwala pobrać wymagane nasycienie w zależności od koloru dla algorytmu z dynamicznym progiem
   *
   * \param color - poszukiwany kolor przez algorytm
   * \returns wartość nasycenia
   */
  double getReqSaturationValueForDynamicThreshold(Color color) const;

private:
  /*!
   * \brief Metoda pomocnicza dla algorytmu nieczułego na cienie i odbicia
   *
   * Metoda analizuje binarny obraz, wyszukując regionów 16x16 i
   * zlicza ilość białych pikseli, by sprawdzić czy dodać środek
   * regionu jako punkt startowy dla flood fill. Następnie
   * dla każdego takiego punktu jest uruchamiany wspomniany algorytm
   * rozlewowy.
   *
   * \param hueChannel - binarny obraz poddawany analizie
   * \returns wynik algorytmu flood fill (również obraz binarny)
   */
  cv::Mat subRegionFilter(cv::Mat& hueChannel) const;

  /*!
   * \brief Pole przechowujące macierz obrazu
   */
  cv::Mat m_mat;

  /*!
   * \brief Pole przechowujące informacje o formacie obrazu
   */
  VideoFrameFormat m_format;
};

/*!
 * \brief Przeciążony operator wczytywania ramki obrazu z kamery
 *
 * \param vc - obiekt, który służy do nagrywania
 * \param frame - ramka obrazu
 */
cv::VideoCapture& operator>>(cv::VideoCapture& vc, VideoFrame& frame);

#endif /* VIDEOFRAME_HPP */
