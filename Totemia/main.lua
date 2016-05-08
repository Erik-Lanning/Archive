_w = display.contentWidth;
_h = display.contentHeight;
system.deactivate( "multitouch" )
display.setStatusBar( display.HiddenStatusBar )

---------------------------------------------------------------
-- Import director class
---------------------------------------------------------------
director = require("director")
ui = require("ui")
physics = require("physics")
json = require("json")
loadsave = require("loadsave")
--require("gamelogic") no need to require this right now, only slows the app


settings = loadsave.loadTable("settings.json")
if(settings == nil) then --create a new user profile
	settings = {}
	settings.music = 1	--1: on, 0: off
	settings.soundeffects = 1 --1: on, 0: off
	settings.loadlevel = 1 --holds which level the levelloader should load
	settings.currentlevel = 1 --holds the max level the player can play on
	loadsave.saveTable(settings, "settings.json")
end


if (settings.music == 1) then
	bgmusic = audio.loadStream("mellow_chill.mp3")
	bgmusicchannel = audio.play( bgmusic, { channel=1, loops=-1 }  )  -- play the background music on channel 1, loop infinitely ]
	audio.setVolume(0, {channel=1}) --Set to 0 for now REMOVE THISSSSSSSSSSS WHEN DONE TESTINGGGG
end
---------------------------------------------------------------
local mainGroup = display.newGroup()

local function main()
	mainGroup:insert(director.directorView)
	director:changeScene("menu")
	return true
end


main()
