#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <regex>
#include <limits>

class BitcoinExchange {
private:
    std::map<std::string, double> priceDatabase;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& other);
    ~BitcoinExchange();
    BitcoinExchange& operator=(const BitcoinExchange& other);



    int readPriceDatabase(const std::string& filename);
    int readOrders(const std::string& filename);

    std::string trim(const std::string &str);
    bool validateDate(const std::string &date);
    bool validateValue(double value);
    std::string findClosestDate(const std::string &date);

private:

};

#endif
