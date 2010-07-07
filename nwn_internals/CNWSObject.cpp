#include "stdafx.h"
#include "types.h"
#include "nwn_internals.h"

char			(__thiscall *CNWSObject__GetDamageImmunityByFlags)(CNWSObject *pTHIS, uint16_t Flags) = (char (__thiscall *)(CNWSObject * pTHIS, uint16_t))0x004E1D50;
int				(__thiscall *CNWSObject__RemoveEffectById)(CNWSObject *pTHIS, uint64_t EffID) = (int (__thiscall *)(CNWSObject *pTHIS, uint64_t EffID))0x004E2DE0;
CNWSArea * 		(__thiscall *CNWSObject__GetArea)(CNWSObject *pTHIS) = (CNWSArea* (__thiscall *)(CNWSObject *pTHIS))0x004E3F50;
void 			(__thiscall *CNWSObject__SetTag)(CNWSObject *pTHIS, CExoString sTag) = (void (__thiscall*)(CNWSObject *pTHIS, CExoString sTag))0x00466360;
int 			(__thiscall *CNWSObject__GetDead)(CNWSObject *pTHIS) = (int (__thiscall*)(CNWSObject *pTHIS))0x004E59D0;
unsigned int 	(__thiscall *CNWSObject__SetArea)(CNWSObject *pTHIS, CNWSArea *Area) = (unsigned int (__thiscall*)(CNWSObject *pTHIS, CNWSArea *Area))0x004E3F90;


CNWSArea *CNWSObject_s::GetArea() {
	return CNWSObject__GetArea(this);
}

char CNWSObject_s::GetDamageImmunityByFlags(uint16_t Flags) {
	return CNWSObject__GetDamageImmunityByFlags(this, Flags);
}

int CNWSObject_s::GetDead() {
	return CNWSObject__GetDead(this);
}

int CNWSObject_s::RemoveEffectById(uint64_t EffID) {
	return CNWSObject__RemoveEffectById(this, EffID);
}

unsigned int  CNWSObject_s::SetArea(CNWSArea *Area) {
	return CNWSObject__SetArea(this, Area);
}

void  CNWSObject_s::SetTag(CExoString sTag) {
	CNWSObject__SetTag(this, sTag);
}

