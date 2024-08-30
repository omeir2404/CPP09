#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    this->priceDatabase = std::map<std::string, double>();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    this->priceDatabase = other.priceDatabase;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        this->priceDatabase = other.priceDatabase;
    }
    return *this;
}

int BitcoinExchange::readPriceDatabase(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line, date;
    double price;

    if (!file.is_open())
    {
        std::cout << "Error: could not open data file." << std::endl;
        return 1;
    }

    std::getline(file, line);

    int i = 0;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::getline(ss, date, ',');
        ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        price = std::stod(ss.str().substr(date.length() + 1));
        priceDatabase[date] = price;
    }
    return 0;
}

int BitcoinExchange::readOrders(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line, date, valueStr;
    double value;

    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::getline(ss, date, '|');
        std::getline(ss, valueStr);
        date = trim(date);
        valueStr = trim(valueStr);
        // std::cout << date << " => " << valueStr << std::endl;
        if (!validateDate(date))
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
    
        std::istringstream valueStream(valueStr);
        if (!(valueStream >> value))
        {
            std::cout << "Error: not a valid number." << std::endl;
            continue;
        }
    
        if (!validateValue(value))
        {continue;}
    
        std::string closestDate = findClosestDate(date);
        double price = priceDatabase[closestDate];
        double result = value * price;
        std::cout << closestDate << " => " << value << " = " << result << std::endl;
    }
    return 0;
}

std::string BitcoinExchange::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

bool BitcoinExchange::validateDate(const std::string &date)
{
    // Check if the date has the format "YYYY-MM-DD"
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    // Check if the year, month, and day are valid numbers
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);
    int year = std::stoi(yearStr);
    int month = std::stoi(monthStr);
    int day = std::stoi(dayStr);

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Check if the date is a valid calendar date
    std::tm time = {};
    time.tm_year = year - 1900;// beacuase tm_year is years since 1900
    time.tm_mon = month - 1;//because january in tm_mon is 0
    time.tm_mday = day;

    std::time_t timeSinceEpoch = std::mktime(&time);
    if (timeSinceEpoch == -1)
        return false;

    // Check if the date matches the original string
    std::ostringstream oss;
    oss << std::put_time(&time, "%Y-%m-%d");
    std::string formattedDate = oss.str();
    return date == formattedDate;
}

bool BitcoinExchange::validateValue(double value)
{
    if (value < 0){
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000){
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

std::string BitcoinExchange::findClosestDate(const std::string &date)
{
    std::map<std::string, double>::iterator it = priceDatabase.lower_bound(date);
    
    if (it == priceDatabase.end() || it->first != date)
    {
        if (it == priceDatabase.begin())
            return "";
        --it;
    }
    
    return it->first;
}