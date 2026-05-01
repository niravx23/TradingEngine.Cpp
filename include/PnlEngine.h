#pragma once
#include "order.h"

class PnlEngine {
    private:
    int netQty;
    double avgPrice;
    double realizedPnL;
    double unrealizedPnL;
    double marketPrice;

public:
    PnlEngine();
    void FILL(Side side, int price, int qty);
    void PRICE(double price);
    void printPnl();
    ~PnlEngine();

};