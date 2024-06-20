#include <stdio.h>
#include <stdlib.h>

int main() {
    // List files in the current directory
    printf("Listing files in the current directory:\n");
    system("ls");

    // Print the current working directory
    printf("\nCurrent working directory:\n");
    system("pwd");

    // Create a new directory named "newdir"
    printf("\nCreating a new directory named 'newdir':\n");
    system("mkdir newdir");

    // List files to show the new directory
    printf("\nListing files in the current directory after creating 'newdir':\n");
    system("ls");

    // Create a new file named "newfile.txt" inside "newdir"
    printf("\nCreating a new file named 'newfile.txt' in 'newdir':\n");
    system("touch newdir/newfile.txt");

    // List files in the new directory to show the new file
    printf("\nListing files in 'newdir' after creating 'newfile.txt':\n");
    system("ls newdir");

    // Write text to the new file
    printf("\nWriting 'Hello, World!' to 'newfile.txt':\n");
    system("echo 'Hello, World!' > newdir/newfile.txt");

    // Display the content of the new file
    printf("\nDisplaying the content of 'newfile.txt':\n");
    system("cat newdir/newfile.txt");

    // Copy the new file to a new file named "copyfile.txt"
    printf("\nCopying 'newfile.txt' to 'copyfile.txt':\n");
    system("cp newdir/newfile.txt newdir/copyfile.txt");

    // List files in the new directory to show the copied file
    printf("\nListing files in 'newdir' after copying 'newfile.txt' to 'copyfile.txt':\n");
    system("ls newdir");

    // Move (rename) "copyfile.txt" to "renamedfile.txt"
    printf("\nRenaming 'copyfile.txt' to 'renamedfile.txt':\n");
    system("mv newdir/copyfile.txt newdir/renamedfile.txt");

    // List files in the new directory to show the renamed file
    printf("\nListing files in 'newdir' after renaming 'copyfile.txt' to 'renamedfile.txt':\n");
    system("ls newdir");

    // Remove the original file
    printf("\nRemoving 'newfile.txt':\n");
    system("rm newdir/newfile.txt");

    // List files in the new directory to show the file has been removed
    printf("\nListing files in 'newdir' after removing 'newfile.txt':\n");
    system("ls newdir");

    // Remove the directory
    printf("\nRemoving the directory 'newdir':\n");
    system("rmdir newdir");

    // List files in the current directory to show the directory has been removed
    printf("\nListing files in the current directory after removing 'newdir':\n");
    system("ls");

    return 0;
}
