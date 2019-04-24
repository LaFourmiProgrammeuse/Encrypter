#include "xor.h"

Xor::Xor()
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

    do{

        std::cout << "Quelle opration voulez vous effectuer sur ces données ?" << std::endl;
        std::cout << "1) Les chiffrer avec une clé" << std::endl;
        std::cout << "2) Les déchiffrer avec une clé" << std::endl;

        std::cin >> answer;

        if(answer == 1){

            std::cout << "Veuillez entrer la clé de chiffrement :" << std::endl;

            std::cin >> key;
            Encrypt(key);
        }
        else if(answer == 2){

            std::cout << "Veuillez entrer la clé de déchiffrement :" << std::endl;

            std::cin >> key;
            Uncrypt(key);
        }

    }while(answer != 1 && answer != 2);
}

void Xor::Encrypt(std::string key){

    std::string binary_data_encrypted;

    int key_index = 0;

    for(int i = 0; i < data_before_operation.size(); i++){

        int data_char_ascii = int(data_before_operation[i]);

        std::ostringstream ostream_1;
        ostream_1 << convertDecimalToBinary(data_char_ascii);

        std::string binary_data_char;
        binary_data_char = ostream_1.str();

        int key_char_ascii = int(key[key_index]);

        std::ostringstream ostream_2;
        ostream_2 << convertDecimalToBinary(key_char_ascii);

        std::string binary_key_char;
        binary_key_char = ostream_2.str();

        for(int j = 0; j < 7; j++){

            if(binary_data_char[j] == '1' && binary_key_char[j] == '1'){
                binary_data_encrypted.append("0");
            }
            else if(binary_data_char[j] == '0' && binary_key_char[j] == '0'){
                binary_data_encrypted.append("0");
            }
            else if(binary_data_char[j] == '1' && binary_key_char[j] == '0'){
                binary_data_encrypted.append("1");
            }
            else if(binary_data_char[j] == '0' && binary_key_char[j] == '1'){
                binary_data_encrypted.append("1");
            }

            //std::cout << "Key : " << key_index << ", " << binary_key_char << ", Data : " << binary_data_char << ", " << binary_data_char[j] << ", " << binary_key_char[j] << std::endl;

        }

        if(key_index == key.size()-1){
            key_index = 0;
        }
        else{
            key_index++;
        }
    }

    data_after_operation = binary_data_encrypted;

    /*for(int o = 0; o < binary_data_encrypted.size(); o+=7){

        QString char_binary_encrypted = QString::fromStdString(binary_data_encrypted).mid(o, 7); //qDebug() << char_binary_encrypted;

        char char_decimal_encrypted;
        char_decimal_encrypted = char(convertBinaryToDecimal(char_binary_encrypted.toLongLong()));
        std::cout << char_decimal_encrypted << "    " << char_binary_encrypted.toStdString() << "   " << convertBinaryToDecimal(char_binary_encrypted.toLongLong()) << std::endl;
        data_after_operation+=char_decimal_encrypted;
    }*/

    std::cout << "Données chiffrées : " << data_after_operation << std::endl;
}

void Xor::Uncrypt(std::string key){

    int key_index = 0;
    std::string binary_data_uncrypted;

    for(int i = 0; i < data_before_operation.size(); i+=7){

        int key_char_ascii = int(key[key_index]);

        std::ostringstream ostream_2;
        ostream_2 << convertDecimalToBinary(key_char_ascii);

        std::string binary_key_char;
        binary_key_char = ostream_2.str();

        for(int j = 0; j < 7; j++){

            if(binary_key_char[j] == '1' && data_before_operation[i+j] == '1'){
               binary_data_uncrypted+='0';
            }
            else if(binary_key_char[j] == '0' && data_before_operation[i+j] == '1'){
               binary_data_uncrypted+='1';
            }
            else if(binary_key_char[j] == '1' && data_before_operation[i+j] == '0'){
               binary_data_uncrypted+='1';
            }
            else if(binary_key_char[j] == '0' && data_before_operation[i+j] == '0'){
               binary_data_uncrypted+='0';
            }

        }
        char char_data_uncrypted;
        char_data_uncrypted = char(convertBinaryToDecimal(QString::fromStdString(binary_data_uncrypted).toLongLong()));
        data_after_operation+=char_data_uncrypted; //std::cout << convertBinaryToDecimal(QString::fromStdString(binary_data_uncrypted).toLongLong()) << "   " << binary_data_uncrypted << std::endl;

        if(key_index == key.size()-1){
            key_index = 0;
        }
        else{
            key_index++;
        }

        binary_data_uncrypted = "";
    }

    std::cout << "Données déchiffrées : " << data_after_operation << std::endl;
}

int Xor::convertBinaryToDecimal(long long n)
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

long long Xor::convertDecimalToBinary(int n){

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

std::string Xor::convertDecimalToBinaryS(int n){

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

