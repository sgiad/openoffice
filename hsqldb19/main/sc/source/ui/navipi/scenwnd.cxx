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



//------------------------------------------------------------------

#include <sfx2/bindings.hxx>
#include <sfx2/dispatch.hxx>
#include <sfx2/viewfrm.hxx>
#include <svl/slstitm.hxx>
#include <svl/stritem.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/svapp.hxx>
#include "navipi.hxx"
#include "popmenu.hxx"
#include "scresid.hxx"
#include "sc.hrc"
#include "globstr.hrc"

//========================================================================
// class ScScenarioWindow ------------------------------------------------
//========================================================================

ScScenarioListBox::ScScenarioListBox( ScScenarioWindow& rParent ) :
    ListBox( &rParent, WB_BORDER | WB_TABSTOP ),
    mrParent( rParent )
{
	Font aFont( GetFont() );
	aFont.SetTransparent( sal_True );
	aFont.SetWeight( WEIGHT_LIGHT );
	SetFont( aFont );
}

ScScenarioListBox::~ScScenarioListBox()
{
}

void ScScenarioListBox::UpdateEntries( List* pNewEntryList )
{
	Clear();
    maEntries.clear();

    if( !pNewEntryList )
        return;

    switch( pNewEntryList->Count() )
    {
        case 0:
            // no scenarios in current sheet
            mrParent.SetComment( EMPTY_STRING );
        break;

        case 1:
            // sheet is a scenario container, comment only
            mrParent.SetComment( *static_cast< String* >( pNewEntryList->First() ) );
        break;

        default:
        {
            // sheet contains scenarios
            DBG_ASSERT( pNewEntryList->Count() % 3 == 0, "ScScenarioListBox::UpdateEntries - wrong list size" );
            SetUpdateMode( sal_False );
            String* pEntry = static_cast< String* >( pNewEntryList->First() );
            while( pEntry )
            {
                ScenarioEntry aEntry;

                // first entry of a triple is the scenario name
                aEntry.maName = *pEntry;
                // second entry of a triple is the scenario comment
                if( (pEntry = static_cast< String* >( pNewEntryList->Next() )) != 0 )
                    aEntry.maComment = *pEntry;
                // third entry of a triple is the protection ("0" = not protected, "1" = protected)
                if( (pEntry = static_cast< String* >( pNewEntryList->Next() )) != 0 )
                    aEntry.mbProtected = (pEntry->Len() > 0) && (pEntry->GetChar( 0 ) != '0');

                maEntries.push_back( aEntry );
                InsertEntry( aEntry.maName, LISTBOX_APPEND );
                pEntry = static_cast< String* >( pNewEntryList->Next() );
            }
            SetUpdateMode( sal_True );
            SetNoSelection();
            mrParent.SetComment( EMPTY_STRING );
        }
    }
}

void ScScenarioListBox::Select()
{
    if( const ScenarioEntry* pEntry = GetSelectedEntry() )
        mrParent.SetComment( pEntry->maComment );
}

void ScScenarioListBox::DoubleClick()
{
    SelectScenario();
}

long ScScenarioListBox::Notify( NotifyEvent& rNEvt )
{
    bool bHandled = false;

    if( rNEvt.GetType() == EVENT_KEYINPUT )
    {
        KeyCode aCode = rNEvt.GetKeyEvent()->GetKeyCode();
        switch( aCode.GetCode() )
        {
            case KEY_RETURN:
                SelectScenario();
                bHandled = true;
            break;
            case KEY_DELETE:
                DeleteScenario( true );
                bHandled = true;
            break;
        }
    }
    else if ( rNEvt.GetType() == EVENT_COMMAND && GetSelectEntryCount() )
    {
        const CommandEvent* pCEvt = rNEvt.GetCommandEvent();
        if ( pCEvt && pCEvt->GetCommand() == COMMAND_CONTEXTMENU )
        {
            if( const ScenarioEntry* pEntry = GetSelectedEntry() )
            {
                if( !pEntry->mbProtected )
                {
                    ScPopupMenu aPopup( ScResId( RID_POPUP_NAVIPI_SCENARIO ) );
                    aPopup.Execute( this, pCEvt->GetMousePosPixel() );
                    if (aPopup.WasHit())
                    {
                        switch( aPopup.GetSelected() )
                        {
                            case RID_NAVIPI_SCENARIO_DELETE:
                                DeleteScenario( true );
                            break;
                            case RID_NAVIPI_SCENARIO_EDIT:
                                EditScenario();
                            break;
                        }
                    }
                }
            }
            bHandled = true;
        }
    }

    return bHandled ? 1 : ListBox::Notify( rNEvt );
}

