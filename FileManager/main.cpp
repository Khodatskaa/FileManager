#include "FileManager.h"

int main() {
    FileManager fileManager;

    int choice;
    std::string path, newPath, mask;

    do {
        std::cout << "\nFile Manager Menu:\n";
        std::cout << "1. Show Contents\n";
        std::cout << "2. Create Folder\n";
        std::cout << "3. Create File\n";
        std::cout << "4. Edit Folder\n";
        std::cout << "5. Edit File\n";
        std::cout << "6. Delete Folder\n";
        std::cout << "7. Delete File\n";
        std::cout << "8. Copy Folder\n";
        std::cout << "9. Copy File\n";
        std::cout << "10. Move File\n";
        std::cout << "11. Calculate Size\n";
        std::cout << "12. Search by Mask\n";
        std::cout << "0. Exit\n";

        std::cout << "Enter your choice(0-12): ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "\nContents:\n ";
            fileManager.showContents("."); 
            break;

        case 2:
            std::cout << "\nEnter folder name: ";
            std::cin >> path;
            fileManager.createFolder(path);
            break;

        case 3:
            std::cout << "\nEnter file name: ";
            std::cin >> path;
            fileManager.createFile(path);
            break;

        case 4:
            std::cout << "\nEnter folder name: ";
            std::cin >> path;
            std::cout << "Enter new folder name: ";
            std::cin >> newPath;
            fileManager.editFolder(path, newPath);  
            break;

        case 5:
            std::cout << "\nEnter file name: ";
            std::cin >> path;
            std::cout << "Enter new file name: ";
            std::cin >> newPath;
            fileManager.editFile(path, newPath);  
            break;

        case 6:
            std::cout << "\nEnter folder name: ";
            std::cin >> path;
            fileManager.deleteFolder(path);
            break;

        case 7:
            std::cout << "\nEnter file name: ";
            std::cin >> path;
            fileManager.deleteFile(path);
            break;

        case 8:
            std::cout << "\nEnter folder name: ";
            std::cin >> path;
            fileManager.copyFolder(path, newPath);
            break;

        case 9:
            std::cout << "\nEnter file name: ";
            std::cin >> path;
            fileManager.copyFile(path, newPath);
            break;

        case 10:
            std::cout << "\nEnter file name: ";
            std::cin >> path;
            std::cout << "Enter new file location: ";
            std::cin >> newPath;
            fileManager.moveFile(path, newPath);
            break;

        case 11:
            std::cout << "\nEnter folder name: ";
            std::cin >> path;
            std::cout << "Size: " << fileManager.calculateSize(path) << " bytes" << std::endl;
            break;

        case 12:
            std::cout << "\nEnter folder name: ";
            std::cin >> path;
            std::cout << "Enter mask: ";
            std::cin >> mask;
            fileManager.searchByMask(path, mask);
            break;

        case 0:
            std::cout << "Exiting..." << std::endl;
            break;

        default:
            std::cout << "Invalid choice" << std::endl;
        }

    } while (choice != 0);

    return 0;
}
