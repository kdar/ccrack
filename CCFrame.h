#ifndef _CCFRAME_H
#define _CCFRAME_H

#include <wx/listctrl.h>
#include <wx/dnd.h>

class FileDropTarget;

//======================================
class CCFrame : public wxFrame
{
  DECLARE_EVENT_TABLE ()

  public:
    CCFrame (wxWindow *pParent = NULL);
    virtual ~CCFrame ();

  protected:
    void OnButtonBrowse (wxCommandEvent &event);
    void OnButtonCrack (wxCommandEvent &event);
    void OnButtonExit (wxCommandEvent &event);
    void OnButtonHelp (wxCommandEvent &event);

  private:
    friend class FileDropTarget;

    wxTextCtrl *m_pTextPath;
    wxButton *m_pButtonCrack;
    wxListCtrl *m_pCrackListc;

    wxString m_LastDirectory;
};

//======================================
class FileDropTarget : public wxFileDropTarget
{
  public:
    FileDropTarget (CCFrame *pFrame) : wxFileDropTarget (), m_pFrame(pFrame) {}

    virtual bool OnDropFiles (wxCoord x, wxCoord y, const wxArrayString &filenames);

  private:
    CCFrame *m_pFrame;
};

#endif
