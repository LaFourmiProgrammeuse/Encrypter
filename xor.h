#ifndef XOR_H
#define XOR_H

#include <QDebug>
#include <QFile>
#include <QCoreApplication>

#include <iostream>
#include <math.h>
#include <string>
#include <sstream>

class Xor
{
public:
    Xor();

    void Encrypt(std::string key);
    void Uncrypt(std::string key);

    int convertBinaryToDecimal(long long);
    long long convertDecimalToBinary(int);
    std::string convertDecimalToBinaryS(int);

    bool operation_from_file = false;

    std::string data_before_operation;
    std::string data_after_operation = "";

    QFile *data_file_to_read;

    std::string key;
};

#endif // XOR_H
