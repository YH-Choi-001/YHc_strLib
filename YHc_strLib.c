#ifndef YHC_STRLIB_C
// #define YHC_STRLIB_C
#if defined(__DATE__) && defined(__TIME__)
#define YHC_STRLIB_C __DATE__ ", " __TIME__
#elif defined(__DATE__) // && !defined(__TIME__)
#define YHC_STRLIB_C __DATE__ ", noCmpilT"
#elif defined(__TIME__) // && !defined(__DATE__)
#define YHC_STRLIB_C "noCmpilDate, " __TIME__
#else // !defined(__DATE__) && !defined(__TIME__)
#define YHC_STRLIB_C "no Cmpil Date or Time"
#endif // !defined(__DATE__) && !defined(__TIME__)

#ifndef YHC_STRLIB_H
#include "YHc_strLib.h"
#endif // #ifndef YHC_STRLIB_H

// this implementation file does not use strcmp, strcpy because they are dangerous
// instead, a little little little safer strncmp and strncpy are used

// implement only if strlen, strncmp, strncpy is not defined
// implementation copied from YHtextLib.cpp
#if !defined(_STRING_H_)
// strlen
    size_t YHc_strLib_c_strlen (const char *str) {
        size_t i = 0;
        for (;str[i] != '\0'; i++);
        return i;
    }
// strncmp
    int YHc_strLib_c_strncmp (const char *lhs, const char *rhs, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            if (lhs[i] < rhs[i]) return -1;
            else if (lhs[i] > rhs[i]) return 1;
            else if (/*lhs[i] == rhs[i] && */lhs[i] == '\0') return 0;
        }
        return 0;
    }
// strncpy
    char *YHc_strLib_c_strncpy (char *dst, const char *src, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            if ((dst[i] = src[i]) == '\0') return dst;
        }
        return dst;
    }

#define strlen(...) YHc_strLib_c_strlen(__VA_ARGS__)
#define strncmp(...) YHc_strLib_c_strncmp(__VA_ARGS__)
#define strncpy(...) YHc_strLib_c_strncpy(__VA_ARGS__)

#endif // #if !defined(_STRING_H_)

// implement only if wcslen, wcsncmp, wcsncpy is not defined
// implementation copied from YHtextLib.cpp
#if !defined(_WCHAR_H_)
// wcslen
    size_t YHc_strLib_c_wcslen (const wchar_t *str) {
        size_t i = 0;
        for (;str[i] != L'\0'; i++);
        return i;
    }
// wcsncmp
    int YHc_strLib_c_wcsncmp (const wchar_t *lhs, const wchar_t *rhs, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            if (lhs[i] < rhs[i]) return -1;
            else if (lhs[i] > rhs[i]) return 1;
            else if (/*lhs[i] == rhs[i] && */lhs[i] == L'\0') return 0;
        }
        return 0;
    }
// wcsncpy
    wchar_t *YHc_strLib_c_wcsncpy (wchar_t *dst, const wchar_t *src, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            if ((dst[i] = src[i]) == L'\0') return dst;
        }
        return dst;
    }

#define wcslen(...) YHc_strLib_c_wcslen(__VA_ARGS__)
#define wcsncmp(...) YHc_strLib_c_wcsncmp(__VA_ARGS__)
#define wcsncpy(...) YHc_strLib_c_wcsncpy(__VA_ARGS__)

#endif // #if !defined(_WCHAR_H_)

const char YHc_strLib_vers [] = YHC_STRLIB_C;

