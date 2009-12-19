#ifndef _CRACKBASE_H
#define _CRACKBASE_H

class CrackBase
{
  public:
    CrackBase () { m_szTitle = "BAD DERIVATION, CHECK CODE"; }
    CrackBase (char *szTitle) { m_szTitle = szTitle; }
    virtual ~CrackBase () {}

    virtual int CrackFile (const char *szPath) = 0;

    char *GetTitle () { return m_szTitle; }
    void SetTitle (char *szTitle) { m_szTitle = szTitle; }

  protected:
    char *m_szTitle;
};

#endif