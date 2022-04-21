#include "Database.h"
#include "GameComponents.h"
#include "Cryptosystem.h"

using namespace std;

Database::Database() {
    dataInfoPlayer.clear();
    addressFileDatabase = "";
}

Database::~Database() {

}

void Database::encodeDatabase() {
    ifstream input(addressFileDatabase);
    string dataLine;
    vector <string> data;
    while (getline(input, dataLine)) {
        data.push_back(dataLine);
    }
    input.close();
    ofstream output(addressFileDatabase);
    Cryptosystem crypto;
    for (auto& dataLine : data) {
        output << crypto.base64_encode(dataLine) << '\n';
    }
    output.close();
}

void Database::decodeDatabase() {
    ifstream input(addressFileDatabase);
    string dataLine;
    vector <string> data;
    while (getline(input, dataLine)) {
        data.push_back(dataLine);
    }
    input.close();
    ofstream output(addressFileDatabase);
    Cryptosystem crypto;
    for (auto& dataLine : data) {
        output << crypto.base64_decode(dataLine) << '\n';
    }
    output.close();
}

void Database::importDatabase() {
    decodeDatabase();
    dataInfoPlayer.clear();
    ifstream input(addressFileDatabase);
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
        for (int level = 1; level <= MAX_LEVEL; ++level) {
            int unlockLevel;
            input >> unlockLevel;
            info.setUnlockLevel(level, unlockLevel);
        }

        dataInfoPlayer.push_back(info);
    }
    input.close();
    encodeDatabase();
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

void Database::exportDatabase() {
    ofstream output(addressFileDatabase);
    for (int i = 0; i < dataInfoPlayer.size(); ++i) {
        output << dataInfoPlayer[i].getUsername() << ' ' << dataInfoPlayer[i].getPassword()
            << ' ' << dataInfoPlayer[i].getYourHighScore() << ' ';
        for (int level = 1; level <= MAX_LEVEL; ++level)
            output << dataInfoPlayer[i].getUnlockLevel(level) << ' ';
        output << '\n';
    }
    output.close();
    encodeDatabase();
}

pair <string, bool> Database::registerAccount(InfoPlayer info) {
    string username = info.getUsername();
    if (username == "username") {
        return { "Ten tai khoan khong hop le", false };
    }

    if (username.size() > 15) {
        return { "Ten tai khoan khong qua 15 ky tu", false };
    }
    if (username.find(" ", 0) >= 0
        && username.find(" ", 0) < username.size()) {
        return { "Ten tai khoan co dau cach", false };
    }
    InfoPlayer tempData = getDatabaseUsername(username);
    if (tempData.getUsername() == username) {
        return { "Ten tai khoan da ton tai", false };
    }
    dataInfoPlayer.push_back(info);
    exportDatabase();
    importDatabase();
    return { "Dang ky tai khoan thanh cong", true };
}

bool cmp(InfoPlayer infoPlayer1, InfoPlayer infoPlayer2) {
    return infoPlayer1.getYourHighScore() > infoPlayer2.getYourHighScore();
}

void Database::sortAllDataInfoPlayer() {
    sort(dataInfoPlayer.begin(), dataInfoPlayer.end(), cmp);
}