void str_actv (YH_cstring *str) {
    if (str == NULL) return ;
    str->ptr = NULL;
    str->len = 0;
    // str->active = 1;
}
YH_cstring *alloc_str (void) {
    YH_cstring *str = (YH_cstring *)malloc(sizeof(YH_cstring));
    str_actv(str);
    return str;
}
size_t str_len (const YH_cstring *str) {
    if (str == NULL) return 0;
    return str->len;
}
const char *str_ptr (const YH_cstring *str) {
    if (str == NULL) return NULL;
    return str->ptr;
}
const YH_cstring *str_assign (YH_cstring *str, const char *rhs) {
    if (str == NULL || rhs == NULL) return NULL;
    str_deactv(str);
    str->len = strlen(rhs);
    str->ptr = (char *)calloc((str->len + 1), sizeof(char));
    strncpy(str->ptr, rhs, str->len + 1);
    // str->active = 1;
    str->ptr[str->len] = (char)'\0';
    return str;
}
bool str_compare (const YH_cstring *lhs, const char *rhs) {
    if (lhs == NULL || rhs == NULL) return 0;
    return !strncmp(lhs->ptr, rhs, lhs->len + 1);
}
int str_substr (YH_cstring *dest, const YH_cstring *src, const size_t idx, size_t sublen) {
    if (src == NULL || dest == NULL) return -1;
    if (idx + sublen > (src->len)) {
        sublen = src->len - idx;
    }
    str_deactv(dest);
    dest->len = sublen;
    dest->ptr = (char *)calloc((dest->len + 1), sizeof(char));
    strncpy(dest->ptr, &(src->ptr[idx]), dest->len);
    dest->ptr[dest->len] = (char)'\0';
    return 0;
}
bool str_start_with (const YH_cstring *str, const char *start_with) {
    if (str == NULL || start_with == NULL) return 0;
    const size_t target_len = strlen(start_with);
    if (str->len < target_len) return 0;
    YH_cstring temp;
    str_actv(&temp);
    str_substr(&temp, str, 0, target_len);
    bool result = str_compare(&temp, start_with);
    str_deactv(&temp);
    return result;
}
bool str_end_with (const YH_cstring *str, const char *end_with) {
    if (str == NULL || end_with == NULL) return 0;
    const size_t target_len = strlen(end_with);
    if (str->len < target_len) return 0;
    YH_cstring temp;
    str_actv(&temp);
    str_substr(&temp, str, str->len - target_len, target_len);
    // strncmp(&(str->ptr[str->len - target_len]), end_with, target_len);
    bool result = str_compare(&temp, end_with);
    str_deactv(&temp);
    return result;
}
bool str_contain (const YH_cstring *str, const char *to_be_contained) {
    if (str == NULL || to_be_contained == NULL) return 0;
    const size_t tbc_len = strlen(to_be_contained);
    if (tbc_len < 1 || tbc_len > str->len) return false;
    const size_t max_loop_len = str->len - tbc_len + 1;
    for (size_t i = 0; i < max_loop_len; i++) {
        if (!strncmp(&(str->ptr[i]), to_be_contained, tbc_len)) return true;
    }
    return false;
}
char *str_idx (YH_cstring *str, const size_t idx) {
    if (str == NULL) return NULL;
    return &(str->ptr[idx]);
}
char str_idxval (const YH_cstring *str, const size_t idx) {
    if (str == NULL) return 0;
    return str->ptr[idx];
}
long str_find_first (const YH_cstring *str, const char target) {
    if (str == NULL) return -1;
    for (size_t i = 0; i <= str->len; i++) {
        if (str->ptr[i] == target) return i;
    }
    return -1;
}
long str_find_last (const YH_cstring *str, const char target) {
    if (str == NULL) return -1;
    if (str->ptr[0] == target) return 0;
    for (size_t i = str->len; i > 0; i--) {
        if (str->ptr[i] == target) return i;
    }
    return -1;
}
char str_pushfront (YH_cstring *str, const char pushed) {
    if (str == NULL) return -1;
    char temp [str->len + 2];
    temp[0] = pushed;
    if (pushed != '\0') strncpy(&(temp[1]), str->ptr, str->len + 1);
    str_assign(str, temp);
    return pushed;
}
char str_popfront (YH_cstring *str) {
    if (str == NULL) return -1;
    if (str->len == 0) return str->ptr[0];
    const size_t str_len_sub_1 = str->len - 1;
    char first_char = str->ptr[0];
    char temp [str->len];
    strncpy(temp, (str->ptr) + 1, str_len_sub_1);
    temp[str_len_sub_1] = (char)'\0';
    str_assign(str, temp);
    return first_char;
    //
}
char str_pushback (YH_cstring *str, const char pushed) {
    if (str == NULL) return -1;
    char temp [str->len + 2];
    strncpy(temp, str->ptr, str->len);
    temp[str->len] = pushed;
    temp[str->len + 1] = (char)'\0';
    str_assign(str, temp);
    return pushed;
}
char str_popback (YH_cstring *str) {
    if (str == NULL) return -1;
    if (str->len == 0) return str->ptr[0];
    const size_t str_len_sub_1 = str->len - 1;
    char last_char = str->ptr[str_len_sub_1];
    char temp [str->len];
    strncpy(temp, str->ptr, str_len_sub_1);
    temp[str_len_sub_1] = (char)'\0';
    str_assign(str, temp);
    return last_char;
}
YH_cstring *str_append (YH_cstring *str, const char *app) {
    if (str == NULL || app == NULL) return NULL;
    const size_t app_len = strlen(app);
    const size_t str_sumlen = str->len + app_len;
    char temp [str_sumlen + 1];
    strncpy(temp, str->ptr, str->len);
    strncpy(&temp[str->len], app, app_len);
    temp [str_sumlen] = (char)'\0';
    str_assign(str, temp);
    return str;
}
YH_cstring *str_join_multiple (YH_cstring *dest, unsigned long len, const char **tb_joined_arr) {
    str_assign(dest, tb_joined_arr[0]);
    for (unsigned long i = 1; i < len; i++) {
        str_append(dest, tb_joined_arr[i]);
    }
    return dest;
}
YH_cstring *str_insert (YH_cstring *str, const size_t idx, const char *ins) {
    return str_replace(str, idx, 0, ins);
    /*
    String lhs;
    String rhs;
    // calloc
    str_actv(&lhs);
    str_actv(&rhs);
    // brk str to left and right hand side for insert
    str_substr(&lhs, str, 0, idx);
    str_substr(&rhs, str, idx, str->len - idx);
    // lhs + ins + rhs
    str_assign(str, lhs.ptr);
    str_append(str, ins);
    str_append(str, rhs.ptr);
    // free
    str_deactv(&lhs);
    str_deactv(&rhs);
    return str;
    */
}
YH_cstring *str_replace (YH_cstring *str, const size_t idx, size_t sublen, const char *rep) {
    if (str == NULL || rep == NULL) return NULL;
    YH_cstring lhs;
    YH_cstring rhs;
    // calloc
    str_actv(&lhs);
    str_actv(&rhs);
    // brk str to left and right hand side for replace
    str_substr(&lhs, str, 0, idx);
    str_substr(&rhs, str, idx + sublen, str->len - idx - sublen);
    // lhs + ins + rhs
    str_assign(str, lhs.ptr);
    str_append(str, rep);
    str_append(str, rhs.ptr);
    // free
    str_deactv(&lhs);
    str_deactv(&rhs);
    return str;
}
void str_deactv (YH_cstring *str) {
    if (str == NULL) return ;
    if (str->ptr != NULL) {
        free(str->ptr);
        str->ptr = NULL;
        str->len = 0;
        // str->active = 0;
    }
}
void free_str (YH_cstring *str) {
    if (str == NULL) return ;
    str_deactv(str);
    free(str);
}

