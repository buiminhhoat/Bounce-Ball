#ifndef __DATABASE__
#define DATABASE

#include "GameComponents.h"

using namespace std;

class Database {
public:
	Database();
	~Database();
	void encodeDatabase();
	void decodeDatabase();
	void importDatabase();
	InfoPlayer getDatabaseUsername(const string& username);
	void updateDatabaseUsername(InfoPlayer info);
	void exportDatabase();
	pair <string, bool> registerAccount(InfoPlayer info);
	void sortAllDataInfoPlayer();
	std::vector<InfoPlayer> getDataInfoPlayer() {
		return dataInfoPlayer;
	}

	void setAddressFileImportDatabase(string addressFileDatabase) {
		this->addressFileDatabase = addressFileDatabase;
	}

	string getAddressFileImportDatabase() {
		return this->addressFileDatabase;
	}

	void setAddressFileExportDatabase(string addressFileDatabase) {
		this->addressFileDatabase = addressFileDatabase;
	}

	string getAddressFileExportDatabase() {
		return this->addressFileDatabase;
	}
private:
	std::vector<InfoPlayer> dataInfoPlayer;
	string addressFileDatabase;
};
#endif // !__DATABASE__
