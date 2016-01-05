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


#include <swtypes.hxx>
#include <globals.hrc>
#include <misc.hrc>

#include <utlui.hrc>
#include <unotools.hrc>
#include <unoprnms.hxx>
#include <tools/debug.hxx>
#include <vcl/msgbox.hxx>
#include <com/sun/star/text/XTextViewCursorSupplier.hpp>
#include <com/sun/star/view/XScreenCursor.hpp>
#include <com/sun/star/view/DocumentZoomType.hpp>
#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#include <com/sun/star/style/XStyle.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/text/XText.hpp>
#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/awt/PosSize.hpp>
#include <com/sun/star/view/XViewSettingsSupplier.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <comphelper/processfactory.hxx>
#include <sfx2/dispatch.hxx>
#include <svl/stritem.hxx>
#include <shellio.hxx>
#include <docsh.hxx>
#include <view.hxx>
#include <wrtsh.hxx>
#include <swmodule.hxx>
#include <unocrsr.hxx>

#include "swrenamexnameddlg.hxx"


using namespace ::com::sun::star;
using ::rtl::OUString;

SwRenameXNamedDlg::SwRenameXNamedDlg( Window* pWin,
			uno::Reference< container::XNamed > & xN,
			uno::Reference< container::XNameAccess > & xNA ) :
	ModalDialog(pWin, SW_RES(DLG_RENAME_XNAMED)),
   aNameFL(this, SW_RES(FL_NAME)),
    aNewNameFT(this, SW_RES(FT_NEW_NAME)),
   aNewNameED(this, SW_RES(ED_NEW_NAME)),
   aOk(this, SW_RES(PB_OK)),
   aCancel(this, SW_RES(PB_CANCEL)),
   aHelp(this, SW_RES(PB_HELP)),
   xNamed(xN),
   xNameAccess(xNA)
{
	FreeResource();
	sRemoveWarning = String(SW_RES(STR_REMOVE_WARNING));

	String sTmp(GetText());
	aNewNameED.SetText(xNamed->getName());
    aNewNameED.SetSelection(Selection(SELECTION_MIN, SELECTION_MAX));
	sTmp += String(xNamed->getName());
	SetText(sTmp);

	aOk.SetClickHdl(LINK(this, SwRenameXNamedDlg, OkHdl));
	aNewNameED.SetModifyHdl(LINK(this, SwRenameXNamedDlg, ModifyHdl));
	aOk.Enable(sal_False);
}
/* -----------------09.06.99 15:34-------------------
 *
 * --------------------------------------------------*/
IMPL_LINK(SwRenameXNamedDlg, OkHdl, OKButton*, EMPTYARG)
{
	try
	{
		xNamed->setName(aNewNameED.GetText());
	}
	catch(uno::RuntimeException&)
	{
		DBG_ERROR("Name wurde nicht geaendert");
	}
	EndDialog(RET_OK);
	return 0;
}
/* -----------------09.06.99 15:48-------------------
 *
 * --------------------------------------------------*/
IMPL_LINK(SwRenameXNamedDlg, ModifyHdl, NoSpaceEdit*, pEdit)
{
	String sTmp(pEdit->GetText());

	// prevent from pasting illegal characters
	sal_uInt16 nLen = sTmp.Len();
	String sMsg;
	for(sal_uInt16 i = 0; i < pEdit->GetForbiddenChars().Len(); i++)
	{
		sal_uInt16 nTmpLen = sTmp.Len();
		sTmp.EraseAllChars(pEdit->GetForbiddenChars().GetChar(i));
		if(sTmp.Len() != nTmpLen)
			sMsg += pEdit->GetForbiddenChars().GetChar(i);
	}
	if(sTmp.Len() != nLen)
	{
		pEdit->SetText(sTmp);
		String sWarning(sRemoveWarning);
		sWarning += sMsg;
		InfoBox(this, sWarning).Execute();
	}

	aOk.Enable(sTmp.Len() && !xNameAccess->hasByName(sTmp)
	&& (!xSecondAccess.is() || !xSecondAccess->hasByName(sTmp))
	&& (!xThirdAccess.is() || !xThirdAccess->hasByName(sTmp))
	);
	return 0;
}
