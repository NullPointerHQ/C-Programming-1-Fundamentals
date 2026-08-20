//Preprocessor Directives
#include <stdio.h>
#include <string.h>

void railFenceEncrypt(char* msg, char* encrypted, int numRails); //Encryption F(x) Prototype
void railFenceDecrypt(char* msg, char* decrypted, int numRails); //Decryption F(x) Prototype

int main(void) {
	//Given Variables
	char input[200], encrypted[200], decrypted[200], encryptedFile[200],
		decryptedFile[200];
	int choice, numRails;

	while (1) {
		printf("\nRail Fence Cipher Menu\n");
		printf("1. Encrypt a message\n");
		printf("2. Decrypt a message\n");
		printf("3. Read from a file and decrypt\n");
		printf("4. Encrypt a message and check against reference\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		if (choice > 5 || choice < 0) {
			printf("Invalid option please start again.\n");
			return 0;
		}
		switch (choice) {
		case 1://Generic Input Encryption,|| Fully functional
			printf("\nEncrypt a Message\n");
			printf("Enter a message to encrypt: \n");
			getchar();//To consume the newline character
			fgets(input, sizeof(input), stdin);
			input[strcspn(input, "\n")] = '\0'; // Remove the newline character || Done, addressed in line 37

			printf("Enter the number of rails: \n");
			scanf("%d", &numRails); //Limit is 10

			if (numRails > 10 || numRails < 2) { //Error Handling - Applies only if Rails exceed 10 or falls below 2
				printf("Please keep the amount of rails between 2 and 10.\n");
				printf(" Please enter another number: \n");
				scanf("%d", &numRails);
			}

			railFenceEncrypt(input, encrypted, numRails); //Function call to perform the encryption
			printf("After Encryption your message is: \n %s", encrypted);
			break;

		case 2: //Decryption || Fully Functional
			/*Decryption is copy pasted from case 1, only difference is in the function called.*/
			printf("\nDecrypt a Message\n");
			printf("Enter the message to Decrypt: \n"); //Gathering input from the user using fgets
			getchar();//To consume the newline character
			fgets(input, sizeof(input), stdin);
			input[strcspn(input, "\n")] = '\0'; // Remove the newline character || Done, addressed in line 57

			printf("Enter the number of rails: \n");
			scanf("%d", &numRails);
			if (numRails > 10 || numRails < 2) { //Error Handling - Applies only if Rails exceed 10 or falls below 2
				printf("Please keep the amount of rails between 2 and 10.\n");
				printf(" Please enter another number: \n");
				scanf("%d", &numRails);
			}
			railFenceDecrypt(input, decrypted, numRails); //Function call to perform the Decryption
			printf("After decryption your message is: \n %s", decrypted);
			break;

		case 3: //Read from file and decrypt || Mostly Functional, Decryption has issues with complete sentences.
			char fileName[200]; //Will be used to let the user enter the name of the file.
			printf("Please enter the name of the file including the type: \n");
			scanf("%s", fileName); //Gathering file's name


			FILE* file = fopen(fileName, "r");//Opening the file given by the user in read-only

			if (file == NULL) { //Error Handling - Applies if the file doesn't open correctly.
				printf("An error has been encountered while opening file.\n");
				printf("Please ensure that the file exists and that you have given");
				printf("the correct name for it. It is case sensitive.");
				return 1;
			}

			if (fscanf(file, "%d \n", &numRails) != 1) { //Reading the number of rails in.
				printf("Error encountered while reading the number of rails from file.\n");//Applies if there was in fact an error
				fclose(file); // Close the file
				return 1;
			}

			if (fgets(input, sizeof(input), file) == NULL) { //Reads in message
				printf("Error reading the message from file.\n");//Applies if message wasnt read in correctly.
				fclose(file);
				return 1;
			}
			fclose(file);
			printf("Number of rails: %d\n", numRails);
			printf("Cipher taken: %s\n", input);

			//Information gathered, setting the correct variables and calling in the F(x)
			railFenceDecrypt(input, decrypted, numRails); //Function call to perform the Decryption

			printf("After decryption your message is: \n %s", decrypted);
			break;

		case 4: //Encrypt and check against reference ||Fully functional.

			printf("Enter a message to encrypt: \n");
			getchar();//To consume the newline character
			fgets(input, sizeof(input), stdin);
			input[strcspn(input, "\n")] = '\0'; // Remove the newline character || Done, addressed in line 114
			printf("Enter the number of rails: \n");
			scanf("%d", &numRails); //Limit is 10
			if (numRails > 10 || numRails < 2) { //Error Handling - Applies only if Rails exceed 10 or falls below 2
				printf("Please keep the amount of rails between 2 and 10.\n");
				printf(" Please enter another number: \n");
				scanf("%d", &numRails);
			}
			railFenceEncrypt(input, encrypted, numRails); //Function call to perform the encryption
			printf("After Encryption your message is: \n %s\n", encrypted);

			char ReffileName[200]; //Will be used to let the user enter the name of the file.
			printf("Please enter the name of the reference file including the type: \n");
			scanf("%s", ReffileName); //Gathering file's name

			FILE* file2 = fopen(ReffileName, "r");//Opening the file given by the user in read-only

			if (file2 == NULL) { //Error Handling - Applies if the file doesn't open correctly.
				printf("An error has been encountered while opening file.\n");
				printf("Please ensure that the file exists and that you have given\n");
				printf("the correct name for it. It is case sensitive.\n");
				return 1;
			}
			char throwaway[200]; //Consumes First line of Reference File
			char reference[200]; //String variable for reference string
			
			if (fgets(throwaway, sizeof(throwaway), file2) == NULL) { //Reads in first line, checks if it read it correctly
			printf("Error reading the message from file.\n"); //Applies if line wasnt read in correctly.
			fclose(file2);
			return 1;
			}
			
			if (fgets(reference, sizeof(reference), file2) == NULL) {//Same as above but will take the second line instead
				printf("Error reading the message from file.\n");
				fclose(file2);
				return 1;
			}
			printf("%s \n", encrypted);
			printf("%s \n", reference);
			input[strcspn(reference, "\n")] = '\0';
			printf("Message taken from file: %s\n", reference);
			for (int i = 0; encrypted[i] != '\0'; i++) {
				printf("%c \n", encrypted[i]);
				printf("%c \n", reference[i]);
			}
			int comparison = strcmp(encrypted, reference); //Using string compare function to compare strings
			printf("%d", comparison);
			if (comparison == 0) {//Strings are identical
				printf("Strings are identical.\n");
			}
			else { //Only need to see if they're identical, don't need extra detail.
				printf("Strings are not identical\n");
			}
			break;
		case 5: //Exit
			printf("Exiting Program..."); /*Added to keep the user informed of what the program is doing.*/
			return 0;
		default:;
		}
	}
}


