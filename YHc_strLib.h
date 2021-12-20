#ifndef YHC_STRLIB_H

// #define YHC_STRLIB_H
#if defined(__DATE__) && defined(__TIME__)
#define YHC_STRLIB_H __DATE__ ", " __TIME__
#elif defined(__DATE__) // && !defined(__TIME__)
#define YHC_STRLIB_H __DATE__ ", noCmpilT"
#elif defined(__TIME__) // && !defined(__DATE__)
#define YHC_STRLIB_H "noCmpilDate, " __TIME__
#else // !defined(__DATE__) && !defined(__TIME__)
#define YHC_STRLIB_H "no Cmpil Date or Time"
#endif // !defined(__DATE__) && !defined(__TIME__)

// #include <stdio.h>

// Since standard C++ library in Arduino is missing <wchar.h>
// Therefore macros are used to switch between C++ standard usage and Arduino usage of this library.
#if defined(ARDUINO)
// this header file is being used in arduino software

#include <stdlib.h> // included for malloc(), calloc(), free() functions on dynamic memory
#include <string.h> // included for simple string processing functions like strncpy(), strncmp()

#else // #if !defined(ARDUINO)
// this header file is being used in standard C++ computer software

#include <stdlib.h> // included for malloc(), calloc(), free() functions on dynamic memory
#include <string.h> // included for simple string processing functions like strncpy(), strncmp()
#include <wchar.h>  // included for use of UTF-8 encoded characters

#endif // #if !defined(ARDUINO)

#if !defined(__cplusplus)
#include <stdbool.h>
#endif // #if !defined(__cplusplus)

// #ifdef __cplusplus
// extern "C" {
// #endif // #ifdef __cpluscplus

// commented and not using extern "C" {} wrap, because this C header file is already wrapped by a C++ header file
// to use this library in C++, you should not include me, instead include "YHstrLib.hpp"

#ifdef DEF_YHC_STRLIB_KEYWORDS

#define YHc_strLib_vers YHc_strLib_vers

#define YH_cstring YH_cstring
#define YH_cstring_arr YH_cstring_arr

#define str_actv(...)           str_actv(__VA_ARGS__)
#define alloc_str(...)          alloc_str(__VA_ARGS__)
#define str_len(...)            str_len(__VA_ARGS__)
#define str_ptr(...)            str_ptr(__VA_ARGS__)
#define str_assign(...)         str_assign(__VA_ARGS__)
#define str_compare(...)        str_compare(__VA_ARGS__)
#define str_substr(...)         str_substr(__VA_ARGS__)
#define str_start_with(...)     str_start_with(__VA_ARGS__)
#define str_end_with(...)       str_end_with(__VA_ARGS__)
#define str_contain(...)        str_contain(__VA_ARGS__)
#define str_idx(...)            str_idx(__VA_ARGS__)
#define str_idxval(...)         str_idxval(__VA_ARGS__)
#define str_find_first(...)     str_find_first(__VA_ARGS__)
#define str_find_last(...)      str_find_last(__VA_ARGS__)
#define str_pushfront(...)      str_pushfront(__VA_ARGS__)
#define str_popfront(...)       str_popfront(__VA_ARGS__)
#define str_pushback(...)       str_pushback(__VA_ARGS__)
#define str_popback(...)        str_popback(__VA_ARGS__)
#define str_append(...)         str_append(__VA_ARGS__)
#define str_join_multiple(...)  str_join_multiple(__VA_ARGS__)
#define str_insert(...)         str_insert(__VA_ARGS__)
#define str_replace(...)        str_replace(__VA_ARGS__)
#define str_deactv(...)         str_deactv(__VA_ARGS__)
#define free_str(...)           free_str(__VA_ARGS__)

