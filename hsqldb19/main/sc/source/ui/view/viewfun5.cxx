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
#include <com/sun/star/embed/XEmbedObjectClipboardCreator.hpp>
#include <com/sun/star/embed/Aspects.hpp>


#include <svx/unomodel.hxx>
#include <unotools/streamwrap.hxx>

//------------------------------------------------------------------

#include <svx/dbexch.hrc>
#include <svx/fmmodel.hxx>
#include <svx/svdetc.hxx>
#include <svx/svditer.hxx>
#include <svx/svdobj.hxx>
#include <svx/svdogrp.hxx>
#include <svx/svdouno.hxx>
#include <svx/svdoole2.hxx>
#include <svx/svdpage.hxx>
#include <sfx2/dispatch.hxx>
#include <sfx2/docfile.hxx>
#include <sot/clsids.hxx>
#include <sot/formats.hxx>
#include <sot/filelist.hxx>
#include <unotools/pathoptions.hxx>
#include <svl/ptitem.hxx>
#include <svl/stritem.hxx>
#include <svtools/transfer.hxx>
#include <vcl/graph.hxx>

#include <comphelper/storagehelper.hxx>
#include <comphelper/processfactory.hxx>

#include <sot/formats.hxx>
#define SOT_FORMATSTR_ID_STARCALC_CURRENT	SOT_FORMATSTR_ID_STARCALC_50

#include "viewfunc.hxx"
#include "docsh.hxx"
#include "drawview.hxx"
#include "impex.hxx"
#include "dbfunc.hxx"
#include "dbcolect.hxx"
#include "sc.hrc"
#include "filter.hxx"
#include "scextopt.hxx"
#include "tabvwsh.hxx"		//	wegen GetViewFrame
#include "compiler.hxx"

#include "asciiopt.hxx"
#include "scabstdlg.hxx"
#include "clipparam.hxx"
#include <vcl/msgbox.hxx>
#include <sfx2/viewfrm.hxx>
#include <svx/dbaexchange.hxx>

using namespace com::sun::star;

//------------------------------------------------------------------

