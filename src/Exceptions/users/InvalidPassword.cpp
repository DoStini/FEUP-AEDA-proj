//
// Created by Nuno Alves on 29/10/2020.
//

#include "InvalidPassword.h"

const char *InvalidPassword::what() const noexcept {
    return "An Invalid Password was used.";
}
