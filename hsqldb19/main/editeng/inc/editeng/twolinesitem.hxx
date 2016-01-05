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


#ifndef _SVX_TWOLINESITEM_HXX
#define _SVX_TWOLINESITEM_HXX

#include <sal/types.h>
#include <svl/poolitem.hxx>
#include <editeng/editengdllapi.h>

class SvXMLUnitConverter;
namespace rtl
{
	class OUString;
}

class EDITENG_DLLPUBLIC SvxTwoLinesItem : public SfxPoolItem
{
	sal_Unicode	cStartBracket, cEndBracket;
	sal_Bool bOn;
public:
	TYPEINFO();
    SvxTwoLinesItem( sal_Bool bOn /*= sal_True*/,
                     sal_Unicode nStartBracket /*= 0*/,
                     sal_Unicode nEndBracket /*= 0*/,
                     sal_uInt16 nId  );
	SvxTwoLinesItem( const SvxTwoLinesItem& rAttr );
	virtual ~SvxTwoLinesItem();

	// "pure virtual Methoden" vom SfxPoolItem
	virtual int             operator==( const SfxPoolItem& ) const;
	virtual SfxPoolItem*	Clone( SfxItemPool* pPool = 0 ) const;
	virtual SfxPoolItem*	Create(SvStream &, sal_uInt16 nVer) const;
	virtual SvStream&		Store(SvStream &, sal_uInt16 nIVer) const;
	virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
									SfxMapUnit eCoreMetric,
									SfxMapUnit ePresMetric,
									String &rText,
                                    const IntlWrapper* pIntl = 0 ) const;

	virtual	sal_Bool       	QueryValue( com::sun::star::uno::Any& rVal,
										sal_uInt8 nMemberId = 0 ) const;
	virtual	sal_Bool		PutValue( const com::sun::star::uno::Any& rVal,
										sal_uInt8 nMemberId = 0 );

	virtual sal_uInt16			GetVersion( sal_uInt16 nFFVer ) const;

	SvxTwoLinesItem& 		operator=( const SvxTwoLinesItem& rCpy )
	{
		SetValue( rCpy.GetValue() );
		SetStartBracket( rCpy.GetStartBracket() );
		SetEndBracket( rCpy.GetEndBracket() );
		return *this;
	}

	sal_Bool GetValue() const 					{ return bOn; }
	void SetValue( sal_Bool bFlag ) 			{ bOn = bFlag; }

	sal_Unicode GetStartBracket() const 		{ return cStartBracket; }
	void SetStartBracket( sal_Unicode c ) 		{ cStartBracket = c; }

	sal_Unicode GetEndBracket() const 			{ return cEndBracket; }
	void SetEndBracket( sal_Unicode c ) 		{ cEndBracket = c; }
};

#endif

