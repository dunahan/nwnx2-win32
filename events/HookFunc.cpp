/***************************************************************************
    Chat plugin for NWNX  - hooks implementation
    (c) 2005 dumbo (dumbo@nm.ru)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***************************************************************************/

#include "HookFunc.h"
#include "madCHook.h"
#include "NWNXEvents.h"

extern CNWNXEvents events;

void (*SaveCharNextHook)();
void (*PickPocketNextHook)();
void (*AttackNextHook)();
void (*ExamineItemNextHook)();
void (*ExamineCreatureNextHook)();
void (*ExaminePlaceableNextHook)();
void (*ExamineDoorNextHook)();

void (*pRunScript)();

dword pServThis = 0;
dword pList = 0;
dword pScriptThis = 0;
dword oPC = 0;
dword oTarget_b = OBJECT_INVALID;

char scriptRun = 0;

unsigned long lastRet;

void SaveCharHookProc()
{
//  _asm { int 3 }
  _asm { pushad }
	if (!scriptRun)
	{
		_asm { add ebx, 4 }
		_asm { mov oPC, ebx }
		_asm { sub ebx, 4 }
		events.FireEvent(*(dword *)oPC, EVENT_SAVE_CHAR);
	}
  _asm { popad }
  _asm { leave }

  _asm { jmp SaveCharNextHook }
}

void __declspec(naked) PickPocketHookProc()
{
	_asm { pushad }
	if (!scriptRun)
	{
		_asm
		{
			//Get oPC
			mov eax, ecx
			mov eax, [eax+4]
			mov oPC, eax

			//Get oTarget
			mov eax, [esp+0x24]  //0x4+0x20
			mov oTarget_b, eax
		}
		events.oTarget = oTarget_b;
		
		events.FireEvent(oPC, EVENT_PICKPOCKET);
	}
	_asm { popad }
	//_asm { leave }
  _asm { jmp PickPocketNextHook }
}

void __declspec(naked) AttackHookProc()
{
	_asm { pushad }
	if (!scriptRun)
	{
		_asm
		{
			//Get oPC
			mov eax, ecx
			mov eax, [eax+4]
			mov oPC, eax

			//Get oTarget
			mov eax, [esp+0x24]  //0x4+0x20
			mov oTarget_b, eax
		}
		events.oTarget = oTarget_b;
		
		events.FireEvent(oPC, EVENT_ATTACK);
	}
	_asm { popad }
	//_asm { leave }
  _asm { jmp AttackNextHook }
}

void __declspec(naked) ExamineItemHookProc()
{
	_asm { pushad }
	if (!scriptRun)
	{
		_asm
		{
			//Get oPC
			mov eax, [esp+0x24]
			mov eax, [eax+0x30]
			mov oPC, eax

			//Get oTarget
			mov eax, [esp+0x28]  //0x24+0x4
			mov oTarget_b, eax
		}
		events.oTarget = oTarget_b;
		
		events.FireEvent(oPC, EVENT_EXAMINE);
	}
	_asm { popad }
	//_asm { leave }
	_asm { jmp ExamineItemNextHook };
}

void __declspec(naked) ExamineCreatureHookProc()
{
	_asm { pushad }
	if (!scriptRun)
	{
		_asm
		{
			//Get oPC
			mov eax, [esp+0x24]
			mov eax, [eax+0x30]
			mov oPC, eax

			//Get oTarget
			mov eax, [esp+0x28]  //0x24+0x4
			mov oTarget_b, eax
		}
		events.oTarget = oTarget_b;
		
		events.FireEvent(oPC, EVENT_EXAMINE);
	}
	_asm { popad }
	//_asm { leave }
	_asm { jmp ExamineCreatureNextHook };
}

void __declspec(naked) ExaminePlaceableHookProc()
{
	_asm { pushad }
	if (!scriptRun)
	{
		_asm
		{
			//Get oPC
			mov eax, [esp+0x24]
			mov eax, [eax+0x30]
			mov oPC, eax

			//Get oTarget
			mov eax, [esp+0x28]  //0x24+0x4
			mov oTarget_b, eax
		}
		events.oTarget = oTarget_b;
		
		events.FireEvent(oPC, EVENT_EXAMINE);
	}
	_asm { popad }
	//_asm { leave }
	_asm { jmp ExaminePlaceableNextHook };
}

