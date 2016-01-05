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
#include "precompiled_svx.hxx"
#include <tools/shl.hxx>
#include <vcl/msgbox.hxx>
#include <sfx2/viewfrm.hxx>
#include <sfx2/viewsh.hxx>
#ifndef _SFXOBJSH_HXX
#include <sfx2/objsh.hxx>
#endif
#include <sfx2/request.hxx>

#include <svx/dialmgr.hxx>
#include <svx/grfflt.hxx>
//#include "grfflt.hrc"
#include <svx/dialogs.hrc>
#include <svx/svxdlg.hxx> //CHINA001

// --------------------
// - SvxGraphicFilter -
// --------------------

sal_uIntPtr SvxGraphicFilter::ExecuteGrfFilterSlot( SfxRequest& rReq, GraphicObject& rFilterObject )
{
	const Graphic&	rGraphic = rFilterObject.GetGraphic();
	sal_uIntPtr			nRet = SVX_GRAPHICFILTER_UNSUPPORTED_GRAPHICTYPE;

	if( rGraphic.GetType() == GRAPHIC_BITMAP )
	{
		SfxViewFrame*	pViewFrame = SfxViewFrame::Current();
		SfxObjectShell*	pShell = pViewFrame ? pViewFrame->GetObjectShell() : NULL;
		Window*			pWindow = ( pViewFrame && pViewFrame->GetViewShell() ) ? pViewFrame->GetViewShell()->GetWindow() : NULL;
		Graphic			aGraphic;

		switch( rReq.GetSlot() )
		{
			case( SID_GRFFILTER_INVERT ):
			{
				if( pShell )
					pShell->SetWaitCursor( sal_True );

				if( rGraphic.IsAnimated() )
				{
					Animation aAnimation( rGraphic.GetAnimation() );

					if( aAnimation.Invert() )
						aGraphic = aAnimation;
				}
				else
				{
					BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

					if( aBmpEx.Invert() )
						aGraphic = aBmpEx;
				}

				if( pShell )
					pShell->SetWaitCursor( sal_False );
			}
			break;

			case( SID_GRFFILTER_SMOOTH ):
			{
				if( pShell )
					pShell->SetWaitCursor( sal_True );

				if( rGraphic.IsAnimated() )
				{
					Animation aAnimation( rGraphic.GetAnimation() );

					if( aAnimation.Filter( BMP_FILTER_SMOOTH ) )
						aGraphic = aAnimation;
				}
				else
				{
					BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

					if( aBmpEx.Filter( BMP_FILTER_SMOOTH ) )
						aGraphic = aBmpEx;
				}

				if( pShell )
					pShell->SetWaitCursor( sal_False );
			}
			break;

			case( SID_GRFFILTER_SHARPEN ):
			{
				if( pShell )
					pShell->SetWaitCursor( sal_True );

				if( rGraphic.IsAnimated() )
				{
					Animation aAnimation( rGraphic.GetAnimation() );

					if( aAnimation.Filter( BMP_FILTER_SHARPEN ) )
						aGraphic = aAnimation;
				}
				else
				{
					BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

					if( aBmpEx.Filter( BMP_FILTER_SHARPEN ) )
						aGraphic = aBmpEx;
				}

				if( pShell )
					pShell->SetWaitCursor( sal_False );
			}
			break;

			case( SID_GRFFILTER_REMOVENOISE ):
			{
				if( pShell )
					pShell->SetWaitCursor( sal_True );

				if( rGraphic.IsAnimated() )
				{
					Animation aAnimation( rGraphic.GetAnimation() );

					if( aAnimation.Filter( BMP_FILTER_REMOVENOISE ) )
						aGraphic = aAnimation;
				}
				else
				{
					BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

					if( aBmpEx.Filter( BMP_FILTER_REMOVENOISE ) )
						aGraphic = aBmpEx;
				}

				if( pShell )
					pShell->SetWaitCursor( sal_False );
			}
			break;

			case( SID_GRFFILTER_SOBEL ):
			{
				if( pShell )
					pShell->SetWaitCursor( sal_True );

				if( rGraphic.IsAnimated() )
				{
					Animation aAnimation( rGraphic.GetAnimation() );

					if( aAnimation.Filter( BMP_FILTER_SOBEL_GREY ) )
						aGraphic = aAnimation;
				}
				else
				{
					BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

					if( aBmpEx.Filter( BMP_FILTER_SOBEL_GREY ) )
						aGraphic = aBmpEx;
				}

				if( pShell )
					pShell->SetWaitCursor( sal_False );
			}
			break;

			case( SID_GRFFILTER_MOSAIC ):
			{
				//CHINA001 GraphicFilterMosaic aDlg( pWindow, rGraphic, 4, 4, sal_False );
				SvxAbstractDialogFactory* pFact = SvxAbstractDialogFactory::Create();
				if(pFact)
				{
					AbstractGraphicFilterDialog* aDlg = pFact->CreateGraphicFilterMosaic( pWindow, rGraphic, 4, 4, sal_False, RID_SVX_GRFFILTER_DLG_MOSAIC);
					DBG_ASSERT(aDlg, "Dialogdiet fail!");//CHINA001
					if( aDlg->Execute() == RET_OK ) //CHINA001 if( aDlg.Execute() == RET_OK )
						aGraphic = aDlg->GetFilteredGraphic( rGraphic, 1.0, 1.0 ); //CHINA001 aGraphic = aDlg.GetFilteredGraphic( rGraphic, 1.0, 1.0 );
					delete aDlg; //add by CHINA001
				}
			}
			break;

			case( SID_GRFFILTER_EMBOSS	):
			{
				//CHINA001 GraphicFilterEmboss aDlg( pWindow, rGraphic, RP_MM );
				SvxAbstractDialogFactory* pFact = SvxAbstractDialogFactory::Create();
				if(pFact)
				{
					AbstractGraphicFilterDialog* aDlg = pFact->CreateGraphicFilterEmboss( pWindow, rGraphic, RP_MM, RID_SVX_GRFFILTER_DLG_EMBOSS );
					DBG_ASSERT(aDlg, "Dialogdiet fail!");//CHINA001
					if( aDlg->Execute() == RET_OK ) //CHINA001 if( aDlg.Execute() == RET_OK )
						aGraphic = aDlg->GetFilteredGraphic( rGraphic, 1.0, 1.0 ); //CHINA001 aGraphic = aDlg.GetFilteredGraphic( rGraphic, 1.0, 1.0 );
					delete aDlg; //add by CHINA001
				}
			}
			break;

			case( SID_GRFFILTER_POSTER	):
			{
				//CHINA001 GraphicFilterPoster aDlg( pWindow, rGraphic, 16 );
				SvxAbstractDialogFactory* pFact = SvxAbstractDialogFactory::Create();
				if(pFact)
				{
					AbstractGraphicFilterDialog* aDlg = pFact->CreateGraphicFilterPosterSepia( pWindow, rGraphic, 16, RID_SVX_GRFFILTER_DLG_POSTER );
					DBG_ASSERT(aDlg, "Dialogdiet fail!");//CHINA001
					if( aDlg->Execute() == RET_OK ) //CHINA001 if( aDlg.Execute() == RET_OK )
						aGraphic = aDlg->GetFilteredGraphic( rGraphic, 1.0, 1.0 ); //CHINA001 aGraphic = aDlg.GetFilteredGraphic( rGraphic, 1.0, 1.0 );
					delete aDlg; //add by CHINA001
				}
			}
			break;

			case( SID_GRFFILTER_POPART	):
			{
				if( pShell )
					pShell->SetWaitCursor( sal_True );

				if( rGraphic.IsAnimated() )
				{
					Animation aAnimation( rGraphic.GetAnimation() );

					if( aAnimation.Filter( BMP_FILTER_POPART ) )
						aGraphic = aAnimation;
				}
				else
				{
					BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

					if( aBmpEx.Filter( BMP_FILTER_POPART ) )
						aGraphic = aBmpEx;
				}

				if( pShell )
					pShell->SetWaitCursor( sal_False );
			}
			break;

			case( SID_GRFFILTER_SEPIA ):
			{
				//CHINA001 GraphicFilterSepia aDlg( pWindow, rGraphic, 10 );
				SvxAbstractDialogFactory* pFact = SvxAbstractDialogFactory::Create();
				if(pFact)
				{
					AbstractGraphicFilterDialog* aDlg = pFact->CreateGraphicFilterPosterSepia( pWindow, rGraphic, 10, RID_SVX_GRFFILTER_DLG_SEPIA );
					DBG_ASSERT(aDlg, "Dialogdiet fail!");//CHINA001
					if( aDlg->Execute() == RET_OK ) //CHINA001 if( aDlg.Execute() == RET_OK )
						aGraphic = aDlg->GetFilteredGraphic( rGraphic, 1.0, 1.0 ); //CHINA001 aGraphic = aDlg.GetFilteredGraphic( rGraphic, 1.0, 1.0 );
					delete aDlg; //add by CHINA001
				}
			}
			break;

			case( SID_GRFFILTER_SOLARIZE ):
			{
				//CHINA001 GraphicFilterSolarize aDlg( pWindow, rGraphic, 128, sal_False );
				SvxAbstractDialogFactory* pFact = SvxAbstractDialogFactory::Create();
				if(pFact)
				{
					AbstractGraphicFilterDialog* aDlg = pFact->CreateGraphicFilterSolarize( pWindow, rGraphic, 128, sal_False, RID_SVX_GRFFILTER_DLG_SOLARIZE );
					DBG_ASSERT(aDlg, "Dialogdiet fail!");//CHINA001
					if( aDlg->Execute() == RET_OK ) //CHINA001 if( aDlg.Execute() == RET_OK )
						aGraphic = aDlg->GetFilteredGraphic( rGraphic, 1.0, 1.0 ); //CHINA001 aGraphic = aDlg.GetFilteredGraphic( rGraphic, 1.0, 1.0 );
					delete aDlg; //add by CHINA001
				}
			}
			break;

            case SID_GRFFILTER :
            {
                // do nothing; no error
                nRet = SVX_GRAPHICFILTER_ERRCODE_NONE;
                break;
            }

			default:
			{
				DBG_ERROR( "SvxGraphicFilter: selected filter slot not yet implemented" );
				nRet = SVX_GRAPHICFILTER_UNSUPPORTED_SLOT;
			}
			break;
		}

		if( aGraphic.GetType() != GRAPHIC_NONE )
		{
			rFilterObject.SetGraphic( aGraphic );
			nRet = SVX_GRAPHICFILTER_ERRCODE_NONE;
		}
	}

	return nRet;
}

