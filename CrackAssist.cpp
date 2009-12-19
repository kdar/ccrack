#include <cstring>

#include "CrackAssist.h"

//======================================
//remember, this returns offsets within the boundries of x, not
//within the file you opened
int CrackAssist::Search (const char *x, int m, const char *y, int n, int nStartOffset)
{
  switch (m_nAlgorithm) {
    case SEARCH_TBM:
      return TBM (x, m, y, n, nStartOffset);
    break;
  }

  return -1;
}

//======================================
//Turbo Boyer Moore algorithm
int CrackAssist::TBM (const char *x, int m, const char *y, int n, int nStartOffset)
{
  int bcShift, i, j, shift, u, v, turboShift;
  int bmGs[XSIZE], bmBc[ASIZE];

   //Preprocessing
   preBmGs (x, m, bmGs);
   preBmBc (x, m, bmBc);

   //Searching
   j = u = nStartOffset;  //changed
   shift = m;
   while (j <= n - m) {
      i = m - 1;
      while (i >= 0 && x[i] == y[i + j]) {
         --i;
         if (u != 0 && i == m - 1 - shift)
            i -= u;
      }
      if (i < 0) {
         return j; //changed
         shift = bmGs[0];
         u = m - shift;
      }
      else {
         v = m - 1 - i;
         turboShift = u - v;
         bcShift = bmBc[y[i + j]] - m + 1 + i;
         shift = max (turboShift, bcShift);
         shift = max (shift, bmGs[i]);
         if (shift == bmGs[i])
            u = min (m - shift, v);
         else {
           if (turboShift < bcShift)
              shift = max (shift, u + 1);
           u = 0;
         }
      }
      j += shift;
   }

   return -1; //changed
}

//======================================
bool CrackAssist::FOpen (const char *szPath, const char *modes)
{
  FILE *fp = fopen (szPath, modes);
  if (fp != NULL) {
    m_fp = fp;
    return true;
  } else {
    return false;
  }
}

//======================================
bool CrackAssist::FClose ()
{
  int nRet = fclose (m_fp);

  if (nRet == 0)
    return true;
  return false;
}

//======================================
size_t CrackAssist::FRead (void *ptr, size_t size, size_t nMemb)
{
  return fread (ptr, size, nMemb, m_fp);
}

//======================================
size_t CrackAssist::FWrite (const void *ptr, size_t size, size_t nMemb)\
{
  return fwrite (ptr, size, nMemb, m_fp);
}

//======================================
bool CrackAssist::FSeek (long lOffset, int nWhence)
{
  int nRet = fseek (m_fp, lOffset, nWhence);

  if (nRet == 0)
    return true;
  return false;
}

//======================================
long CrackAssist::FTell ()
{
  return ftell (m_fp);
}

//======================================
void CrackAssist::FRewind ()
{
  rewind (m_fp);
}

//======================================
long CrackAssist::FSize ()
{
  long lOld = FTell ();
  FSeek (0, SEEK_END);
  long lSize = FTell ();
  FSeek (lOld);

  return lSize;
}

//======================================
//note, if bMaintainSeek is true, it makes patching EXTREMELY slow
//my advice is patch in order, with no maintain seek, default is false
bool CrackAssist::PatchOffset (long lOffset, unsigned char *pWith, unsigned int nWithSize, bool bMaintainSeek)
{
  long nSave;
  if (bMaintainSeek) nSave = ftell (m_fp);

  fseek (m_fp, lOffset, SEEK_SET);
  int nWrote = fwrite ((char *)pWith, 1, nWithSize, m_fp);

  if (bMaintainSeek) fseek (m_fp, nSave, SEEK_SET);

  if (nWrote > 0) return true;
  return false;
}

//======================================
void CrackAssist::preBmGs (const char *x, int m, int bmGs[])
{
  int i, j, suff[XSIZE];
 
  suffixes (x, m, suff);
 
  for (i = 0; i < m; ++i)
     bmGs[i] = m;
  j = 0;
  for (i = m - 1; i >= -1; --i)
    if (i == -1 || suff[i] == i + 1)
      for (; j < m - 1 - i; ++j)
        if (bmGs[j] == m)
          bmGs[j] = m - 1 - i;
  for (i = 0; i <= m - 2; ++i)
    bmGs[m - 1 - suff[i]] = m - 1 - i;
}

//======================================
void CrackAssist::preBmBc (const char *x, int m, int bmBc[])
{
  int i;
 
  for (i = 0; i < ASIZE; ++i)
    bmBc[i] = m;
  for (i = 0; i < m - 1; ++i)
    bmBc[x[i]] = m - i - 1;
}

//======================================
void CrackAssist::suffixes (const char *x, int m, int *suff)
{
  int f, g, i;
 
  suff[m - 1] = m;
  g = m - 1;
  for (i = m - 2; i >= 0; --i) {
    if (i > g && suff[i + m - 1 - f] < i - g) {
      suff[i] = suff[i + m - 1 - f];
    } else {
      if (i < g)
        g = i;
      f = i;
      while (g >= 0 && x[g] == x[g + m - 1 - f])
        --g;
      suff[i] = f - g;
    }
  }
}
