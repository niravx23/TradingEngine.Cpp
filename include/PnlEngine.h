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

    int getNetQty() const;
    double getAvgPrice() const;
    double getRealizedPnL() const;
    double getUnrealizedPnL() const;
    double getMarketPrice() const;

    // Setters (rarely needed but added for tests/debug)
    void setMarketPrice(double price);
    

};