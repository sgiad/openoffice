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



#ifndef CONNECTIVITY_STATEMENTCOMPOSER_HXX
#define CONNECTIVITY_STATEMENTCOMPOSER_HXX

/** === begin UNO includes === **/
#include <com/sun/star/sdbc/XConnection.hpp>
#include <com/sun/star/sdb/XSingleSelectQueryComposer.hpp>
/** === end UNO includes === **/

#include <boost/noncopyable.hpp>

#include <memory>
#include "connectivity/dbtoolsdllapi.hxx"

//........................................................................
namespace dbtools
{
//........................................................................

	//====================================================================
	//= StatementComposer
	//====================================================================
    struct StatementComposer_Data;
    /** a class which is able to compose queries (SELECT statements) from a command and a command type
    */
    class OOO_DLLPUBLIC_DBTOOLS StatementComposer : public ::boost::noncopyable
	{
        ::std::auto_ptr< StatementComposer_Data >   m_pData;

    public:
        /** constructs an instance

            @param _rxConnection
                the connection to work with. Must not be <NULL/>.
        */
        StatementComposer(
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConnection,
            const ::rtl::OUString&  _rCommand,
            const sal_Int32         _nCommandType,
            const sal_Bool          _bEscapeProcessing
        );

        ~StatementComposer();

        /** controls whether or not the instance disposes its XSingleSelectQueryComposer upon
            destruction

            Unless you explicitly call this method with the parameter being <TRUE/>,
            the XSingleSelectQueryComposer will be disposed when the StatementComposer
            instance is destroyed.
        */
        void    setDisposeComposer( bool _bDoDispose );
        bool    getDisposeComposer() const;

        void    setFilter( const ::rtl::OUString& _rFilter );
        void    setOrder( const ::rtl::OUString& _rOrder );

        /** returns the composer which has been fed with the current settings

            @throws ::com::sun::star::sdbc::SQLException
                if such an exception occurs while creating the composer
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSingleSelectQueryComposer >
                getComposer();

        /** returns the composer statement

            Effectively, this is equivalent to calling getComposer, and asking the composer
            for its Query attribute.

            @throws ::com::sun::star::sdbc::SQLException
                if such an exception occurs while creating the composer
        */
        ::rtl::OUString
                getQuery();

    private:
        StatementComposer();    // not implemented
	};

//........................................................................
} // namespace dbtools
//........................................................................

#endif // CONNECTIVITY_STATEMENTCOMPOSER_HXX
