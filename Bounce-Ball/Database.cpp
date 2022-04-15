#include "Database.h"

using namespace std;

Database::Database() {

}

Database::~Database() {

}

void Database::importDatabase(const string& importDatabase) {
    dataInfoPlayer.clear();
    ifstream input(importDatabase);
    string dataLine;
    int lines = 0;

    InfoPlayer info;
    string username;
    string password;
    int highScore;
    while (input >> username) {
        ++lines;
        input >> password;
        input >> highScore;
        info.setUsername(username);
        info.setPassword(password);
        info.setYourHighScore(highScore);
        for (int level = 1; level <= 50; ++level) {
            int unlockLevel;
            input >> unlockLevel;
            info.setUnlockLevel(level, unlockLevel);
        }

        dataInfoPlayer.push_back(info);
    }
    input.close();
}

InfoPlayer Database::getDatabaseUsername(const string& username) {
    InfoPlayer info;
    for (int i = 0; i < dataInfoPlayer.size(); ++i) {
        if (dataInfoPlayer[i].getUsername() == username) return dataInfoPlayer[i];
    }
    return info;
}

void Database::updateDatabaseUsername(InfoPlayer updateInfo) {
    string usernameUpdateInfo = updateInfo.getUsername();
    for (int i = 0; i < dataInfoPlayer.size(); ++i) {
        string usernameDatabase = dataInfoPlayer[i].getUsername();
        if (usernameDatabase == usernameUpdateInfo) {
            dataInfoPlayer[i] = updateInfo;
        }
    }
}

void Database::exportDatabase(const string& exportDatabase) {
    ofstream output(exportDatabase);
    for (int i = 0; i < dataInfoPlayer.size(); ++i) {
        output << dataInfoPlayer[i].getUsername() << ' ' << dataInfoPlayer[i].getPassword()
            << ' ' << dataInfoPlayer[i].getYourHighScore() << ' ';
        for (int level = 1; level <= 50; ++level)
            output << dataInfoPlayer[i].getUnlockLevel(level) << ' ';
        output << '\n';
    }
    output.close();
}

pair <string, bool> Database::createAccount(InfoPlayer info) {
    string username = info.getUsername();
    if (username.find(" ", 0) >= 0
        && username.find(" ", 0) < username.size()) {
        return { "Ten tai khoan co dau cach", false };
    }
    InfoPlayer tempData = getDatabaseUsername(username);
    if (tempData.getUsername() == username) {
        return { "Tai khoan da ton tai", false };
    }
    dataInfoPlayer.push_back(info);
    return { "Tao tai khoan thanh cong", true };
}
