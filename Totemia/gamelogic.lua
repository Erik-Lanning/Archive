--gamelogic.lua by Erik Lanning
--Description: self file holds all the game logic and level creation tools
physics.start()
local physicsData = (require "meshes").physicsData(1.0)
local movieclip = require( "movieclip" )
local director = require("director")
audio.setVolume( 1 )


smallb = 1
longb = 2
medb = 3
--GLOBAL GAMESETTINGS VARIABLES [
	playerlevel = 0; --Holds the level the player is on
	totemstate = 1; -- 1=not broken, 0=broken
	blocksneeded = 0;
	currentamountblocks = 0;
	totemtimer = 5000; --5 seconds for level to be counted as "done"
	--lazy man temp fix
local totem,
	levelHUDDisplay, 
	blocksHUDDisplay, 
	homeButton, 
	resetButton, 
	background, 
	grass, 
	text_blocksleft, 
	text_Level, 
	createstage
	blockArray = {};
	--sounds
local totemgroundSound = audio.loadSound("popsound1.mp3")
local standardblockSound1 = audio.loadSound("popsound1.mp3")
local standardblockSound2 = audio.loadSound("popsound2.mp3")
local bgmusic1 = audio.loadStream("you_make_me_dizzy.mp3")
local bgmusic2 = audio.loadStream("valkimer.mp3")	
local bgmusic3 = audio.loadStream("too_ambitious.mp3")	
local bgmusic4 = audio.loadStream("mellow_chill.mp3")	
local bgmusic5 = audio.loadStream("back_and_forth.mp3")
local bgmusic6 = audio.loadStream("ro-ads.mp3")
--								]

function clearscreen()
	local stage = display.getCurrentStage()
	while stage.numChildren > 0 do
        local obj = stage[1]
        obj:removeSelf()
        obj = nil
	end
end
----------------------------------Game State logic----------------------------
	function CheckState()
		currentamountblocks = currentamountblocks - 1
		blocksHUDDisplay:setText( currentamountblocks )
		if (currentamountblocks <= blocksneeded) then
			--pause for totem duration
			local listener = {}
			function listener:timer( event )
				if(totemstate ~= 0) then
					--player has won.
				end
			end
 
			timer.performWithDelay(totemtimer, listener )
		end
	end
	function blocktouched(event)
		blockArray[event.target.param1]:removeSelf()
		local valinteger = math.random(1, 2)
		if(valinteger == 1) then 
			audio.play( standardblockSound1 )
		end
		if(valinteger == 2) then
			audio.play( standardblockSound2 )		
		end
		CheckState()
	end
---------------------------------Totem hit the ground function----------------
function totemhitground(self, event)
	if ( event.phase == "began" or event.phase == "ended") then
		if(self.myName == "totem" and event.other.myName == "ground") then
			--restart level
			totemstate = 0;
			self:stopAtFrame(2)
			local listener = {}
			function listener:timer( event )
				--createstage(playerlevel)
			end
			timer.performWithDelay(1500, listener )
		end
	end
end
------------------------------------------------------------------------------
		local onRestartTouch = function( event )
			print("restart button loading kinda")
				--audio.play( tapSound )
				local theModule = "levelloader"
				director:changeScene( theModule )
		end
		local onHomeTouch = function( event )
			print("Home button loading kinda")
				--audio.play( tapSound )
				local theModule = "menu"
				director:changeScene( theModule )
		end
	setbackstage = function(currentlevel)
		
		--Load Background
		local background = display.newImage("img/Scenario/Background.png", true) -- flag overrides large image downscaling
		background.x = display.contentWidth / 2
		background.y = display.contentHeight / 2
		localGroup:insert(background)
		--Level ground is based on current level, every 5 levels it changes?{
		local grass = display.newImage( "img/Scenario/Ground/levelground_00.png", true )
			grass.myName = "ground"
			grass.x = 240
			grass.y = 160
			physics.addBody( grass, "static", physicsData:get("levelground_00") )
			localGroup:insert(grass)
		--}
		--labels for UI
		local text_blocksleft = display.newText("Blocks Left:", 0, 0, native.systemFontBold, 18);
		text_blocksleft.x = 50; text_blocksleft.y = 17
		localGroup:insert(text_blocksleft)
		local text_Level = display.newText("Level", 0, 0, native.systemFontBold, 18);
		text_Level.x = 240; text_Level.y = 17
		localGroup:insert(text_Level)		
		--CREATE RESTART BUTTON
		resetButton = ui.newButton{
			default = "img/Buttons/tempbutton.png",
			over = "img/Buttons/tempbutton.png",
			x = 436,
			y = 301,
			--onPress = newRound,
			text = "Reset",
			emboss = true
		}
			resetButton:addEventListener("tap", onRestartTouch );
			localGroup:insert(resetButton)
		homeButton = ui.newButton{
			default = "img/Buttons/tempbutton.png",
			over = "img/Buttons/tempbutton.png",
			x = 436,
			y = 21,
			--onPress = newRound,
			text = "Home",
			emboss = true
		}
			homeButton:addEventListener("tap", onHomeTouch);
			localGroup:insert(homeButton)
		--DISPLAY BLOCKS NEEDED
		blocksHUDDisplay = ui.newLabel{
			bounds = { 103, 5, 0, 0 }, -- align label with right side of current screen
			text = "0",
			font = "Trebuchet-BoldItalic",
			textColor = { 255, 225, 102, 255 },
			size = 18,
			align = "left"
		}
		blocksHUDDisplay:setText( blocksneeded )
		localGroup:insert(blocksHUDDisplay)
		--Current Level
		levelHUDDisplay = ui.newLabel{
			bounds = { 267, 5, 0, 0 }, -- align label with right side of current screen
			text = "0",
			font = "Trebuchet-BoldItalic",
			textColor = { 255, 225, 102, 255 },
			size = 18,
			align = "left"
		}
		levelHUDDisplay:setText( playerlevel )
		localGroup:insert(levelHUDDisplay)
	end
------------------------------------------Blocks + Totem-----------------------------
	function createtotem(x, y, size)
		--create totem
		--if totem touches ground, you lose
		if(size == 1) then -- 1x1 totem
			local totem = movieclip.newAnim{ "img/Statue/statue_s_1.png", "img/Statue/statue_s_2.png" }
			totem.myName = "totem"
			if(totem ~= nil) then
				totem.x = x; totem.y = y
				totem.collision = totemhitground
				totem:addEventListener( "collision", totem)
				physics.addBody( totem, physicsData:get("statue_s_1") )
				localGroup:insert(totem)
			end
		end
		if(size == 2) then -- 2x2 totem
			local totem = display.newImage("img/Statue/statue_b_1.png")
			totem.myName = "totem"
			if(totem ~= nil) then
				totem.x = x; totem.y = y
				totem.collision = totemhitground
				totem:addEventListener( "collision", totem)
				physics.addBody( totem, physicsData:get("statue_b_1") )
				localGroup:insert(totem)
			end
		end
	end
	--standard block
	function createblock(x, y, z, size, blockid)
		if (size == 1) then -- 1x1 block
			blockArray[blockid] = display.newImage( "img/Blocks/1x1/1x1_standard.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = orientation;
				blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x1_standard") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 2) then -- 1x4 block
			blockArray[blockid] = display.newImage( "img/Blocks/1x4/1x4_standard.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = orientation;
				blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x4_standard") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 3) then -- 2x2 block
			blockArray[blockid] = display.newImage( "img/Blocks/2x2/2x2_standard.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = orientation;
				blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("2x2_standard") )
				localGroup:insert(blockArray[blockid])
			end		
		end
	end