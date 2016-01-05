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


#ifndef _SRCVIEW_HXX
#define _SRCVIEW_HXX

#include <sfx2/viewfac.hxx>
#include <sfx2/viewsh.hxx>
#include <vcl/outdev.hxx>

#include "srcedtw.hxx"
#include "shellid.hxx"

class SwDocShell;
class SvxSearchItem;
class SfxMedium;

/*--------------------------------------------------------------------
	Beschreibung:
 --------------------------------------------------------------------*/

class SwSrcView: public SfxViewShell
{
	SwSrcEditWindow 	aEditWin;

	SvxSearchItem*		pSearchItem;

	sal_Bool				bSourceSaved	:1;
    rtl_TextEncoding    eLoadEncoding;
    void                Init();

	// fuer Readonly-Umschaltung
	virtual void		Notify( SfxBroadcaster& rBC, const SfxHint& rHint );


protected:
	sal_uInt16 				StartSearchAndReplace(const SvxSearchItem& rItem,
														sal_Bool bFromStart,
														sal_Bool bApi,
														sal_Bool bRecursive = sal_False);


public:

	SFX_DECL_VIEWFACTORY(SwSrcView);
	SFX_DECL_INTERFACE(SW_SRC_VIEWSHELL)
	TYPEINFO();


	SwSrcView(SfxViewFrame* pFrame, SfxViewShell*);

	~SwSrcView();

	SwDocShell*			GetDocShell();
	SwSrcEditWindow&    GetEditWin() {return aEditWin;}
	void				SaveContent(const String& rTmpFile);
	void				SaveContentTo(SfxMedium& rMed);

	sal_Bool				IsModified() {return aEditWin.IsModified();}



	void			Execute(SfxRequest&);
	void			GetState(SfxItemSet&);

	SvxSearchItem* 	GetSearchItem();
	void 			SetSearchItem( const SvxSearchItem& rItem );

	void			Load(SwDocShell* pDocShell);

    virtual sal_uInt16  SetPrinter( SfxPrinter* pNew, sal_uInt16 nDiff = SFX_PRINTER_ALL, bool bIsAPI=false );
    virtual         SfxPrinter*     GetPrinter( sal_Bool bCreate = sal_False );
    
    sal_Int32       PrintSource( OutputDevice *pOutDev, sal_Int32 nPage, bool bCalcNumPagesOnly );

	void			SourceSaved() {bSourceSaved = sal_True;}
	sal_Bool			HasSourceSaved() const {return bSourceSaved;}

};


#endif





















