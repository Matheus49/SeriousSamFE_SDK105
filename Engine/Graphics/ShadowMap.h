#ifndef SE_INCL_SHADOWMAP_H
#define SE_INCL_SHADOWMAP_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Graphics/GfxLibrary.h>

#define SMF_DYNAMICINVALID  (1UL<<0)    // dynamic shadows are not up to date
#define SMF_DYNAMICBLACK    (1UL<<1)    // there was no need to mix dynamic shadow layer(s) (they were all black)
#define SMF_DYNAMICUPLOADED (1UL<<2)    // dynamic shadowmap was uploaded last
#define SMF_ANIMATINGLIGHTS (1UL<<3)    // set when shadowmap has at least one animating light
#define SMF_PROBED          (1UL<<19)   // set if last binding was as probe-texture


// class that holds information about shadow cluster map of each scene polygon
// format flags (16+) are defined by texture data
class ENGINE_API CShadowMap {
// implementation:
public:
  CListNode sm_lnInGfx;              // for linking in list of all cached shadow maps
  ULONG sm_ulFlags;                  // various flags
  INDEX sm_iFirstMipLevel;           // best mip level possible for this shadow map
  INDEX sm_iLastMipLevel;            // minimum possible mip level
  ULONG sm_ulFlatRGBA;               // color of whole shadowmap if shadowmap is flat
  MEX sm_mexOffsetX, sm_mexOffsetY;  // X and Y offset from the begining of the polygon
  MEX sm_mexWidth,   sm_mexHeight;   // width and height of shadow map

  ULONG *sm_pulCachedShadowMap;   // pointer to cached calculated shadow map
  ULONG *sm_pulDynamicShadowMap;  // pointer to shadow map with dynamic lights
  SLONG sm_slMemoryUsed;          // memory in use by shadow map (in bytes)
  INDEX sm_iFirstCachedMipLevel;  // first mip level currently cached
  CTimerValue sm_tvLastDrawn;     // timer for shadow uncaching and probing

  PIX sm_pixPolygonSizeU, sm_pixPolygonSizeV;  // dimensions of used part of shadowmap
  PIX sm_pixUploadWidth,  sm_pixUploadHeight;  // dimensions of last upload size
  ULONG sm_ulInternalFormat;    // last format in which shadowmap was uploaded
  ULONG sm_ulObject;            // for API
  ULONG sm_ulProbeObject;       // for API
  CTexParams sm_tpLocal;        // local texture parameters

  INDEX sm_iRenderFrame; // frame number currently rendering (for profiling)

  // skip old shadows saved in stream
  void Read_old_t(CTStream *inFile); // throw char *
  // mix all layers into cached shadow map
  virtual void MixLayers( INDEX iFirstMip, INDEX iLastMip, BOOL bDynamic=FALSE);  // iFirstMip<iLastMip
  // check if all layers are up to date
  virtual void CheckLayersUpToDate(void);
  // test if there is any dynamic layer
  virtual BOOL HasDynamicLayers(void);
  // this one always fail - CBrushShadowmap is the one that matters
  inline virtual BOOL IsShadowFlat( ULONG &ulFlatRGBA) { return FALSE; };
  // mark that shadow has been drawn
  void MarkDrawn(void);

// interface:
public:
  // constructor
   CShadowMap();
   // destructor
   ~CShadowMap();

  // clear the object
  void Clear();
  // initialize the shadow map
  void Initialize( INDEX iMipLevel, MEX mexOffsetX, MEX mexOffsetY, MEX mexWidth, MEX mexHeight);

  // read/write from a stream
  void Read_t( CTStream *pstrm);        // throw char *
  void Write_t( CTStream *pstrm);       // throw char *
  virtual void ReadLayers_t( CTStream *pstrm);  // throw char *
  virtual void WriteLayers_t( CTStream *pstrm); // throw char *

  // get shadowmap memory usage (in bytes)
  ULONG GetShadowSize(void);
  // returns used memory - static, dynamic and uploaded size separately, slack space ratio (0-1 float) and flatness
  BOOL GetUsedMemory( SLONG &slStaticSize, SLONG &slDynamicSize, SLONG &slUploadSize, FLOAT &fSlackRatio);

  // cache the shadow map
  void Cache( INDEX iWantedMipLevel);
  // update dynamic layers of the shadow map
  // (returns mip in which shadow needs to be uploaded)
  ULONG UpdateDynamicLayers(void);
  // invalidate the shadow map
  void Invalidate( BOOL bDynamicOnly=FALSE);
  // uncache the shadow map (returns total ammount of memory that has been freed)
  SLONG Uncache(void);

  // set shadow as current for accelerator (this will upload shadow texture that needs uploading)
  void SetAsCurrent(void);
};


#endif  /* include-once check. */

