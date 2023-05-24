#include <iostream>
#include "include/discord_register.h"
#include "include/discord_rpc.h"
#include <thread>
#include <chrono>
#include <Windows.h>

constexpr auto BOT_ID = "1016036808745832478";

class DiscordRPC {

public:
    DiscordRPC(const char* bot_id) {
        DiscordEventHandlers handlers;  //initialize handlers
        memset(&handlers, 0, sizeof(handlers));

        Discord_Initialize(BOT_ID, &handlers, true, nullptr);   //initialize with bot id
        std::cout << "Initialized\n";
    }

    ~DiscordRPC() {
        Discord_Shutdown();
        std::cout << "Uninitialized\n";
    }

public:
    DiscordRichPresence discordPresence{}; //class to update the info
  
    void UpdatePresence() {
        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = "GTA, RDR & Phasmophobia Mods";
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
        DiscordRPC discord(BOT_ID); //initialize discord class
        
        while (running) {

            if (GetKeyState(VK_ESCAPE) & 0x8000)    /*If ESC is pressed exit*/
                running = false;

            discord.UpdatePresence();/*Update presence*/
            std::this_thread::sleep_for(std::chrono::milliseconds(50));     //wait for some optimization
        }
    
	return 0;
}

