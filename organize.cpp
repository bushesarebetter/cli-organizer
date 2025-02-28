#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <cctype>

namespace fs = std::filesystem;
using RuleMap = std::unordered_map<std::string, std::vector<std::string>>;

bool moveFile(std::string& source, std::string& destination){
    std::error_code ec;
    fs::rename(source, destination, ec);
    return !ec;
}
std::string assign_key(const std::string name, const RuleMap rules) {
    for (const auto& [key, value] : rules) {
        if (std::find(value.begin(), value.end(), name) != value.end()) {
            return key;
        }
    }
    return "Others";
}
RuleMap loadRules(std::string& filename){
    RuleMap rules;
    std::ifstream file(filename);
    std::string line;

    while(std::getline(file, line)){
        std::istringstream ss(line);
        std::string category, ext;
        if (std::getline(ss, category, ':')) {
            std::vector<std::string> extensions;
            while (ss >> ext) {
                extensions.push_back(ext);
            }
            rules[category] = extensions;
        }

    }
    return rules;
}
int main(int argc, char* argv[]) {

    bool sort_folders = false;
    bool forced = false;
    for (int i = 0; i < argc; ++i){
        if (strcmp(argv[i], "--sf") == 0) {
            sort_folders = true;
        }
        if (strcmp(argv[i], "--force") == 0){
            forced = true;
        }
    }
    if(argc < 2 + sort_folders + forced){
        std::cout << "Usage: organize <foldername> --sf (optional) --force (optional)" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    if(!forced){
        std::string input;
        std::cout << "You want to sort this folder: " << path << " , correct? (Y/N)" << std::endl;
        std::cin >> input;
        if(!(input =="Y" || input=="y")){
            std::cout << "Understood, quitting" <<std::endl;
            return 1;
        }
    }
    std::cout << "Beginning sorting" <<std::endl;
    std::string look = "settings.txt";
    RuleMap rules = loadRules(look);

    for (const auto& entry : fs::directory_iterator(path)) {
        std::string fp = entry.path().lexically_relative(path).string();

        size_t pos = fp.rfind(".");
        
        if (pos != std::string::npos) {
            std::string ext = fp.substr(pos + 1);
            std::string old_filename = path + "/" + fp;
            std::string new_filename = path + "/" + assign_key(ext, rules) + "/" + fp;
            fs::create_directories(fs::path(new_filename).parent_path());
            if(!(std::rename(old_filename.c_str(), new_filename.c_str()) == 0)) {
                std::cout << "Unable to sort file: " << fp << std::endl;
            }
        } else if (!fs::is_directory(entry)) {
            std::string old_filename = path + "/" + fp;
            std::string new_filename = path + "/" + "Others" + "/" + fp;
            fs::create_directories(fs::path(new_filename).parent_path());
            if(!(std::rename(old_filename.c_str(), new_filename.c_str()) == 0)) {
                std::cout << "Unable to sort file: " << fp << std::endl;
            }
        } else if (sort_folders) {
            // at this point we assume the entry is a directory
            // we need to check if the directory exists in settings.txt, so we need to check all KEYS to see if they match
            bool isenforced = false;
            for(const auto& [key, value] : rules) {
                if(fp == key || fp == "Folders"){
                    isenforced = true;
                    break; // force next iter, don't sort
                }
            }

            // if for loop fails then continue sorting
            if( !isenforced){
                std::string old_filename = path + "/" + fp;
                std::string new_filename = path + "/" + "Folders" + "/" + fp;
                fs::create_directories(fs::path(new_filename).parent_path());
                if(!(std::rename(old_filename.c_str(), new_filename.c_str()) == 0)) {
                    std::cout<< "Unable to sort folder: " << fp << std::endl;
                }
            }
        }
    }

    std::cout << "Sorting finished!" <<std::endl;



// how do we check if the folder is already a folder defined 
    
}   