void __declspec(naked) ExamineDoorHookProc()
{
	_asm { pushad }
	if (!scriptRun)
	{
		_asm
		{
			//Get oPC
			mov eax, [esp+0x24]
			mov eax, [eax+0x30]
			mov oPC, eax

			//Get oTarget
			mov eax, [esp+0x28]  //0x24+0x4
			mov oTarget_b, eax
		}
		events.oTarget = oTarget_b;
		
		events.FireEvent(oPC, EVENT_EXAMINE);
	}
	_asm { popad }
	//_asm { leave }
	_asm { jmp ExamineDoorNextHook };
}

DWORD FindSaveChar()
{
	char* ptr = (char*) 0x400000;
	while (ptr < (char*) 0x600000)
	{
		if ((ptr[0] == (char) 0x6A) &&
			(ptr[1] == (char) 0xFF) &&
			(ptr[7] == (char) 0x64) &&
			(ptr[8] == (char) 0xA1) &&
			(ptr[9] == (char) 0x00) &&
			(ptr[0x2F] == (char) 0x52) &&
			(ptr[0x30] == (char) 0x89) &&
			(ptr[0x31] == (char) 0x7C) &&
			(ptr[0x32] == (char) 0x24) &&
			(ptr[0x33] == (char) 0x2C) &&
			(ptr[0x34] == (char) 0x89) &&
			(ptr[0x35] == (char) 0x74) &&
			(ptr[0x36] == (char) 0x24) &&
			(ptr[0x37] == (char) 0x1C)
			)
			return (DWORD) ptr;
		else
			ptr++;
	}
	return NULL;
}

/*
.text:00492CB0 51                                      push    ecx
.text:00492CB1 56                                      push    esi
.text:00492CB2 8B F1                                   mov     esi, ecx
.text:00492CB4 8B 06                                   mov     eax, [esi]
.text:00492CB6 FF 50 30                                call    dword ptr [eax+30h]
*/
// 51 56 8B F1 8B 06 FF 50 30
// 51568BF18B06FF5030
DWORD FindPickPocket()
{
	char* ptr = (char*) 0x400000;
	while (ptr < (char*) 0x600000)
	{
		if ((ptr[0] == (char) 0x51) &&
			(ptr[1] == (char) 0x56) &&
			(ptr[2] == (char) 0x8B) &&
			(ptr[3] == (char) 0xF1) &&
			(ptr[4] == (char) 0x8B) &&
			(ptr[5] == (char) 0x06) &&
			(ptr[6] == (char) 0xFF) &&
			(ptr[7] == (char) 0x50) &&
			(ptr[8] == (char) 0x30)
			)
			return (DWORD) ptr;
		else
			ptr++;
	}
	return NULL;
}

/*
.text:004932C0 64 A1 00 00 00 00                       mov     eax, large fs:0
.text:004932C6 6A FF                                   push    0FFFFFFFFh
.text:004932C8 68 6B E5 61 00                          push    offset loc_61E56B
.text:004932CD 50                                      push    eax
.text:004932CE 64 89 25 00 00 00 00                    mov     large fs:0, esp
.text:004932D5 53                                      push    ebx
.text:004932D6 55                                      push    ebp
.text:004932D7 56                                      push    esi
.text:004932D8 57                                      push    edi
.text:004932D9 8B F1                                   mov     esi, ecx

.text:004932E0 8B 86 C0 00 00 00                       mov     eax, [esi+0C0h]
*/
// 0x004932C0 in 1.67
DWORD FindAttack()
{
	char* ptr = (char*) 0x400000;
	while (ptr < (char*) 0x600000)
	{
		if ((ptr[0] == (char) 0x64) &&
			(ptr[1] == (char) 0xA1) &&
			(ptr[2] == (char) 0x00) &&
			(ptr[3] == (char) 0x00) &&
			(ptr[4] == (char) 0x00) &&
			(ptr[5] == (char) 0x00) &&
			(ptr[6] == (char) 0x6A) &&
			(ptr[7] == (char) 0xFF) &&
			(ptr[0xD] == (char) 0x50) &&
			(ptr[0xE] == (char) 0x64) &&
			(ptr[0xF] == (char) 0x89) &&
			(ptr[0x10] == (char) 0x25) &&
			(ptr[0x11] == (char) 0x00) &&
			(ptr[0x15] == (char) 0x53) &&
			(ptr[0x16] == (char) 0x55) &&
			(ptr[0x17] == (char) 0x56) &&
			(ptr[0x20] == (char) 0x8B) &&
			(ptr[0x21] == (char) 0x86) &&
			(ptr[0x22] == (char) 0xC0) &&
			(ptr[0x23] == (char) 0x00)
			)
			return (DWORD) ptr;
		else
			ptr++;
	}
	ptr = (char*) 0x400000;
	while (ptr < (char*) 0x600000)
	{
		if ((ptr[0] == (char) 0x6A) &&
			(ptr[1] == (char) 0xFF) &&
			(ptr[7] == (char) 0x64) &&
			(ptr[8] == (char) 0xA1) &&
			(ptr[9] == (char) 0x00) &&
			(ptr[0xA] == (char) 0x00) &&
			(ptr[0xB] == (char) 0x00) &&
			(ptr[0xC] == (char) 0x00) &&
			(ptr[0xD] == (char) 0x50) &&
			(ptr[0xE] == (char) 0x64) &&
			(ptr[0xF] == (char) 0x89) &&
			(ptr[0x10] == (char) 0x25) &&
			(ptr[0x11] == (char) 0x00) &&
			(ptr[0x15] == (char) 0x51) &&
			(ptr[0x16] == (char) 0x55) &&
			(ptr[0x17] == (char) 0x56) &&
			(ptr[0x1A] == (char) 0x8B) &&
			(ptr[0x1B] == (char) 0x86) &&
			(ptr[0x1C] == (char) 0xD4)
			)
			return (DWORD) ptr;
		else
			ptr++;
	}
	//return 0x004942D0;
	return NULL;
}

