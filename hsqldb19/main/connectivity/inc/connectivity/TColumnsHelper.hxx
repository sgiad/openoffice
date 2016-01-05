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



#ifndef CONNECTIVITY_COLUMNSHELPER_HXX
#define CONNECTIVITY_COLUMNSHELPER_HXX

#include "connectivity/sdbcx/VCollection.hxx"
#include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
#include "connectivity/sdbcx/IRefreshable.hxx"
#include "connectivity/dbtoolsdllapi.hxx"

namespace connectivity
{
	class OTableHelper;
	class OColumnsHelperImpl;
	/** contains generell column handling to creat default columns and default sql statements.
	*/
	class OOO_DLLPUBLIC_DBTOOLS OColumnsHelper : public sdbcx::OCollection
	{
		OColumnsHelperImpl* m_pImpl;
	protected:
		OTableHelper*	m_pTable;

        virtual sdbcx::ObjectType createObject(const ::rtl::OUString& _rName);
        virtual void impl_refresh() throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > createDescriptor();
        virtual sdbcx::ObjectType appendObject( const ::rtl::OUString& _rForName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& descriptor );
		virtual void dropObject(sal_Int32 _nPos,const ::rtl::OUString _sElementName);
	public:
		OColumnsHelper(	::cppu::OWeakObject& _rParent
						,sal_Bool _bCase
						,::osl::Mutex& _rMutex
						,const TStringVector &_rVector
						,sal_Bool _bUseHardRef = sal_True
					);
		virtual ~OColumnsHelper();

		/**	set the parent of the columns. Can also be <NULL/>.
			@param	_pTable
				The parent.
		*/
		inline void setParent(OTableHelper* _pTable) { m_pTable = _pTable;}
	};
}
#endif // CONNECTIVITY_COLUMNSHELPER_HXX

