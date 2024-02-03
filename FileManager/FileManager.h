#ifndef FileManager_h
#define FileManager_h

#include <boost/filesystem.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileManager {
private:
	bool isFile(const std::string& path);
	bool isDirectory(const std::string& path);

public:
	FileManager();

	void showContents(const std::string& path);
	void createFolder(const std::string& path);
	void createFile(const std::string& path);
	void editFolder(const std::string& path, const std::string& newName);
	void editFile(const std::string& path, const std::string& newName);
	void deleteFolder(const std::string& path);
	void deleteFile(const std::string& path);
	void copyFolder(const std::string& path, const std::string& newPath);
	void copyFile(const std::string& path, const std::string& newPath);
	void moveFile(const std::string& path, const std::string& newPath);
	int calculateSize(const std::string& path);
	void searchByMask(const std::string& path, const std::string& mask);

	~FileManager();

};

#endif 
