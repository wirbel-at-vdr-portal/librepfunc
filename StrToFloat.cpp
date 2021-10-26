/*******************************************************************************
 * librepfunc: A tiny lib of common functions and tasks in my c++ projects.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <string>    // std::stod
#include <iostream>  // std::cerr
#include <exception> // std::exception
#include <repfunc.h>

template<class T>
double StrToFloatT(const std::basic_string<T>& s, size_t* pos, const char* f) {
  if (s.empty()) {
     std::cerr << f
               << ": ERROR: cannot convert empty string to double."
               << std::endl;
     return std::stod("NAN");
     }
  else {
     try {
        return std::stod(s, pos);
        }
     catch(const std::exception& e) {
        std::cerr << f
               << ": ERROR: cannot convert '"
               << (const T*)s.c_str()
               << "' to double: "
               << (const T*)e.what() << std::endl;
        return std::stod("NAN");
        }
     }
}

double StrToFloat(const std::string& s, size_t* pos) {
  return StrToFloatT(s, pos, __PRETTY_FUNCTION__);
}

double WStrToFloat(const std::wstring& s, size_t* pos) {
  return StrToFloatT(s, pos, __PRETTY_FUNCTION__);
}
