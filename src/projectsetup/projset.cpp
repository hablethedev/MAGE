#include "projset.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void addDir(const std::string& name, const std::string& path, const std::string& usever, const std::string& pmver) {
    fs::path projectPath = fs::path(path) / name;

    try {
        if (!fs::exists(projectPath)) {
            fs::create_directories(projectPath);
            std::cout << "[DBG] folder created: " << projectPath << std::endl;
        } else {
            std::cout << "[DBG] folder already exists: " << projectPath << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[ERR] error creating folder: " << e.what() << std::endl;
    }
}

void addProjectFile(const std::string& name, const std::string& path, const std::string& usever, const std::string& pmver) {
    fs::path projectFilePath = fs::path(path) / name / "project.mage";

    try {
        std::ofstream file(projectFilePath);
        if (!file) {
            throw std::ios_base::failure("failed to create project.mage");
        }

        file << "[\n";
        file << "  {\"version\":\"" << usever << "\"},\n";
        file << "  {\"pm-ver\":\"" << pmver << "\"},\n";
        file << "  {\"project-name\":\"" << name << "\"}\n";
        file << "]\n";

        file.close();
        std::cout << "[DBG] file created: " << projectFilePath << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERR] error creating project file: " << e.what() << std::endl;
    }
}

void makeProject(const std::string& name, const std::string& path, const std::string& usever, const std::string& pmver) {
    std::cout << "[DBG] project creating" << std::endl;
    std::cout << "[DBG] name:  " << name << std::endl;
    std::cout << "[DBG] path: " << path << std::endl;
    std::cout << "[DBG] user set ver: " << usever << std::endl;
    std::cout << "[DBG] package manager ver:  " << pmver << std::endl;

    addDir(name, path, usever, pmver);

    fs::path scriptPath = fs::path(path) / name / "script";
    fs::path resourcePath = fs::path(path) / name / "resource";
    fs::path scenePath = fs::path(path) / name / "scene";
    fs::path pluginPath = fs::path(path) / name / "plugin";

    try {
        fs::create_directories(scriptPath);
        fs::create_directories(resourcePath);
        fs::create_directories(scenePath);
        fs::create_directories(pluginPath);
        std::cout << "[DBG] directories created for script, resource, scene, and plugin." << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "[ERR] error creating directories: " << e.what() << std::endl;
    }

    addProjectFile(name, path, usever, pmver);
}

