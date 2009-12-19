/////////////////////////////////////////////////////////////////////////////
// Name:        CCPanel.cpp
// Purpose:     
// Author:      crenix
// Modified by: 
// Created:     12/30/03 15:40:49
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "CCPanel.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

////@begin includes
#include "wx/wx.h"
#include "wx/listctrl.h"
#include "wx/statline.h"
////@end includes

#include "CCPanel.h"

////@begin XPM images

////@end XPM images

/*!
 * CCPanel type definition
 */

IMPLEMENT_CLASS( CCPanel, wxPanel )

/*!
 * CCPanel event table definition
 */

BEGIN_EVENT_TABLE( CCPanel, wxPanel )

////@begin CCPanel event table entries
////@end CCPanel event table entries

END_EVENT_TABLE()

/*!
 * CCPanel constructors
 */

CCPanel::CCPanel( )
{
}

CCPanel::CCPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, pos, size, style);
}

/*!
 * CCPanel creator
 */

bool CCPanel::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CCPanel member initialisation
////@end CCPanel member initialisation

////@begin CCPanel creation
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end CCPanel creation
    return TRUE;
}

/*!
 * Control creation for CCPanel
 */

void CCPanel::CreateControls()
{    
////@begin CCPanel content construction

    CCPanel* item1 = this;

    wxBoxSizer* item2 = new wxBoxSizer(wxVERTICAL);
    item1->SetSizer(item2);
    item1->SetAutoLayout(TRUE);

    wxBoxSizer* item3 = new wxBoxSizer(wxHORIZONTAL);
    item2->Add(item3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3);

    wxListCtrl* item4 = new wxListCtrl( item1, ID_ListCracks, wxDefaultPosition, wxSize(150, 100), wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_HRULES|wxSIMPLE_BORDER );
    item3->Add(item4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    item3->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1);

    wxBoxSizer* item6 = new wxBoxSizer(wxVERTICAL);
    item3->Add(item6, 0, wxALIGN_TOP|wxALL, 0);

    wxBoxSizer* item7 = new wxBoxSizer(wxHORIZONTAL);
    item6->Add(item7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxTextCtrl* item8 = new wxTextCtrl( item1, ID_TextPath, _T(""), wxDefaultPosition, wxSize(200, 20), wxTE_READONLY|wxSIMPLE_BORDER );
    item8->SetHelpText(_("Path to the software executable."));
    if (ShowToolTips())
        item8->SetToolTip(_("Path to the software executable."));
    item7->Add(item8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    item7->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1);

    wxButton* item10 = new wxButton( item1, ID_ButtonBrowse, _("Browse..."), wxDefaultPosition, wxSize(-1, 20), 0 );
    item10->SetHelpText(_("Find the program to crack..."));
    if (ShowToolTips())
        item10->SetToolTip(_("Find the program to crack..."));
    item7->Add(item10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    wxStaticLine* item11 = new wxStaticLine( item1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    item6->Add(item11, 0, wxGROW|wxALL, 5);

    wxBoxSizer* item12 = new wxBoxSizer(wxHORIZONTAL);
    item6->Add(item12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxButton* item13 = new wxButton( item1, ID_ButtonCrack, _("Crack"), wxDefaultPosition, wxSize(-1, 20), 0 );
    item13->SetHelpText(_("Crack the above program."));
    if (ShowToolTips())
        item13->SetToolTip(_("Crack the above program."));
    item12->Add(item13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    item12->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1);

    wxButton* item15 = new wxButton( item1, ID_ButtonHelp, _("?"), wxDefaultPosition, wxSize(15, 20), 0 );
    item15->SetHelpText(_("View the about."));
    if (ShowToolTips())
        item15->SetToolTip(_("View the about."));
    item12->Add(item15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    item12->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 1);

    wxButton* item17 = new wxButton( item1, ID_ButtonExit, _("Exit"), wxDefaultPosition, wxSize(-1, 20), 0 );
    item17->SetHelpText(_("Exit the program."));
    if (ShowToolTips())
        item17->SetToolTip(_("Exit the program."));
    item12->Add(item17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

    item6->Add(0, 27, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxBoxSizer* item19 = new wxBoxSizer(wxHORIZONTAL);
    item6->Add(item19, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

    wxGauge* item20 = new wxGauge( item1, ID_Gauge, 100, wxDefaultPosition, wxSize(250, 20), wxGA_HORIZONTAL|wxGA_PROGRESSBAR|wxGA_SMOOTH|wxSIMPLE_BORDER );
    item20->SetValue(0);
    item19->Add(item20, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

////@end CCPanel content construction
}

/*!
 * Should we show tooltips?
 */

bool CCPanel::ShowToolTips()
{
    return TRUE;
}
