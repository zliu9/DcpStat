#ifndef DCP_STAT_H
#define DCP_STAT_H

#define STAT_PREFIX extern

#define STAT_MAX_PLAYER_NUM 4
#define STAT_SHARE_MEM_NAME _T("DcpStatShareMem")

#undef SERVER_STAT_DEF
#undef PLAYER_STAT_DEF
#define SERVER_STAT_DEF(t, n, s, desc) t n;
#define PLAYER_STAT_DEF(t, n, s, desc) 

struct DcpServerStat{
    #include "stat_def.h"
    bool live;
};


#undef SERVER_STAT_DEF
#undef PLAYER_STAT_DEF
#define SERVER_STAT_DEF(t, n, s, desc)
#define PLAYER_STAT_DEF(t, n, s, desc) t n;

struct DcpPlayerStat{
    #include "stat_def.h"
    bool live;
};

struct DcpStat {
    DcpServerStat servStat;
    DcpPlayerStat playerStat[STAT_MAX_PLAYER_NUM];
};

STAT_PREFIX DcpStat *g_dcpStat;

STAT_PREFIX void InitDcpStat();
STAT_PREFIX void DumpStatDesc();

STAT_PREFIX int ServStat2Str(TCHAR *str, DcpServerStat *servStat);
STAT_PREFIX int PlayerStat2Str(TCHAR *str, DcpPlayerStat *playerStat);
STAT_PREFIX int Stat2Str(TCHAR *str, DcpStat *stat);

#endif