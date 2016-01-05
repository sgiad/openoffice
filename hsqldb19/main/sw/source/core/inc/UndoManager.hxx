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



#ifndef SW_UNDO_MANAGER_HXX
#define SW_UNDO_MANAGER_HXX

#include <IDocumentUndoRedo.hxx>
#include <memory>
#include <svx/sdrundomanager.hxx>

class IDocumentDrawModelAccess;
class IDocumentRedlineAccess;
class IDocumentState;

namespace sw {

class UndoManager
    : public IDocumentUndoRedo
    , public SdrUndoManager
{
public:

    UndoManager(::std::auto_ptr<SwNodes> pUndoNodes,
        IDocumentDrawModelAccess & rDrawModelAccess,
        IDocumentRedlineAccess & rRedlineAccess,
        IDocumentState & rState);

    /** IDocumentUndoRedo */
    virtual void DoUndo(bool const bDoUndo);
    virtual bool DoesUndo() const;
    virtual void DoGroupUndo(bool const bDoUndo);
    virtual bool DoesGroupUndo() const;
    virtual void DoDrawUndo(bool const bDoUndo);
    virtual bool DoesDrawUndo() const;
    virtual void SetUndoNoModifiedPosition();
    virtual void LockUndoNoModifiedPosition();
    virtual void UnLockUndoNoModifiedPosition();
    virtual void SetUndoNoResetModified();
    virtual bool IsUndoNoResetModified() const;
    virtual SwUndoId StartUndo(SwUndoId const eUndoId,
                SwRewriter const*const pRewriter);
    virtual SwUndoId EndUndo(SwUndoId const eUndoId,
                SwRewriter const*const pRewriter);
    virtual void DelAllUndoObj();
    virtual bool GetLastUndoInfo(::rtl::OUString *const o_pStr,
                                 SwUndoId *const o_pId) const;
    virtual SwUndoComments_t GetUndoComments() const;
    virtual bool GetFirstRedoInfo(::rtl::OUString *const o_pStr,
                                  SwUndoId *const o_pId = 0) const;
    virtual SwUndoComments_t GetRedoComments() const;
    virtual bool Repeat(::sw::RepeatContext & rContext,
                sal_uInt16 const nRepeatCnt);
    virtual SwUndoId GetRepeatInfo(::rtl::OUString *const o_pStr) const;
    virtual void AppendUndo(SwUndo *const pUndo);
    virtual void ClearRedo();
    virtual bool IsUndoNodes(SwNodes const& rNodes) const;

    // ::svl::IUndoManager
    virtual void     AddUndoAction(SfxUndoAction *pAction,
                                   sal_Bool bTryMerg = sal_False);
    virtual sal_Bool Undo();
    virtual sal_Bool Redo();
    virtual void     EnableUndo(bool bEnable);

    SwUndo * RemoveLastUndo();
    SwUndo * GetLastUndo();

    SwNodes const& GetUndoNodes() const;
    SwNodes      & GetUndoNodes();

private:
    IDocumentDrawModelAccess & m_rDrawModelAccess;
    IDocumentRedlineAccess & m_rRedlineAccess;
    IDocumentState & m_rState;

    /// Undo nodes array: content not currently in document
    ::std::auto_ptr<SwNodes> m_pUndoNodes;

    bool m_bGroupUndo       : 1;    // TRUE: Undo grouping enabled
    bool m_bDrawUndo        : 1;    // TRUE: Draw Undo enabled
    bool m_bLockUndoNoModifiedPosition : 1;
    /// position in Undo-Array at which Doc was saved (and is not modified)
    UndoStackMark m_UndoSaveMark;

    typedef enum { UNDO = true, REDO = false } UndoOrRedo_t;
    bool impl_DoUndoRedo(UndoOrRedo_t const undoOrRedo);

    // UGLY: should not be called
    using SdrUndoManager::Repeat;
};

} // namespace sw

#endif // SW_UNDO_MANAGER_HXX

