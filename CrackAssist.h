#ifndef _CRACKASSIST_H
#define _CRACKASSIST_H

#include <cstdio>

//string search algorithms found at: http://www-igm.univ-mlv.fr/~lecroq/string/
//we use descendants of the Boyer-Moore algorithm

enum CrackStatus
{
  CRACK_Failed = 0,
  CRACK_Success,
  CRACK_NotFound
};

enum SearchAlgorithm
{
  SEARCH_TBM = 0
};

class CrackAssist
{
  public:
    CrackAssist () : m_fp(0), m_nAlgorithm(SEARCH_TBM) {}

    //try changing to const
    virtual int Search (const char *x, int m, const char *y, int n, int nStartOffset = 0);    

    //file functions
    bool FOpen (const char *szPath, const char *modes);
    bool FClose ();
    size_t FRead (void *ptr, size_t size, size_t nMemb);
    size_t FWrite (const void *ptr, size_t size, size_t nMemb);
    bool FSeek (long lOffset, int nWhence = SEEK_SET);
    long FTell ();
    void FRewind ();
    int FNo () { return fileno (m_fp); }
    long FSize ();

    void SetAlgorithm (int nAlgorithm) { m_nAlgorithm = nAlgorithm; }
    int GetAlgorithm () { return m_nAlgorithm; }

    bool PatchOffset (long lOffset, unsigned char *pWith, unsigned int nWithSize, bool bMaintainSeek = false);

    static const int ASIZE = 0xFFFF; //0xFFFF is needed to accommodate binary, ascii only needs 256
    static const int XSIZE = 8080; //max size of item being searched

  protected:
    //search algorithm functions
    virtual int TBM (const char *x, int m, const char *y, int n, int nStartOffset = 0);
    //table building functions for search algorithms
    virtual void preBmBc (const char *x, int m, int bmBc[]);
    virtual void preBmGs (const char *x, int m, int bmGs[]);
    virtual void suffixes (const char *x, int m, int *suff);

    int min (int x, int y) { return x < y ? x : y; }
    int max (int x, int y) { return x > y ? x : y; }    

  private:
    FILE *m_fp;

    int m_nAlgorithm;
};

#endif
