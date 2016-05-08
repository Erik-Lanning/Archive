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
			director:changeScene(e.target.scene, "moveFromRight");
		end
	end
	local totemia_title = display.newText("Totem Story", 0, 0, "Yikes!", 36);
	totemia_title.x = 385; totemia_title.y = 40	
	local block1 = display.newImage("2x2_standard.png", 400, 110, true ) -- flag overrides large image downscaling
	local block2 = display.newImage("2x2_draggable.png", 328, 175, true ) -- flag overrides large image downscaling
	local block3 = display.newImage("2x2_bomb.png", 400, 245, true ) -- flag overrides large image downscaling
	-- menu buttons	
	local btn_play = ui.newButton{
			default = "buttonRed.png",
			over = "buttonRedOver.png",
			x = 150,
			y = 70,
			text = "Play",
			font = "comic andy",
			size = 40,
			emboss = true,
			id = "btn_play"
		}
		btn_play.scene = "selectlevel";
		btn_play:addEventListener("touch", changeScene);
	
	local btn_options = ui.newButton{
			default = "buttonRed.png",
			over = "buttonRedOver.png",
			x = 150,
			y = 140,			
			text = "Settings",
			font = "comic andy",
			size = 40,
			emboss = true,
			id = "btn_options"
		}
		btn_options.scene = "options";
		btn_options:addEventListener("touch", changeScene);
		
	local btn_tutorial = ui.newButton{
			default = "buttonRed.png",
			over = "buttonRedOver.png",
			x = 150,
			y = 210,			
			text = "Tutorial",
			font = "comic andy",
			size = 40,
			emboss = true,
			id = "btn_tutorial"
		}
		btn_tutorial.scene = "tutorial";
		btn_tutorial:addEventListener("touch", changeScene);
	local btn_credits = ui.newButton{
			default = "buttonRed.png",
			over = "buttonRedOver.png",
			x = 150,
			y = 280,
			text = "Credits",
			font = "comic andy",
			size = 40,
			emboss = true,
			id = "btn_credits"
		}
		btn_credits.scene = "ccrediz";
		btn_credits:addEventListener("touch", changeScene);	
	
		
		
	--- insert everything into the localGroup	
	localGroup:insert(btn_play)
	localGroup:insert(btn_options)
	localGroup:insert(btn_tutorial)	
	localGroup:insert(btn_credits)
	localGroup:insert(block1)
	localGroup:insert(block2)
	localGroup:insert(block3)
	localGroup:insert(totemia_title)
	
	-- clean everything up
	clean = function ()
	
	end
	
	-- do not remove lest the sky shalt fall upon thine head
	return localGroup
	
end