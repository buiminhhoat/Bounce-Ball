#ifndef __DATABASE__
#define DATABASE

#include "GameComponents.h"

using namespace std;

class Database {
public:
	Database();
	~Database();
	void importDatabase(const string& importDatabase);
	InfoPlayer getDatabaseUsername(const string& username);
	void updateDatabaseUsername(InfoPlayer info);
	void exportDatabase(const string& exportDatabase);
	pair <string, bool> createAccount(InfoPlayer info);
	void sortAllDataInfoPlayer();
	std::vector<InfoPlayer> getDataInfoPlayer() {
		return dataInfoPlayer;
	}
private:
	std::vector<InfoPlayer> dataInfoPlayer;
};
#endif // !__DATABASE__