sal_Bool ScViewFunc::PasteDataFormat( sal_uLong nFormatId,
					const uno::Reference<datatransfer::XTransferable>& rxTransferable,
					SCCOL nPosX, SCROW nPosY, Point* pLogicPos, sal_Bool bLink, sal_Bool bAllowDialogs )
{
    ScDocument* pDoc = GetViewData()->GetDocument();
    pDoc->SetPastingDrawFromOtherDoc( sal_True );

	Point aPos;						//	inserting position (1/100 mm)
	if (pLogicPos)
		aPos = *pLogicPos;
	else
	{
		//	inserting position isn't needed for text formats
		sal_Bool bIsTextFormat = ( ScImportExport::IsFormatSupported( nFormatId ) ||
								nFormatId == FORMAT_RTF );
		if ( !bIsTextFormat )
		{
			//	Window MapMode isn't drawing MapMode if DrawingLayer hasn't been created yet

			SCTAB nTab = GetViewData()->GetTabNo();
			long nXT = 0;
			for (SCCOL i=0; i<nPosX; i++)
				nXT += pDoc->GetColWidth(i,nTab);
			if (pDoc->IsNegativePage(nTab))
				nXT = -nXT;
			sal_uLong nYT = pDoc->GetRowHeight( 0, nPosY-1, nTab);
			aPos = Point( (long)(nXT * HMM_PER_TWIPS), (long)(nYT * HMM_PER_TWIPS) );
		}
	}

	TransferableDataHelper aDataHelper( rxTransferable );
	sal_Bool bRet = sal_False;

	//
	//	handle individual formats
	//

	if ( nFormatId == SOT_FORMATSTR_ID_EMBED_SOURCE ||
		 nFormatId == SOT_FORMATSTR_ID_LINK_SOURCE ||
		 nFormatId == SOT_FORMATSTR_ID_EMBED_SOURCE_OLE ||
		 nFormatId == SOT_FORMATSTR_ID_LINK_SOURCE_OLE ||
		 nFormatId == SOT_FORMATSTR_ID_EMBEDDED_OBJ_OLE )
	{
        uno::Reference < io::XInputStream > xStm;
        TransferableObjectDescriptor   aObjDesc;

		if( aDataHelper.GetTransferableObjectDescriptor( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR, aObjDesc ) &&
            aDataHelper.GetInputStream( nFormatId, xStm ) )
		{
            if ( aObjDesc.maClassName == SvGlobalName( SO3_SC_CLASSID_60 ) )
			{
                uno::Reference < embed::XStorage > xStore = ::comphelper::OStorageHelper::GetStorageFromInputStream( xStm );

                // mba: BaseURL doesn't make sense for clipboard
                // #i43716# Medium must be allocated with "new".
                // DoLoad stores the pointer and deletes it with the SfxObjectShell.
                SfxMedium* pMedium = new SfxMedium( xStore, String() );

                //  TODO/LATER: is it a problem that we don't support binary formats here?
				ScDocShellRef xDocShRef = new ScDocShell(SFX_CREATE_MODE_EMBEDDED);
                if (xDocShRef->DoLoad(pMedium))
				{
					ScDocument* pSrcDoc = xDocShRef->GetDocument();
					SCTAB nSrcTab = pSrcDoc->GetVisibleTab();
					if (!pSrcDoc->HasTable(nSrcTab))
						nSrcTab = 0;

					ScMarkData aSrcMark;
					aSrcMark.SelectOneTable( nSrcTab );			// for CopyToClip
					ScDocument* pClipDoc = new ScDocument( SCDOCMODE_CLIP );

                    SCCOL nFirstCol, nLastCol;
                    SCROW nFirstRow, nLastRow;
                    if ( pSrcDoc->GetDataStart( nSrcTab, nFirstCol, nFirstRow ) )
						pSrcDoc->GetCellArea( nSrcTab, nLastCol, nLastRow );
					else
				    {
						nFirstCol = nLastCol = 0;
						nFirstRow = nLastRow = 0;
                    }
                    ScClipParam aClipParam(ScRange(nFirstCol, nFirstRow, nSrcTab, nLastCol, nLastRow, nSrcTab), false);
                    pSrcDoc->CopyToClip(aClipParam, pClipDoc, &aSrcMark);
					ScGlobal::SetClipDocName( xDocShRef->GetTitle( SFX_TITLE_FULLNAME ) );

					SetCursor( nPosX, nPosY );
					Unmark();
					PasteFromClip( IDF_ALL, pClipDoc,
									PASTE_NOFUNC, sal_False, sal_False, sal_False, INS_NONE, IDF_NONE,
									bAllowDialogs );
					delete pClipDoc;
					bRet = sal_True;
				}

                xDocShRef->DoClose();
				xDocShRef.Clear();
			}
			else
			{
                ::rtl::OUString aName;
                uno::Reference < embed::XEmbeddedObject > xObj = GetViewData()->GetViewShell()->GetObjectShell()->
                        GetEmbeddedObjectContainer().InsertEmbeddedObject( xStm, aName );
                if ( xObj.is() )
				{
					// try to get the replacement image from the clipboard
					Graphic aGraphic;
					sal_uLong nGrFormat = 0;
// (wg. Selection Manager bei Trustet Solaris)
#ifndef SOLARIS
/*
                    if( aDataHelper.GetGraphic( SOT_FORMATSTR_ID_SVXB, aGraphic ) )
						nGrFormat = SOT_FORMATSTR_ID_SVXB;
					else if( aDataHelper.GetGraphic( FORMAT_GDIMETAFILE, aGraphic ) )
						nGrFormat = SOT_FORMAT_GDIMETAFILE;
					else if( aDataHelper.GetGraphic( FORMAT_BITMAP, aGraphic ) )
						nGrFormat = SOT_FORMAT_BITMAP;
*/
#endif

					// insert replacement image ( if there is one ) into the object helper
					if ( nGrFormat )
					{
						datatransfer::DataFlavor aDataFlavor;
						SotExchange::GetFormatDataFlavor( nGrFormat, aDataFlavor );
                    	PasteObject( aPos, xObj, &aObjDesc.maSize, &aGraphic, aDataFlavor.MimeType, aObjDesc.mnViewAspect );
					}
					else
                    	PasteObject( aPos, xObj, &aObjDesc.maSize );

					bRet = sal_True;
				}
				else
				{
					DBG_ERROR("Error in CreateAndLoad");
				}
			}
		}
		else
        {
//            uno::Reference < io::XInputStream > xStm;
//            TransferableObjectDescriptor    aObjDesc;

            if ( aDataHelper.GetTransferableObjectDescriptor( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR_OLE, aObjDesc ) )
			{
                ::rtl::OUString aName;
                uno::Reference < embed::XEmbeddedObject > xObj;

            	if ( aDataHelper.GetInputStream( SOT_FORMATSTR_ID_EMBED_SOURCE_OLE, xStm )
                  || aDataHelper.GetInputStream( SOT_FORMATSTR_ID_EMBEDDED_OBJ_OLE, xStm ) )
            	{
                	xObj = GetViewData()->GetDocShell()->GetEmbeddedObjectContainer().InsertEmbeddedObject( xStm, aName );
				}
				else
				{
					try
					{
						uno::Reference< embed::XStorage > xTmpStor = ::comphelper::OStorageHelper::GetTemporaryStorage();
						uno::Reference < embed::XEmbedObjectClipboardCreator > xClipboardCreator(
							::comphelper::getProcessServiceFactory()->createInstance( ::rtl::OUString(
											RTL_CONSTASCII_USTRINGPARAM("com.sun.star.embed.MSOLEObjectSystemCreator") ) ),
							uno::UNO_QUERY_THROW );

						embed::InsertedObjectInfo aInfo = xClipboardCreator->createInstanceInitFromClipboard(
															xTmpStor,
															::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM ( "DummyName" ) ),
															uno::Sequence< beans::PropertyValue >() );

						// TODO/LATER: in future InsertedObjectInfo will be used to get container related information
						// for example whether the object should be an iconified one
						xObj = aInfo.Object;
						if ( xObj.is() )
							GetViewData()->GetDocShell()->GetEmbeddedObjectContainer().InsertEmbeddedObject( xObj, aName );
					}
					catch( uno::Exception& )
					{}
				}

                if ( xObj.is() )
				{
					// try to get the replacement image from the clipboard
					Graphic aGraphic;
                    sal_uLong nGrFormat = 0;

// (wg. Selection Manager bei Trustet Solaris)
#ifndef SOLARIS
					if( aDataHelper.GetGraphic( SOT_FORMATSTR_ID_SVXB, aGraphic ) )
						nGrFormat = SOT_FORMATSTR_ID_SVXB;
					else if( aDataHelper.GetGraphic( FORMAT_GDIMETAFILE, aGraphic ) )
						nGrFormat = SOT_FORMAT_GDIMETAFILE;
					else if( aDataHelper.GetGraphic( FORMAT_BITMAP, aGraphic ) )
						nGrFormat = SOT_FORMAT_BITMAP;
#endif

					// insert replacement image ( if there is one ) into the object helper
					if ( nGrFormat )
					{
						datatransfer::DataFlavor aDataFlavor;
						SotExchange::GetFormatDataFlavor( nGrFormat, aDataFlavor );
                    	PasteObject( aPos, xObj, &aObjDesc.maSize, &aGraphic, aDataFlavor.MimeType, aObjDesc.mnViewAspect );
					}
					else
                    	PasteObject( aPos, xObj, &aObjDesc.maSize );

					// let object stay in loaded state after insertion
					SdrOle2Obj::Unload( xObj, embed::Aspects::MSOLE_CONTENT );
					bRet = sal_True;
				}
				else
				{
                    DBG_ERROR("Error creating external OLE object");
				}
			}
            //TODO/LATER: if format is not available, create picture
		}
	}
	else if ( nFormatId == SOT_FORMATSTR_ID_LINK )		// LINK is also in ScImportExport
	{
		bRet = PasteDDE( rxTransferable );
	}
	else if ( ScImportExport::IsFormatSupported( nFormatId ) || nFormatId == SOT_FORMAT_RTF )
	{
		if ( nFormatId == SOT_FORMAT_RTF && aDataHelper.HasFormat( SOT_FORMATSTR_ID_EDITENGINE ) )
		{
			//	use EditView's PasteSpecial / Drop
			PasteRTF( nPosX, nPosY, rxTransferable );
			bRet = sal_True;
		}
		else
		{
			ScAddress aCellPos( nPosX, nPosY, GetViewData()->GetTabNo() );
			ScImportExport aObj( GetViewData()->GetDocument(), aCellPos );

            ::rtl::OUString aStr;
			SotStorageStreamRef xStream;
			if ( aDataHelper.GetSotStorageStream( nFormatId, xStream ) && xStream.Is() )
                // mba: clipboard always must contain absolute URLs (could be from alien source)
                bRet = aObj.ImportStream( *xStream, String(), nFormatId );
			else if (nFormatId == FORMAT_STRING && aDataHelper.GetString( nFormatId, aStr ))
            {
                // Do CSV dialog if more than one line.
                sal_Int32 nDelim = aStr.indexOf('\n');
#if 0
                ::rtl::OString tmpStr = OUStringToOString( aStr,
                        RTL_TEXTENCODING_UTF8 );
                fprintf( stderr, "String is '%s' (%d) [%d]\n", tmpStr.getStr(),
                        tmpStr.getLength(), nDelim);
#endif
                if (nDelim >= 0 && nDelim != aStr.getLength () - 1)
                {
                    ScImportStringStream aStrm( aStr);
                    ScAbstractDialogFactory* pFact =
                        ScAbstractDialogFactory::Create();
                    AbstractScImportAsciiDlg *pDlg =
                        pFact->CreateScImportAsciiDlg( NULL, String(), &aStrm,
                                RID_SCDLG_ASCII);

                    if (pDlg->Execute() == RET_OK)
                    {
                        ScAsciiOptions aOptions;
                        pDlg->GetOptions( aOptions );
                        aObj.SetExtOptions( aOptions );

                        bRet = aObj.ImportString( aStr, nFormatId );

                        // TODO: what if (aObj.IsOverflow())
                        // Content was partially pasted, which can be undone by
                        // the user though.
                        if (aObj.IsOverflow())
                            bRet = sal_False;
                    }
                    else
                        bRet = sal_True;
                        // Yes, no failure, don't raise a "couldn't paste"
                        // dialog if user cancelled.
                    delete pDlg;
                }
                else
                    bRet = aObj.ImportString( aStr, nFormatId );
            }
			else if (nFormatId != FORMAT_STRING && aDataHelper.GetString( nFormatId, aStr ))
                bRet = aObj.ImportString( aStr, nFormatId );

			InvalidateAttribs();
			GetViewData()->UpdateInputHandler();
		}
	}
	else if (nFormatId == SOT_FORMATSTR_ID_SBA_DATAEXCHANGE)
	{
		//	import of database data into table

        const DataFlavorExVector& rVector = aDataHelper.GetDataFlavorExVector();
        if ( svx::ODataAccessObjectTransferable::canExtractObjectDescriptor(rVector) )
        {
            // transport the whole ODataAccessDescriptor as slot parameter
            svx::ODataAccessDescriptor aDesc = svx::ODataAccessObjectTransferable::extractObjectDescriptor(aDataHelper);
            uno::Any aDescAny;
            uno::Sequence<beans::PropertyValue> aProperties = aDesc.createPropertyValueSequence();
            aDescAny <<= aProperties;
            SfxUsrAnyItem aDataDesc(SID_SBA_IMPORT, aDescAny);

			ScDocShell* pDocSh = GetViewData()->GetDocShell();
			SCTAB nTab = GetViewData()->GetTabNo();

			ClickCursor(nPosX, nPosY, sal_False);				// set cursor position

			//	Creation of database area "Import1" isn't here, but in the DocShell
			//	slot execute, so it can be added to the undo action

			ScDBData* pDBData = pDocSh->GetDBData( ScRange(nPosX,nPosY,nTab), SC_DB_OLD, SC_DBSEL_KEEP );
			String sTarget;
			if (pDBData)
				sTarget = pDBData->GetName();
			else
			{
				ScAddress aCellPos( nPosX,nPosY,nTab );
				aCellPos.Format( sTarget, SCA_ABS_3D, pDoc, pDoc->GetAddressConvention() );
			}
			SfxStringItem aTarget(FN_PARAM_1, sTarget);

			sal_Bool bAreaIsNew = !pDBData;
			SfxBoolItem aAreaNew(FN_PARAM_2, bAreaIsNew);

			//	asynchronous, to avoid doing the whole import in drop handler
			SfxDispatcher& rDisp = GetViewData()->GetDispatcher();
			rDisp.Execute(SID_SBA_IMPORT, SFX_CALLMODE_ASYNCHRON,
                                        &aDataDesc, &aTarget, &aAreaNew, (void*)0 );

			bRet = sal_True;
		}
	}
	else if (nFormatId == SOT_FORMATSTR_ID_SBA_FIELDDATAEXCHANGE)
	{
		//	insert database field control

        if ( ::svx::OColumnTransferable::canExtractColumnDescriptor( aDataHelper.GetDataFlavorExVector(), CTF_COLUMN_DESCRIPTOR | CTF_CONTROL_EXCHANGE ) )
		{
			MakeDrawLayer();
			ScDrawView* pScDrawView = GetScDrawView();
            SdrObject* pObj = pScDrawView->CreateFieldControl( ::svx::OColumnTransferable::extractColumnDescriptor( aDataHelper ) );
			if (pObj)
			{
				Point aInsPos = aPos;
				Rectangle aRect(pObj->GetLogicRect());
				aInsPos.X() -= aRect.GetSize().Width()  / 2;
				aInsPos.Y() -= aRect.GetSize().Height() / 2;
				if ( aInsPos.X() < 0 ) aInsPos.X() = 0;
				if ( aInsPos.Y() < 0 ) aInsPos.Y() = 0;
				aRect.SetPos(aInsPos);
				pObj->SetLogicRect(aRect);

				if ( pObj->ISA(SdrUnoObj) )
					pObj->NbcSetLayer(SC_LAYER_CONTROLS);
				else
					pObj->NbcSetLayer(SC_LAYER_FRONT);
				if (pObj->ISA(SdrObjGroup))
				{
					SdrObjListIter aIter( *pObj, IM_DEEPWITHGROUPS );
					SdrObject* pSubObj = aIter.Next();
					while (pSubObj)
					{
						if ( pSubObj->ISA(SdrUnoObj) )
							pSubObj->NbcSetLayer(SC_LAYER_CONTROLS);
						else
							pSubObj->NbcSetLayer(SC_LAYER_FRONT);
						pSubObj = aIter.Next();
					}
				}

				pScDrawView->InsertObjectSafe(pObj, *pScDrawView->GetSdrPageView());

				GetViewData()->GetViewShell()->SetDrawShell( sal_True );
				bRet = sal_True;
			}
		}
	}
	else if (nFormatId == SOT_FORMAT_BITMAP || nFormatId == SOT_FORMATSTR_ID_PNG)
	{
		BitmapEx aBmpEx;
		if( aDataHelper.GetBitmapEx( FORMAT_BITMAP, aBmpEx ) )
			bRet = PasteBitmapEx( aPos, aBmpEx );
	}
	else if (nFormatId == SOT_FORMAT_GDIMETAFILE)
	{
		GDIMetaFile aMtf;
		if( aDataHelper.GetGDIMetaFile( FORMAT_GDIMETAFILE, aMtf ) )
			bRet = PasteMetaFile( aPos, aMtf );
	}
	else if (nFormatId == SOT_FORMATSTR_ID_SVXB)
	{
		SotStorageStreamRef xStm;
		if( aDataHelper.GetSotStorageStream( SOT_FORMATSTR_ID_SVXB, xStm ) )
		{
			Graphic aGraphic;
			*xStm >> aGraphic;
			bRet = PasteGraphic( aPos, aGraphic, EMPTY_STRING, EMPTY_STRING );
		}
	}
	else if ( nFormatId == SOT_FORMATSTR_ID_DRAWING )
	{
		SotStorageStreamRef xStm;
		if( aDataHelper.GetSotStorageStream( SOT_FORMATSTR_ID_DRAWING, xStm ) )
		{
			MakeDrawLayer();	// before loading model, so 3D factory has been created

			SvtPathOptions aPathOpt;
			String aPath = aPathOpt.GetPalettePath();

			ScDocShellRef aDragShellRef( new ScDocShell );
			aDragShellRef->DoInitNew(NULL);
			FmFormModel* pModel = new FmFormModel( aPath, NULL, aDragShellRef );

			pModel->GetItemPool().FreezeIdRanges();
			xStm->Seek(0);

			com::sun::star::uno::Reference< com::sun::star::io::XInputStream > xInputStream( new utl::OInputStreamWrapper( *xStm ) );
			SvxDrawingLayerImport( pModel, xInputStream );

			// set everything to right layer:
			sal_uLong nObjCount = 0;
			sal_uInt16 nPages = pModel->GetPageCount();
			for (sal_uInt16 i=0; i<nPages; i++)
			{
				SdrPage* pPage = pModel->GetPage(i);
				SdrObjListIter aIter( *pPage, IM_DEEPWITHGROUPS );
				SdrObject* pObject = aIter.Next();
				while (pObject)
				{
					if ( pObject->ISA(SdrUnoObj) )
						pObject->NbcSetLayer(SC_LAYER_CONTROLS);
					else
						pObject->NbcSetLayer(SC_LAYER_FRONT);
					pObject = aIter.Next();
				}

				nObjCount += pPage->GetObjCount();			// #105888# count group object only once
			}

			PasteDraw( aPos, pModel, (nObjCount > 1) );		// grouped if more than 1 object
			delete pModel;
			aDragShellRef->DoClose();
			bRet = sal_True;
		}
	}
    else if ( (nFormatId == SOT_FORMATSTR_ID_BIFF_5) || (nFormatId == SOT_FORMATSTR_ID_BIFF_8) )
	{
		//	do excel import into a clipboard document
        //TODO/MBA: testing
        uno::Reference < io::XInputStream > xStm;
        if( aDataHelper.GetInputStream( nFormatId, xStm ) )
		{
#if 0
			SotStorage aDest( "d:\\test.xls" );	// to see the file
			pStor->CopyTo( &aDest );
#endif
			ScDocument* pInsDoc = new ScDocument( SCDOCMODE_CLIP );
			SCTAB nSrcTab = 0;		// Biff5 in clipboard: always sheet 0
			pInsDoc->ResetClip( pDoc, nSrcTab );

            SfxMedium aMed;
            aMed.GetItemSet()->Put( SfxUsrAnyItem( SID_INPUTSTREAM, uno::makeAny( xStm ) ) );
            FltError eErr = ScFormatFilter::Get().ScImportExcel( aMed, pInsDoc, EIF_AUTO );
			if ( eErr == eERR_OK )
			{
				ScRange aSource;
				const ScExtDocOptions* pExtOpt = pInsDoc->GetExtDocOptions();
                const ScExtTabSettings* pTabSett = pExtOpt ? pExtOpt->GetTabSettings( nSrcTab ) : 0;
                if( pTabSett && pTabSett->maUsedArea.IsValid() )
				{
                    aSource = pTabSett->maUsedArea;
                    // ensure correct sheet indexes
                    aSource.aStart.SetTab( nSrcTab );
                    aSource.aEnd.SetTab( nSrcTab );
// #92240# don't use selection area: if cursor is moved in Excel after Copy, selection
// represents the new cursor position and not the copied area
				}
				else
				{
					DBG_ERROR("no dimension");	//!	possible?
                    SCCOL nFirstCol, nLastCol;
                    SCROW nFirstRow, nLastRow;
                    if ( pInsDoc->GetDataStart( nSrcTab, nFirstCol, nFirstRow ) )
						pInsDoc->GetCellArea( nSrcTab, nLastCol, nLastRow );
					else
					{
						nFirstCol = nLastCol = 0;
						nFirstRow = nLastRow = 0;
					}
					aSource = ScRange( nFirstCol, nFirstRow, nSrcTab,
										nLastCol, nLastRow, nSrcTab );
				}

				if ( pLogicPos )
				{
					// position specified (Drag&Drop) - change selection
					MoveCursorAbs( nPosX, nPosY, SC_FOLLOW_NONE, sal_False, sal_False );
					Unmark();
				}

				pInsDoc->SetClipArea( aSource );
				PasteFromClip( IDF_ALL, pInsDoc,
								PASTE_NOFUNC, sal_False, sal_False, sal_False, INS_NONE, IDF_NONE,
								bAllowDialogs );
				delete pInsDoc;

				bRet = sal_True;
			}
		}
	}
	else if ( nFormatId == SOT_FORMAT_FILE )
	{
        String aFile;
        if ( aDataHelper.GetString( nFormatId, aFile ) )
            bRet = PasteFile( aPos, aFile, bLink );
    }
    else if ( nFormatId == SOT_FORMAT_FILE_LIST )
    {
        FileList aFileList;
        if ( aDataHelper.GetFileList( nFormatId, aFileList ) )
        {
            sal_uLong nCount = aFileList.Count();
            for( sal_uLong i = 0; i < nCount ; i++ )
			{
                String aFile = aFileList.GetFile( i );

                PasteFile( aPos, aFile, bLink );
#if 0
				SfxStringItem aNameItem( FID_INSERT_FILE, aFile );
				SfxPointItem aPosItem( FN_PARAM_1, aPos );
				SfxDispatcher* pDisp =
					GetViewData()->GetViewShell()->GetViewFrame()->GetDispatcher();
				if (pDisp)
					pDisp->Execute( FID_INSERT_FILE, SFX_CALLMODE_ASYNCHRON,
										&aNameItem, &aPosItem, (void*)0 );
#endif

				aPos.X() += 400;
				aPos.Y() += 400;
			}
			bRet = sal_True;
		}
	}
	else if ( nFormatId == SOT_FORMATSTR_ID_SOLK ||
			  nFormatId == SOT_FORMATSTR_ID_UNIFORMRESOURCELOCATOR ||
			  nFormatId == SOT_FORMATSTR_ID_NETSCAPE_BOOKMARK ||
			  nFormatId == SOT_FORMATSTR_ID_FILEGRPDESCRIPTOR )
	{
		bRet = PasteBookmark( nFormatId, rxTransferable, nPosX, nPosY );
	}

    pDoc->SetPastingDrawFromOtherDoc( sal_False );

	return bRet;
}

