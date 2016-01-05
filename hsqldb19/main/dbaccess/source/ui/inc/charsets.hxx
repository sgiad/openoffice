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



#ifndef _DBAUI_CHARSETS_HXX_
#define _DBAUI_CHARSETS_HXX_

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _TOOLS_RC_HXX
#include <tools/rc.hxx>
#endif
#ifndef _DBHELPER_DBCHARSET_HXX_
#include <connectivity/dbcharset.hxx>
#endif
#ifndef _SVX_TXENCTAB_HXX
#include <svx/txenctab.hxx>
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

	//=========================================================================
	//= OCharsetDisplay
	//=========================================================================
	typedef ::dbtools::OCharsetMap OCharsetDisplay_Base;
	class OCharsetDisplay
			:protected OCharsetDisplay_Base
			,protected SvxTextEncodingTable
	{
	protected:
		::rtl::OUString	m_aSystemDisplayName;

	public:
		class ExtendedCharsetIterator;
		friend class OCharsetDisplay::ExtendedCharsetIterator;

		typedef ExtendedCharsetIterator iterator;
		typedef ExtendedCharsetIterator const_iterator;

		OCharsetDisplay();

		// various find operations
		const_iterator findEncoding(const rtl_TextEncoding _eEncoding) const;
		const_iterator findIanaName(const ::rtl::OUString& _rIanaName) const;
		const_iterator findDisplayName(const ::rtl::OUString& _rDisplayName) const;

		/// get access to the first element of the charset collection
		const_iterator	begin() const;
		/// get access to the (last + 1st) element of the charset collection
		const_iterator	end() const;
		// size of the map
		sal_Int32	size() const { return OCharsetDisplay_Base::size(); }

	protected:
		virtual	sal_Bool approveEncoding( const rtl_TextEncoding _eEncoding, const rtl_TextEncodingInfo& _rInfo ) const;

    private:
        using OCharsetDisplay_Base::find;
	};

	//-------------------------------------------------------------------------
	//- CharsetDisplayDerefHelper
	//-------------------------------------------------------------------------
	typedef ::dbtools::CharsetIteratorDerefHelper CharsetDisplayDerefHelper_Base;
	class CharsetDisplayDerefHelper : protected CharsetDisplayDerefHelper_Base
	{
		friend class OCharsetDisplay::ExtendedCharsetIterator;

		::rtl::OUString							m_sDisplayName;

	public:
		CharsetDisplayDerefHelper(const CharsetDisplayDerefHelper& _rSource);

		rtl_TextEncoding	getEncoding() const			{ return CharsetDisplayDerefHelper_Base::getEncoding(); }
		::rtl::OUString		getIanaName() const			{ return CharsetDisplayDerefHelper_Base::getIanaName(); }
		::rtl::OUString		getDisplayName() const		{ return m_sDisplayName; }

	protected:
		CharsetDisplayDerefHelper(const ::dbtools::CharsetIteratorDerefHelper& _rBase, const ::rtl::OUString& _rDisplayName);
	};

	//-------------------------------------------------------------------------
	//- OCharsetDisplay::ExtendedCharsetIterator
	//-------------------------------------------------------------------------
	class OCharsetDisplay::ExtendedCharsetIterator
	{
		friend class OCharsetDisplay;

		friend bool operator==(const ExtendedCharsetIterator& lhs, const ExtendedCharsetIterator& rhs);
		friend bool operator!=(const ExtendedCharsetIterator& lhs, const ExtendedCharsetIterator& rhs) { return !(lhs == rhs); }

		typedef ::dbtools::OCharsetMap		container;
		typedef container::CharsetIterator	base_iterator;

	protected:
		const OCharsetDisplay*		m_pContainer;
		base_iterator				m_aPosition;

	public:
		ExtendedCharsetIterator(const ExtendedCharsetIterator& _rSource);

		CharsetDisplayDerefHelper operator*() const;

		/// prefix increment
		const ExtendedCharsetIterator&	operator++();
		/// postfix increment
		const ExtendedCharsetIterator	operator++(int) { ExtendedCharsetIterator hold(*this); ++*this; return hold; }

		/// prefix decrement
		const ExtendedCharsetIterator&	operator--();
		/// postfix decrement
		const ExtendedCharsetIterator	operator--(int) { ExtendedCharsetIterator hold(*this); --*this; return hold; }

	protected:
		ExtendedCharsetIterator( const OCharsetDisplay* _pContainer, const base_iterator& _rPosition );
	};

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_CHARSETS_HXX_

