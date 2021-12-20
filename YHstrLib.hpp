#ifndef YHSTRLIB_HPP
#define YHSTRLIB_HPP __DATE__ ", " __TIME__

#ifndef YHC_STRLIB_H
#include "YHc_strLib.h"
#endif // #ifndef YHC_STRLIB_H

// WARNINGS ON USING THE CLASS "String" :

// DO NOT CALL String.c_str() METHOD AND INPUT IT TO SCANF AS A C-STRING

// String.c_str() METHOD IS ALWAYS FOR READ ONLY

// TO IMPLEMENT ASSIGNMENTS OF STRINGS WITH UNKNOWN LENGTH,
// LIKE GETTING USER INPUT FROM STDIN BUFFER OR CIN BUFFER
// USE WHILE LOOPS AND String.push_back(char_to_be_pushed)

// my greatest fine art on using dynamic memory

#if defined(__cplusplus)

#define YH_CPP_STRVER GEN_4 // YH C++ string version
#define YH_CPP_STR_NMSPCE ::YH_CPP_STRVER

#define START_YH_CPP_STR_NAMESPACE namespace YH_CPP_STRVER {

#define ENDOF_YH_CPP_STR_NAMESPACE }

namespace YH {
    namespace Lib {
        typedef ::YH_cstring Cstr;
        typedef ::YH_wcstring Cwstr;
        typedef ::YH_cstring_arr Cstrarr;
        typedef ::YH_wcstring_arr Cwstrarr;
        namespace Func {
            namespace c_strs {
                using ::str_actv;
                using ::alloc_str;
                using ::str_len;
                using ::str_ptr;
                using ::str_assign;
                using ::str_compare;
                using ::str_substr;
                using ::str_start_with;
                using ::str_end_with;
                using ::str_idx;
                using ::str_idxval;
                using ::str_find_first;
                using ::str_find_last;
                using ::str_pushback;
                using ::str_popback;
                using ::str_append;
                using ::str_join_multiple;
                using ::str_insert;
                using ::str_replace;
                using ::str_deactv;
                using ::free_str;
                //
                using ::wstr_actv;
                using ::alloc_wstr;
                using ::wstr_len;
                using ::wstr_ptr;
                using ::wstr_assign;
                using ::wstr_compare;
                using ::wstr_substr;
                using ::wstr_start_with;
                using ::wstr_end_with;
                using ::wstr_idx;
                using ::wstr_idxval;
                using ::wstr_find_first;
                using ::wstr_find_last;
                using ::wstr_pushback;
                using ::wstr_popback;
                using ::wstr_append;
                using ::wstr_join_multiple;
                using ::wstr_insert;
                using ::wstr_replace;
                using ::wstr_deactv;
                using ::free_wstr;
                #if !defined(ARDUINO)
                using ::str_to_wstr;
                #endif // #if !defined(ARDUINO)
                using ::wstr_to_str;
                extern const char YHstrLib_vers [];
            }
        }
        START_YH_CPP_STR_NAMESPACE
        class String {
            private:
                // the core of the object: the YH_cstring object
                Cstr strbuf;
            protected:
                // for non-method functions use only
                      String &myself ()       { return *this; }
                const String &myself () const { return *this; }
            public:
            // constructors and destructors
                // default constructor, does not init any strings to the object
                String ();
                // constructor, inits the inputed C-string to the object
                String (const char *init_str);
                // constructor, inits the inputed String to the object
                String (const String &init_str);
                // destructor, free memory to the heap
                ~String ();

            // basic functions
                // get the reference to the cstring in this object
                const Cstr &get_c_string () const;
                // get the length of the string, not counting the \\0
                size_t length () const;
                // get the pointer of char [] for old functions like printf
                const char *c_str () const;

            // assignment
                // copy the C-string in the parameter to this String
                String &assign     (const char *rhs);
                // copy the content of String in the parameter to this String
                String &assign     (const String rhs);
            // assignment operator
                // copy the C-string in the parameter to this String
                String &operator = (const char *rhs);
                // copy the content of String in the parameter to this String
                String &operator = (const String rhs);

            // comparison
                // compare the content of this String and the inputed C-string
                // return 1 if both content are the same, else 0
                bool    compare (const char *rhs) const;
                // compare the content of this String and the inputed String
                // return 1 if both content are the same, else 0
                bool    compare (const String rhs) const;
                // return 1 if this String is empty, else 0
                bool    empty () const;
                // return 1 if this String is empty, else 0
                bool    operator ! () const;
            // note: comparison operators are declared as non-method