// 53 55 56 57 8B 7C 24 14 8B F1 8B CF
DWORD FindRunScript()
{
	char* ptr = (char*) 0x400000;
	while (ptr < (char*) 0x600000)
	{
		if ((ptr[0] == (char) 0x53) &&
			(ptr[1] == (char) 0x55) &&
			(ptr[2] == (char) 0x56) &&
			(ptr[3] == (char) 0x57) &&
			(ptr[4] == (char) 0x8B) &&
			(ptr[5] == (char) 0x7C) &&
			(ptr[6] == (char) 0x24) &&
			(ptr[7] == (char) 0x14) &&
			(ptr[8] == (char) 0x8B) &&
 			(ptr[9] == (char) 0xF1) &&
 			(ptr[0xA] == (char) 0x8B) &&
 			(ptr[0xB] == (char) 0xCF) &&
			(ptr[0xC] == (char) 0xE8) &&
			(ptr[0x11] == (char) 0x85) &&
			(ptr[0x12] == (char) 0xC0)
			)
			return (DWORD) ptr;
		else
			ptr++;
	}
	//64 A1 00 00 00 00 6A FF 68 ** ** ** ** 50 64 89 25 00 00 00 00 83 EC 1C 53 8B 5C 24 30
	ptr = (char*) 0x400000;
	while (ptr < (char*) 0x600000)
	{
		if ((ptr[0] == (char) 0x64) &&
			(ptr[1] == (char) 0xA1) &&
			(ptr[2] == (char) 0x00) &&
			(ptr[3] == (char) 0x00) &&
			(ptr[4] == (char) 0x00) &&
			(ptr[5] == (char) 0x00) &&
			(ptr[6] == (char) 0x6A) &&
			(ptr[7] == (char) 0xFF) &&
			(ptr[8] == (char) 0x68) &&
			(ptr[0xD] == (char) 0x50) &&
 			(ptr[0xE] == (char) 0x64) &&
 			(ptr[0xF] == (char) 0x89) &&
			(ptr[0x10] == (char) 0x25) &&
			(ptr[0x11] == (char) 0x00) &&
			(ptr[0x12] == (char) 0x00) &&
			(ptr[0x13] == (char) 0x00) &&
			(ptr[0x14] == (char) 0x00) &&
			(ptr[0x15] == (char) 0x83) &&
			(ptr[0x16] == (char) 0xEC) &&
			(ptr[0x17] == (char) 0x1C) &&
			(ptr[0x18] == (char) 0x53) &&
			(ptr[0x19] == (char) 0x8B) &&
			(ptr[0x1A] == (char) 0x5C) &&
			(ptr[0x1B] == (char) 0x24) &&
			(ptr[0x1C] == (char) 0x30) &&
			//8D 8E 70 01 00 00
			(ptr[0x3B] == (char) 0x8D) &&
			(ptr[0x3C] == (char) 0x8E) &&
			(ptr[0x3D] == (char) 0x70) &&
			(ptr[0x3E] == (char) 0x01) &&
			(ptr[0x3F] == (char) 0x00)
			)
			return (DWORD) ptr;
		else
			ptr++;
	}
	return NULL;
}

void RunScript(char * sname, int ObjID)
{
  int sptr[4];
  sptr[1] = strlen(sname);
  _asm
  {
    lea  edx, sptr
    mov  eax, sname
    mov  [edx], eax
    push 1
    push ObjID
    push edx
    mov ecx, pScriptThis
    mov ecx, [ecx]
  }
  scriptRun = 1;
  pRunScript();
  scriptRun = 0;
}

