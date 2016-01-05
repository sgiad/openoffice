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
#include "precompiled_connectivity.hxx"
#include "NCatalog.hxx"
#include "NConnection.hxx"
#include "NTables.hxx"
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/sdbc/XResultSet.hpp>
#include "NDebug.hxx"


// -------------------------------------------------------------------------
using namespace connectivity::evoab;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
// -------------------------------------------------------------------------
OEvoabCatalog::OEvoabCatalog(OEvoabConnection* _pCon) :
	connectivity::sdbcx::OCatalog(_pCon)
	,m_pConnection(_pCon)
	,m_xMetaData(m_pConnection->getMetaData())
{
}
void OEvoabCatalog::refreshTables()
{
	TStringVector aVector;
	Sequence< ::rtl::OUString > aTypes(1);
	aTypes[0] = ::rtl::OUString::createFromAscii("TABLE");
	Reference< XResultSet > xResult = m_xMetaData->getTables(Any(),
		::rtl::OUString::createFromAscii("%"),::rtl::OUString::createFromAscii("%"),aTypes);

	if(xResult.is())
	{
		Reference< XRow > xRow(xResult,UNO_QUERY);
		::rtl::OUString aName;
		
		while(xResult->next())
		{
			aName = xRow->getString(3);
			aVector.push_back(aName);
		}
	}
	if(m_pTables)
		m_pTables->reFill(aVector);
	else
		m_pTables = new OEvoabTables(m_xMetaData,*this,m_aMutex,aVector);
}
// XTablesSupplier
Reference< XNameAccess > SAL_CALL  OEvoabCatalog::getTables(  ) throw(RuntimeException)
{
        ::osl::MutexGuard aGuard(m_aMutex);

        try
        {
                if (!m_pTables) {
                        refreshTables();
                        }
        }
        catch( const RuntimeException& )
        {
                // allowed to leave this method
                throw;
        }
        catch( const Exception& )
        {
                // allowed
        }

        return m_pTables;
}

