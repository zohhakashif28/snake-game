#include "Logger.h"
#include <fstream>
#include <ctime>
#include <cstring>
using namespace std;

void LogEvent(const string& event) {
    ofstream logFile("game_log.txt", ios::app);
    if (logFile.is_open()) {
        time_t now = time(nullptr);
        char dt[26];
        ctime_s(dt, sizeof(dt), &now);
        dt[strlen(dt) - 1] = '\0'; // Remove newline

        logFile << "[" << dt << "] " << event << endl;
        logFile.close();
    }
}
