#ifndef EVENTS_H
#define EVENTS_H

// From https://discord.com/developers/docs/topics/gateway#commands-and-events





// GATEWAY
static String DISCORD_EVENT_HELLO = "HELLO";
//   - 	defines the heartbeat interval

static String DISCORD_EVENT_READY = "READY";
//   - 	contains the initial state information

static String DISCORD_EVENT_RESUMED = "RESUMED";
//   - 	response to Resume

static String DISCORD_EVENT_RECONNECTED = "RECONNECTED";
//   - 	server is going away, client should reconnect to gateway and resume

static String DISCORD_EVENT_INVALID_SESSION = "INVALID_SESSION";
//   - failure response to Identify or Resume or invalid active session



// CHANNELS

static String DISCORD_EVENT_CHANNEL_CREATE = "CHANNEL_CREATE";
//   - new guild channel created

static String DISCORD_EVENT_CHANNEL_UPDATE = "CHANNEL_UPDATE";
//   - channel was updated

static String DISCORD_EVENT_CHANNEL_DELETE = "CHANNEL_DELETE";
//   - 	channel was deleted

static String DISCORD_EVENT_CHANNEL_PINS_UPDATE = "CHANNEL_PINS_UPDATE";
//   - message was pinned or unpinned



// THREADS

static String DISCORD_EVENT_THREAD_CREATE = "THREAD_CREATE";
//   - thread created, also sent when being added to a private thread

static String DISCORD_EVENT_THREAD_UPDATE = "THREAD_UPDATE";
//   - thread was updated

static String DISCORD_EVENT_THREAD_DELETE = "THREAD_DELETE";
//   - thread was deleted

static String DISCORD_EVENT_THREAD_LIST_SYNC = "THREAD_LIST_SYNC";
//   - sent when gaining access to a channel, contains all active threads in that channel

static String DISCORD_EVENT_THREAD_MEMBER_UPDATE = "THREAD_MEMBER_UPDATE";
//   - thread member for the current user was updated

static String DISCORD_EVENT_THREAD_MEMBERS_UPDATE = "THREAD_MEMBERS_UPDATE";
//   - some user(s) were added to or removed from a thread



// GUILDS

static String DISCORD_EVENT_GUILD_CREATE = "GUILD_CREATE";
//   - lazy-load for unavailable guild, guild became available, or user joined a new guild

static String DISCORD_EVENT_GUILD_UPDATE = "GUILD_UPDATE";
//   - guild was updated

static String DISCORD_EVENT_GUILD_DELETE = "GUILD_DELETE";
//   - guild became unavailable, or user left/was removed from a guild

static String DISCORD_EVENT_GUILD_BAN_ADD = "GUILD_BAN_ADD";
//   - user was banned from a guild

static String DISCORD_EVENT_GUILD_BAN_REMOVE = "GUILD_BAN_REMOVE";
//   - user was unbanned from a guild

static String DISCORD_EVENT_GUILD_EMOJIS_UPDATE = "GUILD_EMOJIS_UPDATE";
//   - guild emojis were updated

static String DISCORD_EVENT_GUILD_STICKERS_UPDATE = "GUILD_STICKERS_UPDATE";
//   - guild stickers were updated

static String DISCORD_EVENT_GUILD_INTERACTIONS_UPDATE = "GUILD_INTERACTIONS_UPDATE";
//   - guild integration was updated

static String DISCORD_EVENT_GUILD_MEMBER_ADD = "GUILD_MEMBER_ADD";
//   - new user joined a guild

static String DISCORD_EVENT_GUILD_MEMBER_REMOVE = "GUILD_MEMBER_REMOVE";
//   - user was removed from a guild

static String DISCORD_EVENT_GUILD_MEMBER_UPDATE = "GUILD_MEMBER_UPDATE";
//   - guild member was updated

static String DISCORD_EVENT_GUILD_MEMBERS_CHUNK = "GUILD_MEMBERS_CHUNK";
//   - response to Request Guild Members

static String DISCORD_EVENT_GUILD_ROLE_CREATE = "GUILD_ROLE_CREATE";
//   - guild role was created

static String DISCORD_EVENT_GUILD_ROLE_UPDATE = "GUILD_ROLE_UPDATE";
//   - guild role was updated

static String DISCORD_EVENT_GUILD_ROLE_DELETE = "GUILD_ROLE_DELETE";
//   - guild role was deleted



// SCHEDULED EVENTS