#if defined(_WCHAR_H_) || defined(__cplusplus)
void wstr_actv (YH_wcstring *str) {
    if (str == NULL) return ;
    str->ptr = NULL;
    str->len = 0;
    // str->active = 1;
}
YH_wcstring *alloc_wstr (void) {
    YH_wcstring *str = (YH_wcstring *)malloc(sizeof(YH_wcstring));
    wstr_actv(str);
    return str;
}
size_t wstr_len (const YH_wcstring *str) {
    if (str == NULL) return 0;
    return str->len;
}
const wchar_t *wstr_ptr (const YH_wcstring *str) {
    if (str == NULL) return NULL;
    return str->ptr;
}
const YH_wcstring *wstr_assign (YH_wcstring *str, const wchar_t *rhs) {
    if (str == NULL || rhs == NULL) return NULL;
    wstr_deactv(str);
    str->len = wcslen(rhs);
    str->ptr = (wchar_t *)calloc((str->len + 1), sizeof(wchar_t));
    wcsncpy(str->ptr, rhs, str->len + 1);
    // str->active = 1;
    str->ptr[str->len] = (wchar_t)'\0';
    return str;
}
bool wstr_compare (const YH_wcstring *lhs, const wchar_t *rhs) {
    if (lhs == NULL || rhs == NULL) return 0;
    return !wcsncmp(lhs->ptr, rhs, lhs->len + 1);
}
int wstr_substr (YH_wcstring *dest, const YH_wcstring *src, const size_t idx, size_t sublen) {
    if (dest == NULL || src == NULL) return -1;
    if (idx + sublen > (src->len)) {
        sublen = src->len - idx;
    }
    wstr_deactv(dest);
    dest->len = sublen;
    dest->ptr = (wchar_t *)calloc((dest->len + 1), sizeof(wchar_t));
    wcsncpy(dest->ptr, &(src->ptr[idx]), dest->len);
    dest->ptr[dest->len] = (wchar_t)'\0';
    return 0;
}
bool wstr_start_with (const YH_wcstring *str, const wchar_t *start_with) {
    if (str == NULL || start_with == NULL) return 0;
    const size_t target_len = wcslen(start_with);
    if (str->len < target_len) return 0;
    YH_wcstring temp;
    wstr_actv(&temp);
    wstr_substr(&temp, str, 0, target_len);
    bool result = wstr_compare(&temp, start_with);
    wstr_deactv(&temp);
    return result;
}
bool wstr_end_with (const YH_wcstring *str, const wchar_t *end_with) {
    if (str == NULL || end_with == NULL) return 0;
    const size_t target_len = wcslen(end_with);
    if (str->len < target_len) return 0;
    YH_wcstring temp;
    wstr_actv(&temp);
    wstr_substr(&temp, str, str->len - target_len, target_len);
    bool result = wstr_compare(&temp, end_with);
    wstr_deactv(&temp);
    return result;
}
bool wstr_contain (const YH_wcstring *str, const wchar_t *to_be_contained) {
    if (str == NULL || to_be_contained == NULL) return 0;
    const size_t tbc_len = wcslen(to_be_contained);
    if (tbc_len < 1 || tbc_len > str->len) return false;
    const size_t max_loop_len = str->len - tbc_len + 1;
    for (size_t i = 0; i < max_loop_len; i++) {
        if (!wcsncmp(&(str->ptr[i]), to_be_contained, tbc_len)) return true;
    }
    return false;
}
wchar_t *wstr_idx (YH_wcstring *str, const size_t idx) {
    if (str == NULL) return NULL;
    return &(str->ptr[idx]);
}
wchar_t wstr_idxval (const YH_wcstring *str, const size_t idx) {
    if (str == NULL) return 0;
    return str->ptr[idx];
}
long wstr_find_first (const YH_wcstring *str, const wchar_t target) {
    if (str == NULL) return -1;
    for (size_t i = 0; i < str->len; i++) {
        if (str->ptr[i] == target) return i;
    }
    return -1;
}
long wstr_find_last (const YH_wcstring *str, const wchar_t target) {
    if (str == NULL) return -1;
    if (str->ptr[0] == target) return 0;
    for (size_t i = str->len; i > 0; i--) {
        if (str->ptr[i] == target) return i;
    }
    return -1;
}
wchar_t wstr_pushfront (YH_wcstring *str, const wchar_t pushed) {
    if (str == NULL) return -1;
    wchar_t temp [str->len + 2];
    temp[0] = pushed;
    if (pushed != '\0') wcsncpy(&(temp[1]), str->ptr, str->len + 1);
    wstr_assign(str, temp);
    return pushed;
}
wchar_t wstr_popfront (YH_wcstring *str) {
    if (str == NULL) return -1;
    if (str->len == 0) return str->ptr[0];
    const size_t str_len_sub_1 = str->len - 1;
    wchar_t first_char = str->ptr[0];
    wchar_t temp [str->len];
    wcsncpy(temp, (str->ptr) + 1, str_len_sub_1);
    temp[str_len_sub_1] = (wchar_t)'\0';
    wstr_assign(str, temp);
    return first_char;
    //
}
wchar_t wstr_pushback (YH_wcstring *str, const wchar_t pushed) {
    if (str == NULL) return -1;
    wchar_t temp [str->len + 2];
    wcsncpy(temp, str->ptr, str->len);
    temp[str->len] = pushed;
    temp[str->len + 1] = (wchar_t)'\0';
    wstr_assign(str, temp);
    return pushed;
}
wchar_t wstr_popback (YH_wcstring *str) {
    if (str == NULL) return -1;
    if (str->len == 0) return str->ptr[0];
    const size_t str_len_sub_1 = str->len - 1;
    wchar_t last_char = str->ptr[str_len_sub_1];
    wchar_t temp [str->len];
    wcsncpy(temp, str->ptr, str_len_sub_1);
    temp[str_len_sub_1] = '\0';
    wstr_assign(str, temp);
    return last_char;
}
YH_wcstring *wstr_append (YH_wcstring *str, const wchar_t *app) {
    if (str == NULL || app == NULL) return NULL;
    const size_t app_len = wcslen(app);
    const size_t str_sumlen = str->len + app_len;
    wchar_t temp [str_sumlen + 1];
    wcsncpy(temp, str->ptr, str->len);
    wcsncpy(&temp[str->len], app, app_len);
    temp [str_sumlen] = (wchar_t)'\0';
    wstr_assign(str, temp);
    return str;
}
YH_wcstring *wstr_join_multiple (YH_wcstring *raw, unsigned long len, const wchar_t **tb_joined_arr) {
    wstr_assign(raw, tb_joined_arr[0]);
    for (unsigned long i = 1; i < len; i++) {
        wstr_append(raw, tb_joined_arr[i]);
    }
    return raw;
}
YH_wcstring *wstr_insert (YH_wcstring *str, const size_t idx, const wchar_t *ins) {
    return wstr_replace(str, idx, 0, ins);
    /*
    wString lhs;
    wString rhs;
    // calloc
    wstr_actv(&lhs);
    wstr_actv(&rhs);
    // brk str to left and right hand side for insert
    wstr_substr(&lhs, str, 0, idx);
    wstr_substr(&rhs, str, idx, str->len - idx);
    // lhs + ins + rhs
    wstr_assign(str, lhs.ptr);
    wstr_append(str, ins);
    wstr_append(str, rhs.ptr);
    // free
    wstr_deactv(&lhs);
    wstr_deactv(&rhs);
    return str;
    */
}
YH_wcstring *wstr_replace (YH_wcstring *str, const size_t idx, size_t sublen, const wchar_t *rep) {
    if (str == NULL || rep == NULL) return NULL;
    const size_t removed_len = idx + sublen;
    YH_wcstring lhs;
    YH_wcstring rhs;
    // calloc
    wstr_actv(&lhs);
    wstr_actv(&rhs);
    // brk str to left and right hand side for replace
    wstr_substr(&lhs, str, 0, idx);
    wstr_substr(&rhs, str, removed_len, str->len - removed_len);
    // lhs + ins + rhs
    wstr_assign(str, lhs.ptr);
    wstr_append(str, rep);
    wstr_append(str, rhs.ptr);
    // free
    wstr_deactv(&lhs);
    wstr_deactv(&rhs);
    return str;
}
void wstr_deactv (YH_wcstring *str) {
    if (str == NULL) return ;
    if (str->ptr != NULL) {
        free(str->ptr);
        str->ptr = NULL;
        str->len = 0;
        // str->active = 0;
    }
}
void free_wstr (YH_wcstring *str) {
    if (str == NULL) return ;
    wstr_deactv(str);
    free(str);
}

