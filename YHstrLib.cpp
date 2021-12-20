#ifndef YHSTRLIB_CPP
#define YHSTRLIB_CPP __DATE__ ", " __TIME__

#ifndef YHC_STRLIB_C
#include "YHc_strLib.c"
#endif // #ifndef YHC_STRLIB_C

const char YH::Lib::Func::c_strs::YHstrLib_vers [] = YHSTRLIB_CPP;

#ifdef __cplusplus
// constructors and destructors
YH::Lib YH_CPP_STR_NMSPCE::String::String ()                       { str_actv(&strbuf); }
YH::Lib YH_CPP_STR_NMSPCE::String::String (const char *init_str)   { str_actv(&strbuf); str_assign(&strbuf, init_str); }
YH::Lib YH_CPP_STR_NMSPCE::String::String (const String &init_str) { str_actv(&strbuf); str_assign(&strbuf, init_str.c_str()); }
YH::Lib YH_CPP_STR_NMSPCE::String::~String ()                      { str_deactv(&strbuf); }

// basic functions
const YH::Lib::Cstr &YH::Lib YH_CPP_STR_NMSPCE::String::get_c_string () const { return strbuf; }
size_t               YH::Lib YH_CPP_STR_NMSPCE::String::length       () const { return strbuf.len; }
const char *         YH::Lib YH_CPP_STR_NMSPCE::String::c_str        () const { return strbuf.ptr; }

// assignment
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::assign (const char *rhs)  { str_assign(&strbuf, rhs); return myself(); }
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::assign (const String rhs) { str_assign(&strbuf, rhs.c_str()); return myself(); }
// assignment operator
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::operator = (const char *rhs)  { return this->assign(rhs); }
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::operator = (const String rhs) { return this->assign(rhs); }

// comparison
bool YH::Lib YH_CPP_STR_NMSPCE::String::compare (const char *rhs)  const { return str_compare(&strbuf, rhs); }
bool YH::Lib YH_CPP_STR_NMSPCE::String::compare (const String rhs) const { return str_compare(&strbuf, rhs.c_str()); }
bool YH::Lib YH_CPP_STR_NMSPCE::String::empty   ()                 const { return strbuf.ptr[0] == '\0'; }
bool YH::Lib YH_CPP_STR_NMSPCE::String::operator ! ()              const { return this->empty(); }

// sub-string
YH::Lib YH_CPP_STR_NMSPCE::String YH::Lib YH_CPP_STR_NMSPCE::String::substr (const size_t idx, size_t len) const {
    YH::Lib::Cstr temp; str_actv(&temp); str_substr(&temp, &strbuf, idx, len);
    YH::Lib YH_CPP_STR_NMSPCE::String to_return (temp.ptr); str_deactv(&temp); return to_return;
}

// start-with, end-with, contain
bool YH::Lib YH_CPP_STR_NMSPCE::String::start_with (const char *cont)  const { return str_start_with(&strbuf, cont); }
bool YH::Lib YH_CPP_STR_NMSPCE::String::start_with (const String cont) const { return str_start_with(&strbuf, cont.c_str()); }
bool YH::Lib YH_CPP_STR_NMSPCE::String::end_with   (const char *cont)  const { return str_end_with(&strbuf, cont); }
bool YH::Lib YH_CPP_STR_NMSPCE::String::end_with   (const String cont) const { return str_end_with(&strbuf, cont.c_str()); }
bool YH::Lib YH_CPP_STR_NMSPCE::String::contain   (const char *cont)  const { return str_contain(&strbuf, cont); }
bool YH::Lib YH_CPP_STR_NMSPCE::String::contain   (const String cont) const { return str_contain(&strbuf, cont.c_str()); }

// indices
      char &YH::Lib YH_CPP_STR_NMSPCE::String::idx (size_t idx)       { return strbuf.ptr[idx]; }
const char &YH::Lib YH_CPP_STR_NMSPCE::String::idx (size_t idx) const { return strbuf.ptr[idx]; }
// index operator
      char &YH::Lib YH_CPP_STR_NMSPCE::String::operator [] (size_t idx)       { return this->idx(idx); }
const char &YH::Lib YH_CPP_STR_NMSPCE::String::operator [] (size_t idx) const { return this->idx(idx); }

// extra
      char &YH::Lib YH_CPP_STR_NMSPCE::String::front ()       { return strbuf.ptr[0]; }
const char &YH::Lib YH_CPP_STR_NMSPCE::String::front () const { return strbuf.ptr[0]; }
      char &YH::Lib YH_CPP_STR_NMSPCE::String::back  ()       { return strbuf.ptr[strbuf.len - 1]; }
const char &YH::Lib YH_CPP_STR_NMSPCE::String::back  () const { return strbuf.ptr[strbuf.len - 1]; }

