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



#ifndef INCLUDED_CONFIGMGR_SOURCE_WRITEMODFILE_HXX
#define INCLUDED_CONFIGMGR_SOURCE_WRITEMODFILE_HXX

#include "sal/config.h"

namespace rtl { class OUString; }

namespace configmgr {

class Components;
struct Data;

void writeModFile(
    Components & components, rtl::OUString const & url, Data const & data);

}

#endif