#if !defined(ARDUINO)
int str_to_wstr (YH_cstring *orig_str, YH_wcstring *dest_wstr) {
    if (orig_str == NULL) return -1;
    if (dest_wstr == NULL) return -2;
    wstr_assign(dest_wstr, L"");
    unsigned char orig_str_ptr_idx_i = '\0';
    wchar_t temp_holding_char = L'\0';
    for (size_t i = 0; i < orig_str->len; i++) {
        orig_str_ptr_idx_i = (unsigned char)(orig_str->ptr[i]);
        if (orig_str_ptr_idx_i > 0x7f) {
            // if the above statement returns 1, this wchar occupies more than one byte
            // the 5 variants below are valid
            // 110x xxxx 10xx xxxx
            // 1110 xxxx 10xx xxxx 10xx xxxx
            // 1111 0xxx 10xx xxxx 10xx xxxx 10xx xxxx
            // 1111 10xx 10xx xxxx 10xx xxxx 10xx xxxx 10xx xxxx
            // 1111 110x 10xx xxxx 10xx xxxx 10xx xxxx 10xx xxxx 10xx xxxx
            if (/*orig_str_ptr_idx_i > 0x7f &&*/ orig_str_ptr_idx_i < 0xc0) {
                // 10xx xxxx > 0111 1111, < 1100 0000
                // 1 byte, error ????? only 1 byte ?????
                temp_holding_char = (wchar_t)orig_str_ptr_idx_i;
            } else if (orig_str_ptr_idx_i > 0xbf && orig_str_ptr_idx_i < 0xe0) {
                // 110x xxxx > 1011 1111, < 1110 0000
                // 2 bytes
                if (sizeof(wchar_t) > 1) {
                    temp_holding_char =  ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] );
                } else {
                    temp_holding_char = (wchar_t)orig_str->ptr[i];
                }
            } else if (orig_str_ptr_idx_i > 0xdf && orig_str_ptr_idx_i < 0xf0) {
                // 1110 xxxx > 1101 1111, < 1111 0000
                // 3 bytes
                if (sizeof(wchar_t) > 2) {
                    temp_holding_char =  ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 2) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] );
                } else {
                    temp_holding_char = (wchar_t)orig_str->ptr[i];
                }
            } else if (orig_str_ptr_idx_i > 0xef && orig_str_ptr_idx_i < 0xf8) {
                // 1111 0xxx > 1110 1111, < 1111 1000
                // 4 bytes
                if (sizeof(wchar_t) > 3) {
                    temp_holding_char =  ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 3) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 2) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] );
                } else {
                    temp_holding_char = (wchar_t)orig_str->ptr[i];
                }
            } else if (orig_str_ptr_idx_i > 0xf7 && orig_str_ptr_idx_i < 0xfc) {
                // 1111 10xx > 1111 0111, < 1111 1100
                // 5 bytes
                if (sizeof(wchar_t) > 4) {
                    temp_holding_char =  ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 4) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 3) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 2) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] );
                } else {
                    temp_holding_char = (wchar_t)orig_str->ptr[i];
                }
            } else if (orig_str_ptr_idx_i > 0xfb && orig_str_ptr_idx_i < 0xfe) {
                // 1111 110x > 1111 1011, < 1111 1110
                // 6 bytes
                if (sizeof(wchar_t) > 5) {
                    temp_holding_char =  ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 5) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 4) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 3) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8 * 2) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] << (sizeof(*(orig_str->ptr)) * 8) );
                    if (orig_str->ptr[++i] == '\0') break;
                    temp_holding_char += ( (wchar_t)orig_str->ptr[i] );
                } else {
                    temp_holding_char = (wchar_t)orig_str->ptr[i];
                }
            // } else if (orig_str_ptr_idx_i > 0xfd && orig_str_ptr_idx_i < 0xff) {
            } else if (orig_str_ptr_idx_i == 0xfe) {
                // 1111 1110 > 1111 1101 , < 1111 1111
                // 7 bytes, error ????? occupy 7 bytes ?????
                temp_holding_char = (wchar_t)orig_str_ptr_idx_i;
            } else if (orig_str_ptr_idx_i == 0xff) {
                // 1111 1111, error
                temp_holding_char = (wchar_t)orig_str_ptr_idx_i;
            }
        } else {
            // 0xxx xxxx
            // this char occupies only one byte
            // simply append it to the dest_wstr
            temp_holding_char = (wchar_t)orig_str_ptr_idx_i;
        }
        wstr_pushback(dest_wstr, temp_holding_char);
        // end of for-loop
    }
    return 0;
}
#endif // #if !defined(ARDUINO)

