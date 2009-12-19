#include <wx/wx.h>

#include "DialogBlocks.h"
#include "ProgressControl.h"

#define SCOUNT(a,b) (sizeof (a) / sizeof (b))

extern ProgressControl *g_Pc;

DialogBlocks::DialogBlocks () 
  : CrackBase ("DialogBlocks (ALL VERSIONS)")
{
}

//======================================
int DialogBlocks::CrackFile (const char *szPath)
{
  int ret;

  if (m_ca.FOpen (szPath, "rb+") == false)
    return CRACK_NotFound;

  ret = CrackMethods ();

  m_ca.FClose ();

  return ret;
}

//======================================
int DialogBlocks::CrackMethods ()
{
  volatile unsigned int checksum, mchecksum;

  //---
  //---this is for DialogBlocks 0.80 - 1.19 (I think)---
  //---

  //this actually makes the program usable. In the function to enable or disable
  //the "Register DialogBlocks..." menu item, I replace one of the cmp's to a mov. This
  //way it sets in memory that it is registered.  
  unsigned char find1_1[]    = {0x80, 0xB8, 0xB8, 0x01, 0x00, 0x00, 0x00}; //cmp byte [eax+0x1b8],bl
  unsigned char replace1_1[] = {0xC6, 0x80, 0xB8, 0x01, 0x00, 0x00, 0x01}; //mov byte [eax+0x1b8],0x1

  //disables the "Register DialogBlocks..." menu
  unsigned char find1_2[]    = {0x8B, 0x44, 0x24, 0x04, //mov eax, dword ptr [esp+04]
                              0x0F, 0x94, 0xC1};      //setz cl
  unsigned char replace1_2[] = {0x8B, 0x44, 0x24, 0x04, //mov eax, dword ptr [esp+04]
                              0xB1, 0x00, 0x90};      //mov cl,0

  //this just erases unregistered, for the user's sake
  unsigned char find1_3[]    = " [UNREGISTERED]";
  unsigned char replace1_3[] = "               ";  

  //must be in the same order as found in the file
  ReplaceEntry entries1[] = {
    {find1_1, sizeof (find1_1), replace1_1, sizeof (replace1_1), 1, 0, 0},
    {find1_2, sizeof (find1_2), replace1_2, sizeof (replace1_2), 1, 0, 0},
    {find1_3, sizeof (find1_3), replace1_3, sizeof (replace1_3), 1, 0, 0}
  };

  //---
  //---this is for DialogBlock 1.20+ (I think)---
  //---

  //makes the program functional
  unsigned char find2_1[]    = {0x80, 0xB8, 0x98, 0x00, 0x00, 0x00, 0x00}; //cmp byte [eax+0x62], 0x0
  unsigned char replace2_1[] = {0x80, 0xB8, 0x98, 0x00, 0x00, 0x00, 0x01}; //cmp byte [eax+0x62], 0x1 

  //effectively removes all the nags in the program
  unsigned char find2_2[]    = {0x38, 0x98, 0x98, 0x00, 0x00, 0x00}; //cmp byte [eax+0x62], bl
  unsigned char replace2_2[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90}; //NOPs

  //this was found by searching for "Register Dialogblocks" until i found a part in the asm that
  //it was trying to create the dialog, and was using this name as the title bar. i then looked a little
  //above and saw that 6 memory areas were jumping to this location, so obviously this was the memory area
  //where this particular dialog is created
  unsigned char find2_3[]    = {0xB8, 0xCB, 0x74, 0x62, 0x00}; //the start of the Register Dialog creation
  unsigned char replace2_3[] = {0xC3, 0x90, 0x90, 0x90, 0x90}; //put a ret(C3) at the beginning, don't create dialog

  //must be in the same order as found in the file
  ReplaceEntry entries2[] = {
    {find2_1, sizeof (find2_1), replace2_1, sizeof (replace2_1), ONE_MINIMUM, 0, 0},
    {find2_2, sizeof (find2_2), replace2_2, sizeof (replace2_2), ONE_MINIMUM, 0, 0},
    {find2_3, sizeof (find2_3), replace2_3, sizeof (replace2_3), ZERO_MINIMUM, 0, 0}
  };

  //---
  //---our methods---
  //---

  Methods methods[] = {
    {entries1, SCOUNT (entries1, ReplaceEntry)},
    {entries2, SCOUNT (entries2, ReplaceEntry)}
  };  

  //---
  //---Algorithm---
  //---

  //since this is a dynamic cracking algorithm, it may take
  //some time to crack the program. It searches for opcode offsets
  //and replaces them with new opcode

  char block[CrackAssist::XSIZE];  
  Methods *p;
  ReplaceEntry *p2;
  long lFileSize = m_ca.FSize ();
  for (int i = 0; i < SCOUNT (methods, Methods); i++) {
    long lCurrentOffset = 0;
    checksum = 0;
    p = &methods[i];

    //calculate minimum checksum (checksum much reach this to become a successful crack)
    mchecksum = 0;
    for (unsigned int x = 0; x < p->nEntries; x++) {
      if (p->entries[x].nOccurrences == ZERO_MINIMUM) {
        //don't add anything to minimum checksum
      } else if (p->entries[x].nOccurrences == ONE_MINIMUM) {
        mchecksum += 1;
      } else {
        mchecksum += p->entries[x].nOccurrences;
      }
    }

    while (int nRead = m_ca.FRead (block, 1, sizeof (block))) {
      lCurrentOffset += nRead;
      //repeatedly search the buffer for all occurrences for all entries
      for (unsigned int x = 0; x < p->nEntries; x++) {
        p2 = &p->entries[x];

        //must set search offset back to 0 for each entry when searching the same block. because what if
        //you have 2 matches for the first entry inside a block, and 1 match for another entry inbetween
        //the other 2 matches. once the search offset goes finds the first and the last match, it will completely
        //skip the middle one. this is because it searches 1 entry at a time for one whole block.
        //*Situation 1: not setting search offset to 0:
        //           [-----------------------------block------------------------------]
        //           .....[entry 1 match].....[entry 2 match]........[entry 1 match]...
        //First run:          *MATCH*                                    *MATCH*
        //Second run:  A NEW BLOCK IS LOADED, MISSING entry #2
        //*Situation 2: setting search offset to 0:
        //           [-----------------------------block------------------------------]
        //           .....[entry 1 match].....[entry 2 match]........[entry 1 match]...
        //First run:          *MATCH*                                    *MATCH*
        //Second run:                             *MATCH*
        //lSearchOffset is the offset to start searching from within a block
        //lOffset is the offset to where it found the match, but this is only relative to the
        //block location + where lSearchOffset is
        long lSearchOffset = 0, lOffset;                               //[  effectively shifts where to search  ]
        while ((lOffset = m_ca.Search ((char *)p2->pFind, p2->nFindSize, block+lSearchOffset, nRead-lSearchOffset)) != -1) {
          if (p2->nOccurrences == ZERO_MINIMUM) {
            //             [    matched offset   ]    [   block location   ]
            AddOffset (p2, lOffset + lSearchOffset + (lCurrentOffset - nRead));
            //skip where you found the match + the size of the match
            lSearchOffset += lOffset + p2->nFindSize;  
          } else if ((unsigned int)p2->nOccurrences > p2->nOffsets || p2->nOccurrences == ONE_MINIMUM) {
            if (!(p2->nOccurrences == ONE_MINIMUM && p2->lpOffsets != 0) || 
                (p2->nOccurrences == ONE_MINIMUM && p2->lpOffsets == 0))
              checksum++;
            //             [    matched offset   ]    [   block location   ]
            AddOffset (p2, lOffset + lSearchOffset + (lCurrentOffset - nRead));
            //skip where you found the match + the size of the match
            lSearchOffset += lOffset + p2->nFindSize;          
          } else {
            break;
          }
        }
      }

      //indicates progression only by how much of the file was read
      g_Pc->SetValue (100 - static_cast<int>(lFileSize / lCurrentOffset));
    }

    //make sure we found everything we need to replace, then patch those offsets
    //we have to do >=, because if they use -1 for number of occurences, the checksum
    //could be much greater than the minimum checksum
    if (checksum >= mchecksum) {
      //wxString test;
      for (unsigned int x = 0; x < p->nEntries; x++) {
        p2 = &p->entries[x];        
        for (unsigned int i = 0; i < p2->nOffsets; i++) {
          //test += wxString::Format ("%d - %d\n", p2->nOffsets, p2->lpOffsets[i]);
          m_ca.PatchOffset (p2->lpOffsets[i], p2->pReplace, p2->nReplaceSize);
        }
      }
      //wxMessageBox (test);
      
      Cleanup (methods, SCOUNT (methods, Methods));
      return CRACK_Success;
    }

    //get ready to try to crack with the next method
    g_Pc->SetValue (0);
    m_ca.FRewind ();
  }  

  Cleanup (methods, SCOUNT (methods, Methods));
  return CRACK_Failed;  
}

//======================================
void DialogBlocks::AddOffset (ReplaceEntry *entry, long lOffset)
{
  long *lpOldOffsets = entry->lpOffsets;
  entry->lpOffsets = new long [entry->nOffsets + 1];
  for (unsigned int x = 0; x < entry->nOffsets; x++) {
    entry->lpOffsets[x] = lpOldOffsets[x];
  }
  entry->lpOffsets[x] = lOffset;
  if (lpOldOffsets) delete []lpOldOffsets;
  entry->nOffsets += 1;
}

//======================================
void DialogBlocks::Cleanup (Methods *methods, unsigned int nMethods)
{
  for (unsigned int i = 0; i < nMethods; i++) {
    for (unsigned int x = 0; x < methods[i].nEntries; x++) {
      if (methods[i].entries[x].lpOffsets)
        delete []methods[i].entries[x].lpOffsets;
    }
  }
}
