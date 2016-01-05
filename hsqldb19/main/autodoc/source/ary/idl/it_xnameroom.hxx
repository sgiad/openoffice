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



#ifndef ARY_IDL_IT_XNAMEROOM_HXX
#define ARY_IDL_IT_XNAMEROOM_HXX

// BASE CLASSES
#include <ary/idl/i_type.hxx>
#include <nametreenode.hxx>




namespace ary
{
namespace idl
{


/** A namespace for ->Type s, as they are explicitely written in code.

    The search/identification string is usually the local name of
    the Type. But for templated structs, the search string has this
    pattern:
                <LocalName> '<' <StringOfTemplateTypeId>
*/
class ExplicitNameRoom : public Type
{
  public:
    enum E_ClassId { class_id = 2204 };

    // LIFECYCLE
                        ExplicitNameRoom();
                        ExplicitNameRoom(
                            const String &      i_sName,
                            const ExplicitNameRoom &
                                                i_rParent );
    virtual             ~ExplicitNameRoom();

    // OPERATIONS
    /** @param i_sSearchString
                A local type name  usually.
                For templated types see class docu.
        @see ExplicitNameRoom
    */
    void                Add_Name(
                            const String &      i_sSearchString,
                            Type_id             i_nId )
                            { aImpl.Add_Name(i_sSearchString,i_nId); }
    // INQUIRY
    const String &      Name() const            { return aImpl.Name(); }
    intt                Depth() const           { return aImpl.Depth(); }
    void                Get_FullName(
                            StringVector &      o_rText,
                            Ce_idList *         o_pRelatedCes,
                            const Gate &        i_rGate ) const;
    bool                IsAbsolute() const      { return Depth() > 0
                                                    ?   (*NameChain_Begin()).empty()
                                                    :   false; }
    /** @param i_sSearchString
                A local type name  usually.
                For templated types see class docu.
        @see ExplicitNameRoom
    */
    Type_id             Search_Name(
                            const String &      i_sSearchString ) const
                            { return aImpl.Search_Name(i_sSearchString); }

    StringVector::const_iterator
                        NameChain_Begin() const
                            { return aImpl.NameChain_Begin(); }
    StringVector::const_iterator
                        NameChain_End() const
                            { return aImpl.NameChain_End(); }
  private:
    // Interface csv::ConstProcessorClient:
    virtual void        do_Accept(
                            csv::ProcessorIfc & io_processor ) const;
    // Interface Object:
    virtual ClassId     get_AryClass() const;

    // Interface Type:
    virtual void        inq_Get_Text(
                            StringVector &      o_module,
                            String &            o_name,
                            Ce_id &             o_nRelatedCe,
                            int &               o_nSequemceCount,
                            const Gate &        i_rGate ) const;
    // DATA
    NameTreeNode<Type_id>
                        aImpl;
};




}   // namespace idl
}   // namespace ary
#endif
