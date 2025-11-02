#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <sstream>

struct Product {
    std::string id;
    double price;
};

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&t), "%Y-%m-%dT%H:%M:%SZ");
    return ss.str();
}

int main() {
    std::vector<Product> products;
    
    for (int i = 1; i <= 50; ++i) {
        Product p;
        p.id = "P" + std::to_string(i);
        p.price = (double)(rand() % 2000 + 50) / 100.0;
        products.push_back(p);
    }

    std::ofstream file("/data/cash.log", std::ios::app);
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> qty(1, 5);
    std::uniform_int_distribution<> prodIdx(0, products.size() - 1);
    std::uniform_int_distribution<> shopId(100, 999);
    std::uniform_int_distribution<> orderId(10000, 99999);

    int orderCounter = 10000;

    while (true) {
        Product p = products[prodIdx(gen)];
        int q = qty(gen);
        std::string ts = getTimestamp();

        file << "{"
             << "\"timestamp\":\"" << ts << "\","
             << "\"shop_id\":\"S" << shopId(gen) << "\","
             << "\"order_id\":\"O" << orderCounter++ << "\","
             << "\"product_id\":\"" << p.id << "\","
             << "\"quantity\":" << q << ","
             << "\"price\":" << p.price
             << "}" << std::endl;

        file.flush();
        
        // Aspetta 2 secondi
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}