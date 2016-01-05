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


#ifndef CONNECTIVITY_ADO_WRAP_KEY_HXX
#define CONNECTIVITY_ADO_WRAP_KEY_HXX

#include "ado/WrapTypeDefs.hxx"

namespace connectivity
{
	namespace ado
	{
		class WpADOKey : public WpOLEBase<ADOKey>
		{
		public:
			WpADOKey(ADOKey* pInt=NULL)	:	WpOLEBase<ADOKey>(pInt){}
			WpADOKey(const WpADOKey& rhs){operator=(rhs);}

			inline WpADOKey& operator=(const WpADOKey& rhs)
				{WpOLEBase<ADOKey>::operator=(rhs); return *this;}

			void Create();

			::rtl::OUString get_Name() const;
			void put_Name(const ::rtl::OUString& _rName);
			KeyTypeEnum get_Type() const;
			void put_Type(const KeyTypeEnum& _eNum) ;
			::rtl::OUString get_RelatedTable() const;
			void put_RelatedTable(const ::rtl::OUString& _rName);
			RuleEnum get_DeleteRule() const;
			void put_DeleteRule(const RuleEnum& _eNum) ;
			RuleEnum get_UpdateRule() const;
			void put_UpdateRule(const RuleEnum& _eNum) ;
			WpADOColumns get_Columns() const;
		};
	}
}

#endif //CONNECTIVITY_ADO_WRAP_KEY_HXX