#if defined(_WCHAR_H_) || defined(__cplusplus)
    #define YH_wcstring YH_wcstring
    #define YH_wcstring_arr YH_wcstring_arr

    #define wstr_actv(...)           wstr_actv(__VA_ARGS__)
    #define alloc_wstr(...)          alloc_wstr(__VA_ARGS__)
    #define wstr_len(...)            wstr_len(__VA_ARGS__)
    #define wstr_ptr(...)            wstr_ptr(__VA_ARGS__)
    #define wstr_assign(...)         wstr_assign(__VA_ARGS__)
    #define wstr_compare(...)        wstr_compare(__VA_ARGS__)
    #define wstr_substr(...)         wstr_substr(__VA_ARGS__)
    #define wstr_start_with(...)     wstr_start_with(__VA_ARGS__)
    #define wstr_end_with(...)       wstr_end_with(__VA_ARGS__)
    #define wstr_contain(...)        wstr_contain(__VA_ARGS__)
    #define wstr_idx(...)            wstr_idx(__VA_ARGS__)
    #define wstr_idxval(...)         wstr_idxval(__VA_ARGS__)
    #define wstr_find_first(...)     wstr_find_first(__VA_ARGS__)
    #define wstr_find_last(...)      wstr_find_last(__VA_ARGS__)
    #define wstr_pushfront(...)      wstr_pushfront(__VA_ARGS__)
    #define wstr_popfront(...)       wstr_popfront(__VA_ARGS__)
    #define wstr_pushback(...)       wstr_pushback(__VA_ARGS__)
    #define wstr_popback(...)        wstr_popback(__VA_ARGS__)
    #define wstr_append(...)         wstr_append(__VA_ARGS__)
    #define wstr_join_multiple(...)  wstr_join_multiple(__VA_ARGS__)
    #define wstr_insert(...)         wstr_insert(__VA_ARGS__)
    #define wstr_replace(...)        wstr_replace(__VA_ARGS__)
    #define wstr_deactv(...)         wstr_deactv(__VA_ARGS__)
    #define free_wstr(...)           free_wstr(__VA_ARGS__)
    #define str_to_wstr(...)         str_to_wstr(__VA_ARGS__)
    #define wstr_to_str(...)         wstr_to_str(__VA_ARGS__)
#endif // #if defined(_WCHAR_H_) || defined (__cplusplus)

#endif // #ifdef

extern const char YHc_strLib_vers [];

typedef struct {
    char *ptr;
    size_t len;
    // unsigned int active; unused
} YH_cstring;

#if defined(_WCHAR_H_) || defined(__cplusplus)
typedef struct {
    wchar_t *ptr;
    size_t len;
    // unsigned int active; unused
} YH_wcstring;
#endif // #ifdef _WHCAR_H_

typedef struct {
    YH_cstring *ptr;
    size_t len;
    // unsigned int active; unused
} YH_cstring_arr;

#if defined(_WCHAR_H_) || defined(__cplusplus)
typedef struct {
    YH_wcstring *ptr;
    size_t len;
    // unsigned int active; unused
} YH_wcstring_arr;
#endif // #ifdef _WHCAR_H_

// constructor
void str_actv (YH_cstring *str);
// memory allocation with malloc() and auto calls str_actv(String *)
YH_cstring *alloc_str (void);
// returns the length of the String
size_t str_len (const YH_cstring *str);
// returns the char * of the String
const char *str_ptr (const YH_cstring *str);
// assign the inputed char[] to this String
const YH_cstring *str_assign (YH_cstring *str, const char *rhs);
// compares the 2 strings
bool str_compare (const YH_cstring *lhs, const char *rhs);
// get a substr of inputed String, and stored in dest
int str_substr (YH_cstring *dest, const YH_cstring *src, const size_t idx, size_t sublen);
// check if the String starts with a pattern
bool str_start_with (const YH_cstring *str, const char *start_with);
// check if the String ends with a pattern
bool str_end_with (const YH_cstring *str, const char *end_with);
// check if the String contains a pattern
bool str_contain (const YH_cstring *str, const char *to_be_contained);
// get the pointer of a certain character in the String
char *str_idx (YH_cstring *str, const size_t idx);
// get the value of a certain character in the String
char str_idxval (const YH_cstring *str, const size_t idx);
// returns the index of the first occuring inputed character in the String, -1 if not found
long str_find_first (const YH_cstring *str, const char target);
// returns the index of the last occuring inputed character in the String, -1 if not found
long str_find_last (const YH_cstring *str, const char target);
// inserts the inputed character in front of the String
char str_pushfront (YH_cstring *str, const char pushed);
// removes the first character in the String and returns it
char str_popfront (YH_cstring *str);
// appends the inputed character to the String
char str_pushback (YH_cstring *str, const char pushed);
// removes the last character in the String and returns it
char str_popback (YH_cstring *str);
// appends the String with the char[] app
YH_cstring *str_append (YH_cstring *str, const char *app);
// joins multiple strings to 1 string, and stored in dest
#define str_join(strptr,...) str_join_multiple(strptr,sizeof((const char *[]){__VA_ARGS__})/sizeof(const char *),(const char *[]){__VA_ARGS__})
YH_cstring *str_join_multiple (YH_cstring *dest, unsigned long len, const char **tb_joined_arr);
// inserts char[] ins before char[idx] in the String
YH_cstring *str_insert (YH_cstring *str, const size_t idx, const char *ins);
// replaces the selected part of the String to the rep
YH_cstring *str_replace (YH_cstring *str, const size_t idx, size_t sublen, const char *rep);
// destructor
void str_deactv (YH_cstring *str);
// auto calls str_deactv(String *) and free memory allocated with free()
void free_str (YH_cstring *str);


