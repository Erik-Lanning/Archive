module(..., package.seeall)
function new()	
	
	-- we store everything inside this group at the end
	local localGroup = display.newGroup()

	-- change scene function
	function changeScene(e)
		if(settings.soundeffects) then
			--play button click sound effect
			local buttonsound =  audio.loadSound("buttonclick.mp3")
			audio.play( buttonsound )
		end
		if(e.phase == "ended") then
			director:changeScene(e.target.scene, "moveFromLeft");
		end
	end
	--Options backgtound
--	local background = display.newImage("img/Menu/background.jpg", true) -- flag overrides large image downscaling
--	background.x = display.contentWidth / 2
--	background.y = display.contentHeight / 2	

	-- menu buttons
	local music = display.newText("Music:", 0, 0, "Comic Book", 20);	
	music.x = 137; music.y = 137		
	local soundeffects = display.newText("Sound Effects:", 0, 0, "Comic Book", 20);
	soundeffects.x = 175; soundeffects.y = 32
------------- Music Button module------------------------
	local btn_music = ui.newButton{
		default = "buttonRed.png",
		over = "buttonRedOver.png",
		font = "comic andy",
		size = 40,
		x = 240,
		y = 180,
		emboss = true
	}
	if (settings.music == 1) then
		btn_music:setText("On")
	else
		btn_music:setText("Off")
	end
	function togglemusic()
		if(settings.music == 1) then
			settings.music = 0
			btn_music:setText("Off")
		elseif(settings.music == 0) then
			settings.music = 1
			btn_music:setText("On")
		end
		loadsave.saveTable(settings, "settings.json")
	end
	btn_music:addEventListener("tap", togglemusic)
----------------------------------------------------------
-----------------Sound Effects Button Module--------------		
	local btn_soundeffects = ui.newButton{
		default = "buttonRed.png",
		over = "buttonRedOver.png",
		font = "comic andy",
		size = 40,
		x = 240,
		y = 75,
		emboss = true,
		id = "btn_soundeffects"
	}
	if (settings.soundeffects == 1) then
		btn_soundeffects:setText("On")
	else
		btn_soundeffects:setText("Off")
	end
	function togglesoundeffects()
		if(settings.soundeffects == 1) then
			settings.soundeffects = 0
			btn_soundeffects:setText("Off")
		elseif(settings.soundeffects == 0) then
			settings.soundeffects = 1
			btn_soundeffects:setText("On")
		end
		loadsave.saveTable(settings, "settings.json")
	end
	btn_soundeffects:addEventListener("tap", togglesoundeffects)
-----------------------------------------------------------	
	local btn_back = ui.newButton{
			default = "buttonRed.png",
			over = "buttonRedOver.png",
			x = 240,
			y = 285,
			text = "Back",
			font = "comic andy",
			size = 40,
			emboss = true,
			id = "btn_back"
		}
		btn_back.scene = "menu";
		btn_back:addEventListener("touch", changeScene);	
		
		
	--- insert everything into the localGroup	
	localGroup:insert(btn_music)
	localGroup:insert(btn_soundeffects)
	localGroup:insert(btn_back)
	localGroup:insert(soundeffects)
	localGroup:insert(music)
	--localGroup:insert(background)	
		
	-- clean everything up
	clean = function ()
	
	end
	
	
	-- do not remove lest the sky shalt fall upon thine head
	return localGroup
	
end