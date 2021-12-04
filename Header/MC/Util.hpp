// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#include <Global.h>
#include "Json.hpp"
#define EXTRA_INCLUDE_PART_UTIL
#include "Extra/UtilAPI.hpp"
#undef EXTRA_INCLUDE_PART_UTIL
namespace Util {
#include "Extra/UtilAPI.hpp"

MCAPI int const COLOR_CODE;
MCAPI std::string const EMPTY_GUID;
MCAPI std::string const EMPTY_STRING;
MCAPI std::string const NEW_LINE;
MCAPI void _breakIntoWordsAndFindProfanity(std::string&, std::string&, std::vector<struct std::pair<int, int>> const&, class std::unordered_set<char, struct std::hash<char>, struct std::equal_to<char>, class std::allocator<char>> const&, class std::set<struct std::pair<int, int>, struct std::less<struct std::pair<int, int>>, class std::allocator<struct std::pair<int, int>>>&, class std::unordered_map<std::string, int, struct std::hash<std::string>, struct std::equal_to<std::string>, class std::allocator<struct std::pair<std::string const, int>>> const&, class std::unordered_set<std::string, struct std::hash<std::string>, struct std::equal_to<std::string>, class std::allocator<std::string>> const&);
MCAPI void _logIfValidLogArea(enum LogArea, std::string const&);
MCAPI void _recordProfanityLocationInWord(std::string const&, std::string&, std::vector<struct std::pair<int, int>> const&, int, int, class std::set<struct std::pair<int, int>, struct std::less<struct std::pair<int, int>>, class std::allocator<struct std::pair<int, int>>>&, class std::unordered_map<std::string, int, struct std::hash<std::string>, struct std::equal_to<std::string>, class std::allocator<struct std::pair<std::string const, int>>> const&, class std::unordered_set<std::string, struct std::hash<std::string>, struct std::equal_to<std::string>, class std::allocator<std::string>> const&);
MCAPI std::string base64_decode(std::string const&);
MCAPI std::string base64_encode(std::string const&, bool);
MCAPI std::string base64_encode(unsigned char const*, unsigned int, bool);
MCAPI std::string base64url_decode(std::string);
MCAPI std::string base64url_encode(std::string);
MCAPI std::string boolToString(bool);
MCAPI bool compareNoCase(class gsl::basic_string_span<char const, -1>, class gsl::basic_string_span<char const, -1>);
MCAPI std::string cp1252ToUTF8(std::string const&);
MCAPI std::string cp437ToUTF8(std::string const&);
MCAPI bool decompressRaw(std::string const&, std::string&);
MCAPI bool endsWith(class gsl::basic_string_span<char const, -1>, class gsl::basic_string_span<char const, -1>);
MCAPI bool endsWith(std::string const&, std::string const&);
MCAPI std::string ensureNamespace(std::string const&);
MCAPI std::string filterProfanityFromString(std::string const&, class std::unordered_map<std::string, int, struct std::hash<std::string>, struct std::equal_to<std::string>, class std::allocator<struct std::pair<std::string const, int>>> const&, class std::unordered_set<std::string, struct std::hash<std::string>, struct std::equal_to<std::string>, class std::allocator<std::string>> const&);
MCAPI std::string format(char const*, ...);
MCAPI void freeStringMemory(std::string&);
MCAPI std::string fromHex(std::string const&);
MCAPI unsigned __int64 generateHashFromTag(class Tag const&);
MCAPI class BidirectionalUnorderedMap<int, unsigned __int64> generateHashMapFromListTag(class ListTag const&);
MCAPI struct std::pair<std::string, std::string> getDataInheritance(std::string const&);
MCAPI std::unique_ptr<class Tag> getDataTagFromJson(class Json::Value const&, enum Tag::Type const&);
MCAPI std::string getNameWithoutNamespace(std::string const&);
MCAPI std::string getNamespace(std::string const&);
MCAPI unsigned int hashCode(std::string const&);
MCAPI bool isAlphaNumeric(char);
MCAPI bool isDigit(char);
MCAPI bool isIdentifierChar(char);
MCAPI bool isIntegral(std::string);
MCAPI bool isStartIdentifierChar(char);
MCAPI bool isUpperCaseAlphabetic(char);
MCAPI bool isValidNamespaceFormat(std::string const&);
MCAPI bool isValidUTF8(std::string const&);
MCAPI bool isVanillaNamespace(std::string const&);
MCAPI int isWhiteSpace(char);
MCAPI std::string join(std::vector<std::string> const&, class gsl::basic_string_span<char const, -1>);
MCAPI void loadGameVersion(class SemVersion&, class Json::Value const&);
MCAPI std::string removeChars(std::string, std::string const&);
MCAPI std::string removeIllegalChars(std::string);
MCAPI std::string removeTrailingSpaces(std::string);
MCAPI void replaceUtf8CharactersWithAscii(std::string&, std::vector<struct std::pair<std::string, char>> const&);
MCAPI class std::basic_istream<char, struct std::char_traits<char>>& safeGetline(class std::basic_istream<char, struct std::char_traits<char>>&, std::string&);
MCAPI std::string simpleFormat(std::string const&, std::vector<std::string> const&);
MCAPI std::string simpleJoin(class buffer_span<class gsl::basic_string_span<char const, -1>>, class gsl::basic_string_span<char const, -1>);
MCAPI std::vector<std::string> split(std::string const&, char);
MCAPI std::vector<std::string> splitLines(std::string const&, std::vector<std::string> const&, bool, bool, class std::basic_istream<char, struct std::char_traits<char>>& (*)(class std::basic_istream<char, struct std::char_traits<char>>&, std::string&));
MCAPI std::vector<std::string>& splitString(std::string const&, char, std::vector<std::string>&);
MCAPI bool startsWith(std::string const&, std::string const&);
MCAPI bool startsWith(class gsl::basic_string_span<char const, -1>, class gsl::basic_string_span<char const, -1>);
MCAPI bool stringContains(std::string const&, char);
MCAPI std::string& stringReplace(std::string&, std::string const&, std::string const&, int);
MCAPI std::string stringTrim(std::string const&);
MCAPI void stripBOM(std::string&);
MCAPI bool toBool(std::string const&, bool&);
MCAPI std::string toCamelCase(std::string const&, char);
MCAPI std::string toHex(std::string const&);
MCAPI enum Util::NumberConversionResult toIntWithMinMax(class gsl::basic_string_span<char const, -1>, int&, int, int);
MCAPI std::string toLower(std::string const&);
MCAPI std::string toLower(char const*);
MCAPI std::string toLower(class gsl::basic_string_span<char const, -1> const&);
MCAPI void toLowerInPlace(std::string&);
MCAPI enum Tag::Type toSimpleTagValueType(enum Json::ValueType const&);
MCAPI std::string toString(class std::basic_string<wchar_t, struct std::char_traits<wchar_t>, class std::allocator<wchar_t>> const&);
MCAPI std::string toString(float, int);
MCAPI std::string toString(std::string const&);
MCAPI char const* toString(enum BoneTransformType);
MCAPI std::string toStringWithPaddedZeroes(unsigned int, unsigned char);
MCAPI std::string toUpper(std::string const&);
MCAPI std::string toUpper(class gsl::basic_string_span<char const, -1> const&);
MCAPI class std::basic_string<wchar_t, struct std::char_traits<wchar_t>, class std::allocator<wchar_t>> toWideString(std::string const&);
MCAPI unsigned __int64 u64FromString(std::string const&);
MCAPI int utf8len(std::string const&);
MCAPI std::string utf8substring(std::string const&, int, int);
MCAPI std::string vFormat(char const*, char*);
MCAPI bool validateIdentifier(std::string const&, enum LogArea, bool, struct std::pair<std::string, std::string>*);
MCAPI bool validateIdentifierChunk(std::string const&, enum LogArea);

} // namespace Util