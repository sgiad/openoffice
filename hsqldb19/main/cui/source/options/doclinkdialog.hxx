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



#ifndef _SVX_DOCLINKDIALOG_HXX_
#define _SVX_DOCLINKDIALOG_HXX_

#include <vcl/dialog.hxx>
#include <vcl/fixed.hxx>
#include <vcl/edit.hxx>
#ifndef _SV_BUTTON_HXX 
#include <vcl/button.hxx>
#endif
#include <svtools/inettbc.hxx>
#include <svtools/urlcontrol.hxx>

//......................................................................
namespace svx
{
//......................................................................

	//==================================================================
	//= ODocumentLinkDialog
	//==================================================================
	/** dialog for editing document links associated with data sources
	*/
	class ODocumentLinkDialog : public ModalDialog
	{
	protected:
		FixedText				m_aURLLabel;
		::svt::OFileURLControl	m_aURL;
		PushButton				m_aBrowseFile;
		FixedText				m_aNameLabel;
		Edit					m_aName;		

		FixedLine				m_aBottomLine;
		OKButton				m_aOK;
		CancelButton			m_aCancel;
		HelpButton				m_aHelp;

		sal_Bool				m_bCreatingNew;

		Link					m_aNameValidator;

	public:
		ODocumentLinkDialog( Window* _pParent, sal_Bool _bCreateNew );

		// name validation has to be done by an external instance
		// the validator link gets a pointer to a String, and should return 0 if the string is not
		// acceptable
		void	setNameValidator( const Link& _rValidator ) { m_aNameValidator = _rValidator; }
		Link	getNameValidator( ) const { return m_aNameValidator; }

		void	set( const	String& _rName, const	String& _rURL );
		void	get(		String& _rName,			String& _rURL ) const;

	protected:
		DECL_LINK( OnTextModified, Control* );
		DECL_LINK( OnBrowseFile, void* );
		DECL_LINK( OnOk, void* );

		void validate( );
	};

//......................................................................
}	// namespace svx
//......................................................................

#endif // _SVX_DOCLINKDIALOG_HXX_

