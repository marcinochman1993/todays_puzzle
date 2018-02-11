#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

/*! \brief Klasa mierząca długość interwału czasu.
 *
 *  Do funkcjonowania używa high_resolution_clock z
 *  z biblioteki standardowej C++.
 */
class Timer
{
public:

  Timer()
  {
    reset();
  }

  /*! \brief Oblicza długość odcinka czasu w nanosekundach.
   *
   * Jeśli nie została użyta metoda start() to czas liczony jest
   * od tzw epoch.
   * Jeśli zostanie użyta metoda end() a start() nie to pojawi się
   * ujemny czas liczony od epoch
   * UWAGA! Nie na każdym systemie dokładność czasu jest tak duża!
   */
  double nsInterval() const;

  /*! \brief Oblicza długość odcinka czasu w mikrosekundach.
   *
   * Jeśli nie została użyta metoda start() to czas liczony jest
   * od tzw epoch.
   * Jeśli zostanie użyta metoda end() a start() nie to pojawi się
   * ujemny czas liczony od epoch
   */
  double usInterval() const;

  /*! \brief Oblicza długość odcinka czasu w milisekundach.
   *
   * Jeśli nie została użyta metoda start() to czas liczony jest
   * od tzw epoch.
   * Jeśli zostanie użyta metoda end() a start() nie to pojawi się
   * ujemny czas liczony od epoch
   */
  double msInterval() const;

  /*! \brief Oblicza długość odcinka czasu w sekundach.
   *
   * Jeśli nie została użyta metoda start() to czas liczony jest
   * od tzw epoch.
   * Jeśli zostanie użyta metoda end() a start() nie to pojawi się
   * ujemny czas liczony od epoch
   */
  double sInterval() const;

  /*!
   * \brief Zwraca precyzję zegara w sekundach.
   */
  static double precision();

  /*! \brief Zaczyna odmierzać czas.
   *
   * Metoda zapisuje do prywatnego pola aktualną chwilę, od której ma być
   * liczony czas
   */
  void start()
  {
    m_start = std::chrono::high_resolution_clock::now();
  }

  /*! \brief Kończy odmierzać czas.
   *
   * Metoda zapisuje do prywatnego pola aktualną chwilę, do której ma być
   * liczony czas
   */
  void stop()
  {
    m_end = std::chrono::high_resolution_clock::now();
  }

  void saveAndResume()
  {
    m_start = m_end;
    m_end = std::chrono::high_resolution_clock::now();
  }

  void reset()
  {
    m_start = std::chrono::high_resolution_clock::now();
    m_end = std::chrono::high_resolution_clock::now();
  }

private:
  /*! \brief Przechowuje informacje o chwili od której odliczać czas
   */
  std::chrono::high_resolution_clock::time_point m_start;

  /*! \brief Przechowuje informacje o chwili do której odliczać czas
   */
  std::chrono::high_resolution_clock::time_point m_end;
};

#endif /* TIMER_HPP */
