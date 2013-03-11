// EmuStat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dcp_stat.h"

int _tmain(int argc, _TCHAR* argv[])
{
    InitDcpStat();

    while(true) {
        g_dcpStat->servStat.syncTime = (60 * rand() / (RAND_MAX));
        _tprintf(_T("rand: %d\n"), g_dcpStat->servStat.syncTime);
        g_dcpStat->playerStat[0].decodeTime = 555;
        Sleep(500);
    }

    getchar();
    return 0;
}

