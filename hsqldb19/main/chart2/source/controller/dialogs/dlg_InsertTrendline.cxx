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
#include "precompiled_chart2.hxx"

#include "dlg_InsertTrendline.hxx"
#include "dlg_InsertTrendline.hrc"
#include "res_Trendline.hxx"
#include "ResourceIds.hrc"
#include "ResId.hxx"
#include "Strings.hrc"
#include "chartview/ExplicitValueProvider.hxx"
#include "ChartModelHelper.hxx"
#include "ObjectIdentifier.hxx"
#include "DiagramHelper.hxx"
#include "AxisHelper.hxx"
#include "ObjectNameProvider.hxx"
#include <com/sun/star/chart2/XAxis.hpp>
#include <com/sun/star/chart2/XDiagram.hpp>

#include <svtools/controldims.hrc>

using namespace ::com::sun::star;
using namespace ::com::sun::star::chart2;

namespace
{
void lcl_SetControlXPos( Control & rControl, long nPosPixel )
{
    Point aPos( rControl.GetPosPixel());
    aPos.setX( nPosPixel );
    rControl.SetPosPixel( aPos );
}
} // anonymous namespace

//.............................................................................
namespace chart
{
//.............................................................................

InsertTrendlineDialog::InsertTrendlineDialog( Window* pParent, const SfxItemSet& rMyAttrs ) :
        ModalDialog( pParent, SchResId( DLG_DATA_TRENDLINE )),
        rInAttrs( rMyAttrs ),
        aBtnOK( this, SchResId( BTN_OK )),
        aBtnCancel( this, SchResId( BTN_CANCEL )),
        aBtnHelp( this, SchResId( BTN_HELP )),
        m_apTrendlineResources( new TrendlineResources( this, rInAttrs, true ))
{
    FreeResource();
    this->SetText( ObjectNameProvider::getName_ObjectForAllSeries( OBJECTTYPE_DATA_CURVE ) );
}

InsertTrendlineDialog::~InsertTrendlineDialog()
{
}

void InsertTrendlineDialog::adjustSize()
{
    long nControlsRightEdge = m_apTrendlineResources->adjustControlSizes();
    long nButtonXPos = nControlsRightEdge +
        LogicToPixel( Size( RSC_SP_CTRL_X, 10 ), MapMode( MAP_APPFONT )).getWidth();
    lcl_SetControlXPos( aBtnOK, nButtonXPos );
    lcl_SetControlXPos( aBtnCancel, nButtonXPos );
    lcl_SetControlXPos( aBtnHelp, nButtonXPos );

    Size aDialogSize( GetSizePixel());
    aDialogSize.setWidth(
        nControlsRightEdge +
        LogicToPixel( Size( RSC_SP_CTRL_X + RSC_CD_PUSHBUTTON_WIDTH + RSC_SP_DLG_INNERBORDER_RIGHT, 0 ),
                      MapMode( MAP_APPFONT )).getWidth());
    SetSizePixel( aDialogSize );
}

void InsertTrendlineDialog::FillItemSet(SfxItemSet& rOutAttrs)
{
    m_apTrendlineResources->FillItemSet(rOutAttrs);
}

void InsertTrendlineDialog::DataChanged( const DataChangedEvent& rDCEvt )
{
    ModalDialog::DataChanged( rDCEvt );

    if ( (rDCEvt.GetType() == DATACHANGED_SETTINGS) && (rDCEvt.GetFlags() & SETTINGS_STYLE) )
        m_apTrendlineResources->FillValueSets();
}

//.............................................................................
} //namespace chart
//.............................................................................
