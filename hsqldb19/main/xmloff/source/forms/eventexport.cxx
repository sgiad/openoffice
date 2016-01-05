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
#include "precompiled_xmloff.hxx"
#include "eventexport.hxx"
#include <osl/diagnose.h>
#include "strings.hxx"
#include <tools/debug.hxx>

//.........................................................................
namespace xmloff
{
//.........................................................................

	using namespace ::com::sun::star::uno;
	using namespace ::com::sun::star::script;
	using namespace ::com::sun::star::container;
	using namespace ::com::sun::star::beans;
	using namespace ::com::sun::star::lang;

	//=====================================================================
	//= OEventDescriptorMapper
	//=====================================================================
	//---------------------------------------------------------------------
	OEventDescriptorMapper::OEventDescriptorMapper(const Sequence< ScriptEventDescriptor >& _rEvents)
	{
		sal_Int32 nEvents = _rEvents.getLength();

		// translate the events
		const ScriptEventDescriptor* pEvents = _rEvents.getConstArray();
		::rtl::OUString sName;
		::rtl::OUString sLibrary, sLocalMacroName;
		for (sal_Int32 i=0; i<nEvents; ++i, ++pEvents)
		{
			// the name of the event is build from listener interface and listener method name
			sName = pEvents->ListenerType;
			sName += EVENT_NAME_SEPARATOR;
			sName += pEvents->EventMethod;

			Sequence< PropertyValue >& rMappedEvent = m_aMappedEvents[sName];

			sLocalMacroName = pEvents->ScriptCode;
			sLibrary = ::rtl::OUString();
			if ( 0 == pEvents->ScriptType.compareToAscii( EVENT_STARBASIC ) )
			{	// for StarBasic, the library name is part of the ScriptCode
				sal_Int32 nPrefixLen = sLocalMacroName.indexOf( ':' );
				DBG_ASSERT( 0 <= nPrefixLen, "OEventDescriptorMapper::OEventDescriptorMapper: invalid script code prefix!" );
				if ( 0 <= nPrefixLen )
				{
					// the export handler for StarBasic expects "StarOffice", not "application" for application modules ...
					sLibrary = sLocalMacroName.copy( 0, nPrefixLen );
					if ( sLibrary.equalsAscii( EVENT_APPLICATION ) )
						sLibrary = EVENT_STAROFFICE;

					sLocalMacroName = sLocalMacroName.copy( nPrefixLen + 1 );
				}
				// tree property values to describe one event ...
				rMappedEvent.realloc( sLibrary.getLength() ? 3 : 2 );

				// ... the type
				rMappedEvent[0] = PropertyValue(EVENT_TYPE, -1, makeAny(pEvents->ScriptType), PropertyState_DIRECT_VALUE);

				// and the macro name
				rMappedEvent[1] = PropertyValue(EVENT_LOCALMACRONAME, -1, makeAny(sLocalMacroName), PropertyState_DIRECT_VALUE);

				// the library
				if ( sLibrary.getLength() )
					rMappedEvent[2] = PropertyValue(EVENT_LIBRARY, -1, makeAny(sLibrary), PropertyState_DIRECT_VALUE);
			}
			else
			{
				rMappedEvent.realloc( 2 );
				rMappedEvent[0] = PropertyValue(EVENT_TYPE, -1, makeAny(pEvents->ScriptType), PropertyState_DIRECT_VALUE);
				// and the macro name
				rMappedEvent[1] = PropertyValue(EVENT_SCRIPTURL, -1, makeAny(pEvents->ScriptCode), PropertyState_DIRECT_VALUE);
			}
		}
	}

	//---------------------------------------------------------------------
	void SAL_CALL OEventDescriptorMapper::replaceByName( const ::rtl::OUString&, const Any& ) throw(IllegalArgumentException, NoSuchElementException, WrappedTargetException, RuntimeException)
	{
		throw IllegalArgumentException(
			::rtl::OUString::createFromAscii("replacing is not implemented for this wrapper class."), static_cast< ::cppu::OWeakObject* >(this), 1);
	}

	//---------------------------------------------------------------------
	Any SAL_CALL OEventDescriptorMapper::getByName( const ::rtl::OUString& _rName ) throw(NoSuchElementException, WrappedTargetException, RuntimeException)
	{
		ConstMapString2PropertyValueSequenceIterator aPos = m_aMappedEvents.find(_rName);
		if (m_aMappedEvents.end() == aPos)
			throw NoSuchElementException(
				::rtl::OUString::createFromAscii("There is no element named ") += _rName,
				static_cast< ::cppu::OWeakObject* >(this));

		return makeAny(aPos->second);
	}

	//---------------------------------------------------------------------
	Sequence< ::rtl::OUString > SAL_CALL OEventDescriptorMapper::getElementNames(  ) throw(RuntimeException)
	{
		Sequence< ::rtl::OUString > aReturn(m_aMappedEvents.size());
		::rtl::OUString* pReturn = aReturn.getArray();
		for	(	ConstMapString2PropertyValueSequenceIterator aCollect = m_aMappedEvents.begin();
				aCollect != m_aMappedEvents.end();
				++aCollect, ++pReturn
			)
			*pReturn = aCollect->first;

		return aReturn;
	}

	//---------------------------------------------------------------------
	sal_Bool SAL_CALL OEventDescriptorMapper::hasByName( const ::rtl::OUString& _rName ) throw(RuntimeException)
	{
		ConstMapString2PropertyValueSequenceIterator aPos = m_aMappedEvents.find(_rName);
		return m_aMappedEvents.end() != aPos;
	}

	//---------------------------------------------------------------------
	Type SAL_CALL OEventDescriptorMapper::getElementType(  ) throw(RuntimeException)
	{
		return ::getCppuType(static_cast< PropertyValue* >(NULL));
	}

	//---------------------------------------------------------------------
	sal_Bool SAL_CALL OEventDescriptorMapper::hasElements(  ) throw(RuntimeException)
	{
		return !m_aMappedEvents.empty();
	}

//.........................................................................
}	// namespace xmloff
//.........................................................................