const ScScenarioListBox::ScenarioEntry* ScScenarioListBox::GetSelectedEntry() const
{
    size_t nPos = GetSelectEntryPos();
    return (nPos < maEntries.size()) ? &maEntries[ nPos ] : 0;
}

void ScScenarioListBox::ExecuteScenarioSlot( sal_uInt16 nSlotId )
{
    if( SfxViewFrame* pViewFrm = SfxViewFrame::Current() )
    {
        SfxStringItem aStringItem( nSlotId, GetSelectEntry() );
        pViewFrm->GetDispatcher()->Execute( nSlotId, SFX_CALLMODE_SLOT | SFX_CALLMODE_RECORD, &aStringItem, 0L, 0L );
    }
}

void ScScenarioListBox::SelectScenario()
{
    if( GetSelectEntryCount() > 0 )
        ExecuteScenarioSlot( SID_SELECT_SCENARIO );
}

void ScScenarioListBox::EditScenario()
{
    if( GetSelectEntryCount() > 0 )
        ExecuteScenarioSlot( SID_EDIT_SCENARIO );
}

void ScScenarioListBox::DeleteScenario( bool bQueryBox )
{
    if( GetSelectEntryCount() > 0 )
        if( !bQueryBox || (::QueryBox( 0, WinBits( WB_YES_NO | WB_DEF_YES ), ScGlobal::GetRscString( STR_QUERY_DELSCENARIO ) ).Execute() == RET_YES) )
            ExecuteScenarioSlot( SID_DELETE_SCENARIO );
}

//========================================================================
// class ScScenarioWindow ------------------------------------------------
//========================================================================

ScScenarioWindow::ScScenarioWindow( Window* pParent,const String& aQH_List,
									const String& aQH_Comment)
    :   Window      ( pParent, WB_TABSTOP | WB_DIALOGCONTROL ),
        aLbScenario ( *this ),
        aEdComment  ( this,  WB_BORDER | WB_LEFT | WB_READONLY | WB_VSCROLL | WB_TABSTOP )
{
	Font aFont( GetFont() );
	aFont.SetTransparent( sal_True );
	aFont.SetWeight( WEIGHT_LIGHT );
	aEdComment.SetFont( aFont );
	aEdComment.SetMaxTextLen( 512 );
	aLbScenario.SetPosPixel( Point(0,0) );
	aLbScenario.SetHelpId(HID_SC_SCENWIN_TOP);
	aEdComment.SetHelpId(HID_SC_SCENWIN_BOTTOM);
	aLbScenario.Show();
	aEdComment.Show();

	aLbScenario.SetQuickHelpText(aQH_List);
	aEdComment.SetQuickHelpText(aQH_Comment);
	aEdComment.SetBackground( Color( COL_LIGHTGRAY ) );

	SfxViewFrame* pViewFrm = SfxViewFrame::Current();
	if (pViewFrm)
	{
		SfxBindings& rBindings = pViewFrm->GetBindings();
		rBindings.Invalidate( SID_SELECT_SCENARIO );
		rBindings.Update( SID_SELECT_SCENARIO );
	}
}

// -----------------------------------------------------------------------

ScScenarioWindow::~ScScenarioWindow()
{
}

void ScScenarioWindow::Paint( const Rectangle& rRec )
{
	const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
	Color aBgColor = rStyleSettings.GetFaceColor();

	SetBackground( aBgColor );

	Window::Paint( rRec );
}

// -----------------------------------------------------------------------

void ScScenarioWindow::NotifyState( const SfxPoolItem* pState )
{
	if( pState )
	{
		aLbScenario.Enable();

		if ( pState->ISA(SfxStringItem) )
		{
			String aNewEntry( ((const SfxStringItem*)pState)->GetValue() );

			if ( aNewEntry.Len() > 0 )
				aLbScenario.SelectEntry( aNewEntry );
			else
				aLbScenario.SetNoSelection();
		}
		else if ( pState->ISA(SfxStringListItem) )
		{
			aLbScenario.UpdateEntries( ((SfxStringListItem*)pState)->GetList() );
		}
	}
	else
	{
		aLbScenario.Disable();
		aLbScenario.SetNoSelection();
	}
}

// -----------------------------------------------------------------------

void ScScenarioWindow::SetSizePixel( const Size& rNewSize )
{
	Size aSize( rNewSize );
	long nHeight = aSize.Height() / 2;

	Window::SetSizePixel( aSize );

	aSize.Height() = nHeight;
	aLbScenario.SetSizePixel( aSize );

	aSize.Height() -= 4;
	aEdComment.SetPosSizePixel(	Point( 0, nHeight+4 ), aSize );
}




