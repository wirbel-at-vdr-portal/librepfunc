/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <codecvt>    // std::codecvt_utf8
#include <locale>     // std::wstring_convert
#include <sys/stat.h> // stat()


bool FileExists(std::string aFile) {
  struct stat Stat;
  return stat(aFile.c_str(), &Stat) == 0;
}

bool FileExistsW(std::wstring aFile) {
  if (aFile.empty())
     return false;
  std::wstring_convert<std::codecvt_utf8<wchar_t>> Utf8;
  return FileExists(Utf8.to_bytes(aFile));
}
