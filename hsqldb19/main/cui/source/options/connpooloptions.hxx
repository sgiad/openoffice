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



#ifndef _OFFAPP_CONNPOOLOPTIONS_HXX_
#define _OFFAPP_CONNPOOLOPTIONS_HXX_

#include <svl/solar.hrc>
#include <sfx2/tabdlg.hxx>
#include <vcl/fixed.hxx>
#include <vcl/button.hxx>
#include <vcl/field.hxx>
#include <svx/databaseregistrationui.hxx>

//........................................................................
namespace offapp
{
//........................................................................

	//====================================================================
	//= ConnectionPoolOptionsPage
	//====================================================================
	class DriverListControl;
	class ConnectionPoolOptionsPage : public SfxTabPage
	{
		using TabPage::ActivatePage;

	protected:
		FixedLine				m_aFrame;
		CheckBox				m_aEnablePooling;
		FixedText				m_aDriversLabel;
		DriverListControl*		m_pDriverList;
		FixedText				m_aDriverLabel;
		FixedText				m_aDriver;
		CheckBox				m_aDriverPoolingEnabled;
		FixedText				m_aTimeoutLabel;
		NumericField			m_aTimeout;

	protected:
		ConnectionPoolOptionsPage(Window* _pParent, const SfxItemSet& _rAttrSet);

	public:
		static SfxTabPage*	Create(Window* _pParent, const SfxItemSet& _rAttrSet);

		~ConnectionPoolOptionsPage();

	protected:
		virtual long		Notify( NotifyEvent& _rNEvt );

		virtual sal_Bool		FillItemSet(SfxItemSet& _rSet);
		virtual void		Reset(const SfxItemSet& _rSet);
		virtual void		ActivatePage( const SfxItemSet& _rSet);

	protected:
		DECL_LINK( OnEnabledDisabled, const CheckBox* );
		DECL_LINK( OnDriverRowChanged, const void* );

		void implInitControls(const SfxItemSet& _rSet, sal_Bool _bFromReset);

		void commitTimeoutField();
	};

//........................................................................
}	// namespace offapp
//........................................................................

#endif // _OFFAPP_CONNPOOLOPTIONS_HXX_


