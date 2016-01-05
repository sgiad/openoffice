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


#ifndef _BYTE_GRABBER_HXX_
#define _BYTE_GRABBER_HXX_

#include <com/sun/star/uno/Sequence.h>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/io/BufferSizeExceededException.hpp>
#include <com/sun/star/io/IOException.hpp>
#include <com/sun/star/io/NotConnectedException.hpp>
#include <com/sun/star/uno/RuntimeException.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>

#include <osl/mutex.hxx>

namespace com { namespace sun { namespace star {
	namespace io { class XSeekable; class XInputStream; }
} } }
class ByteGrabber 
{
protected:
    ::osl::Mutex m_aMutex;

	com::sun::star::uno::Reference < com::sun::star::io::XInputStream > xStream;
	com::sun::star::uno::Reference < com::sun::star::io::XSeekable > xSeek;
	com::sun::star::uno::Sequence < sal_Int8 > aSequence;
	const sal_Int8 *pSequence;

public:
	ByteGrabber (com::sun::star::uno::Reference < com::sun::star::io::XInputStream > xIstream);
	~ByteGrabber();
	
	void setInputStream (com::sun::star::uno::Reference < com::sun::star::io::XInputStream > xNewStream);
	// XInputStream
    sal_Int32 SAL_CALL readBytes( ::com::sun::star::uno::Sequence< sal_Int8 >& aData, sal_Int32 nBytesToRead ) 
		throw(::com::sun::star::io::NotConnectedException, ::com::sun::star::io::BufferSizeExceededException, ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
	// XSeekable
    sal_Int64 SAL_CALL seek( sal_Int64 location ) 
		throw(::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
    sal_Int64 SAL_CALL getPosition(  ) 
		throw(::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
    sal_Int64 SAL_CALL getLength(  )
		throw(::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);

	ByteGrabber& operator >> (sal_Int8& rInt8);
	ByteGrabber& operator >> (sal_Int16& rInt16);
	ByteGrabber& operator >> (sal_Int32& rInt32);
	ByteGrabber& operator >> (sal_uInt8& ruInt8);
	ByteGrabber& operator >> (sal_uInt16& ruInt16);
	ByteGrabber& operator >> (sal_uInt32& ruInt32);
};

#endif
