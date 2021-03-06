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
#include "zipexcptn.hxx"
#include "internal/zipfile.hxx"
#include "internal/global.hxx"

#include <malloc.h>
#include <algorithm>
#include <functional>

#include <string.h>

#ifdef OS2
#include <alloca.h>
#define _alloca alloca
#define ERROR_NOT_ENOUGH_MEMORY 8
#endif

namespace internal
{
    /* for case in-sensitive string comparison */
    struct stricmp : public std::unary_function<std::string, bool>
    {
        stricmp(const std::string& str) : str_(str)
        {}
        
        bool operator() (const std::string& other)
        { return (0 == _stricmp(str_.c_str(), other.c_str())); }
                    
        std::string str_;        
    };
} // namespace internal

/** Checks whether a file is a zip file or not

	@precond	The given parameter must be a string with length > 0
			The file must exist
			The file must be readable for the current user
			
	@returns	true if the file is a zip file 
			false if the file is not a zip file
			
	@throws	ParameterException if the given file name is empty 
			IOException if the specified file doesn't exist
			AccessViolationException if read access to the file is denied			
*/
bool ZipFile::IsZipFile(const std::string& /*FileName*/)
{
	return true;
}

bool ZipFile::IsZipFile(void* /*stream*/)
{
	return true;
}


/** Returns wheter the version of the specified zip file may be uncompressed with the
	      currently used zlib version or not
	      
	@precond	The given parameter must be a string with length > 0
			The file must exist
			The file must be readable for the current user
			The file must be a valid zip file
			
	@returns	true if the file may be uncompressed with the currently used zlib
			false if the file may not be uncompressed with the currently used zlib
			
	@throws	ParameterException if the given file name is empty 
			IOException if the specified file doesn't exist or is no zip file
			AccessViolationException if read access to the file is denied			
*/
bool ZipFile::IsValidZipFileVersionNumber(const std::string& /*FileName*/)
{
	return true;
}

bool ZipFile::IsValidZipFileVersionNumber(void* /* stream*/)
{
	return true;
}


/** Constructs a zip file from a zip file
	
	@precond	The given parameter must be a string with length > 0
			The file must exist
			The file must be readable for the current user
			
	@throws	ParameterException if the given file name is empty 
			IOException if the specified file doesn't exist or is no valid zip file
			AccessViolationException if read access to the file is denied
			WrongZipVersionException if the zip file cannot be uncompressed 
			with the used zlib version
*/
ZipFile::ZipFile(const std::string& FileName)
{
	m_uzFile = unzOpen(FileName.c_str());

	if (0 == m_uzFile)
		throw IOException(-1);
}

ZipFile::ZipFile(void* stream, zlib_filefunc_def* fa) 
{
	fa->opaque = stream;
	m_uzFile = unzOpen2((const char *)NULL, fa);

	if (0 == m_uzFile)
		throw IOException(-1);
}


/** Destroys a zip file
*/
ZipFile::~ZipFile()
{
	unzClose(m_uzFile);
}

/** Provides an interface to read the uncompressed data of a content of the zip file
	
	@precond	The specified content must exist in this file
			ppstm must not be NULL
*/
void ZipFile::GetUncompressedContent(
	const std::string& ContentName, /*inout*/ ZipContentBuffer_t& ContentBuffer)	
{
	int rc = unzLocateFile(m_uzFile, ContentName.c_str(), 0); 
	
	if (UNZ_END_OF_LIST_OF_FILE == rc)
		throw ZipContentMissException(rc);

	unz_file_info finfo;
	unzGetCurrentFileInfo(m_uzFile, &finfo, 0, 0, 0, 0, 0, 0);
		
	ContentBuffer.resize(finfo.uncompressed_size);

	rc = unzOpenCurrentFile(m_uzFile);
	
	if (UNZ_OK != rc)
		throw ZipException(rc);

	rc = unzReadCurrentFile(m_uzFile, &ContentBuffer[0], finfo.uncompressed_size);
	
	if (rc < 0)
		throw ZipException(rc);

	rc = unzCloseCurrentFile(m_uzFile);	

	if (rc < 0)
		throw ZipException(rc);
}

/** Returns a list with the content names contained within this file
	
*/
ZipFile::DirectoryPtr_t ZipFile::GetDirectory() const 
{
	DirectoryPtr_t dir(new Directory_t());

	long lmax = GetFileLongestFileNameLength() + 1;
	char* szFileName = reinterpret_cast<char*>(_alloca(lmax));

	if (!szFileName)
		throw ZipException(ERROR_NOT_ENOUGH_MEMORY);

	int rc = unzGoToFirstFile(m_uzFile);

	while (UNZ_OK == rc && UNZ_END_OF_LIST_OF_FILE != rc)
	{				
		unz_file_info finfo;
		unzGetCurrentFileInfo(
			m_uzFile, &finfo, szFileName, lmax, 0, 0, 0, 0);

		dir->push_back(szFileName);

		rc = unzGoToNextFile(m_uzFile);
	}

	if (UNZ_OK != rc && UNZ_END_OF_LIST_OF_FILE != rc)
		throw ZipException(rc);

	return dir;
}

/** Convinience query function may even realized with 
	iterating over a ZipFileDirectory returned by
	GetDirectory */
bool ZipFile::HasContent(const std::string& ContentName) const
{
    //#i34314# we need to compare package content names
    //case in-sensitive as it is not defined that such
    //names must be handled case sensitive
	DirectoryPtr_t dir = GetDirectory();
	Directory_t::iterator iter = 
        std::find_if(dir->begin(), dir->end(), internal::stricmp(ContentName));
            
	return (iter != dir->end());
}


/** Returns the length of the longest file name
		in the current zip file
*/
long ZipFile::GetFileLongestFileNameLength() const
{
	long lmax = 0;
	unz_file_info finfo;

	int rc = unzGoToFirstFile(m_uzFile);

	while (UNZ_OK == rc && UNZ_END_OF_LIST_OF_FILE != rc)
	{				
		unzGetCurrentFileInfo(m_uzFile,	&finfo, 0, 0, 0, 0, 0, 0);		
		lmax = std::max<long>(lmax, finfo.size_filename);
		rc = unzGoToNextFile(m_uzFile);
	}

	if (UNZ_OK != rc && UNZ_END_OF_LIST_OF_FILE != rc)
		throw ZipException(rc);

	return lmax;
}

