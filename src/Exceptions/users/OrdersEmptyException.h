//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_ORDERSEMPTYEXCEPTION_H
#define FEUP_AEDA_PROJ_ORDERSEMPTYEXCEPTION_H

#include <exception>
#include <string>
#include <ostream>

/**
 * Exception to be thrown when someone tries to dispatch an empty order queue
 */
class OrdersEmptyException : public std::exception{
public:
    OrdersEmptyException();
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
    friend std::ostream &operator<<(std::ostream &os, const OrdersEmptyException &exception);
};


#endif
