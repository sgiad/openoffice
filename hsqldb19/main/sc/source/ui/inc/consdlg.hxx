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



#ifndef SC_CONSDLG_HXX
#define SC_CONSDLG_HXX

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif
#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#ifndef _GROUP_HXX //autogen
#include <vcl/group.hxx>
#endif
#ifndef _MOREBTN_HXX //autogen
#include <vcl/morebtn.hxx>
#endif
#include "global.hxx"
#include "anyrefdg.hxx"

class ScViewData;
class ScDocument;
class ScRangeUtil;
class ScAreaData;


//============================================================================

class ScConsolidateDlg : public ScAnyRefDlg
{
public:
					ScConsolidateDlg( SfxBindings* pB, SfxChildWindow* pCW, Window* pParent,
									  const SfxItemSet&	rArgSet );
					~ScConsolidateDlg();

	virtual void	SetReference( const ScRange& rRef, ScDocument* pDoc );

	virtual sal_Bool	IsRefInputMode() const { return sal_True; }
	virtual void	SetActive();

	virtual sal_Bool	Close();

protected:
	virtual void	Deactivate();

private:
	FixedText		aFtFunc;
	ListBox			aLbFunc;

	FixedText		aFtConsAreas;
	MultiListBox	aLbConsAreas;

	ListBox			aLbDataArea;
	FixedText		aFtDataArea;
	formula::RefEdit		aEdDataArea;
	formula::RefButton		aRbDataArea;

	ListBox			aLbDestArea;
	FixedText		aFtDestArea;
	formula::RefEdit		aEdDestArea;
	formula::RefButton		aRbDestArea;

    FixedLine       aFlConsBy;
	CheckBox		aBtnByRow;
	CheckBox		aBtnByCol;

    FixedLine       aFlSep;
    FixedLine       aFlOptions;
	CheckBox		aBtnRefs;

	OKButton		aBtnOk;
	CancelButton	aBtnCancel;
	HelpButton		aBtnHelp;
	PushButton		aBtnAdd;
	PushButton		aBtnRemove;
	MoreButton		aBtnMore;

	String			aStrUndefined;

	ScConsolidateParam	theConsData;
	ScViewData*			pViewData;
	ScDocument*			pDoc;
	ScRangeUtil*		pRangeUtil;
	ScAreaData*			pAreaData;
	sal_uInt16				nAreaDataCount;
	sal_uInt16				nWhichCons;

	formula::RefEdit*			pRefInputEdit;
	sal_Bool				bDlgLostFocus;

#ifdef _CONSDLG_CXX
private:
	void Init				();
	void FillAreaLists		();
	sal_Bool VerifyEdit			( formula::RefEdit* pEd );

	DECL_LINK( OkHdl,		 void* );
	DECL_LINK( ClickHdl,	 PushButton* );
	DECL_LINK( GetFocusHdl, Control* );
	DECL_LINK( ModifyHdl,	 formula::RefEdit* );
	DECL_LINK( SelectHdl,	 ListBox* );

	ScSubTotalFunc	LbPosToFunc( sal_uInt16 nPos );
	sal_uInt16 			FuncToLbPos( ScSubTotalFunc eFunc );
#endif // _CONSDLG_CXX
};



#endif // SC_CONSDLG_HXX

