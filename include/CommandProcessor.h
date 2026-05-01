#pragma once
#include "orderBook.h"
#include "PnlEngine.h"
#include <string>


class CommandProcessor {
    public :
    // declaration only
    Side parseSide(const std::string &s);
    void process(const std::string &line, OrderBook &ob, PnlEngine &pnl);
};