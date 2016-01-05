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
#include "precompiled_dtrans.hxx"
#include "transferable.hxx"

//----------------------------------------------------------------
//	ctor
//----------------------------------------------------------------



CTransferable::CTransferable( wchar_t* dataString ) :
	m_seqDFlv( 1 ),
	m_Data( dataString )
{
	DataFlavor df;
	
	/*
	df.MimeType = L"text/plain; charset=unicode";
	df.DataType = getCppuType( ( OUString* )0 );

	m_seqDFlv[0] = df;
	*/
	
	//df.MimeType = L"text/plain; charset=windows1252";
	df.MimeType = L"text/plain";
	df.DataType = getCppuType( ( Sequence< sal_Int8 >* )0 );


	m_seqDFlv[0] = df;	
}

//----------------------------------------------------------------
//	getTransferData
//----------------------------------------------------------------

Any SAL_CALL CTransferable::getTransferData( const DataFlavor& aFlavor ) 
	throw(UnsupportedFlavorException, IOException, RuntimeException)
{	
	Any anyData;

	/*if ( aFlavor == m_seqDFlv[0] )
	{
		anyData = makeAny( m_Data );
	}
	else*/ if ( aFlavor == m_seqDFlv[0] )
	{
		OString aStr( m_Data.getStr( ), m_Data.getLength( ), 1252 );
		Sequence< sal_Int8 > sOfChars( aStr.getLength( ) );
		sal_Int32 lenStr = aStr.getLength( );

		for ( sal_Int32 i = 0; i < lenStr; ++i )
			sOfChars[i] = aStr[i];

		anyData = makeAny( sOfChars );
	}

	return anyData;
}

//----------------------------------------------------------------
//	getTransferDataFlavors
//----------------------------------------------------------------

Sequence< DataFlavor > SAL_CALL CTransferable::getTransferDataFlavors(  ) 
	throw(RuntimeException)
{
	return m_seqDFlv;
}

//----------------------------------------------------------------
//	isDataFlavorSupported
//----------------------------------------------------------------

sal_Bool SAL_CALL CTransferable::isDataFlavorSupported( const DataFlavor& aFlavor ) 
	throw(RuntimeException)
{
	sal_Int32 nLength = m_seqDFlv.getLength( );
	sal_Bool bRet     = sal_False;

	for ( sal_Int32 i = 0; i < nLength; ++i )
	{
		if ( m_seqDFlv[i] == aFlavor )
		{
			bRet = sal_True;
			break;
		}
	}

	return bRet;
}

//----------------------------------------------------------------
//	lostOwnership
//----------------------------------------------------------------

void SAL_CALL CTransferable::lostOwnership( const Reference< XClipboard >& xClipboard, const Reference< XTransferable >& xTrans ) 
	throw(RuntimeException)
{
}