int wstr_to_str (YH_wcstring *orig_wstr, YH_cstring *dest_str) {
    if (orig_wstr == NULL) return -1;
    if (dest_str == NULL) return -2;
    str_assign(dest_str, "");
    wchar_t orig_wstr_ptr_idx_i = L'\0';
    for (size_t i = 0; i < orig_wstr->len; i++) {
        orig_wstr_ptr_idx_i = (orig_wstr->ptr[i]);
        if (orig_wstr_ptr_idx_i < (wchar_t)0x80) {
            // 7-bit ASCII character
            str_pushback(dest_str, orig_wstr->ptr[i]);
        } else {
            // UTF-encoding character
            for (short j = sizeof(wchar_t) / sizeof(char); j > 0; j--) {
                str_pushback( dest_str, (orig_wstr->ptr[i]) >> ((j-1) * 8 * sizeof(char)) );
            }
        }
    }
    return 0;
}
#endif // #if defined(_WCHAR_H_) || defined(__cplusplus)

#if !defined(_STRING_H_)
#undef strlen
#undef strncmp
#undef strncpy
#endif // #if !defined(_STRING_H_)
#if !defined(_WCHAR_H_)
#undef wcslen
#undef wcsncmp
#undef wcsncpy
#endif // #if !defined(_WCHAR_H_)

