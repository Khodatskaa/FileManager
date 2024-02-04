#include "FileManager.h"

namespace fs = boost::filesystem;

FileManager::FileManager() {}

bool FileManager::isFile(const std::string& path) {
    fs::path filePath(path);
    return fs::exists(filePath) && fs::is_regular_file(filePath);
}

bool FileManager::isDirectory(const std::string& path) {
    fs::path directoryPath(path);
    return fs::exists(directoryPath) && fs::is_directory(directoryPath);
}

void FileManager::showContents(const std::string& path) {
    fs::path directoryPath(path);
    if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    else {
        std::cout << "Error: Invalid directory path" << std::endl;
    }
}

void FileManager::createFolder(const std::string& path) {
    fs::path folderPath(path);
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        if (fs::create_directory(folderPath)) {
            std::cout << "Folder created successfully!" << std::endl;
        }
        else {
            std::cout << "Error: Unable to create folder" << std::endl;
        }
    }
    else {
        std::cout << "Error: Folder already exists" << std::endl;
    }
}

void FileManager::createFile(const std::string& path) {
    fs::path filePath(path);
    if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
        std::ofstream file(path);
        if (file.is_open()) {
            file.close();
            std::cout << "File created successfully!" << std::endl;
        }
        else {
            std::cout << "Error: Unable to create file" << std::endl;
        }
    }
    else {
        std::cout << "Error: File already exists" << std::endl;
    }
}

void FileManager::editFolder(const std::string& path, const std::string& newName) {
    fs::path oldFolderPath(path);
    fs::path newFolderPath(path);
    newFolderPath.remove_filename();
    newFolderPath /= newName;

    if (fs::exists(oldFolderPath) && fs::is_directory(oldFolderPath)) {
        try {
            fs::rename(oldFolderPath, newFolderPath);
            std::cout << "Folder renamed successfully!" << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Error: Source folder not found" << std::endl;
    }
}

void FileManager::editFile(const std::string& path, const std::string& newName) {
    fs::path oldFilePath(path);
    fs::path newFilePath(oldFilePath.parent_path() / newName);

    if (fs::exists(oldFilePath) && fs::is_regular_file(oldFilePath)) {
        try {
            fs::rename(oldFilePath, newFilePath);
            std::cout << "File renamed successfully!" << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Error: Source file not found" << std::endl;
    }
}

void FileManager::deleteFolder(const std::string& path) {
    fs::path folderPath(path);
    if (fs::exists(folderPath) && fs::is_directory(folderPath)) {
        try {
            fs::remove_all(folderPath);
            std::cout << "Folder deleted successfully!" << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Error: Folder not found" << std::endl;
    }
}

void FileManager::deleteFile(const std::string& path) {
    fs::path filePath(path);
    if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
        try {
            fs::remove(filePath);
            std::cout << "File deleted successfully!" << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Error: File not found" << std::endl;
    }
}

void FileManager::copyFolder(const std::string& path, const std::string& newPath) {
    fs::path sourcePath(path);
    fs::path destinationPath(newPath);
    destinationPath /= sourcePath.filename();

    if (fs::exists(sourcePath) && fs::is_directory(sourcePath)) {
        try {
            fs::copy(sourcePath, destinationPath, fs::copy_options::recursive);
            std::cout << "Folder copied successfully!" << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Error: Source folder not found" << std::endl;
    }
}

void FileManager::copyFile(const std::string& path, const std::string& newPath) {
    fs::path sourcePath(path);
    fs::path destinationPath(newPath);
    destinationPath /= sourcePath.filename();

    if (fs::exists(sourcePath) && fs::is_regular_file(sourcePath)) {
        if (fs::exists(destinationPath)) {
            std::cout << "Destination file already exists. Do you want to overwrite it? (y/n): ";
            char overwriteChoice;
            std::cin >> overwriteChoice;

            if (tolower(overwriteChoice) == 'y') {
                try {
                    fs::copy_file(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
                    std::cout << "File copied successfully!" << std::endl;
                }
                catch (const fs::filesystem_error& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }
            else {
                std::cout << "Copy operation canceled by user" << std::endl;
            }
        }
        else {
            try {
                fs::copy_file(sourcePath, destinationPath);
                std::cout << "File copied successfully!" << std::endl;
            }
            catch (const fs::filesystem_error& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
    else {
        std::cout << "Error: Source file not found" << std::endl;
    }
}

void FileManager::moveFile(const std::string& path, const std::string& newPath) {
    fs::path sourcePath(path);
    fs::path destinationPath(newPath);

    if (fs::exists(sourcePath) && fs::is_regular_file(sourcePath)) {
        try {
            fs::rename(sourcePath, destinationPath / sourcePath.filename());
            std::cout << "File moved successfully!" << std::endl;
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Error: Source file not found" << std::endl;
    }
}

int FileManager::calculateSize(const std::string& path) {
    fs::path objectPath(path);
    if (fs::exists(objectPath)) {
        try {
            uintmax_t size = fs::file_size(objectPath);
            std::cout << "Size of '" << path << "': " << size << " bytes" << std::endl;
            return static_cast<int>(size);
        }
        catch (const fs::filesystem_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cout << "Error: File or folder not found" << std::endl;
    }
    return -1;
}

void FileManager::searchFile(const std::string& fileName) {
    fs::path currentPath = fs::current_path();
    for (const auto& entry : fs::recursive_directory_iterator(currentPath)) {
        if (entry.path().filename() == fileName) {
            std::cout << "File found at: " << entry.path() << std::endl;

            recentFiles.push_back(entry.path().string());

            return;
        }
    }
    std::cout << "File not found" << std::endl;
}

void FileManager::searchFolder(const std::string& folderName) {
    fs::path currentPath = fs::current_path();
    for (const auto& entry : fs::recursive_directory_iterator(currentPath)) {
        if (entry.path().filename() == folderName) {
            std::cout << "Folder found at: " << entry.path() << std::endl;

            recentFolders.push_back(entry.path().string());

            return;
        }
    }
    std::cout << "Folder not found" << std::endl;
}

const std::vector<std::string>& FileManager::getRecentFiles() const {
    return recentFiles;
}

const std::vector<std::string>& FileManager::getRecentFolders() const {
    return recentFolders;
}

FileManager::~FileManager() {}
