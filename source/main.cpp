#include <iostream>
#include "include/discord_register.h"
#include "include/discord_rpc.h"
#include <thread>
#include <chrono>
#include <Windows.h>
#include "json.hpp"
#include <filesystem>
#include <fstream>
#include <shellapi.h>

constexpr auto config_file = "config.json";


#include "main.hpp"


int main() {
    
    bool running = true;    //runnin?
       
    if (!std::filesystem::exists(config_file)) {        //If config file doesnt exist ask for application id and open developer portal
            std::ofstream configfile(config_file); 


            std::cout << "Put in APP ID: \n";
            std::string app_id;
            std::cin >> app_id;

            nlohmann::json config;
            config["app_id"] = app_id;
            config["text1"] = "RPC by Narweex";
            config["text2"] = "RPC by Narweex";
            configfile << config;
            
            ShellExecute(0, 0, "https://discord.com/developers", 0, 0, SW_SHOW);
            
    } 
    
    //open config and fetch info 
    std::ifstream config_load("config.json");
    nlohmann::json load;
    config_load >> load;


    //if there is no info ask to fill config
    if (load.empty())
        std::cout << "Please fill in app ID in config.json";


    //Load information to variables
    std::string application_id = load["app_id"];
    std::string status_text1 = load["text1"];
    std::string status_text2 = load["text2"];


    DiscordRPC discord(application_id.c_str()); //initialize discord class with application id
    
        
    std::cout << " Press ESC to EXIT \n Press F1 to start running on background. ";
    //main loop
        while (running) {

            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)    /*If ESC is pressed exit*/
                running = false;

            if (GetAsyncKeyState(VK_F1) & 0x8000) {
                for (int i = 10; i > 0; i--) {
                    std::cout << "\r Console will detach in " << i << " seconds... you can close this program by restarting your PC or in task manager";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                FreeConsole();
            }
               

            discord.UpdatePresence(status_text1.c_str(), status_text2.c_str());//Update presence
           
            std::this_thread::sleep_for(std::chrono::milliseconds(100));     //wait for some optimization
        }
    
	return 0;
}

