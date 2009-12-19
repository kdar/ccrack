#include <wx/wx.h>
#include <wx/stattext.h>

#include "ProgressControl.h"
#include "CCPanel.h"

//======================================
ProgressControl::ProgressControl (wxWindow *pFrame)
  : m_nValue(0)
{ 
  m_pFrame = pFrame;
  m_pGauge = (wxGauge *)m_pFrame->FindWindow (ID_Gauge);

  SetValue (0);
}

//======================================
void ProgressControl::Increment (int nCount)
{
  m_nValue += nCount;
  Refresh ();
}

//======================================
void ProgressControl::Decrement (int nCount)
{
  m_nValue -= nCount;
  Refresh ();
}

//======================================
void ProgressControl::SetValue (int nCount)
{
  m_nValue = nCount;
  Refresh ();
}

//======================================
void ProgressControl::Reset ()
{
  m_nValue = 0;
  Refresh ();
}

//======================================
void ProgressControl::Refresh ()
{
  //make value sane
  if (m_nValue > 100) m_nValue = 100;
  if (m_nValue < 0) m_nValue = 0;

  m_pGauge->SetValue (m_nValue);
}