// -----------------------------------------------------------------------------

void SvxGraphicFilter::DisableGraphicFilterSlots( SfxItemSet& rSet )
{
	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER ) )
		rSet.DisableItem( SID_GRFFILTER );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_INVERT ) )
		rSet.DisableItem( SID_GRFFILTER_INVERT );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_SMOOTH ) )
		rSet.DisableItem( SID_GRFFILTER_SMOOTH );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_SHARPEN ) )
		rSet.DisableItem( SID_GRFFILTER_SHARPEN );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_REMOVENOISE ) )
		rSet.DisableItem( SID_GRFFILTER_REMOVENOISE );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_SOBEL ) )
		rSet.DisableItem( SID_GRFFILTER_SOBEL );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_MOSAIC ) )
		rSet.DisableItem( SID_GRFFILTER_MOSAIC );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_EMBOSS ) )
		rSet.DisableItem( SID_GRFFILTER_EMBOSS );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_POSTER ) )
		rSet.DisableItem( SID_GRFFILTER_POSTER );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_POPART ) )
		rSet.DisableItem( SID_GRFFILTER_POPART );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_SEPIA ) )
		rSet.DisableItem( SID_GRFFILTER_SEPIA );

	if( SFX_ITEM_AVAILABLE <= rSet.GetItemState( SID_GRFFILTER_SOLARIZE ) )
		rSet.DisableItem( SID_GRFFILTER_SOLARIZE );
};
/* CHINA001 move to cuigrfflt.cxx
// --------------------------------------
// - GraphicFilterDialog::PreviewWindow -
// --------------------------------------

GraphicFilterDialog::PreviewWindow::PreviewWindow( Window* pParent, const ResId& rResId ) :
	Control( pParent, rResId )
{
}

// -----------------------------------------------------------------------------

GraphicFilterDialog::PreviewWindow::~PreviewWindow()
{
}

// -----------------------------------------------------------------------------

void GraphicFilterDialog::PreviewWindow::Paint( const Rectangle& rRect )
{
	Control::Paint( rRect );

	const Size	aGrfSize( LogicToPixel( maGraphic.GetPrefSize(), maGraphic.GetPrefMapMode() ) );
	const Size	aOutSize( GetOutputSizePixel() );
	const Point aGrfPos( ( aOutSize.Width() - aGrfSize.Width() ) >> 1,
						 ( aOutSize.Height() - aGrfSize.Height() ) >> 1 );

	if( maGraphic.IsAnimated() )
		maGraphic.StartAnimation( this , aGrfPos, aGrfSize );
	else
		maGraphic.Draw( this, aGrfPos, aGrfSize );
}

// -----------------------------------------------------------------------------

void GraphicFilterDialog::PreviewWindow::SetGraphic( const Graphic& rGraphic )
{
	maGraphic = rGraphic;

	if( maGraphic.IsAnimated() || maGraphic.IsTransparent() )
		Invalidate();
	else
		Paint( Rectangle( Point(), GetOutputSizePixel() ) );
}

// -----------------------
// - GraphicFilterDialog -
// -----------------------

GraphicFilterDialog::GraphicFilterDialog( Window* pParent, const ResId& rResId, const Graphic& rGraphic ) :
	ModalDialog		( pParent, rResId ),
	mfScaleX		( 0.0 ),
	mfScaleY		( 0.0 ),
	maSizePixel		( LogicToPixel( rGraphic.GetPrefSize(), rGraphic.GetPrefMapMode() ) ),
	maModifyHdl		( LINK( this, GraphicFilterDialog, ImplModifyHdl ) ),
	maPreview		( this, SVX_RES( CTL_PREVIEW ) ),
	maFlParameter	( this, SVX_RES( FL_PARAMETER ) ),
	maBtnOK			( this, SVX_RES( BTN_OK ) ),
	maBtnCancel		( this, SVX_RES( BTN_CANCEL ) ),
	maBtnHelp		( this, SVX_RES( BTN_HELP ) )
{
	const Size	aPreviewSize( maPreview.GetOutputSizePixel() );
	Size		aGrfSize( maSizePixel );

	if( rGraphic.GetType() == GRAPHIC_BITMAP &&
		aPreviewSize.Width() && aPreviewSize.Height() &&
		aGrfSize.Width() && aGrfSize.Height() )
	{
		const double fGrfWH = (double) aGrfSize.Width() / aGrfSize.Height();
		const double fPreWH = (double) aPreviewSize.Width() / aPreviewSize.Height();

		if( fGrfWH < fPreWH )
		{
			aGrfSize.Width() = (long) ( aPreviewSize.Height() * fGrfWH );
			aGrfSize.Height()= aPreviewSize.Height();
		}
		else
		{
			aGrfSize.Width() = aPreviewSize.Width();
			aGrfSize.Height()= (long) ( aPreviewSize.Width() / fGrfWH);
		}

		mfScaleX = (double) aGrfSize.Width() / maSizePixel.Width();
		mfScaleY = (double) aGrfSize.Height() / maSizePixel.Height();

		if( !rGraphic.IsAnimated() )
		{
			BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

			if( aBmpEx.Scale( aGrfSize, BMP_SCALE_INTERPOLATE ) )
				maGraphic = aBmpEx;
		}
	}

	maTimer.SetTimeoutHdl( LINK( this, GraphicFilterDialog, ImplPreviewTimeoutHdl ) );
	maTimer.SetTimeout( 100 );
	ImplModifyHdl( NULL );
}

// -----------------------------------------------------------------------------

GraphicFilterDialog::~GraphicFilterDialog()
{
}

// -----------------------------------------------------------------------------

IMPL_LINK( GraphicFilterDialog, ImplPreviewTimeoutHdl, Timer*, pTimer )
{
	maTimer.Stop();
	maPreview.SetGraphic( GetFilteredGraphic( maGraphic, mfScaleX, mfScaleY ) );

	return 0;
}

// -----------------------------------------------------------------------------

IMPL_LINK( GraphicFilterDialog, ImplModifyHdl, void*, p )
{
	if( maGraphic.GetType() == GRAPHIC_BITMAP )
	{
		maTimer.Stop();
		maTimer.Start();
	}

	return 0;
}

// ----------------
// - FilterMosaic -
// ----------------

GraphicFilterMosaic::GraphicFilterMosaic( Window* pParent, const Graphic& rGraphic,
										  sal_uInt16 nTileWidth, sal_uInt16 nTileHeight, sal_Bool bEnhanceEdges ) :
	GraphicFilterDialog( pParent, SVX_RES( RID_SVX_GRFFILTER_DLG_MOSAIC ), rGraphic ),
	maFtWidth	( this, SVX_RES( DLG_FILTERMOSAIC_FT_WIDTH ) ),
	maMtrWidth	( this, SVX_RES( DLG_FILTERMOSAIC_MTR_WIDTH ) ),
	maFtHeight	( this, SVX_RES( DLG_FILTERMOSAIC_FT_HEIGHT ) ),
	maMtrHeight ( this, SVX_RES( DLG_FILTERMOSAIC_MTR_HEIGHT ) ),
	maCbxEdges	( this, SVX_RES( DLG_FILTERMOSAIC_CBX_EDGES ) )
{
	FreeResource();

	maMtrWidth.SetValue( nTileWidth );
	maMtrWidth.SetLast( GetGraphicSizePixel().Width() );
	maMtrWidth.SetModifyHdl( GetModifyHdl() );

	maMtrHeight.SetValue( nTileHeight );
	maMtrHeight.SetLast( GetGraphicSizePixel().Height() );
	maMtrHeight.SetModifyHdl( GetModifyHdl() );

	maCbxEdges.Check( bEnhanceEdges );
	maCbxEdges.SetToggleHdl( GetModifyHdl() );

	maMtrWidth.GrabFocus();
}

// -----------------------------------------------------------------------------

GraphicFilterMosaic::~GraphicFilterMosaic()
{
}

// -----------------------------------------------------------------------------

Graphic	GraphicFilterMosaic::GetFilteredGraphic( const Graphic& rGraphic,
												 double fScaleX, double fScaleY )
{
	Graphic			aRet;
	const Size		aSize( Max( FRound( GetTileWidth() * fScaleX ), 1L ),
						   Max( FRound( GetTileHeight() * fScaleY ), 1L ) );
	BmpFilterParam	aParam( aSize );

	if( rGraphic.IsAnimated() )
	{
		Animation aAnim( rGraphic.GetAnimation() );

		if( aAnim.Filter( BMP_FILTER_MOSAIC, &aParam ) )
		{
			if( IsEnhanceEdges() )
				aAnim.Filter( BMP_FILTER_SHARPEN );

			aRet = aAnim;
		}
	}
	else
	{
		BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

		if( aBmpEx.Filter( BMP_FILTER_MOSAIC, &aParam ) )
		{
			if( IsEnhanceEdges() )
				aBmpEx.Filter( BMP_FILTER_SHARPEN );

			aRet = aBmpEx;
		}
	}

	return aRet;
}

// ------------------
// - GraphicFilterSolarize -
// ------------------

GraphicFilterSolarize::GraphicFilterSolarize( Window* pParent, const Graphic& rGraphic,
											  sal_uInt8 cGreyThreshold, sal_Bool bInvert ) :
	GraphicFilterDialog	( pParent, SVX_RES( RID_SVX_GRFFILTER_DLG_SOLARIZE ), rGraphic ),
	maFtThreshold	( this, SVX_RES( DLG_FILTERSOLARIZE_FT_THRESHOLD ) ),
	maMtrThreshold	( this, SVX_RES( DLG_FILTERSOLARIZE_MTR_THRESHOLD ) ),
	maCbxInvert		( this, SVX_RES( DLG_FILTERSOLARIZE_CBX_INVERT ) )
{
	FreeResource();

	maMtrThreshold.SetValue( FRound( cGreyThreshold / 2.55 ) );
	maMtrThreshold.SetModifyHdl( GetModifyHdl() );

	maCbxInvert.Check( bInvert );
	maCbxInvert.SetToggleHdl( GetModifyHdl() );

	maMtrThreshold.GrabFocus();
}

// -----------------------------------------------------------------------------

GraphicFilterSolarize::~GraphicFilterSolarize()
{
}

// -----------------------------------------------------------------------------

Graphic	GraphicFilterSolarize::GetFilteredGraphic( const Graphic& rGraphic,
												   double fScaleX, double fScaleY )
{
	Graphic			aRet;
	BmpFilterParam	aParam( GetGreyThreshold() );

	if( rGraphic.IsAnimated() )
	{
		Animation aAnim( rGraphic.GetAnimation() );

		if( aAnim.Filter( BMP_FILTER_SOLARIZE, &aParam ) )
		{
			if( IsInvert() )
				aAnim.Invert();

			aRet = aAnim;
		}
	}
	else
	{
		BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

		if( aBmpEx.Filter( BMP_FILTER_SOLARIZE, &aParam ) )
		{
			if( IsInvert() )
				aBmpEx.Invert();

			aRet = aBmpEx;
		}
	}

	return aRet;
}

// ----------------------
// - GraphicFilterSepia -
// ----------------------

GraphicFilterSepia::GraphicFilterSepia( Window* pParent, const Graphic& rGraphic,
										sal_uInt16 nSepiaPercent ) :
	GraphicFilterDialog	( pParent, SVX_RES( RID_SVX_GRFFILTER_DLG_SEPIA ), rGraphic ),
	maFtSepia		( this, SVX_RES( DLG_FILTERSEPIA_FT_SEPIA ) ),
	maMtrSepia		( this, SVX_RES( DLG_FILTERSEPIA_MTR_SEPIA ) )
{
	FreeResource();

	maMtrSepia.SetValue( nSepiaPercent );
	maMtrSepia.SetModifyHdl( GetModifyHdl() );

	maMtrSepia.GrabFocus();
}

// -----------------------------------------------------------------------------

GraphicFilterSepia::~GraphicFilterSepia()
{
}

// -----------------------------------------------------------------------------

Graphic	GraphicFilterSepia::GetFilteredGraphic( const Graphic& rGraphic,
												double fScaleX, double fScaleY )
{
	Graphic			aRet;
	BmpFilterParam	aParam( GetSepiaPercent() );

	if( rGraphic.IsAnimated() )
	{
		Animation aAnim( rGraphic.GetAnimation() );

		if( aAnim.Filter( BMP_FILTER_SEPIA, &aParam ) )
			aRet = aAnim;
	}
	else
	{
		BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

		if( aBmpEx.Filter( BMP_FILTER_SEPIA, &aParam ) )
			aRet = aBmpEx;
	}

	return aRet;
}

// -----------------------
// - GraphicFilterPoster -
// -----------------------

GraphicFilterPoster::GraphicFilterPoster( Window* pParent, const Graphic& rGraphic,
										  sal_uInt16 nPosterCount ) :
	GraphicFilterDialog	( pParent, SVX_RES( RID_SVX_GRFFILTER_DLG_POSTER ), rGraphic ),
	maFtPoster		( this, SVX_RES( DLG_FILTERPOSTER_FT_POSTER ) ),
	maNumPoster		( this, SVX_RES( DLG_FILTERPOSTER_NUM_POSTER ) )
{
	FreeResource();

	maNumPoster.SetFirst( 2 );
	maNumPoster.SetLast( rGraphic.GetBitmapEx().GetBitCount() );
	maNumPoster.SetValue( nPosterCount );
	maNumPoster.SetModifyHdl( GetModifyHdl() );
	maNumPoster.GrabFocus();
}

// -----------------------------------------------------------------------------

GraphicFilterPoster::~GraphicFilterPoster()
{
}

// -----------------------------------------------------------------------------

Graphic	GraphicFilterPoster::GetFilteredGraphic( const Graphic& rGraphic, 
												 double fScaleX, double fScaleY )
{
	Graphic			aRet;
	const sal_uInt16	nPosterCount = GetPosterColorCount();

	if( rGraphic.IsAnimated() )
	{
		Animation aAnim( rGraphic.GetAnimation() );

		if( aAnim.ReduceColors( nPosterCount, BMP_REDUCE_POPULAR ) )
			aRet = aAnim;
	}
	else
	{
		BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

		if( aBmpEx.ReduceColors( nPosterCount, BMP_REDUCE_POPULAR ) )
			aRet = aBmpEx;
	}

	return aRet;
}

// -----------------------
// - GraphicFilterEmboss -
// -----------------------

void GraphicFilterEmboss::EmbossControl::MouseButtonDown( const MouseEvent& rEvt )
{
	const RECT_POINT eOldRP = GetActualRP();

	SvxRectCtl::MouseButtonDown( rEvt );

	if( GetActualRP() != eOldRP )
		maModifyHdl.Call( this );
}

// -----------------------------------------------------------------------------

GraphicFilterEmboss::GraphicFilterEmboss( Window* pParent, const Graphic& rGraphic,
										  RECT_POINT eLightSource ) :
	GraphicFilterDialog	( pParent, SVX_RES( RID_SVX_GRFFILTER_DLG_EMBOSS ), rGraphic ),
	maFtLight		( this, SVX_RES( DLG_FILTEREMBOSS_FT_LIGHT ) ),
	maCtlLight		( this, SVX_RES( DLG_FILTEREMBOSS_CTL_LIGHT ), eLightSource )
{
	FreeResource();

	maCtlLight.SetModifyHdl( GetModifyHdl() );
	maCtlLight.GrabFocus();
}

// -----------------------------------------------------------------------------

GraphicFilterEmboss::~GraphicFilterEmboss()
{
}

// -----------------------------------------------------------------------------

Graphic	GraphicFilterEmboss::GetFilteredGraphic( const Graphic& rGraphic, 
												 double fScaleX, double fScaleY )
{
	Graphic	aRet;
	sal_uInt16	nAzim, nElev;

	switch( maCtlLight.GetActualRP() )
	{
		case( RP_LT ): nAzim = 4500,	nElev = 4500; break;
		case( RP_MT ): nAzim = 9000,	nElev = 4500; break;
		case( RP_RT ): nAzim = 13500,	nElev = 4500; break;
		case( RP_LM ): nAzim = 0,		nElev = 4500; break;
		case( RP_MM ): nAzim = 0,		nElev = 9000; break;
		case( RP_RM ): nAzim = 18000,	nElev = 4500; break;
		case( RP_LB ): nAzim = 31500,	nElev = 4500; break;
		case( RP_MB ): nAzim = 27000,	nElev = 4500; break;
		case( RP_RB ): nAzim = 22500,	nElev = 4500; break;
	}

	BmpFilterParam aParam( nAzim, nElev );

	if( rGraphic.IsAnimated() )
	{
		Animation aAnim( rGraphic.GetAnimation() );

		if( aAnim.Filter( BMP_FILTER_EMBOSS_GREY, &aParam ) )
			aRet = aAnim;
	}
	else
	{
		BitmapEx aBmpEx( rGraphic.GetBitmapEx() );

		if( aBmpEx.Filter( BMP_FILTER_EMBOSS_GREY, &aParam ) )
			aRet = aBmpEx;
	}

	return aRet;
}
*/
