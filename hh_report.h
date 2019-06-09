#pragma once

#include <time.h>

#include <Windows.h>
#include <pe_sieve_api.h>
#include <map>
#include <vector>

#include "hh_params.h"

class HHScanReport
{
public:
    HHScanReport(DWORD start_tick, time_t start_time)
        : startTick(start_tick), endTick(0),
        startTime(start_time), endTime(0)
    {
    }

    bool setEndTick(DWORD end_tick, time_t end_time)
    {
        if (end_tick < this->startTick) {
            return false;
        }
        this->endTick = end_tick;
        this->endTime = end_time;
        return true;
    }

    DWORD getScanTime() const
    {
        if (startTick == 0 || endTick == 0) return 0;
        return (this->endTick - this->startTick);
    }

    bool appendReport(t_report &scan_report, std::string img_name);

    size_t countSuspicious() const
    {
        return suspicious.size();
    }

    std::string toString();
    

protected:
    size_t reportsToString(std::stringstream &stream);

    std::string toJSON(const t_hh_params &params);
    size_t reportsToJSON(std::stringstream &stream, size_t level, const t_hh_params &params);

    time_t startTime;
    time_t endTime;

    DWORD startTick;
    DWORD endTick;

    std::map<DWORD, t_report> pidToReport;
    std::map<DWORD, std::string> pidToName;
    std::vector<DWORD> suspicious;

    friend class HHScanner;
};