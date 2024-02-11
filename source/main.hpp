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

    void UpdatePresence(const char* text1, const char* text2) {

        memset(&discordPresence, 0, sizeof(discordPresence));
        discordPresence.state = text1;
        discordPresence.details = text2;
        /* discordPresence.state = "✅PayPal Payment Supported";
        discordPresence.details = "✅Official Reseller";*/
        discordPresence.startTimestamp = 1507665886;
        //discordPresence.endTimestamp = 1507665886; DISABLED BECAUSE OF TIME
        discordPresence.largeImageKey = "thumbnail";
        discordPresence.largeImageText = "paramods.xyz";
        discordPresence.smallImageText = "Paramods.xyz";
        discordPresence.partyId = "paramods.xyz";
        Discord_UpdatePresence(&discordPresence);
    }
};