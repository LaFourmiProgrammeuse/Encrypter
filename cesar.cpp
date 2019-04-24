#include "cesar.h"

Cesar::Cesar()
{

    int answer;

    do{

        std::cout << "Veuillez choisir une façon de fournir les données à chiffrer/déchiffrer" << std::endl;
        std::cout << "1) Entrer les données directement" << std::endl;
        std::cout << "2) Traiter les données depuis un fichier" << std::endl;

        std::cin >> answer;

        if(answer == 1){

            std::cout << "Veuillez entrez les données à chiffrer/déchiffrer :" << std::endl;
            std::cin >> data_before_operation;

        }
        else if(answer == 2){

            std::cout << "Veuillez entrez le chemin de votre fichier à chiffrer/déchiffrer :" << std::endl;

            std::string file_path;
            std::cin >> file_path;

            data_file_to_read = new QFile(QString::fromStdString(file_path));
            if(!data_file_to_read->open(QIODevice::ReadOnly)){
                std::cout << "Erreur lors de l'ouverture du fichier..." << std::endl;
                QCoreApplication::exit(-1);
            }

            data_before_operation = data_file_to_read->readAll().toStdString();

        }

    }while(answer != 1 && answer != 2);
}

int Cesar::convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

long long Cesar::convertDecimalToBinary(int n){

    std::string binary_number_string = "0000000";

    for(int i = 0; i < 7; i++){

        if(n >= 64){
            binary_number_string[0] = '1';
            n -= 64;
        }
        else if(n >= 32){
            binary_number_string[1] = '1';
            n -= 32;
        }
        else if(n >= 16){
            binary_number_string[2] = '1';
            n -= 16;
        }
        else if(n >= 8){
            binary_number_string[3] = '1';
            n -= 8;
        }
        else if(n >= 4){
            binary_number_string[4] = '1';
            n -= 4;
        }
        else if(n >= 2){
            binary_number_string[5] = '1';
            n -= 2;
        }
        else if(n == 1){
            binary_number_string[6] = '1';
            n -= 1;
        }
    }

    return atol(binary_number_string.c_str());
}

std::string Cesar::convertDecimalToBinaryS(int n){

    std::string binary_number_string = "00000000";

    for(int i = 0; i < 8; i++){

        if(n >= 128){
            binary_number_string[0] = '1';
            n -= 128;
        }
        else if(n >= 64){
            binary_number_string[1] = '1';
            n -= 64;
        }
        else if(n >= 32){
            binary_number_string[2] = '1';
            n -= 32;
        }
        else if(n >= 16){
            binary_number_string[3] = '1';
            n -= 16;
        }
        else if(n >= 8){
            binary_number_string[4] = '1';
            n -= 8;
        }
        else if(n >= 4){
            binary_number_string[5] = '1';
            n -= 4;
        }
        else if(n >= 2){
            binary_number_string[6] = '1';
            n -= 2;
        }
        else if(n == 1){
            binary_number_string[7] = '1';
            n -= 1;
        }
    }

    return binary_number_string;
}

