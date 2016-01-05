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

 

#ifndef _CONNECTIVITY_EVOAB_TABLE_HXX_
#define _CONNECTIVITY_EVOAB_TABLE_HXX_

#include "NConnection.hxx"
#include "connectivity/sdbcx/VTable.hxx"

namespace connectivity
{
	namespace evoab
	{
		typedef connectivity::sdbcx::OTable OEvoabTable_TYPEDEF;

		::rtl::OUString getTypeString(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& xColProp);

		class OEvoabTable : public OEvoabTable_TYPEDEF
		{
			::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData > m_xMetaData;
			OEvoabConnection* m_pConnection;

		public:
			OEvoabTable(	sdbcx::OCollection* _pTables, 
					OEvoabConnection* _pConnection,
					const ::rtl::OUString& _Name,
					const ::rtl::OUString& _Type,
					const ::rtl::OUString& _Description = ::rtl::OUString(),
					const ::rtl::OUString& _SchemaName = ::rtl::OUString(),
					const ::rtl::OUString& _CatalogName = ::rtl::OUString()
				);

			OEvoabConnection* getConnection() { return m_pConnection;}

			virtual void refreshColumns();

			::rtl::OUString getTableName() const { return m_Name; }
			::rtl::OUString getSchema() const { return m_SchemaName; }
		};
	}
}

#endif // _CONNECTIVITY_EVOAB_TABLE_HXX_