void railFenceEncrypt(char* msg, char* encrypted, int numRails) {
	int len = strlen(msg);
	char railFence[200][200];
	int count = 0;
	//Variables to determine placement
	//Direction: 1 is going down, -1 is going up
	int row = 0, col = 0, direction = 1;

	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			railFence[i][j] = '*';//Used to be just ' ' but I changed to * in order to preserve spaces
		}
	}
	//Placing the characters in the empty grid
	for (int i = 0; i < len; i++) {
		if (row == 0) {
			direction = 1; //Exists to change the direction when at the top rail
		}
		else if (row == numRails - 1) {
			direction = -1; //Exists to change the direction when at the bottom rail
		}

		railFence[row][col] = msg[i];//Placing the character in the grid
		count++;//Keeps track of characters placed in the array to prevent there being extra characters

		//Updating row and column variables depending on position
		if (direction == 1) {
			row++;
		}
		else {
			row--;
			col++;
		}
	}
	int index = 0; //Keeps track of position where characters are stored in the encrypted variable
	for (int i = 0; i < numRails; i++) { //Goes through the rows
		for (int j = 0; j < len; j++) { //Goes through the columns
			if (railFence[i][j] != '*') { //Checks if the current element is NOT an asterisk
				encrypted[index] = railFence[i][j]; //In which case it is a part of the message and gets added here
				index++; //Updating position
			}
		}
	}
	encrypted[index] = '\0';//NULL Terminator
}

void railFenceDecrypt(char* msg, char* decrypted, int numRails) {
	int len = strlen(msg);
	char railFence[200][200];
	int count = 0;

	//Variables to determine placement
	//Direction: 1 is going down, -1 is going up
	int row = 0, direction = 1;

	/*Setting up the 2D Grid with blank spaces so that I can fill it with characters later.*/
	for (int i = 0; i < numRails; i++) {
		for (int j = 0; j < len; j++) {
			railFence[i][j] = '\0';//The Asterisk is used to preserve spaces in provided ciphers
		}
	}
	//Putting placeholder X's where the characters go.

	for (int i = 0; i < len; i++) {
		railFence[row][i] = 'X';
		row += direction;

		if (row == 0 || row == numRails - 1) {
			direction = -direction;
		}
	}

	// Printing out railFence to see if proper pattern is displayed
	for (int i = 0; i < numRails; i++) {
		for (int j = 0; j < len; j++) {
			printf("%c ", railFence[i][j]);;
		}
		printf("\n");
	}
	//Replacing the X's with the characters from the cipher
	for (int i = 0; i < numRails; i++) {
		for (int j = 0; j < len; j++) {
			if (railFence[i][j] == 'X') {
				railFence[i][j] = msg[count];
				count++;
			}
		}
		//Updating row variables depending on position
		if (direction == 1) {
			row++;
		}
		else {
			row--;
		}

	}

	/*Now to loop through the array and decrypt the message*/
	int index = 0; //Keeps track of position where characters are stored in the decrypted variable
	row = 0;
	direction = 1;
	for (int i = 0; i < len; i++) {
		decrypted[index++] = railFence[row][i];
		row += direction;
		//Changes Direction when at top/bottom rail
		if (row == 0 || row == numRails - 1) {
			direction = -direction;
		}
	}
	decrypted[index] = '\0';//NULL Terminator
}