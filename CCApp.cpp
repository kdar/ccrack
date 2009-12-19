#include <wx/wx.h>
#include <wx/app.h>

#include "CCApp.h"
#include "CCFrame.h"
#include "CrackManager.h"
#include "ProgressControl.h"

//crack classes
#include "DialogBlocks.h"

CrackManager *g_Cm;
ProgressControl *g_Pc;

IMPLEMENT_APP (CCApp);

//======================================
bool CCApp::OnInit ()
{
  CCFrame *pFrame = new CCFrame ();
  SetTopWindow (pFrame);
  pFrame->Show (true);

  g_Pc = new ProgressControl (pFrame);

  g_Cm = new CrackManager (pFrame);
  g_Cm->Add (new DialogBlocks ());

  return true;
}

//======================================
int CCApp::OnExit ()
{
  if (g_Cm) delete g_Cm;
  if (g_Pc) delete g_Pc;

  return 0;
}
