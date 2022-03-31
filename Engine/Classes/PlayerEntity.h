/*
 * This file is generated by Entity Class Compiler, (c) CroTeam 1997-98
 */

#ifndef _Engine_Classes_PlayerEntity_INCLUDED
#define _Engine_Classes_PlayerEntity_INCLUDED 1
extern "C" DECL_DLL CDLLEntityClass CPlayerEntity_DLLClass;
class DECL_DLL  CPlayerEntity : public CMovableModelEntity {
public:
   virtual void SetDefaultProperties(void);
  FLOAT en_tmPing;
CPlayerCharacter en_pcCharacter;
CPlacement3D en_plViewpoint;
CPlacement3D en_plLastViewpoint;
   CTString GetPlayerName(void);
   const CTString & GetName(void)const;
   INDEX GetMyPlayerIndex(void);
   void DoMoving(void);
   void Copy(CEntity & enOther,ULONG ulFlags);
   void Read_t(CTStream * istr);
   void Write_t(CTStream * ostr);
  virtual void ApplyAction(const CPlayerAction & pa,FLOAT tmLatency);
  virtual void Disconnect(void);
  virtual void CharacterChanged(const CPlayerCharacter & pcNew);
  virtual void GetGameSpyPlayerInfo(INDEX iPlayer,CTString & strKeys);
   void ChecksumForSync(ULONG & ulCRC,INDEX iExtensiveSyncCheck);
   void DumpSync_t(CTStream & strm,INDEX iExtensiveSyncCheck);
#define  STATE_CPlayerEntity_Dummy 0x00040000
  BOOL 
#line 127 "C:/WORK/Sources/Engine/Classes/PlayerEntity.es"
Dummy(const CEntityEvent &__eeInput);
};
#endif // _Engine_Classes_PlayerEntity_INCLUDED
