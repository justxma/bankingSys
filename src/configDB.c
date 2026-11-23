#include "../include/configDB.h"

#include "../include/colors.h"
#include "../include/cryptString.h" // for #define SHIFT 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>

void saveConfig(dbConfig *config)
{
	config->lastTimeModified = time(NULL);
	FILE *file = fopen(FILE_PATH, "wb");
	if (!file) {
		printf(BOLD_RED
		       "\nError opening the config file for saving!\n" RESET);
		return;
	}

	if (fwrite(config, sizeof(dbConfig), 1, file) != 1) {
		printf(BOLD_RED "\nError saving the config file!\n" RESET);
		return;
	}
	fclose(file);
	printf(BOLD_GREEN
	       "\nConfig file (.meta) was saved successfully!\n" RESET);
}

short int createConfigFile(dbConfig *config)
{
	printf("Initializare date...\n");

	memset(config, 0, sizeof(dbConfig));

	config->createdTime = time(NULL);
	memcpy(config->headerKw, CONFIG_KW, 5);
	config->cypherShift = SHIFT;
	config->isEncrypted = 0;
	config->lastID = 0;
	config->numberOfClients = 0;
	printf(BOLD_GREEN "\n%s file was initialy configured!\n",
	       FILE_PATH RESET);
	config->lastTimeModified = time(NULL);
	saveConfig(config);
	return 1;
}

short int loadConfigFile(dbConfig *config)
{
	FILE *fileConfig = fopen(FILE_PATH, "rb");
	if (!fileConfig) {
		printf(BOLD_RED
		       "\nError on opening and creating config file!\n" RESET);
		return 0;
	}

	size_t read_bytes = fread(config, sizeof(dbConfig), 1, fileConfig);
	fclose(fileConfig);

	if (read_bytes != 1) {
		printf(BOLD_RED "\nConfig file (.meta) is corrupted!\n" RESET);
		return -1;
	}

	if (strncmp(config->headerKw, CONFIG_KW, 5) != 0) {
		printf(BOLD_RED
		       "\n%s may be corrupted or is a different file!\n",
		       FILE_PATH RESET);
		return -1;
	}
	printf(BOLD_GREEN "%s was loaded!\n", FILE_PATH RESET);
	return 1;
}

void verifyFile(dbConfig *fileConfig)
{
	FILE *file = fopen(FILE_PATH, "rb");
	if (file == NULL) {
		printf(BOLD_RED
		       "Error occured when opening config file!\n" RESET);
		return;
	}
	if (file == NULL)
	{
		printf(BOLD_RED "File was not found!\nChecking if directory is directory exists : " RESET);

		if(mkdir(BATABASE_DIR, 0755) == 0){
			printf(BOLD_GREEN "Directory has been created!\n" RESET);
			printf(BOLD "Creating the config file for data base...\n" RESET);
		} else if(errno == EEXIST){
			printf(BOLD_GREEN "data base directory exists!\n" RESET);
			printf(BOLD "Creating the config file for data base...\n" RESET);
		} else {
			perror(BOLD_RED "Failed to create the data base directory!\n" RESET);
		}
		
		file = fopen(FILE_PATH , "wb");

		if (!file) {
			perror("Error ocurred when creating file.\n");
			exit(EXIT_FAILURE);
		}
		createConfigFile(fileConfig);
	}
	char temp;
	temp = fgetc(file);
	if (temp == EOF) {
		if (createConfigFile(fileConfig) != 1) {
			printf(BOLD_RED
			       "\nError on creating config file!\n" RESET);
			return;
		}
	} else {
		loadConfigFile(fileConfig);
	}
	fclose(file);
}

void formatTime(__uint64_t timestamp, char *buffer, size_t bufferSize)
{
	time_t raw_time = (time_t)timestamp;

	struct tm *timeInfo = localtime(&raw_time);
	if (timeInfo == NULL) {
		printf(BOLD_RED "Invalid date!\n" RESET);
		return;
	}

	strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", timeInfo);
}

void displayConfig(dbConfig *config)
{
	char createdTime_mod[30] = { 0 };
	formatTime(config->createdTime, createdTime_mod,
		   sizeof(createdTime_mod));

	char lastModTime[30] = { 0 };
	formatTime(config->lastTimeModified, lastModTime, sizeof(lastModTime));
	printf(BOLD "\nConfig file : \n" RESET);
	printf("Key word : %s\n", config->headerKw);
	printf("Number of clients : %d\n", config->numberOfClients);
	printf("Last id : %d\n", config->lastID);
	printf("Created time : %s\n", createdTime_mod);
	printf("Last time modified : %s\n", lastModTime);
	printf("Cipher shift : %d\n", config->cypherShift);
	printf("Encripted : %s\n\n", (config->isEncrypted == 1) ? "Yes" : "NO");
}
