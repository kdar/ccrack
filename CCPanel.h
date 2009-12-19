/////////////////////////////////////////////////////////////////////////////
// Name:        CCPanel.h
// Purpose:     
// Author:      crenix
// Modified by: 
// Created:     12/30/03 15:40:49
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _CCPANEL_H_
#define _CCPANEL_H_

#ifdef __GNUG__
#pragma interface "CCPanel.h"
#endif

/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10000
#define ID_ListCracks 10006
#define ID_TextPath 10001
#define ID_ButtonBrowse 10002
#define ID_ButtonCrack 10004
#define ID_ButtonHelp 10005
#define ID_ButtonExit 10003
#define ID_Gauge 10007
////@end control identifiers

/*!
 * CCPanel class declaration
 */

class CCPanel: public wxPanel
{    
    DECLARE_CLASS( CCPanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CCPanel( );
    CCPanel( wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxSIMPLE_BORDER );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxSIMPLE_BORDER );

    /// Creates the controls and sizers
    void CreateControls();

////@begin CCPanel event handler declarations
////@end CCPanel event handler declarations

////@begin CCPanel member function declarations
////@end CCPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin CCPanel member variables
////@end CCPanel member variables
};

#endif
    // _CCPANEL_H_
