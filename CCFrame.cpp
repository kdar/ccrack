#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/filedlg.h>

#include "CCFrame.h"
#include "CCPanel.h"
#include "CrackAssist.h"
#include "CrackManager.h"
#include "ProgressControl.h"

extern ProgressControl *g_Pc;
extern CrackManager *g_Cm;

BEGIN_EVENT_TABLE (CCFrame, wxFrame)
  EVT_BUTTON (ID_ButtonBrowse, OnButtonBrowse)
  EVT_BUTTON (ID_ButtonCrack, OnButtonCrack)
  EVT_BUTTON (ID_ButtonExit, OnButtonExit)
  EVT_BUTTON (ID_ButtonHelp, OnButtonHelp)
END_EVENT_TABLE ()

//======================================
CCFrame::CCFrame (wxWindow *pParent)
  : m_LastDirectory("\\")
{
  wxFrame::Create (pParent, -1, " CCrack by crenix", wxDefaultPosition, wxSize (455, 150), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION);

  CCPanel *pPanel = new CCPanel (this);

  SetIcon (wxIcon ("IDI_ICON1", wxBITMAP_TYPE_ICO_RESOURCE));
  CreateStatusBar ();

  SetStatusText (" Open the file to crack or drag-and-drop file into the path textbox...");

  m_pTextPath = (wxTextCtrl *)FindWindow (ID_TextPath);
  m_pButtonCrack = (wxButton *)FindWindow (ID_ButtonCrack);
  m_pCrackListc = (wxListCtrl *)FindWindow (ID_ListCracks);

  m_pTextPath->SetDropTarget (new FileDropTarget (this));

  m_pTextPath->SetEditable (false);
  m_pButtonCrack->Enable (false);
}

//======================================
CCFrame::~CCFrame ()
{
}

//======================================
void CCFrame::OnButtonBrowse (wxCommandEvent &event)
{
  wxFileDialog *pFileDialog = new wxFileDialog (this, "Choose the program", m_LastDirectory, "", "EXE Files (*.exe)|*.exe");
  int nStatus = pFileDialog->ShowModal ();
  
  if (nStatus == wxID_OK) {
    m_pTextPath->SetValue (pFileDialog->GetDirectory () + "\\" + pFileDialog->GetFilename ());
    m_LastDirectory = pFileDialog->GetDirectory ();

    SetStatusText (" Click on Crack to crack the program...");
    m_pButtonCrack->Enable (true);

    g_Pc->Reset ();
  }  
}

//======================================
void CCFrame::OnButtonCrack (wxCommandEvent &event)
{
  if (m_pCrackListc->GetSelectedItemCount () == 0) {
    wxMessageBox ("Please select a crack in the list before cracking the program.");
    return;
  } 

  SetStatusText ("Cracking...");

  int nStatus = g_Cm->CrackFile ();

  switch (nStatus) {
    case CRACK_Success:
      SetStatusText (" Crack was successful! Have fun.");
      g_Pc->SetValue (100);
      return;
    break;

    case CRACK_Failed:
      SetStatusText (" Crack failed. Unsupported version/program or already cracked.");
    break;

    case CRACK_NotFound:
      SetStatusText (" Program not found. Please try again.");
    break;

    default:
      SetStatusText (" ERROR: Unhandled crack status.");
    break;
  }

  g_Pc->SetValue (0);
}

//======================================
void CCFrame::OnButtonExit (wxCommandEvent &event)
{
  Close (true);
}

//======================================
void CCFrame::OnButtonHelp (wxCommandEvent &event)
{
  wxMessageBox ("CCrack for multiple shareware/commercial software\n"
                "Author: crenix\n"
                "IRC: irc.catheadlabs.com  #brained\n\n"
                "This is for educational purposes only. Do not\n"
                "use this program, go buy the software.", "About");
}

//======================================
bool FileDropTarget::OnDropFiles (wxCoord x, wxCoord y, const wxArrayString &filenames)
{ 
  m_pFrame->m_pTextPath->SetValue (filenames[0]);

  m_pFrame->SetStatusText (" Click on Crack to crack the program...");
  m_pFrame->m_pButtonCrack->Enable (true);

  g_Pc->Reset ();
  return true;
}
