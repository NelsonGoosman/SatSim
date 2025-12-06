#include "DllUtils.h"
#include "ElOpsDll_Service.h"

#include "../wrappers/EnvConstDll.h"
#include "../wrappers/AstroFuncDll.h"
#include "../wrappers/ElOpsDll.h"

// Returns all currently loaded satKeys
void GetCurrLoadedSatKeys(int fileType, __int64** pSatKeys, int* numSats)
{
   __int64* tmpSatKeys = NULL;

   if (fileType == FILETYPE_TLE)
      *numSats = TleGetCount();
   else if (fileType == FILETYPE_SPVEC)
      *numSats = SpVecGetCount();
   else if (fileType == FILETYPE_VCM)
      *numSats = VcmGetCount();
   else if (fileType == FILETYPE_EXTEPH)
      *numSats = ExtEphGetCount();

   if (*numSats > 0)
   {
      tmpSatKeys = (__int64*)malloc(*numSats * sizeof(__int64));
      TleGetLoaded(2, tmpSatKeys);
   }

   *pSatKeys = tmpSatKeys;
}

void SatKeysFrFile(int fileType, char* inputFile, __int64** newSatKeys, int* newNumSats)
{
   __int64* preSatKeys = NULL;
   __int64* currSatKeys = NULL;
   __int64* tmpSatKeys = NULL;
   int preNumSats;
   int currNumSats;
   int i, j, k, isNew, errCode;

   *newNumSats = 0;

   GetCurrLoadedSatKeys(fileType, &preSatKeys, &preNumSats);

   if (fileType == FILETYPE_TLE)
      errCode = TleLoadFile(inputFile);
   else if (fileType == FILETYPE_SPVEC)
      errCode = SpVecLoadFile(inputFile);
   else if (fileType == FILETYPE_VCM)
      errCode = VcmLoadFile(inputFile);
   else if (fileType == FILETYPE_EXTEPH)
      errCode = ExtEphLoadFile(inputFile);

   if (errCode != 0)
   {
      free(preSatKeys);
      return;
   }

   GetCurrLoadedSatKeys(fileType, &currSatKeys, &currNumSats);

   if (preNumSats == 0)
   {
      *newNumSats = currNumSats;
      *newSatKeys = currSatKeys;
   }
   else
   {
      *newNumSats = currNumSats - preNumSats;
      tmpSatKeys = (__int64*)malloc(*newNumSats * sizeof(__int64));
      k = 0;
      for (j = 0; j < currNumSats; j++)
      {
         isNew = 1;
         for (i = 0; i < preNumSats; i++)
         {
            if (currSatKeys[j] == preSatKeys[i])
            {
               isNew = 0;
               break;
            }
         }
         if (isNew)
            tmpSatKeys[k++] = currSatKeys[j];
      }
      *newSatKeys = tmpSatKeys;
      free(preSatKeys);
      free(currSatKeys);

   }

}


// Compute perigee height (spherical earth) from Tle data
double ComputePerigeeHt(double mnMotion, double eccen)
{
   double perigeeHt;

   perigeeHt = (NToA(mnMotion) * (1 - eccen)) - EnvGetGeoConst(XF_GEOCON_KMPER);

   return perigeeHt;
}


// Retrieve satellite parameters by the input satKey
void RetrieveSatParms(__int64 satKey, SatParms* satParms)
{
   double xa_satparm[32];

   satParms->errCode = GetSatParameters(satKey, xa_satparm);

   // fail to retrieve satellite parameters
   if (satParms->errCode != 0)
      return;

   satParms->epochUTC   = xa_satparm[XA_SATPARM_EPOCHUTC ];
   satParms->mnAnom     = xa_satparm[XA_SATPARM_MNANOM   ];
   satParms->node       = xa_satparm[XA_SATPARM_NODE     ];
   satParms->omega      = xa_satparm[XA_SATPARM_OMEGA    ];
   satParms->period     = xa_satparm[XA_SATPARM_PERIOD   ];
   satParms->eccen      = xa_satparm[XA_SATPARM_ECCEN    ];
   satParms->inclin     = xa_satparm[XA_SATPARM_INCLI    ];
   satParms->mnMotion   = xa_satparm[XA_SATPARM_MNMOTION ];
   satParms->bField     = xa_satparm[XA_SATPARM_BFIELD   ];
   satParms->perigeeHt  = xa_satparm[XA_SATPARM_PERIGEEHT];
   satParms->apogeeHt   = xa_satparm[XA_SATPARM_APOGEEHT ];
   satParms->perigee    = xa_satparm[XA_SATPARM_PERIGEE  ];
   satParms->apogee     = xa_satparm[XA_SATPARM_APOGEE   ];
   satParms->A          = xa_satparm[XA_SATPARM_A        ];
   satParms->satCat     = (int)xa_satparm[XA_SATPARM_SATCAT   ];
   satParms->cmOffset   = xa_satparm[XA_SATPARM_CMOFFSET ];
   satParms->lonE       = xa_satparm[XA_SATPARM_LONE     ];
   satParms->drift      = xa_satparm[XA_SATPARM_DRIFT    ];
   satParms->omegaDot   = xa_satparm[XA_SATPARM_OMEGADOT ];
   satParms->raDot      = xa_satparm[XA_SATPARM_RADOT    ];
   satParms->nodalPrd   = xa_satparm[XA_SATPARM_NODALPRD ];
   satParms->nodalX     = xa_satparm[XA_SATPARM_NODALX   ];
   satParms->isGeo      = (int)xa_satparm[XA_SATPARM_ISGEO    ];
   satParms->relEnergy  = xa_satparm[XA_SATPARM_RELENERGY];
   satParms->satNum     = (int)xa_satparm[XA_SATPARM_SATNUM   ];
   satParms->oet        = (int)xa_satparm[XA_SATPARM_OET      ];
   satParms->propType   = (int)xa_satparm[XA_SATPARM_PROPTYPE ];
   satParms->elsetNum   = (int)xa_satparm[XA_SATPARM_ELSETNUM];
}