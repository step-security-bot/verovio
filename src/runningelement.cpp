/////////////////////////////////////////////////////////////////////////////
// Name:        runningelement.cpp
// Author:      Laurent Pugin
// Created:     2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "runningelement.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "functorparams.h"
#include "page.h"
#include "staff.h"
#include "text.h"

namespace vrv {

//----------------------------------------------------------------------------
// RunningElement
//----------------------------------------------------------------------------

RunningElement::RunningElement() : Object("re"), AttHorizontalAlign(), AttTyped()
{
    RegisterAttClass(ATT_HORIZONTALALIGN);
    RegisterAttClass(ATT_TYPED);

    Reset();
}

RunningElement::RunningElement(std::string classid) : Object(classid), AttHorizontalAlign(), AttTyped()
{
    RegisterAttClass(ATT_HORIZONTALALIGN);
    RegisterAttClass(ATT_TYPED);

    Reset();
}

RunningElement::~RunningElement()
{
}

void RunningElement::Reset()
{
    Object::Reset();
    ResetHorizontalAlign();
    ResetTyped();
    
    m_drawingPage = NULL;
    m_drawingStaff = NULL;
}
    
int RunningElement::GetDrawingX() const
{
    if (!m_drawingPage) return 0;
    
    /*
    if (this->GetHalign() == HORIZONTALALIGNMENT_left) {
        return 0;
    }
    else if (this->GetHalign() == HORIZONTALALIGNMENT_center) {
        return m_drawingPage->GetContentWidth() / 2;
    }
    else if (this->GetHalign() == HORIZONTALALIGNMENT_right) {
        return m_drawingPage->GetContentWidth();
    }
    */
    
    return 0;
}

int RunningElement::GetDrawingY() const
{
    if (!m_drawingStaff) return 0;
    return m_drawingStaff->GetDrawingY();
}
    
int RunningElement::GetWidth() const
{
    if (!m_drawingPage) return 0;
    
    return m_drawingPage->GetContentWidth();
}
    
void RunningElement::SetDrawingPage(Page *page)
{
    ResetCachedDrawingX();
    m_drawingPage = page;
}

void RunningElement::SetDrawingStaff(Staff *staff)
{
    ResetCachedDrawingY();
    m_drawingStaff = staff;
}
    
//----------------------------------------------------------------------------
// Functor methods
//----------------------------------------------------------------------------

int RunningElement::AlignVertically(FunctorParams *functorParams)
{
    AlignVerticallyParams *params = dynamic_cast<AlignVerticallyParams *>(functorParams);
    assert(params);
    
    params->m_pageWidth = this->GetWidth();

    return FUNCTOR_CONTINUE;
}
    
} // namespace vrv
