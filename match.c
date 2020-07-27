// Copyright 2020 Joshua J Baker. All rights reserved.
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

#include <string.h>
#include "match.h"

// match returns true if str matches pattern. This is a very
// simple wildcard match where '*' matches on any number characters
// and '?' matches on any one character.
//
// pattern:
//   { term }
// term:
// 	 '*'         matches any sequence of non-Separator characters
// 	 '?'         matches any single non-Separator character
// 	 c           matches character c (c != '*', '?')
bool match(const char *pat, int plen, const char *str, int slen)  {
    if (plen < 0) plen = strlen(pat);
    if (slen < 0) slen = strlen(str);
    while (plen > 0) {
        if (pat[0] == '*') {
            if (plen == 1) return true;
            if (match(pat+1, plen-1, str, slen)) return true;
            if (slen == 0) return false;
            str++; slen--;
        } else {
            if (slen == 0) return false;
            if (pat[0] != '?' && str[0] != pat[0]) return false;
            pat++; plen--;
            str++; slen--;
        }
    }
    return slen == 0 && plen == 0;
}

#ifdef MATCH_TEST

#include <assert.h>

int main() {
    assert( match("*"          , -1, "",            -1));
    assert( match(""           , -1, "",            -1));
    assert(!match(""           , -1, "hello world", -1));
    assert(!match("jello world", -1, "hello world", -1));
    assert( match("*"          , -1, "hello world", -1));
    assert( match("*world*"    , -1, "hello world", -1));
    assert( match("*world"     , -1, "hello world", -1));
    assert( match("hello*"     , -1, "hello world", -1));
    assert(!match("jello*"     , -1, "hello world", -1));
    assert( match("hello?world", -1, "hello world", -1));
    assert(!match("jello?world", -1, "hello world", -1));
    assert( match("he*o?world" , -1, "hello world", -1));
    assert( match("he*o?wor*"  , -1, "hello world", -1));
    assert( match("he*o?*r*"   , -1, "hello world", -1));
}

#endif