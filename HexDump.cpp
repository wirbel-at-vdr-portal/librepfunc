/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#include <repfunc.h>
#include <iostream>  // std::cout, std::cerr
#include <sstream>   // std::stringstream
#include <iomanip>   // std::uppercase, std::setfill, std::setw, std::hex
#include <codecvt>   // std::codecvt_utf8
#include <locale>    // std::wstring_convert
#include <cctype>    // std::isprint


std::string hex(std::intmax_t n, size_t width) {
  std::stringstream ss;
  ss << std::uppercase
     << std::setfill('0')
     << std::setw(width)
     << std::hex
     << n;
  return ss.str();
}

void HexDump(std::string intro, const unsigned char* buf, size_t len, bool to_stderr) {
  constexpr size_t hdr_len = 70;
  size_t addr_len = hex(len,2).size();
  size_t len1 = 1;
  size_t len2 = 1;

  std::stringstream ss;
  std::string s;

  if (buf == nullptr)
     len = 0;

  if (intro.empty())
     intro = "(null)";

  /*****************************************************************************
   * write caption and number of bytes.
   ****************************************************************************/
  if (intro.size() <= (hdr_len - 4)) {
     len1 = (hdr_len - 2)/2 - (size_t) (0.5 + intro.size()/2.0);
     len2 = (hdr_len - 2)   - (len1 + intro.size());
     }

  ss << "   "
     << std::string(len1, '=')
     << ' ' << intro << ' '
     << std::string(len2, '=')
     << std::endl
     << "   len = " << len << std::endl;


  /*****************************************************************************
   * now, print rows of 16 bytes and it's 7bit ASCII equivalent.
   ****************************************************************************/
  for(size_t i=0; i<len; i++) {
     size_t r = i % 16;
     unsigned char c = *(buf + i);

     if (r == 0) {
        if (i) ss << std::endl;
        ss << "   " << hex((i/16)*16, addr_len) << ": ";
        s = "                ";
        }

     ss << hex(c, 2) << ' ';
     if (std::isprint(c) == 0)
        c = 32;
     s[i % 16] = c;
     if (r == 15)
        ss << "; " << s;
     if (i == len-1) {
        size_t n = len % 16;
        if (n > 0)
           ss << std::string((16-n)*3, ' ') << "; " << s;
        }
     }

  ss << std::endl << "   " << std::string(hdr_len, '=') << std::endl;

  if (to_stderr)
     std::cerr << ss.str() << std::endl;
  else
     std::cout << ss.str() << std::endl;
}

void HexDumpW(std::wstring intro, const unsigned char* buf, size_t len, bool to_stderr) {
  if (intro.empty())
     intro = L"(null)";
  std::wstring_convert<std::codecvt_utf8<wchar_t>> Utf8;
  hexdump(Utf8.to_bytes(intro), buf, len, to_stderr);
}
