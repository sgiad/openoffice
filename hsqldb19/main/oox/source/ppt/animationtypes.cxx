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




#include "animationtypes.hxx"

#include <com/sun/star/animations/Timing.hpp>

#include "oox/helper/attributelist.hxx"

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::animations;
using namespace ::com::sun::star::xml::sax;

namespace oox { namespace ppt {

// ST_TLTime
Any GetTime(  const ::rtl::OUString & val )
{
	Any aDuration;
	if( val.compareToAscii( "indefinite" ) == 0 )
	{
		aDuration <<= Timing_INDEFINITE;
	}
	else
	{
		aDuration <<= val.toFloat() / 1000.0;
	}
	return aDuration;
}


// ST_TLTimeAnimateValueTime
Any GetTimeAnimateValueTime( const ::rtl::OUString & val )
{
	Any aPercent;
	if( val.compareToAscii( "indefinite" ) == 0 )
	{
		aPercent <<= Timing_INDEFINITE;
	}
	else
	{
		aPercent <<= val.toFloat() / 100000.0;
	}
	return aPercent;
}

} }
