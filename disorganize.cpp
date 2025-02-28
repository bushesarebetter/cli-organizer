// whole purpose is just to look at each file/folder and extract it (E.G. C:/Users/bush/Downloads -> looks at all sorted folders and then extracts them outwards)
#include <filesystem>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

namespace fs = std::filesystem;

bool moveFile(std::string& source, std::string& destination){
    std::error_code ec;
    fs::rename(source, destination, ec);
    return !ec;
}

int main(int argc, char* argv[]) {
    // all args -
    // --omit (leave the given terms from disorganizing)
    // --force (forces disorganizing without confirmation)
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <directory> [--flags]\n";
        return 1;
    }
    std::string directory = argv[1];
    bool force = false;
    std::vector<std::string> omit;
    // take --force and put into bool
    // take --omit and put into vector
    for(int i = 2; i < argc; ++i){
        std::string arg = argv[i];
        if (arg.rfind("--", 0) ==0){
            std::string flagname = arg.substr(2);
            if(flagname == "omit" || flagname == "ignore"){
                int j = 1;
                while(i+j < argc && argv[i+j][0] != '-'){
                    omit.push_back(argv[i+j]);
                    j++;
                }
            } else if(flagname == "force"){
                force = true;
            }

        }
    }

    if(!force){
        std::cout << "Just to confirm, you want to disorganize this folder, correct? (Y/N)\n";
        std::cout << directory << "\n";
        std::cout << "And you want me to ignore these files: ";
        for(int i = 0; i < omit.size(); ++i){
            std::cout << ((i == 0) ? "" : ", ");
            std::cout << omit.at(i);
        }
        std::cout << "\n";
        std::string input;
        std::cin >> input;
        if(!(input =="Y" || input=="y")){
            std::cout << "Understood, quitting." << std::endl;
        }
    }   
    for(const auto& entry : fs::directory_iterator(directory)){
        if(std::find(omit.begin(), omit.end(), entry.path().lexically_relative(directory).string()) != omit.end()){
            continue;
        }
        if(entry.is_directory()){
            for(const auto& nested_entry : fs::directory_iterator(entry)){
                std::string old_path = nested_entry.path().string();
                std::string new_path = directory + "/" + nested_entry.path().lexically_relative(entry).string();
                moveFile(old_path, new_path);
            }
            std::cout << entry.path().string().c_str() << std::endl;
            fs::remove(entry);
        }
    }
}
