/*
 * File: Instrument.h
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:32:02 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:32:02 pm
 * -----
 */

#ifndef _DATA_H
#define _DATA_H

#include <string>

struct DailyBar
{
    std::string symbol;        // 股票代码
    std::string date;          // 日期
    double open;               // 开盘价
    double high;               // 最高价
    double low;                // 最低价
    double close;              // 收盘价
    double adj_close;          // 调整收盘价
    unsigned long long volume; // 成交量
};

#endif