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
#include "precompiled_scripting.hxx"

#include <stdio.h>

#include "ScriptImpl.hxx"
#include <util/util.hxx>

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::script::framework;

namespace func_provider
{

//*************************************************************************
ScriptImpl::ScriptImpl(
    const Reference< beans::XPropertySet > & scriptingContext,
    const Reference< runtime::XScriptInvocation > & runtimeMgr,
    const ::rtl::OUString& scriptURI )
throw ( RuntimeException ) :
        m_XScriptingContext( scriptingContext, UNO_SET_THROW ),
        m_RunTimeManager( runtimeMgr, UNO_SET_THROW ),
        m_ScriptURI( scriptURI )
{
    OSL_TRACE( "<!constucting a ScriptImpl>\n" );
}

//*************************************************************************
ScriptImpl::~ScriptImpl()
{
    OSL_TRACE( "<Destructing a ScriptImpl>\n" );
}

//*************************************************************************
Any SAL_CALL
ScriptImpl::invoke( const Sequence< Any >& aParams,
                      Sequence< sal_Int16 >& aOutParamIndex, Sequence< Any >& aOutParam )
throw ( lang::IllegalArgumentException, script::CannotConvertException,
        reflection::InvocationTargetException, RuntimeException )
{
    OSL_TRACE( "<ScriptImpl::invoke>" );
    Any result;
    Any anyScriptingContext;

    anyScriptingContext <<= m_XScriptingContext;
    try
    {
        result = m_RunTimeManager->invoke( m_ScriptURI, anyScriptingContext, aParams,
                                           aOutParamIndex, aOutParam );
    }
    catch ( lang::IllegalArgumentException & iae )
    {
        ::rtl::OUString temp = OUSTR( "ScriptImpl::invoke IllegalArgumentException : " );
        throw lang::IllegalArgumentException( temp.concat( iae.Message ),
                                              Reference< XInterface > (),
                                              iae.ArgumentPosition );
    }
    catch ( script::CannotConvertException & cce )
    {
        ::rtl::OUString temp = OUSTR( "ScriptImpl::invoke CannotConvertException : " );
        throw script::CannotConvertException( temp.concat( cce.Message ),
                                              Reference< XInterface > (),
                                              cce.DestinationTypeClass,
                                              cce.Reason,
                                              cce.ArgumentIndex );
    }
    catch ( reflection::InvocationTargetException & ite )
    {
        ::rtl::OUString temp = OUSTR( "ScriptImpl::invoke InvocationTargetException : " );
        throw reflection::InvocationTargetException( temp.concat( ite.Message ),
                Reference< XInterface > (),
                ite.TargetException );
    }
    catch ( RuntimeException & re )
    {
        ::rtl::OUString temp = OUSTR( "ScriptImpl::invoke RuntimeException : " );
        throw RuntimeException( temp.concat( re.Message ),
                                Reference< XInterface > () );
    }
#ifdef _DEBUG
    catch ( ... )
    {
        throw RuntimeException(
            OUSTR( "ScriptImpl::invoke Unknown Exception caught - RuntimeException rethrown" ),
            Reference< XInterface > () );
    }
#endif
    return result;
}
} // namespace func_provider
