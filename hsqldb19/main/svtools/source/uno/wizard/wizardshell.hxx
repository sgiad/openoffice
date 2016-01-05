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



#ifndef SVT_UNO_WIZARD_SHELL
#define SVT_UNO_WIZARD_SHELL

/** === begin UNO includes === **/
#include <com/sun/star/ui/dialogs/XWizardController.hpp>
#include <com/sun/star/ui/dialogs/XWizard.hpp>
/** === end UNO includes === **/

#include <svtools/roadmapwizard.hxx>

#include <boost/shared_ptr.hpp>
#include <map>

//......................................................................................................................
namespace svt { namespace uno
{
//......................................................................................................................

    class WizardPageController;
    typedef ::boost::shared_ptr< WizardPageController > PWizardPageController;

	//==================================================================================================================
	//= WizardShell
	//==================================================================================================================
    typedef ::svt::RoadmapWizard    WizardShell_Base;
    class WizardShell : public WizardShell_Base
	{
    public:
        WizardShell(
            Window* _pParent,
            const ::com::sun::star::uno::Reference< ::com::sun::star::ui::dialogs::XWizardController >& i_rController,
            const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< sal_Int16 > >& i_rPaths
        );
        virtual ~WizardShell();

        // Dialog overridables
	    virtual short	Execute();

        // OWizardMachine overridables
		virtual TabPage*	createPage( WizardState i_nState );
	    virtual void        enterState( WizardState i_nState );
		virtual	sal_Bool	leaveState( WizardState i_nState );
        virtual String      getStateDisplayName( WizardState i_nState ) const;
        virtual bool        canAdvance() const;
		virtual sal_Bool    onFinish();
		virtual IWizardPageController*
                            getPageController( TabPage* _pCurrentPage ) const;

        static sal_Int16 convertCommitReasonToTravelType( const CommitPageReason i_eReason );

        // operations
        sal_Bool    advanceTo( const sal_Int16 i_nPageId )
        {
            return skipUntil( impl_pageIdToState( i_nPageId ) );
        }
        sal_Bool    goBackTo( const sal_Int16 i_nPageId )
        {
            return skipBackwardUntil( impl_pageIdToState( i_nPageId ) );
        }
		sal_Bool    travelNext()        { return WizardShell_Base::travelNext(); }
		sal_Bool    travelPrevious()    { return WizardShell_Base::travelPrevious(); }

        void        activatePath( const sal_Int16 i_nPathID, const sal_Bool i_bFinal )
        {
            WizardShell_Base::activatePath( PathId( i_nPathID ), i_bFinal );
        }

        ::com::sun::star::uno::Reference< ::com::sun::star::ui::dialogs::XWizardPage >
                    getCurrentWizardPage() const;

        sal_Int16   getCurrentPage() const
        {
            return impl_stateToPageId( getCurrentState() );
        }

        void        enablePage( const sal_Int16 i_PageID, const sal_Bool i_Enable );

        bool        knowsPage( const sal_Int16 i_nPageID ) const
        {
            return knowsState( impl_pageIdToState( i_nPageID ) );
        }

    private:
        sal_Int16   impl_stateToPageId( const WizardTypes::WizardState i_nState ) const
        {
            return static_cast< sal_Int16 >( i_nState + m_nFirstPageID );
        }

        WizardState impl_pageIdToState( const sal_Int16 i_nPageId ) const
        {
            return static_cast< WizardState >( i_nPageId - m_nFirstPageID );
        }

        PWizardPageController impl_getController( TabPage* i_pPage ) const;

        // prevent outside access to some base class members
        using WizardShell_Base::skip;
        using WizardShell_Base::skipUntil;
        using WizardShell_Base::skipBackwardUntil;
        using WizardShell_Base::getCurrentState;
        using WizardShell_Base::activatePath;

    private:
        typedef ::std::map< TabPage*, PWizardPageController > Page2ControllerMap;

        const ::com::sun::star::uno::Reference< ::com::sun::star::ui::dialogs::XWizardController >  m_xController;
        const sal_Int16                                                                             m_nFirstPageID;
        Page2ControllerMap                                                                          m_aPageControllers;
	};

//......................................................................................................................
} } // namespace svt::uno
//......................................................................................................................

#endif // SVT_UNO_WIZARD_SHELL