#if defined(_WCHAR_H_) || defined(__cplusplus)
// constructor
void wstr_actv (YH_wcstring *str);
// memory allocation with malloc() and auto calls wstr_actv(wString *)
YH_wcstring *alloc_wstr (void);
// returns the length of the wString
size_t wstr_len (const YH_wcstring *str);
// returns the wchar_t * of the wString
const wchar_t *wstr_ptr (const YH_wcstring *str);
// assign the inputed wchar_t[] to this String
const YH_wcstring *wstr_assign (YH_wcstring *str, const wchar_t *rhs);
// compares the 2 strings
bool wstr_compare (const YH_wcstring *lhs, const wchar_t *rhs);
// get a substr of inputed wString, and stored in dest
int wstr_substr (YH_wcstring *dest, const YH_wcstring *src, const size_t idx, size_t sublen);
// check if the wString starts with a pattern
bool wstr_start_with (const YH_wcstring *str, const wchar_t *start_with);
// check if the wString ends with a pattern
bool wstr_end_with (const YH_wcstring *str, const wchar_t *end_with);
// check if the wString contains a pattern
bool wstr_contain (const YH_wcstring *str, const wchar_t *to_be_contained);
// get the pointer of a certain character in the wString
wchar_t *wstr_idx (YH_wcstring *str, const size_t idx);
// get the value of a certain character in the wString
wchar_t wstr_idxval (const YH_wcstring *str, const size_t idx);
// returns the index of the first occuring inputed character in the wString, -1 if not found
long wstr_find_first (const YH_wcstring *str, const wchar_t target);
// returns the index of the last occuring inputed character in the wString, -1 if not found
long wstr_find_last (const YH_wcstring *str, const wchar_t target);
// inserts the inputed character in front of the wString
wchar_t wstr_pushfront (YH_wcstring *str, const wchar_t pushed);
// removes the first character in the wString and returns it
wchar_t wstr_popfront (YH_wcstring *str);
// appends the inputed character to the wString
wchar_t wstr_pushback (YH_wcstring *str, const wchar_t pushed);
// removes the last character in the wString and returns it
wchar_t wstr_popback (YH_wcstring *str);
// appends the wString with the wchar_t[] app
YH_wcstring *wstr_append (YH_wcstring *str, const wchar_t *app);
// joins multiple strings to 1 string, and stored in dest
#define wstr_join(strptr,...) wstr_join_multiple(strptr,sizeof(((const wchar_t *)[]){__VA_ARGS__})/sizeof(const wchar_t *),((const wchar_t *)[]){__VA_ARGS__})
YH_wcstring *wstr_join_multiple (YH_wcstring *raw, unsigned long len, const wchar_t **tb_joined_arr);
// inserts wchar_t[] ins before wchar_t[idx] in the wString
YH_wcstring *wstr_insert (YH_wcstring *str, const size_t idx, const wchar_t *ins);
// replaces the selected part of the wString to the rep
YH_wcstring *wstr_replace (YH_wcstring *str, const size_t idx, size_t sublen, const wchar_t *rep);
// destructor
void wstr_deactv (YH_wcstring *str);
// auto calls str_deactv(String *) and free memory allocated with free()
void free_wstr (YH_wcstring *str);

#if !defined(ARDUINO)
// converts String containing both ASCII and UTF-characters to wString
int str_to_wstr (YH_cstring *orig_str, YH_wcstring *dest_wstr);
#endif // #if !defined(ARDUINO)
// converts ASCII to char, multi-byte UTF-char to multiple chars (depending on the sizeof char)
int wstr_to_str (YH_wcstring *orig_wstr, YH_cstring *dest_str);
#endif // #if defined(_WCHAR_H_) || defined(__cplusplus)

// #ifdef __cplusplus
// } // closing bracket of extern "C" {
// #endif // #ifdef __cpluscplus

#if defined(__cplusplus) && !defined(YHSTRLIB_HPP)
#include "YHstrLib.hpp"
#endif // #if defined(__cplusplus) && !defined(YHSTRLIB_HPP)

#endif // #ifndef YHC_STRLIB_H