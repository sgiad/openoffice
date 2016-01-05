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




#ifndef _SC_ACCESSIBLEPAGEHEADERAREA_HXX
#define _SC_ACCESSIBLEPAGEHEADERAREA_HXX

#ifndef _SC_ACCESSIBLE_CONTEXT_BASE_HXX
#include "AccessibleContextBase.hxx"
#endif
#include <editeng/svxenum.hxx>

class EditTextObject;
namespace accessibility
{
    class AccessibleTextHelper;
}
class ScPreviewShell;

class ScAccessiblePageHeaderArea
	:	public ScAccessibleContextBase
{
public:
	//=====  internal  ========================================================
	ScAccessiblePageHeaderArea(
        const ::com::sun::star::uno::Reference<
        ::com::sun::star::accessibility::XAccessible>& rxParent,
        ScPreviewShell* pViewShell,
        const EditTextObject* pEditObj,
        sal_Bool bHeader,
        SvxAdjust eAdjust);
protected:
	virtual ~ScAccessiblePageHeaderArea	(void);
public:
    const EditTextObject* GetEditTextObject() const { return mpEditObj; }

    using ScAccessibleContextBase::disposing;
    virtual void SAL_CALL disposing();

   ///=====  SfxListener  =====================================================

	virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    ///=====  XAccessibleComponent  ============================================

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible >
		SAL_CALL getAccessibleAtPoint(
		const ::com::sun::star::awt::Point& rPoint )
		throw (::com::sun::star::uno::RuntimeException);

	///=====  XAccessibleContext  ==============================================

    ///	Return the number of currently visible children.
    // is overloaded to calculate this on demand
    virtual sal_Int32 SAL_CALL
    	getAccessibleChildCount(void)
    				throw (::com::sun::star::uno::RuntimeException);

    ///	Return the specified child or NULL if index is invalid.
    // is overloaded to calculate this on demand
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible> SAL_CALL
    	getAccessibleChild(sal_Int32 nIndex)
        throw (::com::sun::star::uno::RuntimeException,
				::com::sun::star::lang::IndexOutOfBoundsException);

	///	Return the set of current states.
	virtual ::com::sun::star::uno::Reference<
            ::com::sun::star::accessibility::XAccessibleStateSet> SAL_CALL
    	getAccessibleStateSet(void)
        throw (::com::sun::star::uno::RuntimeException);

	///=====  XServiceInfo  ====================================================

    /**	Returns an identifier for the implementation of this object.
    */
	virtual ::rtl::OUString SAL_CALL
    	getImplementationName(void)
        throw (::com::sun::star::uno::RuntimeException);

    /** Returns a list of all supported services.  In this case that is just
    	the AccessibleContext and Accessible service.
    */
	virtual ::com::sun::star::uno::Sequence< ::rtl::OUString> SAL_CALL
    	getSupportedServiceNames(void)
        throw (::com::sun::star::uno::RuntimeException);

    ///=====  XTypeProvider  ===================================================

    /**	Returns a implementation id.
    */
    virtual ::com::sun::star::uno::Sequence<sal_Int8> SAL_CALL
        getImplementationId(void)
        throw (::com::sun::star::uno::RuntimeException);

protected:
	virtual ::rtl::OUString SAL_CALL createAccessibleDescription(void) throw(::com::sun::star::uno::RuntimeException);
	virtual ::rtl::OUString SAL_CALL createAccessibleName(void) throw (::com::sun::star::uno::RuntimeException);

	virtual Rectangle GetBoundingBoxOnScreen(void) const throw(::com::sun::star::uno::RuntimeException);
	virtual Rectangle GetBoundingBox(void) const throw (::com::sun::star::uno::RuntimeException);

private:
    EditTextObject* mpEditObj;
	accessibility::AccessibleTextHelper* mpTextHelper;
    ScPreviewShell* mpViewShell;
    sal_Bool mbHeader;
    SvxAdjust meAdjust;

	void CreateTextHelper();
};


#endif

