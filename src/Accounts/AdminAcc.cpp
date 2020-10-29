//
// Created by Nuno Alves on 28/10/2020.
//

#include "AdminAcc.h"
#include "Admin.h"

AdminAcc::AdminAcc(User *admin, StreamZ * streamZ) : Account(admin, streamZ){
    if(Admin * ad = dynamic_cast<Admin*>(admin)) {
        this->admin = ad;
    } else {
        throw WrongUserTypeException(UserType::admin);
    }
}

void AdminAcc::run() {

}
