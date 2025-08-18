#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <random>
#include <vector>
#include <iomanip>
#include <fstream>

std::string getRandomIP (std::mt19937 &gen){
    std::uniform_int_distribution<> dist(0,255); //
    return  std::to_string(dist(gen)) + "." +
            std::to_string(dist(gen)) + "." +
            std::to_string(dist(gen)) + "." +
            std::to_string(dist(gen));
}

std::string getTimestamps(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm , %Y-%m-%d %H:%M:%:%S );
    return oss.str(); // pulls the string from the string buffer which is stored in the oss (scratchpad)
}

std::string getRandomAttacktType(std::mt19937 &gen){
    std::vector<std::string> attackTypes = { "UDP Flood","SYN Flood","ICMP Flood","HTTP Flood"}
    std::uniform_int_distribution<> dist(0, attackTypes.size()-1);
    return attackTypes[dist(gen)] //index of the random attack which will be returned
}

std::string generateLogEntry(std::mt19937 &gen) {
    std::ostringstream oss;
    oss << getTimestamp() << " | "
        << getRandomIP(gen) << " | "
        << getRandomAttackType(gen);
    return oss.str();
}

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::ofstream logdile("ddos_log.txt");

    if(!logfile.is_open()){
        std::cerr<<"Error opening log file!"<<std::endl;
        return 1;
    }

    for( int i =0; int < 50; i++ ){
        logfile << generateLogEntry(gen) << std::endl; 
    }

    logfile.close();
    std::cout << "Fake DDoS logs generated in ddos_log.txt ✅" <<std""endl;
    return 0;
}