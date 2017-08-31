const wchar_t *GetMsg(int MsgId);

static struct PluginStartupInfo Info;
static struct FarStandardFunctions FSF;

#define MAX_SERVER_SIZE 1000
#define MAX_OWNER_SIZE	40
#define MAX_USER_SIZE	MAX_OWNER_SIZE
#define MAX_PWD_SIZE	MAX_OWNER_SIZE

static struct Options
{
	wchar_t Server[MAX_SERVER_SIZE];
	wchar_t Owner[MAX_OWNER_SIZE];
	wchar_t User[MAX_USER_SIZE];
	wchar_t Password[MAX_PWD_SIZE];	
} Opt;