ByteString lcl_GetSubString( sal_Char* pData, long nStart, long nDataSize )
{
	if ( nDataSize <= nStart /* || pData[nDataSize] != 0 */ )
	{
		DBG_ERROR("DDE Data: invalid data");
		return ByteString();
	}
	return ByteString( pData + nStart );
}

sal_Bool ScViewFunc::PasteDDE( const uno::Reference<datatransfer::XTransferable>& rxTransferable )
{
	TransferableDataHelper aDataHelper( rxTransferable );

	//	get link data from transferable before string data,
	//	so the source knows it will be used for a link

	uno::Sequence<sal_Int8> aSequence;
	if ( !aDataHelper.GetSequence( SOT_FORMATSTR_ID_LINK, aSequence ) )
	{
		DBG_ERROR("DDE Data not found.");
		return sal_False;
	}

	//	check size (only if string is available in transferable)

	sal_uInt16 nCols = 1;
	sal_uInt16 nRows = 1;
	if ( aDataHelper.HasFormat( SOT_FORMAT_STRING ) )
	{
		String aDataStr;
		if ( aDataHelper.GetString( SOT_FORMAT_STRING, aDataStr ) )
		{
			//	get size from string the same way as in ScDdeLink::DataChanged

			aDataStr.ConvertLineEnd(LINEEND_LF);
			xub_StrLen nLen = aDataStr.Len();
			if (nLen && aDataStr.GetChar(nLen-1) == '\n')
				aDataStr.Erase(nLen-1);

			if (aDataStr.Len())
			{
				nRows = aDataStr.GetTokenCount( '\n' );
				String aLine = aDataStr.GetToken( 0, '\n' );
				if (aLine.Len())
					nCols = aLine.GetTokenCount( '\t' );
			}
		}
	}

	//	create formula

	long nSeqLen = aSequence.getLength();
	sal_Char* pData = (sal_Char*)aSequence.getConstArray();

	rtl_TextEncoding eSysEnc = gsl_getSystemTextEncoding();

    ByteString aByteApp   = lcl_GetSubString( pData, 0, nSeqLen );
    ByteString aByteTopic = lcl_GetSubString( pData, aByteApp.Len() + 1, nSeqLen );
    ByteString aByteItem  = lcl_GetSubString( pData, aByteApp.Len() + aByteTopic.Len() + 2, nSeqLen );

    String aApp( aByteApp, eSysEnc );
    String aTopic( aByteTopic, eSysEnc );
    String aItem( aByteItem, eSysEnc );

    // TODO: we could define ocQuote for "
    const String aQuote( '"' );
    const String& sSep = ScCompiler::GetNativeSymbol( ocSep);
    String aFormula( '=' );
    aFormula += ScCompiler::GetNativeSymbol( ocDde);
    aFormula += ScCompiler::GetNativeSymbol( ocOpen);
    aFormula += aQuote;
    aFormula += aApp;
    aFormula += aQuote;
    aFormula += sSep;
    aFormula += aQuote;
    aFormula += aTopic;
    aFormula += aQuote;
    aFormula += sSep;
    aFormula += aQuote;
    aFormula += aItem;
    aFormula += aQuote;
    aFormula += ScCompiler::GetNativeSymbol( ocClose);

	//	mark range

	SCTAB nTab = GetViewData()->GetTabNo();
	SCCOL nCurX = GetViewData()->GetCurX();
	SCROW nCurY = GetViewData()->GetCurY();
	HideAllCursors();
	DoneBlockMode();
	InitBlockMode( nCurX, nCurY, nTab );
	MarkCursor( nCurX+static_cast<SCCOL>(nCols)-1, nCurY+static_cast<SCROW>(nRows)-1, nTab );
	ShowAllCursors();

	//	enter formula

	EnterMatrix( aFormula );
	CursorPosChanged();

	return sal_True;
}