static String DISCORD_EVENT_GUILD_SCHEDULED_EVENT_CREATE = "GUILD_SCHEDULED_EVENT_CREATE";
//   - guild scheduled event was created

static String DISCORD_EVENT_GUILD_SCHEDULED_EVENT_UPDATE = "GUILD_ECHEDULED_EVENT_UPDATE";
//   - guild scheduled event was updated

static String DISCORD_EVENT_GUILD_SCHEDULED_EVENT_DELETE = "GUILD_SCHEDULED_EVENT_DELETE";
//   - guild scheduled event was deleted

static String DISCORD_EVENT_GUILD_SCHEDULED_EVENT_USER_ADD = "GUILD_SCHEDULED_EVENT_USER_ADD";
//   - user subscribed to a guild scheduled event

static String DISCORD_EVENT_GUILD_SCHEDULED_EVENT_USER_REMOVE = "GUILD_SCHEDULED_EVENT_USER_REMOVE";
//   - user unsubscribed from a guild scheduled event



// INTEGRATIONS

static String DISCORD_EVENT_INTEGRATION_CREATE = "INTEGRATION_CREATE";
//   - guild integration was created

static String DISCORD_EVENT_INTEGRATION_UPDATE = "INTEGRATION_UPDATE";
//   - guild integration was updated

static String DISCORD_EVENT_INTEGRATION_DELETE = "INTEGRATION_DELETE";
//   - guild integration was deleted

static String DISCORD_EVENT_INTERACION_CREATE = "INTERACTION_CREATE";
//   - user used an interaction, such as an Application Command



// INVITES
static String DISCORD_EVENT_INVITE_CREATE = "INVITE_CREATE";
//   - invite to a channel was created

static String DISCORD_EVENT_INVITE_DELETE = "INVITE_DELETE";
//   - invite to a channel was deleted


// MESSAGES

static String DISCORD_EVENT_TYPING_START = "TYPING_START";
//   - user started typing in a channel

static String DISCORD_EVENT_MESSAGE_CREATE = "MESSAGE_CREATE";
//   - message was created

static String DISCORD_EVENT_MESSAGE_UPDATE = "MESSAGE_UPDATE";
//   - message was edited

static String DISCORD_EVENT_MESSAGE_DELETE = "MESSAGE_DELETE";
//   - message was deleted

static String DISCORD_EVENT_MESSAGE_DELETE_BULK = "MESSAGE_DELETE_BULK";
//   - multiple messages were deleted at once

static String DISCORD_EVENT_MESSAGE_REACTION_ADD = "MESSAGE_REACTION_ADD";
//   - user reacted to a message

static String DISCORD_EVENT_MESSAGE_REACTION_REMOVE = "MMESSAGE_REACTION_REMOVE";
//   - user removed a reaction from a message

static String DISCORD_EVENT_MESSAGE_REACTION_REMOVE_ALL = "MESSAGE_REACTION_REMOVE_ALL";
//   - all reactions were explicitly removed from a message

static String DISCORD_EVENT_MESSAGE_REACTION_REMOVE_EMOJI = "MESSAGE_REACTION_REMOVE_EMOJI";
//   - all reactions for a given emoji were explicitly removed from a message



// PRESENCES

static String DISCORD_EVENT_PRESENCE_UPDATE = "PRESENCE_UPDATE";
//   - user was updated


// STAGES

static String DISCORD_EVENT_STAGE_INSTANCE_CREATE = "STAGE_INSTANCE_CREATE";
//   - stage instance was created

static String DISCORD_EVENT_STAGE_INSTANCE_DELETE = "STAGE_INSTANCE_DELETE";
//   - stage instance was deleted or closed

static String DISCORD_EVENT_STAGE_INSTANCE_UPDATE = "STAGE_INSTANCE_UPDATE";
//   - stage instance was updated




// USER

static String DISCORD_EVENT_USER_UPDATE = "USER_UPDATE";
//   - properties about the user changed



// VOICE

static String DISCORD_EVENT_VOICE_STATE_UPDATE = "VOICE_STATE_UPDATE";
//   - someone joined, left, or moved a voice channel

static String DISCORD_EVENT_VOICE_SERVER_UPDATE = "VOICE_SERVER_UPDATE";
//   - guild's voice server was updated

static String DISCORD_EVENT_WEBOOKS_UPDATE = "WEBHOOKS_UPDATE";
//   - guild channel webhook was created, update, or deleted

#endif