/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_i18npool.hxx"

// prevent internal compiler error with MSVC6SP3
#include <utility>

#define TRANSLITERATION_katakanaToHiragana
#include <transliteration_OneToOne.hxx>

namespace com { namespace sun { namespace star { namespace i18n {

// see http://charts.unicode.org/Web/U3040.html Hiragana (U+3040..U+309F)
// see http://charts.unicode.org/Web/U30A0.html Katakana (U+30A0..U+30FF)
static sal_Unicode toHiragana (const sal_Unicode c)
{
    if ( (0x30a1 <= c && c <= 0x30f6) || (0x30fd <= c && c <= 0x30ff) ) { // 30A0 - 30FF KATAKANA LETTER
        // shift code point by 0x0060
        return c - (0x30a0 - 0x3040);
    }
    return c;
}

katakanaToHiragana::katakanaToHiragana()
{
    func = toHiragana;
    table = 0;
    transliterationName = "katakanaToHiragana";
    implementationName = "com.sun.star.i18n.Transliteration.KATAKANA_HIRAGANA";
}

} } } }
