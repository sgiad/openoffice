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
#include "precompiled_sw.hxx"

#ifdef SW_DLLIMPLEMENTATION
#undef SW_DLLIMPLEMENTATION
#endif

#include <svx/svxdlg.hxx>
#include <svx/svxids.hrc>
#include <svx/dialogs.hrc>
#include <svl/itemset.hxx>
#include <svx/flagsdef.hxx>
#include <sfx2/tabdlg.hxx>
#include <svl/intitem.hxx>

#include "swtypes.hxx"
#include "uiborder.hxx"
#include "frmui.hrc"




SwBorderDlg::SwBorderDlg(Window* pParent, SfxItemSet& rSet, sal_uInt16 nType) :

	SfxSingleTabDialog(pParent, rSet, 0)

{
	SetText(SW_RESSTR(STR_FRMUI_BORDER));

	// TabPage erzeugen
	SfxAbstractDialogFactory* pFact = SfxAbstractDialogFactory::Create();
    DBG_ASSERT(pFact, "Dialogdiet fail!");
	::CreateTabPage fnCreatePage = pFact->GetTabPageCreatorFunc( RID_SVXPAGE_BORDER );
	if ( fnCreatePage )
	{
        SfxTabPage* pNewPage = (*fnCreatePage)( this, rSet );
		SfxAllItemSet aSet(*(rSet.GetPool()));
		aSet.Put (SfxUInt16Item(SID_SWMODE_TYPE,nType));
		if(SW_BORDER_MODE_TABLE == nType)
			aSet.Put (SfxUInt32Item(SID_FLAG_TYPE,SVX_HIDESHADOWCTL));
        pNewPage->PageCreated(aSet);
        SetTabPage(pNewPage);
	}
}



SwBorderDlg::~SwBorderDlg()
{
}


