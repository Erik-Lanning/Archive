--
--	levelloader.lua by Erik Lanning
--		Used for loading the game from the menus
--
module(..., package.seeall)
system.deactivate( "multitouch" )
physics.start()
physics.setGravity( 0, 5 )	--> 0, 9.8 = Earth-like gravity
local physicsData = (require "meshes").physicsData(1.0)
local movieclip = require( "movieclip" )
local director = require("director")
audio.setVolume( 1 )

function new()	
	-- we store everything inside this group at the end
	local localGroup = display.newGroup()
	-- change scene function
	function changeScene(e)
		if(settings.soundeffects==1) then
			--play button click sound effect
			local buttonsound =  audio.loadSound("buttonclick.mp3")
			local buttonsoundchannel = audio.play(buttonsound)
		end
		if(e.phase == "ended") then
			director:changeScene(e.target.scene, "moveFromLeft");
		end
	end
---------------------------------------------Game Logic---------------------------------------------
playerlevel = settings.loadlevel
smallb = 1
longb = 2
medb = 3
--GLOBAL GAMESETTINGS VARIABLES [
	--playerlevel = 0; --Holds the level the player is on
	totemstate = 0; -- 1=not broken, 0=broken
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
local magnetArray = {}
local clouds1, clouds2, clouds3, clouds4, clouds5, clouds6;
-- Timers
timerStash = {}
function cancelAllTimers()
    local k, v
    for k,v in pairs(timerStash) do
        timer.cancel( v )
        v = nil; k = nil
    end
    timerStash = nil
    timerStash = {}
end
--
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

----------------------------------Game State logic----------------------------
	function checkifwon()
		cancelAllTimers()
		if(totemstate ~= 0 and blocksneeded <= 0) then
		--player has won
			print("you won!")
		end
	end
	function CheckState()
		blocksneeded = blocksneeded - 1
		if (blocksneeded >= 0) then blocksHUDDisplay:setText( blocksneeded ) end
		if (blocksneeded <= 0) then
			cancelAllTimers()
			timerStash.newTimer = timer.performWithDelay(totemtimer, checkifwon)
		end
	end
------------------STANDARD BLOCK MODULE----------------------------------
	function blocktouched(event)
		blockArray[event.target.param1]:removeSelf()
		local valinteger = math.random(1, 2)
		if(valinteger == 1 and settings.soundeffects == 1) then 
			audio.play( standardblockSound1 )
		end
		if(valinteger == 2 and settings.soundeffects == 1) then
			audio.play( standardblockSound2 )		
		end
		CheckState()
	end
---------------------EXPLOSIVE BLOCK MODULE------------------------------------
	function explosiveblocktouched(event)
		--Explosion part
		blockArray[event.target.param1]:applyLinearImpulse( 50, 50, blockArray[event.target.param1].x, blockArray[event.target.param1].y )
		--Play explosive block sound
		if(settings.soundeffects==1) then
			audio.play( standardblockSound1 )
		end
		--Play explosive block animation [TODO]
		
		--Remove block
		blockArray[event.target.param1]:removeSelf()
		
		CheckState()
	end
---------------------------MAGNET MODULE--------------------------------------
function distance( a, b )
	if(a ~= nil and b ~= nil) then
		if(b.x ~= nil and a.x ~= nil) then
			nwidth = b.x-a.x
		else
			nwidth = 1
		end
		if(b.y ~= nil and a.y ~= nil) then
			nheight = b.y-a.y
		else
			nheight = 1
		end
		if(nwidth ~= nil and nheight ~= nil) then
			return math.sqrt( nwidth*nwidth + nheight*nheight )
		end
	end
end
local tmax = distance( {x=0,y=0}, {x=display.contentWidth,y=display.contentHeight} )
local strength = 20 --The smaller the number the more force the magnet has (20 seems to be good)
steve = 0
function doGameFunctions( event )
	-- MOVE CLOUDS SLOWLY
	local cloudMoveSpeed = 0.25
			
	clouds1.x = clouds1.x - cloudMoveSpeed
	clouds2.x = clouds2.x - cloudMoveSpeed
	clouds3.x = clouds3.x - cloudMoveSpeed
	clouds4.x = clouds4.x - cloudMoveSpeed
	clouds5.x = clouds5.x - cloudMoveSpeed
	clouds6.x = clouds6.x - cloudMoveSpeed			
	if clouds1.x <= -90 then
		clouds1.x = 540
		clouds1.y = -3 + math.random(0, 67)
	end
			
	if clouds2.x <= -90 then
		clouds2.x = 540
		clouds2.y = -3 + math.random(0, 67)
	end
			
	if clouds3.x <= -90 then
		clouds3.x = 540
		clouds3.y = -3 + math.random(0, 67)
	end
			
	if clouds4.x <= -90 then
		clouds4.x = 540
		clouds4.y = -3 + math.random(0, 67)
	end
	if clouds5.x <= -90 then
		clouds5.x = 540
		clouds5.y = -3 + math.random(0, 67)
	end
	if clouds6.x <= -90 then
		clouds6.x = 540
		clouds6.y = -3 + math.random(0, 67)
	end
			-- END CLOUD MOVEMENT
end
	function blockmagnettouched(event)
		magnetArray[event.target.param1]:removeSelf()
		steve = 1
		CheckState()
	end
-----------------------------DRAG MODULE----------------------------
function blockdrag( event )
	local t = event.target
	local phase = event.phase
	if "began" == phase then
		display.getCurrentStage():setFocus( t )
		t.isFocus = true
		-- Store initial position
		t.x0 = event.x - t.x
		t.y0 = event.y - t.y		
		-- Make body type temporarily "kinematic" (to avoid gravitional forces)
		event.target.bodyType = "kinematic"		
		event.target.isBullet = true -- force continuous collision detection, to stop really fast shots from passing through other balls
		-- Stop current motion, if any
		event.target:setLinearVelocity( 0, 0 )
		event.target.angularVelocity = 0
	elseif t.isFocus then
		if "moved" == phase then
			t.x = event.x - t.x0
			t.y = event.y - t.y0
		elseif "ended" == phase or "cancelled" == phase then
			display.getCurrentStage():setFocus( nil )
			t.isFocus = false
			
			-- Switch body type back to "dynamic", unless we've marked this sprite as a platform
			if ( not event.target.isPlatform ) then
				event.target.bodyType = "dynamic"
			end
		end
	end
	if "ended" == phase then
		local valinteger = math.random(1, 2)
		if(valinteger == 1 and settings.soundeffects == 1) then 
			audio.play( standardblockSound1 )
		end
		if(valinteger == 2 and settings.soundeffects == 1) then
			audio.play( standardblockSound2 )		
		end
		t:removeSelf()
		CheckState()
	end
	-- Stop further propagation of touch event!
	return true
end
---------------------------------Totem hit the ground function----------------
function totemhitgroundtimer()
	director:changeScene("restartmodule")
end
function totemhitground(self, event)
	if ( event.phase == "began" or event.phase == "ended") then
		if(self.myName == "totem" and event.other.myName == "ground") then
			cancelAllTimers()
			--restart level
			totemstate = 0;
			self:stopAtFrame(2)
			timerStash.newTimer2 = timer.performWithDelay(500, totemhitgroundtimer)
		end
	end
end
------------------------------------------------------------------------------
		local onRestartTouch = function( event )
			if event.phase == "release" then
				cancelAllTimers()
				--audio.play( tapSound )
				local theModule = "restartmodule"
				director:changeScene(theModule)
			end
		end
		local onHomeTouch = function( event )
			if event.phase == "release" then
				cancelAllTimers()
				--audio.play( tapSound )
				local theModule = "menu"
				director:changeScene( theModule )
			end
		end
	setbackstage = function(currentlevel)
		
		--Load Background
		local background = display.newImage("Background.png", true) -- flag overrides large image downscaling
		background.x = display.contentWidth / 2
		background.y = display.contentHeight / 2
		localGroup:insert(background)
		--Level ground is based on current level, every 5 levels it changes?{
		local grass = display.newImage( "levelground_00.png", true )
			grass.myName = "ground"
			grass.x = 240
			grass.y = 160
			physics.addBody( grass, "static", physicsData:get("levelground_00") )
			localGroup:insert(grass)
		--}
		--clouds
		clouds1 = display.newImage( "cloud_01.png", true )
		clouds1.x = 540; clouds1.y = math.random(-3, 64)
		clouds2 = display.newImage( "cloud_02.png", true )
		clouds2.x = 660; clouds2.y = math.random(-3, 64)
		clouds3 = display.newImage( "cloud_03.png", true )
		clouds3.x = 780; clouds3.y = math.random(-3, 64)
		clouds4 = display.newImage( "cloud_04.png", true )
		clouds4.x = 900; clouds4.y = math.random(-3, 64)
		clouds5 = display.newImage( "cloud_02.png", true )
		clouds5.x = 1020; clouds5.y = math.random(-3, 64)
		clouds6 = display.newImage( "cloud_03.png", true )
		clouds6.x = 1140; clouds6.y = math.random(-3, 64)
		clouds1.alpha = 0.5
		clouds2.alpha = 0.5
		clouds3.alpha = 0.5
		clouds4.alpha = 0.5
		clouds5.alpha = 0.5
		clouds6.alpha = 0.5
		localGroup:insert( clouds1 )
		localGroup:insert( clouds2 )
		localGroup:insert( clouds3 )
		localGroup:insert( clouds4 )	
		localGroup:insert( clouds5 )
		localGroup:insert( clouds6 )		
		--
		--labels for UI
		local text_blocksleft = display.newText("Blocks Left:", 0, 0, "Yikes!", 18);
		text_blocksleft.x = 50; text_blocksleft.y = 17
		text_blocksleft:setTextColor(255, 255, 255)
		localGroup:insert(text_blocksleft)
		local text_Level = display.newText("Level", 0, 0, "Yikes!", 18);
		text_Level.x = 240; text_Level.y = 17
		text_Level:setTextColor(255, 255, 255)
		localGroup:insert(text_Level)		
		--CREATE RESTART BUTTON
		resetButton = ui.newButton{
			default = "tempbutton.png",
			over = "tempbutton.png",
			onEvent = onRestartTouch,
			font = "comic andy",
			size = 30,
			x = 436,
			y = 301,
			--onPress = newRound,
			text = "Reset",
			emboss = true
		}
		--resetButton.scene = "levelloader";
		--resetButton:addEventListener("touch", changeScene);
			localGroup:insert(resetButton)
		homeButton = ui.newButton{
			default = "tempbutton.png",
			over = "tempbutton.png",
			font = "comic andy",
			size = 30,
			x = 436,
			y = 21,
			onEvent = onHomeTouch,
			text = "Home",
			emboss = true
		}
		--homeButton:addEventListener("tap", onHomeTouch)
		--homeButton.scene = "levelloader";
		--homeButton:addEventListener("touch", changeScene);
			localGroup:insert(homeButton)
		--DISPLAY BLOCKS NEEDED
		blocksHUDDisplay = ui.newLabel{
			bounds = { 103, 5, 0, 0 }, -- align label with right side of current screen
			text = "0",
			font = "Yikes!",
			textColor = { 255, 255, 255, 255 },
			size = 18,
			align = "left"
		}
		blocksHUDDisplay:setText(blocksneeded)
		localGroup:insert(blocksHUDDisplay)
		--Current Level
		levelHUDDisplay = ui.newLabel{
			bounds = { 267, 5, 0, 0 }, -- align label with right side of current screen
			text = "0",
			font = "Yikes!",
			textColor = { 255, 255, 255, 255 },
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
			local totem = movieclip.newAnim{ "statue_s_1.png", "statue_s_2.png" }
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
			blockArray[blockid] = display.newImage( "1x1_standard.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x1_standard") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 2) then -- 1x4 block
			blockArray[blockid] = display.newImage( "1x4_standard.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x4_standard") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 3) then -- 2x2 block
			blockArray[blockid] = display.newImage( "2x2_standard.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("2x2_standard") )
				localGroup:insert(blockArray[blockid])
			end		
		end
	end
	--Explosive block
	function createbombblock(x, y, z, size, blockid)
		if (size == 1) then -- 1x1 block
			blockArray[blockid] = display.newImage( "1x1_bomb.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "tap", explosiveblocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x1_bomb") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 2) then -- 1x4 block
			blockArray[blockid] = display.newImage( "1x4_bomb.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "tap", explosiveblocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x4_bomb") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 3) then -- 2x2 block
			blockArray[blockid] = display.newImage( "2x2_bomb.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "tap", explosiveblocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("2x2_bomb") )
				localGroup:insert(blockArray[blockid])
			end		
		end
	end
	--indestructable block (Maybe we can make them blink when touched?)
	function createunmoveableblock(x, y, z, size, blockid)
		if (size == 1) then -- 1x1 block
			blockArray[blockid] = display.newImage( "1x1_combo.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				--blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x1_combo") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 2) then -- 1x4 block
			blockArray[blockid] = display.newImage( "1x4_combo.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				--blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("1x4_combo") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 3) then -- 2x2 block
			blockArray[blockid] = display.newImage( "2x2_combo.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				--blockArray[blockid]:addEventListener( "tap", blocktouched )
				physics.addBody( blockArray[blockid], physicsData:get("2x2_combo") )
				localGroup:insert(blockArray[blockid])
			end		
		end
	end
	--Moveable Block
	function createmoveableblock(x, y, z, size, blockid)
		if (size == 1) then -- 1x1 block
			blockArray[blockid] = display.newImage( "1x1_draggable.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "touch", blockdrag )
				physics.addBody( blockArray[blockid], physicsData:get("1x1_standard") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 2) then -- 1x4 block
			blockArray[blockid] = display.newImage( "1x4_draggable.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "touch", blockdrag )
				physics.addBody( blockArray[blockid], physicsData:get("1x4_standard") )
				localGroup:insert(blockArray[blockid])
			end
		end
		if (size == 3) then -- 2x2 block
			blockArray[blockid] = display.newImage( "2x2_draggable.png" )
			blockArray[blockid].param1 = blockid
			if(blockArray[blockid] ~= nil) then
				blockArray[blockid].x = x; blockArray[blockid].y = y; blockArray[blockid].rotation = z;
				blockArray[blockid]:addEventListener( "touch", blockdrag )
				physics.addBody( blockArray[blockid], physicsData:get("2x2_standard") )
				localGroup:insert(blockArray[blockid])
			end		
		end
	end
	--Magnet Block
	function createmagnetblock(x, y, z, size, blockid)
		if (size == 1) then -- 1x1 block
			magnetArray[blockid] = display.newImage( "1x1_magnet.png" )
			magnetArray[blockid].param1 = blockid
			if(magnetArray[blockid] ~= nil) then
				magnetArray[blockid].x = x; magnetArray[blockid].y = y; magnetArray[blockid].rotation = z;
				magnetArray[blockid]:addEventListener( "tap", blockmagnettouched )
				physics.addBody( magnetArray[blockid], physicsData:get("1x1_magnet") )
			end
		end
		if (size == 2) then -- 1x4 block
			magnetArray[blockid] = display.newImage( "1x4_magnet.png" )
			magnetArray[blockid].param1 = blockid
			if(magnetArray[blockid] ~= nil) then
				magnetArray[blockid].x = x; magnetArray[blockid].y = y; magnetArray[blockid].rotation = z;
				magnetArray[blockid]:addEventListener( "tap", blockmagnettouched )
				physics.addBody( magnetArray[blockid], physicsData:get("1x4_magnet") )
			end
		end
		if (size == 3) then -- 2x2 block
			magnetArray[blockid] = display.newImage( "2x2_magnet.png" )
			magnetArray[blockid].param1 = blockid
			if(magnetArray[blockid] ~= nil) then
				magnetArray[blockid].x = x; magnetArray[blockid].y = y; magnetArray[blockid].rotation = z;
				magnetArray[blockid]:addEventListener( "tap", blockmagnettouched )
				physics.addBody( magnetArray[blockid], physicsData:get("2x2_magnet") )
			end		
		end
	end
--------------------------------------------End of Logic--------------------------------------------
-------------------------------------------------------------------------------------------
-------------------------------------------Levels------------------------------------------
-------------------------------------------------------------------------------------------
function createstage()
	--Pause menu background music
	audio.pause(bgmusicchannel)
	--
	totemstate = 1; -- this is to prevent reset exploit
	cancelAllTimers()
	--
	if (playerlevel == 1 ) then
		--load stage settings
		if(settings.music==1) then 
			backgroundMusicChannel = audio.play( bgmusic1, { channel=10, loops=-1}  )
			audio.setVolume( 0.25, { channel=10 } )
		end
		playerlevel = 1
		currentamountblocks = 3
		blocksneeded = 2
		setbackstage()
		--Blocks for Level1
		createmoveableblock(228, 253, 0, 2, 1)
		createunmoveableblock(228, 166, 0, 1, 2)
		createbombblock(230, 210, 0, 3, 3)
		createtotem(229, 133, 1)
	end
	if(playerlevel == 2) then
		--load stage settings
		if(settings.music==1) then 
			backgroundMusicChannel = audio.play( bgmusic1, { channel=10, loops=-1}  )
			audio.setVolume( 0.25, { channel=10 } )
		end
		playerlevel = 2
		currentamountblocks = 3
		blocksneeded = 2
		setbackstage()
		--blocks for level2
		createunmoveableblock(352, 258, -0.04, longb, 1)
		createblock(350, 229, -0.04, longb, 2)
		createmoveableblock(383, 198, 0, smallb, 3)
		createtotem(383, 163, 1)
	end
	if(playerlevel == 3) then
		if(settings.music==1) then 
			backgroundMusicChannel = audio.play( bgmusic1, { channel=10, loops=-1}  )
			audio.setVolume( 0.25, { channel=10 } )
		end
		playerlevel = 3
		currentamountblocks = 8
		blocksneeded = 6
		setbackstage()
		--blocks for level2
		createblock(292, 113, 0, smallb, 1)
		createblock(247, 171, 0, smallb, 2)
		createblock(289, 173, 0, smallb, 3)
		createblock(325, 176, 0, smallb, 4)
		createblock(287, 204, 4.24, longb, 5)
		createblock(292, 144, 4.24, longb, 6)
		createunmoveableblock(217, 239, 0, medb, 7)
		createunmoveableblock(353, 248, 0, medb, 8)
		createtotem(293, 78, 1)
	end
end
-------------------------------------------------------------------------------------------
Runtime:addEventListener( "enterFrame", doGameFunctions )
createstage()
-------------------------------------------------------------------------------------------
	-- clean everything up
	clean = function ()
		Runtime:removeEventListener("enterFrame", doGameFunctions)
	end
	
	
	-- do not remove lest the sky shalt fall upon thine head
	return localGroup

end