/*

void str_actv (String *str);
String *alloc_str (void);
size_t str_len (String *str);
const char *str_ptr (String *str);
const String *str_assign (String *str, const char *rhs);
bool str_compare (const String *lhs, const char *rhs);
int str_substr (String *dest, const String *src, const size_t idx, size_t sublen);
bool str_start_with (const String *str, const char *start_with);
bool str_end_with (const String *str, const char *end_with);
bool str_contain (const String *str, const char *to_be_contained);
char *str_idx (String *str, const size_t idx);
char str_idxval (String *str, const size_t idx);
long str_find_first (String *str, const char target);
long str_find_last (String *str, const char target);
char str_pushback (String *str, const char pushed);
char str_popback (String *str);
String *str_append (String *str, const char *app);
String *str_join (String *raw, const char *lhs, const char *rhs);
String *str_insert (String *str, const size_t idx, const char *ins);
String *str_replace (String *str, const size_t idx, size_t sublen, const char *rep);
void str_deactv (String *str);
void free_str (String *str);

*/
/* debug or example use
int main (int argc, char **argv, char **envr) {
    YH_cstring str1;
    YH_cstring str2;
    YH_cstring str3;
    YH_cstring *str_ptr1;
    str_actv(&str1);
    str_actv(&str2);
    str_actv(&str3);
    str_ptr1 = alloc_str();
    str_assign(&str1, "Hello, world!");
    printf("assign: \"%s\"\n", str_ptr(&str1));
    printf("compare \"Hello, world\": %d\n\t(0)\n", str_compare(&str1, "Hello, world"));
    printf("compare \"Hello, world!\": %d\n\t(1)\n", str_compare(&str1, "Hello, world!"));
    str_substr(&str2, &str1, 7, 5);
    printf("substr: \"%s\"\n\t(\"world\")\n", str_ptr(&str2));
    printf("start with \"ell\": %d\n\t(0)\n", str_start_with(&str1, "ell"));
    printf("start with \"Hel\": %d\n\t(1)\n", str_start_with(&str1, "Hel"));
    printf("end with \"rld\": %d\n\t(0)\n", str_end_with(&str1, "rld"));
    printf("end with \"ld!\": %d\n\t(1)\n", str_end_with(&str1, "ld!"));
    printf("contain \"there\": %d\n\t(0)\n", str_contain(&str1, "there"));
    printf("contain \"world\": %d\n\t(1)\n", str_contain(&str1, "world"));
    printf("find first \'l\': %ld\n\t(2)\n", str_find_first(&str1, 'l'));
    printf("find last \'l\': %ld\n\t(10)\n", str_find_last(&str1, 'l'));
    str_pushback(&str1, '{');
    printf("pushback: \'{\': \"%s\"\n\t(\"Hello, world!{\")\n", str_ptr(&str1));
    printf("popback return val: \'%c\'\n\t(\'{\')\n", str_popback(&str1));
    printf("after popback: \"%s\"\n\t(\"Hello, world!\")\n", str_ptr(&str1));
    str_append(&str1, " Welcome!");
    printf("append \" Welcome!\": \"%s\"\n\t(\"Hello, world! Welcome!\")\n", str_ptr(&str1));
    str_join(&str3, str_ptr(&str1), str_ptr(&str2));
    printf("join str1 str2 : \"%s\"\n\t(\"Hello, world! Welcome!world\")\n", str_ptr(&str3));
    str_insert(&str1, 7, "my");
    printf("insert 7 \"my\": \"%s\"\n\t(\"Hello, myworld! Welcome!\")\n", str_ptr(&str1));
    str_replace(&str1, 9, 5, " friend");
    printf("replace \"world\" to \" friend\": \"%s\"\n\t(\"Hello, myfriend! Welcome!\")\n", str_ptr(&str1));
    str_deactv(&str1);
    str_deactv(&str2);
    str_deactv(&str3);
    free_str(str_ptr1);
    return 0;
}
*/

#if defined(__cplusplus) && !defined(YHSTRLIB_CPP)
#include "YHstrLib.cpp"
#endif // #if defined(__cplusplus) && !defined(YHSTRLIB_CPP)

#endif // #ifndef YHC_STRLIB_C