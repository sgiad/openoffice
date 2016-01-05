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
#include "precompiled_sc.hxx"

// -----------------------------------------------------------------------



// INCLUDE ---------------------------------------------------------------

#include "refundo.hxx"
#include "undobase.hxx"
#include "document.hxx"
#include "dbcolect.hxx"
#include "rangenam.hxx"
#include "pivot.hxx"
#include "chartarr.hxx"
#include "stlpool.hxx"
#include "conditio.hxx"
#include "detdata.hxx"
#include "prnsave.hxx"
#include "chartlis.hxx"
#include "dpobject.hxx"
#include "areasave.hxx"
#include "unoreflist.hxx"

// -----------------------------------------------------------------------

ScRefUndoData::ScRefUndoData( const ScDocument* pDoc ) :
    pUnoRefs( NULL )
{
	ScDBCollection* pOldDBColl = pDoc->GetDBCollection();
	pDBCollection = pOldDBColl ? new ScDBCollection(*pOldDBColl) : NULL;

	ScRangeName* pOldRanges = ((ScDocument*)pDoc)->GetRangeName();			//! const
	pRangeName = pOldRanges ? new ScRangeName(*pOldRanges) : NULL;

	pPrintRanges = pDoc->CreatePrintRangeSaver();		// neu erzeugt

	//!	bei Pivot nur Bereiche merken ???

	ScDPCollection* pOldDP = ((ScDocument*)pDoc)->GetDPCollection();		//! const
	pDPCollection = pOldDP ? new ScDPCollection(*pOldDP) : NULL;

	ScConditionalFormatList* pOldCond = pDoc->GetCondFormList();
	pCondFormList = pOldCond ? new ScConditionalFormatList(*pOldCond) : NULL;

	ScDetOpList* pOldDetOp = pDoc->GetDetOpList();
	pDetOpList = pOldDetOp ? new ScDetOpList(*pOldDetOp) : 0;

	ScChartListenerCollection* pOldChartListenerCollection =
		pDoc->GetChartListenerCollection();
	pChartListenerCollection = pOldChartListenerCollection ?
		new ScChartListenerCollection( *pOldChartListenerCollection ) : NULL;

	pAreaLinks = ScAreaLinkSaveCollection::CreateFromDoc(pDoc);		// returns NULL if empty

    const_cast<ScDocument*>(pDoc)->BeginUnoRefUndo();
}

ScRefUndoData::~ScRefUndoData()
{
	delete pDBCollection;
	delete pRangeName;
	delete pPrintRanges;
	delete pDPCollection;
	delete pCondFormList;
	delete pDetOpList;
	delete pChartListenerCollection;
	delete pAreaLinks;
    delete pUnoRefs;
}

void ScRefUndoData::DeleteUnchanged( const ScDocument* pDoc )
{
	if (pDBCollection)
	{
		ScDBCollection* pNewDBColl = pDoc->GetDBCollection();
		if ( pNewDBColl && *pDBCollection == *pNewDBColl )
			DELETEZ(pDBCollection);
	}
	if (pRangeName)
	{
		ScRangeName* pNewRanges = ((ScDocument*)pDoc)->GetRangeName();		//! const
		if ( pNewRanges && *pRangeName == *pNewRanges )
			DELETEZ(pRangeName);
	}

	if (pPrintRanges)
	{
		ScPrintRangeSaver* pNewRanges = pDoc->CreatePrintRangeSaver();
		if ( pNewRanges && *pPrintRanges == *pNewRanges )
			DELETEZ(pPrintRanges);
		delete pNewRanges;
	}

	if (pDPCollection)
	{
		ScDPCollection* pNewDP = ((ScDocument*)pDoc)->GetDPCollection();	//! const
		if ( pNewDP && pDPCollection->RefsEqual(*pNewDP) )
			DELETEZ(pDPCollection);
	}

	if (pCondFormList)
	{
		ScConditionalFormatList* pNewCond = pDoc->GetCondFormList();
		if ( pNewCond && *pCondFormList == *pNewCond )
			DELETEZ(pCondFormList);
	}

	if (pDetOpList)
	{
		ScDetOpList* pNewDetOp = pDoc->GetDetOpList();
		if ( pNewDetOp && *pDetOpList == *pNewDetOp )
			DELETEZ(pDetOpList);
	}

	if ( pChartListenerCollection )
	{
		ScChartListenerCollection* pNewChartListenerCollection =
			pDoc->GetChartListenerCollection();
		if ( pNewChartListenerCollection &&
				*pChartListenerCollection == *pNewChartListenerCollection )
			DELETEZ( pChartListenerCollection );
	}

	if (pAreaLinks)
	{
		if ( pAreaLinks->IsEqual( pDoc ) )
			DELETEZ(pAreaLinks);
	}

    if ( pDoc->HasUnoRefUndo() )
    {
        pUnoRefs = const_cast<ScDocument*>(pDoc)->EndUnoRefUndo();
        if ( pUnoRefs && pUnoRefs->IsEmpty() )
        {
            DELETEZ( pUnoRefs );
        }
    }
}

void ScRefUndoData::DoUndo( ScDocument* pDoc, sal_Bool bUndoRefFirst )
{
	if (pDBCollection)
		pDoc->SetDBCollection( new ScDBCollection(*pDBCollection) );
	if (pRangeName)
		pDoc->SetRangeName( new ScRangeName(*pRangeName) );

	if (pPrintRanges)
		pDoc->RestorePrintRanges(*pPrintRanges);

	if (pDPCollection)
	{
		ScDPCollection* pDocDP = pDoc->GetDPCollection();
		if (pDocDP)
			pDPCollection->WriteRefsTo( *pDocDP );
	}

	if (pCondFormList)
		pDoc->SetCondFormList( new ScConditionalFormatList(*pCondFormList) );
	if (pDetOpList)
		pDoc->SetDetOpList( new ScDetOpList(*pDetOpList) );

	// #65055# bUndoRefFirst ist bSetChartRangeLists
	if ( pChartListenerCollection )
		pDoc->SetChartListenerCollection( new ScChartListenerCollection(
			*pChartListenerCollection ), bUndoRefFirst );

	if (pDBCollection || pRangeName)
	{
		sal_Bool bOldAutoCalc = pDoc->GetAutoCalc();
		pDoc->SetAutoCalc( sal_False );	// Mehrfachberechnungen vermeiden
		pDoc->CompileAll();
		pDoc->SetDirty();
		pDoc->SetAutoCalc( bOldAutoCalc );
	}

	if (pAreaLinks)
		pAreaLinks->Restore( pDoc );

    if ( pUnoRefs )
        pUnoRefs->Undo( pDoc );
}




