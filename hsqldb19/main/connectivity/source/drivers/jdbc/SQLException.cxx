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
#include "java/sql/SQLException.hxx"
#include "java/tools.hxx"

using namespace connectivity;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
//	using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
//**************************************************************
//************ Class: java.sql.SQLException
//**************************************************************
java_sql_SQLException::java_sql_SQLException( const java_sql_SQLException_BASE& _rException,const Reference< XInterface> & _rContext)
	: starsdbc::SQLException(	_rException.getMessage(),
								_rContext,
								_rException.getSQLState(),
								_rException.getErrorCode(),
								makeAny(_rException.getNextException())
							)
{
}

java_sql_SQLException_BASE::java_sql_SQLException_BASE( JNIEnv * pEnv, jobject myObj ) : java_lang_Exception( pEnv, myObj )
{
}

jclass java_sql_SQLException_BASE::theClass = 0;

java_sql_SQLException_BASE::~java_sql_SQLException_BASE()
{}


jclass java_sql_SQLException_BASE::getMyClass() const
{
    return st_getMyClass();
}
jclass java_sql_SQLException_BASE::st_getMyClass()
{
	// die Klasse muss nur einmal geholt werden, daher statisch
	if( !theClass )
        theClass = findMyClass("java/sql/SQLException");
	return theClass;
}

starsdbc::SQLException java_sql_SQLException_BASE::getNextException()  const
{
	SDBThreadAttach t;
    static jmethodID mID(NULL);
    jobject out = callObjectMethod(t.pEnv,"getNextException","()Ljava/sql/SQLException;", mID);
	// ACHTUNG: der Aufrufer wird Eigentuemer des zurueckgelieferten Zeigers !!!
	if( out )
	{
		java_sql_SQLException_BASE	warn_base(t.pEnv,out);
		return (starsdbc::SQLException)java_sql_SQLException(warn_base,0);
	}

	return starsdbc::SQLException();
}

::rtl::OUString java_sql_SQLException_BASE::getSQLState() const
{
    static jmethodID mID(NULL);
    return callStringMethod("getSQLState",mID);
}
sal_Int32 java_sql_SQLException_BASE::getErrorCode() const
{
    static jmethodID mID(NULL);
    return callIntMethod("getErrorCode",mID);
}

