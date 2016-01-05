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



#ifndef DOM_DOMIMPLEMENTATION_HXX
#define DOM_DOMIMPLEMENTATION_HXX

#include <sal/types.h>

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/xml/dom/XDocument.hpp>
#include <com/sun/star/xml/dom/XDocumentType.hpp>
#include <com/sun/star/xml/dom/XDOMImplementation.hpp>

#include <cppuhelper/implbase1.hxx>


using ::rtl::OUString;
using namespace com::sun::star::uno;
using namespace com::sun::star::xml::dom;

namespace DOM
{
    class CDOMImplementation
        : public cppu::WeakImplHelper1< XDOMImplementation >
    {

    public:
        static CDOMImplementation* get();

        // there is just 1 static instance, so these must not delete it!
        virtual void SAL_CALL acquire() throw ();
        virtual void SAL_CALL release() throw ();

        /**
        Creates a DOM Document object of the specified type with its document element.
        */
        virtual Reference <XDocument > SAL_CALL createDocument(const OUString& namespaceURI, const OUString& qualifiedName, const Reference< XDocumentType >& doctype)
            throw (RuntimeException);

        /**
        Creates an empty DocumentType node.
        */
        virtual Reference< XDocumentType > SAL_CALL createDocumentType(const OUString& qualifiedName, const OUString& publicId, const OUString& systemId)
            throw (RuntimeException);

        /**
        Test if the DOM implementation implements a specific feature.
        */
        virtual sal_Bool SAL_CALL hasFeature(const OUString& feature, const OUString& ver)
            throw (RuntimeException);
        };
}
#endif
