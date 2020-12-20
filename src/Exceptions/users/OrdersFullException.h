//
// Created by andre on 10/17/2020.
//

#ifndef FEUP_AEDA_PROJ_ORDERSFULLXCEPTION_H
#define FEUP_AEDA_PROJ_ORDERSFULLXCEPTION_H

#include <exception>
#include <string>
#include <ostream>

/**
 * Exception to be thrown when someone tries to add an order to a full order queue
 */
class OrdersFullException : public std::exception{
public:
    OrdersFullException();
    /**
     * Brief info about exception
     * @return
     */
    const char * what () const noexcept override;
    friend std::ostream &operator<<(std::ostream &os, const OrdersFullException &exception);
};


#endif
