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
#include "precompiled_shell.hxx"

#if defined _MSC_VER
#pragma warning(push, 1)
#endif
#include <windows.h>
#if defined _MSC_VER
#pragma warning(pop)
#endif 
#include <malloc.h>
#include "internal/dbgmacros.hxx"
#include "internal/registry.hxx"

#if defined _MSC_VER
#pragma warning(push, 1)
#endif
#include <objbase.h>
#if defined _MSC_VER
#pragma warning(pop)
#endif 

//---------------------------------------
//
//---------------------------------------

// Size of a CLSID as a string
const int CLSID_STRING_SIZE = 39;

//---------------------------------------
//
//---------------------------------------

bool SetRegistryKey(HKEY RootKey, const char* KeyName, const char* ValueName, const char* Value)
{
	HKEY hSubKey;

	// open or create the desired key
	int rc = RegCreateKeyExA(
		RootKey, KeyName, 0, "", REG_OPTION_NON_VOLATILE, KEY_WRITE, 0, &hSubKey, 0);
	
	if (ERROR_SUCCESS == rc)
	{
		rc = RegSetValueExA(
			hSubKey, ValueName, 0, REG_SZ, reinterpret_cast<const BYTE*>(Value), strlen(Value) + 1);

		RegCloseKey(hSubKey);
	}

	return (ERROR_SUCCESS == rc);
}

//---------------------------------------
//
//---------------------------------------

bool DeleteRegistryKey(HKEY RootKey, const char* KeyName)
{
	HKEY hKey;

	int rc = RegOpenKeyExA(
		RootKey,
		KeyName,
		0,
		KEY_READ | DELETE,
		&hKey);

	if ( rc == ERROR_FILE_NOT_FOUND )
		return true;
	
	if (ERROR_SUCCESS == rc)
	{	
		char* SubKey;
		DWORD nMaxSubKeyLen;

		rc = RegQueryInfoKeyA(
			hKey, 0, 0, 0, 0,
			&nMaxSubKeyLen,
			0, 0, 0, 0, 0, 0);
	
		nMaxSubKeyLen++; // space for trailing '\0'

		SubKey = reinterpret_cast<char*>(
			_alloca(nMaxSubKeyLen*sizeof(char)));

		while (ERROR_SUCCESS == rc)
        {
			DWORD nLen = nMaxSubKeyLen;

			rc = RegEnumKeyExA(
				hKey,
                0,       // always index zero
                SubKey,
                &nLen,
                0, 0, 0, 0);

            if (ERROR_NO_MORE_ITEMS == rc)
            {
				rc = RegDeleteKeyA(RootKey, KeyName);
                break;
            }
            else if (rc == ERROR_SUCCESS)
			{
				DeleteRegistryKey(hKey, SubKey);
			}

		} // while

        RegCloseKey(hKey);        

	} // if

	return (ERROR_SUCCESS == rc);
}

/** May be used to determine if the specified registry key has subkeys
	The function returns true on success else if an error occures false
*/
bool HasSubkeysRegistryKey(HKEY RootKey, const char* KeyName, /* out */ bool& bResult)
{
	HKEY hKey;

	LONG rc = RegOpenKeyExA(RootKey, KeyName, 0, KEY_READ, &hKey);
	
	if (ERROR_SUCCESS == rc)
	{
		DWORD nSubKeys = 0;
		
		rc = RegQueryInfoKeyA(hKey, 0, 0, 0, &nSubKeys, 0, 0, 0, 0, 0, 0, 0);

		bResult = (nSubKeys > 0);
	}

	return (ERROR_SUCCESS == rc);
}

// Convert a CLSID to a char string.
std::string ClsidToString(const CLSID& clsid)
{	
	// Get CLSID
	LPOLESTR wszCLSID = NULL;
	StringFromCLSID(clsid, &wszCLSID);

	char buff[39];
	// Covert from wide characters to non-wide.
	wcstombs(buff, wszCLSID, sizeof(buff));

	// Free memory.
	CoTaskMemFree(wszCLSID) ;

	return std::string(buff);
}

//---------------------------------------
//
//---------------------------------------

bool QueryRegistryKey(HKEY RootKey, const char* KeyName, const char* ValueName, char *pszData, DWORD dwBufLen)
{
	HKEY hKey;

	int rc = RegOpenKeyExA(
		RootKey,
		KeyName,
		0,
		KEY_READ,
		&hKey);
	
	if (ERROR_SUCCESS == rc)
	{	
		rc = RegQueryValueExA(
			hKey, ValueName, NULL, NULL, (LPBYTE)pszData,&dwBufLen);

		RegCloseKey(hKey);    
	}

	return (ERROR_SUCCESS == rc);
}
