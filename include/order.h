#pragma once

enum class Side {
    BUY,
    SELL
};

class Order {
private:
    int id_;
    Side side_;
    int price_;
    int quantity_;

public:
    Order(int id, Side side, int price, int quantity);

    int getId() ;
    Side getSide() ;
    int getPrice() ;
    int getQuantity() ;

    void setPrice(int price);
    void setQuantity(int quantity);
};