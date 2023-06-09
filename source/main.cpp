#include <iostream>
#include "include/discord_register.h"
#include "include/discord_rpc.h"
#include <thread>
#include <chrono>
#include <Windows.h>
#include "json.hpp"
#include <filesystem>
#include <fstream>

constexpr auto config_file = "config.json";

class DiscordRPC {

public:
    DiscordRPC(const char* bot_id) {
        DiscordEventHandlers handlers;  //initialize handlers
        memset(&handlers, 0, sizeof(handlers));

        Discord_Initialize(bot_id, &handlers, true, nullptr);   //initialize with bot id
        std::cout << "Initialized\n";
    }

    ~DiscordRPC() {
        Discord_Shutdown();
        std::cout << "Uninitialized\n";
    }

private:
 
public:
    DiscordRichPresence discordPresence{}; //class to update the info
  
    void UpdatePresence(std::string discord_status) {
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = discord_status.c_str();
        discordPresence.details = "Start modding today";
        discordPresence.startTimestamp = 0;
        discordPresence.largeImageKey = "a";
        discordPresence.largeImageText = "paramods.xyz";
        discordPresence.smallImageText = "paramods.xyz";
        discordPresence.partyId = "https://paramods.xyz=";
        discordPresence.joinSecret = "https://paramods.xyz";
        Discord_UpdatePresence(&discordPresence);
    }
};


int main() {
    
    bool running = true;    //runnin?
       
    if (!std::filesystem::exists(config_file)) {
            std::ofstream configfile(config_file); //create config if not exists

            nlohmann::json config;
            config["app_id"] = "0";
            config["discord_status"] = "RPC by Narweex";
            configfile << config;

            std::cout << "Please fill in app ID in config.json";
            return 0;
    }
    
    std::ifstream config_load("config.json");
    nlohmann::json load;
    config_load >> load;

    if (load.empty())
        std::cout << "Please fill in app ID in config.json";

    std::string application_id = load["app_id"];
    std::string discord_status = load["discord_status"];

    DiscordRPC discord(application_id.c_str()); //initialize discord class
    
        
        while (running) {

            if (GetKeyState(VK_ESCAPE) & 0x8000)    /*If ESC is pressed exit*/
                running = false;

            discord.UpdatePresence(discord_status);/*Update presence*/
            std::this_thread::sleep_for(std::chrono::milliseconds(100));     //wait for some optimization
        }
    
	return 0;
}

