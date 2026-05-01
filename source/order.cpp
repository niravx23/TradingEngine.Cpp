#include "../include/order.h"

Order::Order(int id, Side side, int price, int quantity)
    : id_(id), side_(side), price_(price), quantity_(quantity) {}

int Order::getId() { return id_; }
Side Order::getSide() { return side_; }
int Order::getPrice() { return price_; }
int Order::getQuantity() { return quantity_; }

void Order::setPrice(int price) { price_ = price; }
void Order::setQuantity(int quantity) { quantity_ = quantity; }