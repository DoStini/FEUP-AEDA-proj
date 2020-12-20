//
// Created by andre on 10/17/2020.
//

#include "OrdersEmptyException.h"

#include <utility>

OrdersEmptyException::OrdersEmptyException()  {}

const char *OrdersEmptyException::what() const throw() {
    return "No orders";
}

/**
 * Outputs a detailed explanation to the user on why the exception was thrown
 * @return Output stream reference
 */
std::ostream &operator<<(std::ostream &os, const OrdersEmptyException &exception) {
    os << "Orders queue is empty!";
    return os;
}
