#include <wx/wx.h>

#include "CrackManager.h"
#include "CCPanel.h"

//======================================
CrackManager::CrackManager (wxWindow *pFrame)
{ 
  m_pFrame = pFrame;
  m_pList = (wxListCtrl *)m_pFrame->FindWindow (ID_ListCracks);

  m_pList->InsertColumn (0, "Crack", wxLIST_FORMAT_LEFT);
  wxSize w = m_pList->GetSize ();
  m_pList->SetColumnWidth (0, w.GetWidth ());
}

//======================================
CrackManager::~CrackManager ()
{
  for (unsigned int i = 0; i < m_CrackList.GetCount (); i++) {
    delete m_CrackList[i];
  }
}

//======================================
void CrackManager::Add (CrackBase *pCrack)
{  
  m_CrackList.Add (pCrack);
  
  long tmp = m_pList->InsertItem (0, pCrack->GetTitle ());
  m_pList->SetItemData (tmp, 0);
} 

//======================================
int CrackManager::CrackFile ()
{
  for (long item = m_pList->GetItemCount () - 1; item >= 0; item--) {
    if (m_pList->GetItemState (item, wxLIST_STATE_SELECTED) & wxLIST_STATE_SELECTED) {
      return m_CrackList[item]->CrackFile (((wxTextCtrl *)m_pFrame->FindWindow (ID_TextPath))->GetValue ().c_str ());
    }
  }

  return -1;
}
