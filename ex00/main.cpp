#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./btc [filename]" << std::endl;
        return 1;
    }

    BitcoinExchange exchange;
    if (exchange.readPriceDatabase("data.csv") != 0) {
        return 1;
    }
     // Assuming the price database is named "prices.csv"
    if (exchange.readOrders(argv[1]) != 0) {
        return 1;
    }

    return 0;
}