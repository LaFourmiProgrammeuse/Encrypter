#include <QCoreApplication>
#include <QDebug>

#include <iostream>

#include "xor.h"

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);

    Xor _xor;

    return app.exec();
}
