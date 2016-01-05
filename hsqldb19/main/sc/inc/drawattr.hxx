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


#ifndef _IDLITEMS_HXX
#define _IDLITEMS_HXX

#include <svl/eitem.hxx>
#include <editeng/svxenum.hxx>


class SvxDrawToolItem : public SfxEnumItem
{
public:

		SvxDrawToolItem( const SvxDrawToolItem& rDrawToolItem ) :
								SfxEnumItem( rDrawToolItem ){}

        SvxDrawToolItem(sal_uInt16 nWhichP) : SfxEnumItem(nWhichP){}


	virtual String      		GetValueText() const;


	virtual String				GetValueText(sal_uInt16 nVal) const;
	virtual sal_uInt16 				GetValueCount() const
									{return((sal_uInt16)SVX_SNAP_DRAW_TEXT);}

	virtual SfxPoolItem*    	Clone( SfxItemPool *pPool = 0 ) const;

	virtual SfxPoolItem*    	Create( SvStream& rStream, sal_uInt16 nVer ) const;

	inline SvxDrawToolItem& operator=(const  SvxDrawToolItem&
														rDrawTool)
			{
				SetValue( rDrawTool.GetValue() );
				return *this;

			}
};
#endif


