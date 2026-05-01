#include<iostream>
#include "../include/orderBook.h"
#include "../include/CommandProcessor.h"
#include "../include/PnlEngine.h"

using namespace std ;


int main() {
    OrderBook ob;
    CommandProcessor cp;
    PnlEngine pnl;

    std::string line;   

    while (std::getline(std::cin, line)) {
        cp.process(line, ob, pnl);
    }
}