// push-front and pop-front
char YH::Lib YH_CPP_STR_NMSPCE::String::push_front (const char pushed) { return str_pushfront(&strbuf, pushed); }
char YH::Lib YH_CPP_STR_NMSPCE::String::pop_front  ()                  { return str_popfront(&strbuf); }
// push-back and pop-back
char YH::Lib YH_CPP_STR_NMSPCE::String::push_back (const char pushed) { return str_pushback(&strbuf, pushed); }
char YH::Lib YH_CPP_STR_NMSPCE::String::pop_back  ()                  { return str_popback(&strbuf); }

// append
YH::Lib YH_CPP_STR_NMSPCE::String& YH::Lib YH_CPP_STR_NMSPCE::String::append  (const char *app)  { str_append(&strbuf, app); return myself(); }
YH::Lib YH_CPP_STR_NMSPCE::String& YH::Lib YH_CPP_STR_NMSPCE::String::append  (const String app) { str_append(&strbuf, app.c_str()); return myself(); }
// appending operator
YH::Lib YH_CPP_STR_NMSPCE::String& YH::Lib YH_CPP_STR_NMSPCE::String::operator +=  (const char *app)  { return this->append(app); }
YH::Lib YH_CPP_STR_NMSPCE::String& YH::Lib YH_CPP_STR_NMSPCE::String::operator +=  (const String app) { return this->append(app); }

// joining
YH::Lib YH_CPP_STR_NMSPCE::String  YH::Lib YH_CPP_STR_NMSPCE::String::join    (const char *rhs)  const { String temp (this->c_str()); return temp.append(rhs); }
YH::Lib YH_CPP_STR_NMSPCE::String  YH::Lib YH_CPP_STR_NMSPCE::String::join    (const String rhs) const { String temp (this->c_str()); return temp.append(rhs.c_str()); }

// insert
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::insert  (const size_t idx, const char *ins)  { str_insert(&strbuf, idx, ins); return myself(); }
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::insert  (const size_t idx, const String ins) { str_insert(&strbuf, idx, ins.c_str()); return myself(); }
// replace
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::replace (const size_t idx, const size_t len, const char *rep)  { str_replace (&strbuf, idx, len, rep); return myself(); }
YH::Lib YH_CPP_STR_NMSPCE::String &YH::Lib YH_CPP_STR_NMSPCE::String::replace (const size_t idx, const size_t len, const String rep) { str_replace (&strbuf, idx, len, rep.c_str()); return myself(); }

// non-method operators and their functions supporting behind

// comparison operators
bool YH::Lib::Func::Strings::compare (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return lhs.compare(rhs);
}
bool YH::Lib::Func::Strings::compare (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs) {
    return lhs.compare(rhs);
}
bool YH::Lib::Func::Strings::compare (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return rhs.compare(lhs);
}
bool YH::Lib::Func::Strings::operator == (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return compare(lhs, rhs);
}
bool YH::Lib::Func::Strings::operator == (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs) {
    return compare(lhs, rhs);
}
bool YH::Lib::Func::Strings::operator == (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return compare(lhs, rhs);
}
bool YH::Lib::Func::Strings::operator != (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return !compare(lhs, rhs);
}
bool YH::Lib::Func::Strings::operator != (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs) {
    return !compare(lhs, rhs);
}
bool YH::Lib::Func::Strings::operator != (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return !compare(lhs, rhs);
}

// addition operators
YH::Lib YH_CPP_STR_NMSPCE::String YH::Lib::Func::Strings::join (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return lhs.join(rhs);
}
YH::Lib YH_CPP_STR_NMSPCE::String YH::Lib::Func::Strings::join (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs) {
    return lhs.join(rhs);
}
YH::Lib YH_CPP_STR_NMSPCE::String YH::Lib::Func::Strings::join (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return ( (YH::Lib YH_CPP_STR_NMSPCE::String)(lhs) ).join(rhs);
}
YH::Lib YH_CPP_STR_NMSPCE::String YH::Lib::Func::Strings::operator + (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return join(lhs, rhs);
}
YH::Lib YH_CPP_STR_NMSPCE::String YH::Lib::Func::Strings::operator + (const YH::Lib YH_CPP_STR_NMSPCE::String &lhs, const char *rhs) {
    return join(lhs, rhs);
}
YH::Lib YH_CPP_STR_NMSPCE::String YH::Lib::Func::Strings::operator + (const char *lhs, const YH::Lib YH_CPP_STR_NMSPCE::String &rhs) {
    return join(lhs, rhs);
}
#endif // #ifdef __cplusplus

/*
int main (int argc, char **argv, char **envr) {
    String str1;
    String str2;
    String str3;
    str_actv(&str1);
    str_actv(&str2);
    str_actv(&str3);
    str_assign(&str1, "hello, world");
    str_assign(&str3, str_assign(&str2, str1.ptr)->ptr);
    printf("%d\n", str_compare(&str1, str2.ptr));
    str_insert(&str1, 0, "there ");
    printf("str1: %s\n", str1.ptr);
    str_assign(&str2, "123456789");
    str_replace(&str2, 4, 1, "abc");
    printf("str2: %s\n", str2.ptr);
    str_deactv(&str1);
    str_deactv(&str2);
    str_deactv(&str3);
    return 0;
}
*/

#endif // #ifndef YHSTRLIB_CPP