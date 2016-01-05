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



#ifndef INCLUDED_SLIDESHOW_ACCUMULATION_HXX
#define INCLUDED_SLIDESHOW_ACCUMULATION_HXX

#include <sal/types.h>
#include <rtl/ustring.hxx>


namespace slideshow
{
    namespace internal
    {
        /** Generic accumulation.

        	This template handles value accumulation across repeated
        	effect runs: returned is the end value times the repeat
        	count, plus the current value.
            
        	@param rEndValue
            End value of the simple animation.

            @param nRepeatCount
            Number of completed repeats (i.e. 0 during the first
            effect run)

            @param rCurrValue
            Current animation value
         */
        template< typename ValueType > ValueType accumulate( const ValueType& 	rEndValue, 
                                                             sal_uInt32 		nRepeatCount, 
                                                             const ValueType& 	rCurrValue )
        {
            return nRepeatCount*rEndValue + rCurrValue;
        }

        /// Specialization for non-addable enums/constant values
        template<> sal_Int16 accumulate< sal_Int16 >( const sal_Int16&, 
                                                      sal_uInt32, 
                                                      const sal_Int16& 	rCurrValue )
        {
            // always return rCurrValue, it's forbidden to add enums/constant values...
            return rCurrValue;
        }

        /// Specialization for non-addable strings
        template<> ::rtl::OUString accumulate< ::rtl::OUString >( const ::rtl::OUString&, 
                                                                  sal_uInt32,
                                                                  const ::rtl::OUString& 	rCurrValue )
        {
            // always return rCurrValue, it's impossible to add strings...
            return rCurrValue;
        }

        /// Specialization for non-addable bools
        template<> bool accumulate< bool >( const bool&, 
                                            sal_uInt32, 
                                            const bool&	 	bCurrValue )
        {
            // always return bCurrValue, SMIL spec requires to ignore
            // cumulative behaviour for bools.
            return bCurrValue;
        }
    }
}

#endif /* INCLUDED_SLIDESHOW_ACCUMULATION_HXX */