            // sub-string
                // String substr (const size_t idx, size_t len) const {
                //     Cstr temp; str_actv(&temp); str_substr(&temp, &strbuf, idx, len);
                //     String to_return (temp.ptr); str_deactv(&temp); return to_return; }
                String substr (const size_t idx, size_t len) const;

            // start-with, end-with, contain
                // return 1 if this String starts with the inputed pattern, else 0
                bool    start_with (const char *cont) const;
                // return 1 if this String starts with the inputed pattern, else 0
                bool    start_with (const String cont) const;
                // return 1 if this String ends with the inputed pattern, else 0
                bool    end_with   (const char *cont) const;
                // return 1 if this String ends with the inputed pattern, else 0
                bool    end_with   (const String cont) const;
                // return 1 if this String contains the inputed pattern, else 0
                bool    contain    (const char *cont) const;
                // return 1 if this String contains the inputed pattern, else 0
                bool    contain    (const String cont) const;

            // indices
                // get the reference to the char of the inputed index
                      char &idx         (const size_t idx);
                // get the reference to the char of the inputed index for a const String
                const char &idx         (const size_t idx) const;
            // index operator
                // get the reference to the char of the inputed index
                      char &operator [] (const size_t idx);
                // get the reference to the char of the inputed index for a const String
                const char &operator [] (const size_t idx) const;

            // extra
                // get the reference to the first char in the String
                      char &front ();
                // get the reference to the first char in the const String
                const char &front () const;
                // get the reference to the last char in the String
                      char &back ();
                // get the reference to the last char in the const String
                const char &back () const;

            // push_front and pop_front
                // push the inputed char to be the first letter in the String
                      char  push_front (const char pushed);
                // remove and return the first letter in the String
                      char  pop_front  ();
            // push_back and pop_back
                // push the inputed char to be the last letter in the String
                      char  push_back (const char pushed);
                // remove and return the last letter in the String
                      char  pop_back ();
            // append
                // append the inputed C-string to this String
                    String &append (const char *app);
                // append the inputed String to this String
                    String &append (const String app);
            // appending operator
                // append the inputed C-string to this String
                    String &operator += (const char *app);
                // append the inputed String to this String
                    String &operator += (const String app);
            // joining
                    // String join (const char *rhs) { String temp (this->c_str()); return temp.append(rhs); }
                    String join (const char *rhs) const;
                    // String join (const String rhs) { return join(rhs.c_str()); }
                    String join (const String rhs) const;
            // note: addition operators are declared as non-method
                                        // String operator + (const char *rhs) { return this->join(rhs); }
                                        // String operator + (const String rhs) { return this->join(rhs); }

            // insert
                // insert the inputed C-string to this String before the letter of idx pointing to
                    String &insert (const size_t idx, const char *ins);
                // insert the inputed String to this String before the letter of idx pointing to
                    String &insert (const size_t idx, const String ins);
            // replace
                // replace a selected part of the string (from the letter of idx pointing to, count len words) to the inputed C-string
                    String &replace (const size_t idx, const size_t len, const char *rep);
                // replace a selected part of the string (from the letter of idx pointing to, count len words) to the inputed String
                    String &replace (const size_t idx, const size_t len, const String rep);
        };
        ENDOF_YH_CPP_STR_NAMESPACE
        namespace Func {
            namespace Strings {
            // comparison operators
            // compares left argument and right argument
                bool compare (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                bool compare (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs);
                bool compare (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                bool operator == (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                bool operator == (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs);
                bool operator == (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                bool operator != (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                bool operator != (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs);
                bool operator != (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);

            // addition operators
            // join 2 strings together
                YH::Lib YH_CPP_STR_NMSPCE::String join (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                YH::Lib YH_CPP_STR_NMSPCE::String join (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs);
                YH::Lib YH_CPP_STR_NMSPCE::String join (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                YH::Lib YH_CPP_STR_NMSPCE::String operator + (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
                YH::Lib YH_CPP_STR_NMSPCE::String operator + (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs);
                YH::Lib YH_CPP_STR_NMSPCE::String operator + (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs);
            }
        }
    }
}

using YH::Lib::Func::Strings::operator == ;
using YH::Lib::Func::Strings::operator != ;
using YH::Lib::Func::Strings::operator + ;

#endif // #if defined(__cplusplus)

#endif // #ifndef YHSTRLIB_HPP