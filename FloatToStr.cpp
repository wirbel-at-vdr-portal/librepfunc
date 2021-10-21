/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <sstream>   // std::stringstream
#include <iomanip>   // std::setfill, std::setw, std::fixed, std::left, std::right


template<class T>
std::basic_string<T> FloatToStrT(double n, size_t width, size_t precision, T fillchar, bool left) {
  std::basic_stringstream<T> ss;

  if (precision) {
     ss.precision(precision);
     ss << std::fixed;
     }

  if (left)
     ss << std::left;
  else
     ss << std::right;

  ss << std::setfill(fillchar) << std::setw(width) << n;
  return ss.str();
}

std::string FloatToStr(double n) {
  return FloatToStrT<char>(n, 0, 0, ' ', true);
}


std::string FloatToStr(double n, size_t width, size_t precision, bool left) {
  return FloatToStrT<char>(n, width, precision, ' ', left);
}


std::wstring FloatToStrW(double n) {
  return FloatToStrT<wchar_t>(n, 0, 0, (wchar_t)' ', true);
}


std::wstring FloatToStrW(double n, size_t width, size_t precision, bool left) {
  return FloatToStrT<wchar_t>(n, width, precision, (wchar_t)' ', left);
}
