TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    blocklist.h

DISTFILES += \
    block_part1.csv \
    tx_data_part1_v2.csv \
    tx_data_part2.csv
