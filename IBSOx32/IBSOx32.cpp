#include <plugin.hpp>
#include <DlgBuilder.hpp>
#include <PluginSettings.hpp>
#include "IBSOx32Lng.hpp"
#include "version.hpp"
#include <initguid.h>
#include "guid.hpp"
#include "IBSOx32.hpp"




void WINAPI GetGlobalInfoW(struct GlobalInfo *Info)
{
	Info->StructSize = sizeof(struct GlobalInfo);
	Info->MinFarVersion = FARMANAGERVERSION;
	Info->Version = PLUGIN_VERSION;
	Info->Guid = MainGuid;
	Info->Title = PLUGIN_NAME;
	Info->Description = PLUGIN_DESC;
	Info->Author = PLUGIN_AUTHOR;
}

/*
Функция GetMsg возвращает строку сообщения из языкового файла.
А это надстройка над Info.GetMsg для сокращения кода :-)
*/
const wchar_t *GetMsg(int MsgId)
{
	return Info.GetMsg(&MainGuid, MsgId);
}

/*
Функция SetStartupInfoW вызывается один раз, перед всеми
другими функциями. Она передается плагину информацию,
необходимую для дальнейшей работы.
*/
void WINAPI SetStartupInfoW(const struct PluginStartupInfo *psi)
{
	::Info = *psi;
	FSF = *psi->FSF;
	::Info.FSF = &FSF;
	PluginSettings settings(MainGuid, ::Info.SettingsControl);
	/*
	Opt.ConvertMode = settings.Get(0, L"ConvertMode", 0);
	Opt.ConvertModeExt = settings.Get(0, L"ConvertModeExt", 0);
	Opt.SkipMixedCase = settings.Get(0, L"SkipMixedCase", 1);
	Opt.ProcessSubDir = settings.Get(0, L"ProcessSubDir", 0);
	Opt.ProcessDir = settings.Get(0, L"ProcessDir", 0);
	settings.Get(0, L"WordDiv", Opt.WordDiv, ARRAYSIZE(Opt.WordDiv), L" _");
	Opt.WordDivLen = lstrlen(Opt.WordDiv);
	*/
	settings.Get(0, L"Server", Opt.Server, MAX_SERVER_SIZE, L"CFT");
	settings.Get(0, L"Owner", Opt.Owner, MAX_OWNER_SIZE, L"IBS");
	settings.Get(0, L"User", Opt.User, MAX_USER_SIZE, L"IBS");
}

/*
Функция GetPluginInfoW вызывается для получения информации о плагине
*/
void WINAPI GetPluginInfoW(struct PluginInfo *Info)
{
	Info->StructSize = sizeof(*Info);
	Info->Flags = PF_EDITOR;
	static const wchar_t *PluginMenuStrings[1];
	PluginMenuStrings[0] = L"IBSO x32";//GetMsg(MTitle);
	Info->PluginMenu.Guids = &MenuGuid;
	Info->PluginMenu.Strings = PluginMenuStrings;
	Info->PluginMenu.Count = ARRAYSIZE(PluginMenuStrings);
}

/*
Функция OpenW вызывается при создании новой копии плагина.
*/
HANDLE WINAPI OpenW(const struct OpenInfo *OInfo)
{
	const wchar_t *MsgItems[] =
	{
		 L"IBSOx32" //GetMsg(MTitle),
		,L"Hello"//GetMsg(MMessage1),
		,L"No way"//GetMsg(MMessage2),
		,L"Here i am"//GetMsg(MMessage3),
		,L" and now!" //GetMsg(MMessage4),
		,L"\x01"                      /* separator line */
		,L"&OK"//GetMsg(MButton),
	};

	Info.Message(&MainGuid,           /* GUID */
		NULL,
		FMSG_WARNING | FMSG_LEFTALIGN,  /* Flags */
		L"Contents",                  /* HelpTopic */
		MsgItems,                     /* Items */
		ARRAYSIZE(MsgItems),          /* ItemsNumber */
		1);                           /* ButtonsNumber */

	return NULL;
}