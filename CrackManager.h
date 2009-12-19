#ifndef _CRACKMANAGER_H
#define _CRACKMANAGER_H

#include <wx/listctrl.h>
#include <wx/dynarray.h>

#include "CrackBase.h"

WX_DEFINE_ARRAY (CrackBase *, CrackList);

class CrackManager
{
  public:
    CrackManager (wxWindow *pFrame);
    virtual ~CrackManager ();

    void Add (CrackBase *pCrack);

    int CrackFile ();

  private:
    wxWindow *m_pFrame;
    wxListCtrl *m_pList;

    CrackList m_CrackList;
};

#endif
