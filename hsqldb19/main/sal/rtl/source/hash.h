#ifndef INCLUDED_RTL_SOURCE_HASH_H
#define INCLUDED_RTL_SOURCE_HASH_H
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

#include <sal/types.h>
#include <rtl/ustring.h>

#if defined __cplusplus
extern "C" {
#endif /* __cplusplus */

/* These functions are not multi-thread safe: */

rtl_uString     *rtl_str_hash_intern (rtl_uString       *pString,
                                      int                can_return);
void             rtl_str_hash_remove (rtl_uString       *pString);

#if defined __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUDED_RTL_SOURCE_HASH_H */
