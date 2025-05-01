# SM-ShutUpChallengeMode

Prevents that stupid `Remember to save your challenge from time to time` message that never shuts up while building in challenge mode.

## This DLL mod should work with every game version

In theory, as aslong as the `name` parameter is same across versions and the contents of `ChallengeGame.lua` doesn't get modified where `sm.gui.chatMessage( "#{CHALLENGE_BUILDER_SAVE_REMINDER}" )` isn't there or is bit diffirent, it should work fine.

## Cant you just modfiy the file `ChallengeGame.lua` itself directly?

Well yeah, but its checksummed so modifing it would mean anyone trying to join wouldn't be able to join you. This DLL mod doesn't do that because it only modifies the code of the game. Meaning the checksum works fine and anyone can join you like normal.