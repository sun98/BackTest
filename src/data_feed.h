/*
 * File: data_feed.h
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:34:21 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:34:21 pm
 * -----
 */

#ifndef _DATA_FEED_H
#define _DATA_FEED_H

#include "data.h"

class DataFeed
{
public:
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool hasNextBar() const = 0;
    virtual DailyBar getNextBar() = 0;
};

#endif