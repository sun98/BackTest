/*
 * File: file_data_feed.h
 * Author: Suibin Sun
 * Created Date: 2023-06-03, 3:45:37 pm
 * -----
 * Last Modified by: Suibin Sun
 * Last Modified: 2023-06-03, 3:45:37 pm
 * -----
 */

#ifndef _FILE_DATA_FEED_H
#define _FILE_DATA_FEED_H

#include <fstream>
#include <sstream>
#include <vector>

#include "data_feed.h"

class FileDataFeed : public DataFeed
{
private:
    std::string filename;
    std::ifstream file;
    std::vector<DailyBar> data;
    size_t currentIndex;

public:
    FileDataFeed(const std::string &filename);

    bool connect() override;

    bool disconnect() override;

    bool hasNextBar() const override;

    DailyBar getNextBar() override;

private:
    void initData();
};

#endif