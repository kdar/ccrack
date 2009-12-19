#ifndef _DIALOGBLOCKS_H
#define _DIALOGBLOCKS_H

#include "CrackBase.h"
#include "CrackAssist.h"

#define ONE_MINIMUM -1 //at least one occurrence must be present
#define ZERO_MINIMUM -2 //not finding it won't make the crack unsuccessful, but if found then replace it

struct ReplaceEntry
{
  //user filled
  unsigned char *pFind;
  unsigned int nFindSize;
  unsigned char *pReplace; 
  unsigned int nReplaceSize;
  int nOccurrences;      

  //algorithm filled
  long *lpOffsets;       //this is filled in by the search algorithm
  unsigned int nOffsets; //how many offsets found so far
};

struct Methods
{
  ReplaceEntry *entries;
  unsigned int nEntries;
};

class DialogBlocks : public CrackBase
{
  public:
    DialogBlocks ();

    virtual int CrackFile (const char *szPath);

  protected:
    int CrackMethods ();

  private:
    void AddOffset (ReplaceEntry *entry, long lOffset);
    void Cleanup (Methods *methods, unsigned int nMethods);

    CrackAssist m_ca;
};

#endif
