#ifndef _CCAPP_H
#define _CCAPP_H

class CCApp : public wxApp
{
  public:
    virtual bool OnInit ();
    virtual int OnExit ();
};

DECLARE_APP (CCApp)

#endif
