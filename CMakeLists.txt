cmake_minimum_required(VERSION 3.17)
project(FEUP_AEDA_proj)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -static-libgcc -static-libstdc++ -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_subdirectory(libs/googletest)
include_directories(libs/googletest/googletest/include)
include_directories(libs/googletest/googlemock/include)

include_directories(src/Exceptions/streams
        src/Exceptions/users
        src/Streams 
        src/Users 
        src/Utils 
        src/Date 
        src/Exceptions/date
        src/Exceptions/accounts
        src/Exceptions
        src/managers 
        src/Accounts)


add_executable(FEUP_AEDA_proj
        main.cpp
        src/Users/User.cpp src/Users/User.h
        src/Streams/Stream.cpp src/Streams/Stream.h
        src/Utils/Date.cpp src/Utils/Date.h
        src/Users/Viewer.cpp src/Users/Viewer.h
        src/Users/Streamer.cpp src/Users/Streamer.h
        src/Streams/Stream.h src/Streams/Stream.cpp
        src/Streams/PrivateStream.h src/Streams/PrivateStream.cpp
        src/Streams/PublicStream.h src/Streams/PublicStream.cpp
        src/Exceptions/users/RestrictedAgeException.cpp src/Exceptions/users/RestrictedAgeException.h
        src/Exceptions/streams/AlreadyInStreamException.cpp src/Exceptions/streams/AlreadyInStreamException.h
        src/Exceptions/streams/NotInStreamException.cpp src/Exceptions/streams/NotInStreamException.h
        src/Exceptions/streams/MaxViewersReach.cpp src/Exceptions/streams/MaxViewersReach.h
        src/Exceptions/users/FollowStreamerException.cpp src/Exceptions/users/FollowStreamerException.h
        src/Exceptions/streams/RestrictedStreamException.cpp src/Exceptions/streams/RestrictedStreamException.h
        src/Exceptions/date/BadDateFormat.cpp src/Exceptions/date/BadDateFormat.h
        src/Exceptions/date/InvalidDate.cpp src/Exceptions/date/InvalidDate.h
        src/Exceptions/streams/NotPrivateStreamException.cpp src/Exceptions/streams/NotPrivateStreamException.h
        src/Exceptions/accounts/WrongUserTypeException.cpp src/Exceptions/accounts/WrongUserTypeException.h 
        src/Exceptions/users/InvalidPassword.cpp src/Exceptions/users/InvalidPassword.h
        src/Exceptions/users/OrdersEmptyException.cpp src/Exceptions/users/OrdersEmptyException.h
        src/Exceptions/users/OrdersFullException.cpp src/Exceptions/users/OrdersFullException.h
        src/Exceptions/users/NoSuchOrderException.cpp src/Exceptions/users/NoSuchOrderException.h
        src/Exceptions/DoesNotExist.h
        src/Exceptions/users/AlreadyExists.h
        src/Exceptions/streams/AlreadyInWhiteListException.cpp src/Exceptions/streams/AlreadyInWhiteListException.h
        src/Exceptions/streams/NotInWhiteListException.cpp src/Exceptions/streams/NotInWhiteListException.h 
        src/Exceptions/EmptyDatabaseException.cpp src/Exceptions/EmptyDatabaseException.h
        src/Streams/LiveStream.cpp src/Streams/LiveStream.h 
        src/Streams/FinishedStream.cpp src/Streams/FinishedStream.h 
        src/managers/StreamZ.cpp src/managers/StreamZ.h 
        src/managers/Database.h 
        src/managers/SortingManager.cpp  src/managers/SortingManager.h 
        src/managers/SearchManager.cpp src/managers/SearchManager.h 
        src/managers/UserManager.cpp src/managers/UserManager.h 
        src/managers/LeaderBoard.cpp src/managers/LeaderBoard.h 
        src/Users/Admin.cpp src/Users/Admin.h 
        src/Utils/utils.cpp src/Utils/utils.h
        src/Accounts/Account.cpp src/Accounts/Account.h
        src/Accounts/AdminAcc.cpp src/Accounts/AdminAcc.h
        src/Accounts/ViewerAcc.cpp src/Accounts/ViewerAcc.h
        src/Accounts/StreamerAcc.cpp src/Accounts/StreamerAcc.h
        src/managers/AdminOps.cpp src/managers/AdminOps.h 
        src/managers/StreamManager.cpp
        src/managers/StreamManager.h
        src/Utils/BST.h src/Users/Donation.cpp src/Users/Donation.h src/managers/Database.cpp src/managers/DonationManager.cpp src/managers/DonationManager.h src/Exceptions/NotInRangeValue.h)


target_link_libraries(FEUP_AEDA_proj gtest gtest_main)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
