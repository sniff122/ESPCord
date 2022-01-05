#include <Arduino.h>
#include "GatewayIntents.h"

// Intent options can be found in GatewayIntents.h


// Note that for large servers, the ESP may crash with the GUILD_INTENT intent due to the large amount of members

const uint16_t gateway_intents = GUILD_MEMBERS_INTENT |
 GUILD_BANS_INTENT | GUILD_EMOJIS_INTENT |
 GUILD_INTEGRATIONS_INTENT | GUILD_WEBHOOKS_INTENT |
 GUILD_INVITES_INTENT | GUILD_VOICE_STATES_INTENT |
 GUILD_MESSAGES_INTENT | GUILD_MESSAGE_REACTIONS_INTENT |
 GUILD_MESSAGE_TYPING_INTENT | DIRECT_MESSAGES_INTENT |
 DIRECT_MESSAGE_REACTIONS_INTENT | DIRECT_MESSAGE_TYPING_INTENT;