int HookFunctions()
{
	int success1 = 0, success2 = 0, success3 = 0;
	int success6_1 = 0, success6_2 = 0, success6_3 = 0, success6_4 = 0;
	DWORD org_SaveChar    = FindSaveChar();
	DWORD org_Run         = FindRunScript();
	DWORD org_PickPocket  = FindPickPocket();
	DWORD org_Attack      = FindAttack();
	DWORD org_ExamineItem      = 0x446F60;
	DWORD org_ExamineCreature  = 0x446B00;
	DWORD org_ExaminePlaceable = 0x4474B0;
	DWORD org_ExamineDoor      = 0x447970;

	if (org_SaveChar)
	{
		pServThis = *(dword*)(org_SaveChar + 0x19);
		pScriptThis = pServThis - 8;
		success1 = HookCode((PVOID) org_SaveChar, SaveCharHookProc, (PVOID*) &SaveCharNextHook);
	}
	
	if (org_PickPocket)
	    success2 = HookCode((PVOID) org_PickPocket, PickPocketHookProc, (PVOID*) &PickPocketNextHook);
	
	if (org_Attack)
	    success3 = HookCode((PVOID) org_Attack, AttackHookProc, (PVOID*) &AttackNextHook);
	
	if (org_ExamineItem)
		success6_1 = HookCode((PVOID) org_ExamineItem, ExamineItemHookProc, (PVOID*) &ExamineItemNextHook);

	if (org_ExamineCreature)
		success6_2 = HookCode((PVOID) org_ExamineCreature, ExamineCreatureHookProc, (PVOID*) &ExamineCreatureNextHook);

	if (org_ExaminePlaceable)
		success6_3 = HookCode((PVOID) org_ExaminePlaceable, ExaminePlaceableHookProc, (PVOID*) &ExaminePlaceableNextHook);

	if (org_ExamineDoor)
		success6_4 = HookCode((PVOID) org_ExamineDoor, ExamineDoorHookProc, (PVOID*) &ExamineDoorNextHook);


	if (org_SaveChar && success1)
		fprintf(events.m_fFile, "! DownloadCharacter().....hooked at %08lx.\n", org_SaveChar);
	else
		fprintf(events.m_fFile, "X Could not find DownloadCharacter() function or hook failed: %08lx\n", org_SaveChar);

	if (org_PickPocket && success2)
		fprintf(events.m_fFile, "! PickPocket()............hooked at %08lx.\n", org_PickPocket);
	else
		fprintf(events.m_fFile, "X Could not find PickPocket() function or hook failed: %08lx\n", org_PickPocket);

	if (org_Attack && success3)
		fprintf(events.m_fFile, "! Attack()................hooked at %08lx.\n", org_Attack);
	else
		fprintf(events.m_fFile, "X Could not find Attack() function or hook failed: %08lx\n", org_Attack);

	if (org_ExamineItem && success6_1)
		fprintf(events.m_fFile, "! ExamineItem()...........hooked at %08lx.\n", org_ExamineItem);
	else
		fprintf(events.m_fFile, "X Could not find ExamineItem() function or hook failed: %08lx\n", org_ExamineItem);

	if (org_ExamineCreature && success6_2)
		fprintf(events.m_fFile, "! ExamineCreature().......hooked at %08lx.\n", org_ExamineCreature);
	else
		fprintf(events.m_fFile, "X Could not find ExamineCreature() function or hook failed: %08lx\n", org_ExamineCreature);

	if (org_ExaminePlaceable && success6_3)
		fprintf(events.m_fFile, "! ExaminePlaceable()......hooked at %08lx.\n", org_ExaminePlaceable);
	else
		fprintf(events.m_fFile, "X Could not find ExaminePlaceable() function or hook failed: %08lx\n", org_ExaminePlaceable);

	if (org_ExamineDoor && success6_4)
		fprintf(events.m_fFile, "! ExamineDoor()...........hooked at %08lx.\n", org_ExamineDoor);
	else
		fprintf(events.m_fFile, "X Could not find ExamineDoor() function or hook failed: %08lx\n", org_ExamineDoor);

	if (org_Run)
	{
		*(dword*)&pRunScript = org_Run;
		fprintf(events.m_fFile, "! ExecuteScript().........hooked at %08lx.\n", org_Run);
	}
	else
		fprintf(events.m_fFile, "X Could not find ExecuteScript() function or hook failed: %08lx\n", org_Run);

	fprintf(events.m_fFile, "\n");
	fflush(events.m_fFile);

	return (org_SaveChar && org_Run && pServThis && pScriptThis);
}