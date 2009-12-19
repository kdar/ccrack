#ifndef _PROGRESSCONTROL_H
#define _PROGRESSCONTROL_H

#include <wx/gauge.h>

class ProgressControl
{
  public:
    ProgressControl (wxWindow *pFrame);

    void Increment (int nCount);
    void Decrement (int nCount);
    void SetValue (int nCount);
    void Reset ();
    void Refresh ();

  private:
    wxWindow *m_pFrame;
    wxGauge *m_pGauge;

    int m_nValue;
};

#endif
