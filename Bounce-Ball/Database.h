#ifndef __DATABASE__
#define DATABASE

#include "GameComponents.h"

using namespace std;

class Database {
public:
	Database();
	~Database();
	void importDatabase();
	InfoPlayer getDatabaseUsername(const string& username);
	void updateDatabaseUsername(InfoPlayer info);
	void exportDatabase();
	pair <string, bool> registerAccount(InfoPlayer info);
	void sortAllDataInfoPlayer();
	std::vector<InfoPlayer> getDataInfoPlayer() {
		return dataInfoPlayer;
	}

	void setAddressFileImportDatabase(string addressFileImportDatabase) {
		this->addressFileImportDatabase = addressFileImportDatabase;
	}

	string getAddressFileImportDatabase() {
		return this->addressFileImportDatabase;
	}

	void setAddressFileExportDatabase(string addressFileExportDatabase) {
		this->addressFileExportDatabase = addressFileExportDatabase;
	}

	string getAddressFileExportDatabase() {
		return this->addressFileExportDatabase;
	}
private:
	std::vector<InfoPlayer> dataInfoPlayer;
	string addressFileImportDatabase;
	string addressFileExportDatabase;
};
#endif // !__DATABASE__
