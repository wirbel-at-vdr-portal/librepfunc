/*******************************************************************************
 * librepfunc - a collection of common functions, classes and tools.
 * See the README file for copyright information and how to reach the author.
 ******************************************************************************/
#pragma once
#include <string>  // std::string, size_t
#include <vector>  // std::vector
#include <cstdint> // std::intmax_t


/*******************************************************************************
 * Convert strings to uppercase or lowercase.
 ******************************************************************************/
std::string LowerCase(std::string s);
std::string UpperCase(std::string s);
std::wstring LowerCase(std::wstring s);
std::wstring UpperCase(std::wstring s);



/*******************************************************************************
 * Trim strings, left, right, or, both ends.
 * For details on trimmed chars, pls refer to std::isspace() from <cctype>
 ******************************************************************************/
std::string LeftTrim(std::string s);
std::string RightTrim(std::string s);
std::string Trim(std::string s);
std::wstring LeftTrimW(std::wstring s);
std::wstring RightTrimW(std::wstring s);
std::wstring TrimW(std::wstring s);



/*******************************************************************************
 * Fill up a string with spaces to be at least n chars; the opposite of Trim.
 ******************************************************************************/
std::string FrontFill(std::string s, size_t n);
std::string BackFill(std::string s, size_t n);
std::wstring FrontFillW(std::wstring s, size_t n);
std::wstring BackFillW(std::wstring s, size_t n);



/*******************************************************************************
 * splits a string on a delimiter char, and returns a vector of strings
 * from it.
 *   s         - string to split
 *   delim     - the delimiting char
 ******************************************************************************/
std::vector<std::string> SplitStr(const std::string s, const char delim);
std::vector<std::wstring> SplitStrW(const std::wstring s, const wchar_t delim);



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
 *   intro     - caption string in utf8 (Note: 7bit ascii is valid utf8)
 *   buf       - pointer to buffer
 *   len       - length of buffer
 *   to_stderr - print to stderr, instead of stdout
 *   vec       - reference to vector of unsigned char, instead of buf and len
 ******************************************************************************/
void HexDump(std::string intro, const unsigned char* buf, size_t len, bool to_stderr = false);
void HexDumpW(std::wstring intro, const unsigned char* buf, size_t len, bool to_stderr = false);

void HexDump(std::string intro, std::vector<unsigned char>& vec, bool to_stderr = false);
void HexDumpW(std::wstring intro, std::vector<unsigned char>& vec, bool to_stderr = false);



/*******************************************************************************
 * FileExists() - returns true, if a file exists.
 *   aFile     - filen name in utf8 (Note: 7bit ascii is valid utf8)
 ******************************************************************************/
bool FileExists(std::string aFile);
bool FileExistsW(std::wstring aFile);



/*******************************************************************************
 * Convert between UTF8 <-> UCS2 / UTF-32
 ******************************************************************************/
std::string  WStrToStr(std::wstring ws);
std::wstring StrToWStr(std::string s);
