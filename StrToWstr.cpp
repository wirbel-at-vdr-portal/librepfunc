/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <codecvt>    // std::codecvt_utf8
#include <locale>     // std::wstring_convert


/* NOTE: this code needs to be modified in future,
 *       as C++17 deprecated std::codecvt_utf8
 *
 * https://www.geeksforgeeks.org/cpp/wcstombs-function-in-c-stl/
 */

std::string WStrToStr(std::wstring ws) {
  if (ws.empty())
     return "";
  std::wstring_convert<std::codecvt_utf8<wchar_t>> Utf8;
  return Utf8.to_bytes(ws);
}

std::wstring StrToWStr(std::string s) {
  if (s.empty())
     return L"";
  std::wstring_convert<std::codecvt_utf8<wchar_t>> Utf8;
  return Utf8.from_bytes(s);
}
