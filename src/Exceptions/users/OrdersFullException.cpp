//
// Created by andre on 10/17/2020.
//

#include "OrdersFullException.h"

#include <utility>

OrdersFullException::OrdersFullException()  {}

const char *OrdersFullException::what() const throw() {
    return "No orders";
}

/**
 * Outputs a detailed explanation to the user on why the exception was thrown
 * @return Output stream reference
 */
std::ostream &operator<<(std::ostream &os, const OrdersFullException &exception) {
    os << "Orders queue is full!";
    return os;
}
