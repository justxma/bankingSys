#ifndef CONFIG_DATABASE_H
#define CONFIG_DATABASE_H

#include <stdint.h>
#include <time.h>

#define CONFIG_KW "CFMT"
#define FILE_PATH "dataBase/config.meta"
#define BATABASE_DIR "dataBase"
#define DATABASE "dataBase/dataBase.txt"
#pragma pack(push, 1)

typedef struct {
	char	 headerKw[5]; // verify if we have the rigth file
	uint8_t	 isEncrypted;
	uint8_t	 cypherShift;
	uint32_t numberOfClients;
	uint32_t lastID;
	time_t	 createdTime;
	time_t	 lastTimeModified;
} dbConfig;

#pragma pack(pop)

void	  saveConfig(dbConfig *config);
short int createConfigFile(dbConfig *config);
short int loadConfigFile(dbConfig *config);
void	  verifyFile(dbConfig *fileConfig);
void	  formatTime(uint64_t timestamp, char *buffer, size_t bufferSize);
void	  displayConfig(dbConfig *config);

#endif
