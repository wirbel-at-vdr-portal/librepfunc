/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#pragma once
#include <string>  // std::string, size_t
#include <cstdint> // std::intmax_t


/*******************************************************************************
 * number conversion to std::string
 *   n         - number
 *   width     - minimum number of chars to print
 *   left      - left or right text padding
 *   precision - number of digits after period
 ******************************************************************************/
std::string IntToStr(std::intmax_t n);
std::string IntToStr(std::intmax_t n, size_t width, bool left);
std::string IntToHex(std::intmax_t n, size_t width);
std::string FloatToStr(double n);
std::string FloatToStr(double n, size_t width, size_t precision, bool left);



/*******************************************************************************
 * number conversion to std::wstring
 *   n         - number
 *   width     - minimum number of chars to print
 *   left      - left or right text padding
 *   precision - number of digits after period
 ******************************************************************************/
std::wstring IntToStrW(std::intmax_t n);
std::wstring IntToStrW(std::intmax_t n, size_t width, bool left);
std::wstring IntToHexW(std::intmax_t n, size_t width);
std::wstring FloatToStrW(double n);
std::wstring FloatToStrW(double n, size_t width, size_t precision, bool left);



/*******************************************************************************
 * sleep a thread using STL
 *   s         - seconds
 *   ms        - milliseconds
 *   us        - microseconds
 ******************************************************************************/
void Sleep(size_t s);
void mSleep(size_t ms);
void uSleep(size_t us);



/*******************************************************************************
 * HexDump() - print bytes human readable.
 *   intro     - intro (caption) for byte buffer.
 *   buf       - pointer to buffer 
 *   len       - length of buffer
 *   to_stderr - print to stderr, instead of stdout
 ******************************************************************************/
void HexDump(std::string intro, const unsigned char* buf, size_t len, bool to_stderr = false);
void HexDumpW(std::wstring intro, const unsigned char* buf, size_t len, bool to_stderr = false);

