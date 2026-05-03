#include <iostream>
#include <cmath>
#include "../include/PnlEngine.h"

PnlEngine::PnlEngine()
    : netQty(0), avgPrice(0), realizedPnL(0), unrealizedPnL(0), marketPrice(0) {}

PnlEngine::~PnlEngine() {}

// BUY 100 10
void PnlEngine::FILL(Side side, int price, int qty)
{
    int currentQty = (side == Side::BUY) ? qty : -qty;

    int oldQty = netQty;
    int newQty = netQty + currentQty;

    // SAME DIRECTION (add to position)
    if (oldQty == 0 || (oldQty > 0 && currentQty > 0) || (oldQty < 0 && currentQty < 0))
    {
        double totalCost =
            avgPrice * std::abs(oldQty) +
            price * std::abs(currentQty);

        netQty = newQty;

        if (netQty != 0)
            avgPrice = totalCost / std::abs(netQty);
        else
            avgPrice = 0;
    }
    else
    {
        // OPPOSITE DIRECTION (closing / flip)
        int closingQty = std::min(std::abs(oldQty), std::abs(currentQty));
        
        if (currentQty < 0) {
            // SELL is closing BUY position
            realizedPnL += closingQty * (price - avgPrice);
        }
        else {
            // BUY is closing SHORT position
            realizedPnL += closingQty * (avgPrice - price);
        }
                

        netQty = newQty;

        // FLIP handling
        if (netQty == 0)
        {
            avgPrice = 0;
        }
        else if ((oldQty > 0 && netQty < 0) || (oldQty < 0 && netQty > 0))
        {
            avgPrice = price;
        }
    }

    // SAFE RESET
    if (netQty == 0)
    {
        avgPrice = 0;
        unrealizedPnL = 0;
    }

    std::cout<<netQty<<" "<<avgPrice<<" "<<realizedPnL<<" "<<unrealizedPnL<<"\n";
}

void PnlEngine::PRICE(double price)
{
    marketPrice = price;

    if (netQty == 0)
    {
        unrealizedPnL = 0;
        return;
    }

    if (netQty > 0)
        unrealizedPnL = netQty * (marketPrice - avgPrice);
    else
        unrealizedPnL = (-netQty) * (avgPrice - marketPrice);
}

void PnlEngine::printPnl()
{
    std::cout << "Net Quantity: " << netQty << "\n";
    std::cout << "Average Price: " << avgPrice << "\n";
    std::cout << "Realized PnL: " << realizedPnL << "\n";
    std::cout << "Unrealized PnL: " << unrealizedPnL << "\n";
}

 int PnlEngine::getNetQty() const
{
    return netQty;
}

double PnlEngine::getAvgPrice() const
{
    return avgPrice;
}

double PnlEngine::getRealizedPnL() const
{
    return realizedPnL;
}

double PnlEngine::getUnrealizedPnL() const
{
    return unrealizedPnL;
}

double PnlEngine::getMarketPrice() const
{
    return marketPrice;
}

void PnlEngine::setMarketPrice(double price)
{
    PRICE(price); // Reuse existing logic to update unrealized PnL
}