#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <fmt/core.h>
#include <fstream>
#ifdef _WIN32
#include <windows.h>  // For Windows-specific functions (optional)
#endif

std::string ENV_NAME = "env";
const std::string SETTING_FILENAME = ".configWarden.ini";

bool equals(const std::string &a, const std::string &b){
    bool result = false;
    // std::cout << "comparing \"" << a << "\" with \"" << b << "\"\n";
    int cmp = a.compare(b);
    if (cmp == 0) result = true;
    return result;
}


void help(){
    std::cout << "invalid parameter count\n";
}

void createSettingsFile(){
    //check if the setting file already exists

    std::ofstream settingFile(SETTING_FILENAME);

    if(!settingFile){
        std::cerr << "Error opening file for writing." << std::endl;
        exit(-1);
    }

    settingFile << "ENV_NAME: " << ENV_NAME << std::endl;
    std::filesystem::create_directory(ENV_NAME);
}

void installRequirements(){
      // Check if requirements.txt exists
    std::ifstream requirementsFile("requirements.txt");
    if (requirementsFile) {
        // Close the file after checking
        requirementsFile.close();

        // Install packages from requirements.txt
        std::string install_command;
        
        // For Linux/Mac
        install_command = ENV_NAME + "/bin/pip install -r requirements.txt";
        
        // For Windows, use the following line instead
        // install_command = ENV_NAME + "\\Scripts\\pip install -r requirements.txt";
        
        int result = system(install_command.c_str());
        if (result != 0) {
            std::cerr << "Error installing packages from requirements.txt" << std::endl;
            exit(-1);
        }
    } else {
        std::cout << "requirements.txt not found. Skipping package installation." << std::endl;
    }
    exit(0);
}


void setup(){

    createSettingsFile();
    
    std::string create_env = "python -m venv " + ENV_NAME;
    const char *command = create_env.c_str();
    int result = system(command);
    if (result != 0){
        std::cerr << "Error creating the venv" << std::endl;
        exit(-1);
    }

    installRequirements();
}



void readEnvName(){
    std::ifstream inFile(SETTING_FILENAME);
    if(!inFile){
        std::cerr << "Could not locate the environment configuration file. Create environment with `./warden setup`\n";
        exit(-1);
    }

    std::string line;
    while(std::getline(inFile, line)){
        std::size_t pos = line.find(": ");
        if(pos != std::string::npos){
            ENV_NAME = line.substr(pos + 2);
        }

        if(!std::filesystem::exists(ENV_NAME)){
            std::cerr << "The environment name in the config file is invalid. Recreate the environment using `./warden setup env_name command`\n";
            exit(-1);
        }
    }
}


void execute(const std::string& file_name) {
    // Check if the configuration file exists
    if (!std::filesystem::exists(SETTING_FILENAME)) {
        std::cerr << "Cannot locate the config file. Create the environment with `warden setup`" << std::endl;
        exit(-1);
    }

    // Determine the command based on the platform
    std::string command;
    
#ifdef _WIN32
    // Windows-specific virtual environment activation and execution
    std::string venvPath = ENV_NAME + "\\Scripts\\activate";  // Adjust path for Windows
    command = "cmd.exe /C \"" + venvPath + " && python " + file_name + "\"";
#else
    // Linux/Unix-specific virtual environment activation and execution
    std::string venvPath = ENV_NAME + "/bin/activate";  // Adjust path for Linux/Unix
    command = "bash -c \"source " + venvPath + " && python " + file_name + "\"";
#endif

    // Print command for debugging purposes
    // std::cout << command << std::endl;

    // Execute the command
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Command failed with exit code " << result << std::endl;
        exit(-1);
    }

    exit(0);
}


void updatePip(){
    if(! std::filesystem::exists(SETTING_FILENAME)){
        std::cerr << "Cannot locate the config file. Create the environment with `warden setup`" << std::endl;
        exit(-1);
    }

    std::string install_command;
        
    install_command = ENV_NAME + "/bin/pip install --upgrade pip";
    int result = system(install_command.c_str());
    if (result != 0) {
        std::cerr << "Error updating pip" << std::endl;
        exit(-1);
    }
    exit(0);
}


void installPackage(std::string packageName){
    if(! std::filesystem::exists(SETTING_FILENAME)){
        std::cerr << "Cannot locate the config file. Create the environment with `warden setup`" << std::endl;
        exit(-1);
    }

    std::string install_command;
        
    install_command = ENV_NAME + "/bin/pip install " + packageName;
    int result = system(install_command.c_str());
    if (result != 0) {
        std::cerr << "Error installing packages " << packageName << std::endl;
        exit(-1);
    }
    exit(0);
}


void run(int argc, char **argv){
    if (argc < 2){
        help();
        exit(1);
    }

    std::string command = std::string(argv[1]);
    //setup command
    if (equals(command, std::string("setup"))){
        if(argc > 2)
            ENV_NAME = argv[2];
        setup();
    }
    // run command
    else if (equals(command, std::string("run"))){
        if(argc > 2)
            execute(std::string(argv[2]));
        else {
            std::cerr << "Please provide a valid python script name to execute" << std::endl;
            exit(-1);
        }
    }
    // install command
    else if (equals(command, std::string("install"))){
        if(argc > 2)
            installPackage(std::string(argv[2]));
        else {
            std::cerr << "Please provide a valid package name to execute" << std::endl;
            exit(-1);
        }
    }
    //update command
    else if (equals(command, std::string("update"))){        
        updatePip();
    }
}


int main(int argc, char **argv){
    
    if(std::filesystem::exists(SETTING_FILENAME)){
        readEnvName();
    }

    run(argc, argv);
}