// dcp_stat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "dcp_stat.h"

DcpStat *g_dcpStat = NULL;

PVOID DcpStatCreateShareMemory(int size, TCHAR *name) 
{
    HANDLE fileHandle;
    PVOID  addr;

    fileHandle = CreateFileMapping( 
                     INVALID_HANDLE_VALUE,        // current file handle
                     NULL,                        // default security
                     PAGE_READWRITE,              // read/write permission
                     0,                           // size of mapping object, high
                     size,                        // size of mapping object, low
                     name);                       // name of mapping object

    if(fileHandle != NULL) {
        addr = (PVOID)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    } else {
        addr = NULL;
    }

    return addr;
}

void DumpStatDesc()
{    
    #undef  SERVER_STAT_DEF
    #undef  PLAYER_STAT_DEF
    #define SERVER_STAT_DEF(t, n, s, desc) _tprintf(_T("%s:\t %s\n"), s, desc);
    #define PLAYER_STAT_DEF(t, n, s, desc)
    _tprintf(_T("---=== Server Status ===---\n"));
    #include "stat_def.h"

    #undef  SERVER_STAT_DEF
    #undef  PLAYER_STAT_DEF
    #define SERVER_STAT_DEF(t, n, s, desc) 
    #define PLAYER_STAT_DEF(t, n, s, desc) _tprintf(_T("%s:\t %s\n"), s, desc);

    _tprintf(_T("\n---=== Player Status===---\n"));
    #include "stat_def.h"

}

#define STAT_SPRINTF(...) p += _stprintf(__VA_ARGS__)

#undef  SERVER_STAT_DEF
#undef  PLAYER_STAT_DEF
#define SERVER_STAT_DEF(t, n, s, desc) STAT_SPRINTF(p, _T("  %s: %d, "), s, servStat->n);
#define PLAYER_STAT_DEF(t, n, s, desc)
int ServStat2Str(TCHAR *str, DcpServerStat *servStat)
{   
    int cnt = 0;
    TCHAR *p = str;

    STAT_SPRINTF(p, _T("{ "));
    #include "stat_def.h"
    STAT_SPRINTF(p, _T(" }"));

    return (p - str) / sizeof(TCHAR);
}

#undef  SERVER_STAT_DEF
#undef  PLAYER_STAT_DEF
#define SERVER_STAT_DEF(t, n, s, desc) 
#define PLAYER_STAT_DEF(t, n, s, desc) STAT_SPRINTF(p, _T("  %s: %d, "), s, playerStat->n);

int PlayerStat2Str(TCHAR *str, DcpPlayerStat *playerStat)
{
    int cnt = 0;
    TCHAR *p = str;

    STAT_SPRINTF(p, _T("{"));
    #include "stat_def.h"
    STAT_SPRINTF(p, _T("}"));

    return (p - str) / sizeof(TCHAR);
}

int Stat2Str(TCHAR *str, DcpStat *stat)
{
    TCHAR *p = str;
    int cnt = 0;

    STAT_SPRINTF(p, _T("{ "));

    STAT_SPRINTF(p, _T("servStat: "));
    p += ServStat2Str(p, &stat->servStat);
    STAT_SPRINTF(p, _T(", "));

    STAT_SPRINTF(p, _T("playerStat: { "));
    for(int i = 0; i < STAT_MAX_PLAYER_NUM; i++) {

        //if(!stat->playerStat[i].live)
        //    continue;
        STAT_SPRINTF(p, _T("%d: "), i);
        p += PlayerStat2Str(p, &stat->playerStat[i]);
        //STAT_SPRINTF(p, _T(",\n"));
        STAT_SPRINTF(p, _T(", "));

    }
    STAT_SPRINTF(p, _T("}"));

    STAT_SPRINTF(p, _T(" }"));

    return (str - p )/sizeof(TCHAR);
}

void InitDcpStat()
{
    //g_dcpStat = new DcpStat;
    g_dcpStat = (DcpStat*)DcpStatCreateShareMemory(sizeof(DcpStat), STAT_SHARE_MEM_NAME);

    //memset(g_dcpStat, 0, sizeof(DcpStat));
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//    DumpStatDesc();
//	  return 0;
//}

