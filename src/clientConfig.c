#include "../include/clientConfig.h"

#include "../include/colors.h"
#include "../include/configDB.h"
#include "../include/cryptString.h"
#include "../include/hashTable.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functions for creating hashing table , hash index , add note to table
void loadDataBase(dbConfig *dataBaseConfig, userAccPtr *hashTable,
		  int *tableSize)
{
	FILE *dataBase = fopen(DATABASE_FILE, "r");
	if (!dataBase)
	{
		printf(BOLD_RED "dataBase file not found!\n" BOLD_GREEN "Creating dataBase file..." RESET);

		dataBase = fopen(DATABASE_FILE , "wb");

		if(!dataBase){
			perror("Error occured when creating dataBase file");
			exit(EXIT_FAILURE);
		}

		printf("dataBase file was created Succesfully!\n");
		// fclose(dataBase);
	}

	char *buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);

	uint32_t tempID;
	uint64_t tempCNP;
	uint64_t tempSold;
	char	 tempIBAN[MAX_IBAN_LENGHT];
	char	 tempSurname[MAX_USER_NAME_LENGHT];
	char	 tempName[MAX_USER_NAME_LENGHT];
	char	 tempPassword[MAX_USER_PASS_LENGHT];

	if (dataBaseConfig->isEncrypted == 0) {
		// first time encryption
		while (fgets(buffer, MAX_BUFFER_SIZE, dataBase) != NULL) {
			int parsedArguments = sscanf(
				buffer, "%u " "%"SCNu64 " %s %s %s %s " "%"SCNu64,
				&tempID, &tempCNP, tempIBAN, tempSurname,
				tempName, tempPassword, &tempSold);

			if (parsedArguments != 7) {
				printf(BOLD_RED
				       "Error occurred when reading from data base!\n" RESET);
			}
			addUser(hashTable, tableSize, tempID, tempCNP, tempIBAN,
				tempSurname, tempName, tempPassword, tempSold);
			// cryptString(&buffer);
			// printf("%s" , buffer);
		}
		// dataBaseConfig->isEncrypted = 1;
	} else {
		// the file is already encrypted - first of all decrypt it when load it in mememory
		while (fgets(buffer, MAX_BUFFER_SIZE, dataBase) != NULL) {
			decryptString(&buffer);
			sscanf(buffer, "%u " "%"SCNu64 " %s %s %s %s " "%"SCNu64,
			       &tempID, &tempCNP, tempIBAN, tempSurname,
			       tempName, tempPassword, &tempSold);
		}
	}
	// free(tempIBAN);
	// free(tempSurname);
	// free(tempName);
	// free(tempPassword);
	free(buffer);
	fclose(dataBase);
}

short int checkClient(userAccPtr *hashTable, int size)
{
	if (hashTable == NULL) {
		perror("Table is null!\n");
		return -1;
	}

	if (size == 0) {
		printf("Table is empty!\n");
		return -1;
	}

	return 1;
}
