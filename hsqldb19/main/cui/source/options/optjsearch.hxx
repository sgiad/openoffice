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



#ifndef _SVX_OPTJSEARCH_HXX_
#define _SVX_OPTJSEARCH_HXX_

#include <vcl/fixed.hxx>
#ifndef _SV_BUTTON_HXX
#include <vcl/button.hxx>
#endif
#include <sfx2/tabdlg.hxx>

class Window;
class SfxItemSet;

//////////////////////////////////////////////////////////////////////

class SvxJSearchOptionsPage : public SfxTabPage
{
private:
	FixedLine	aTreatAsEqual;
	CheckBox	aMatchCase;
	CheckBox	aMatchFullHalfWidth;
	CheckBox	aMatchHiraganaKatakana;
	CheckBox	aMatchContractions;
	CheckBox	aMatchMinusDashChoon;
	CheckBox	aMatchRepeatCharMarks;
	CheckBox	aMatchVariantFormKanji;
	CheckBox	aMatchOldKanaForms;
	CheckBox	aMatchDiziDuzu;
	CheckBox	aMatchBavaHafa;
	CheckBox	aMatchTsithichiDhizi;
	CheckBox	aMatchHyuiyuByuvyu;
	CheckBox	aMatchSesheZeje;
	CheckBox	aMatchIaiya;
	CheckBox	aMatchKiku;
    CheckBox    aMatchProlongedSoundMark;
    FixedLine   aIgnore;
	CheckBox	aIgnorePunctuation;
	CheckBox	aIgnoreWhitespace;
    CheckBox    aIgnoreMiddleDot;

	sal_Int32		nTransliterationFlags;
	sal_Bool		bSaveOptions;

	sal_Int32				GetTransliterationFlags_Impl();

protected:
						SvxJSearchOptionsPage( Window* pParent, const SfxItemSet& rSet );

public:
						~SvxJSearchOptionsPage();

	static SfxTabPage*  Create( Window* pParent, const SfxItemSet& rSet );

	virtual void        Reset( const SfxItemSet& rSet );
	virtual sal_Bool        FillItemSet( SfxItemSet& rSet );

	sal_Bool				IsSaveOptions() const			{ return bSaveOptions; }
	void				EnableSaveOptions( sal_Bool bVal )	{ bSaveOptions = bVal; }

	sal_Int32				GetTransliterationFlags() const	{ return nTransliterationFlags; }
	void				SetTransliterationFlags( sal_Int32 nSettings );
};

//////////////////////////////////////////////////////////////////////

#endif

