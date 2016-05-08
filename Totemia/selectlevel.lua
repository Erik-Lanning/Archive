module(..., package.seeall)
local buttons = {}
function new()	
	
	-- we store everything inside this group at the end
	local localGroup = display.newGroup()

	-- change scene function
	function changeScene(e)
		if(settings.soundeffects==1) then
			--play button click sound effect
			local buttonsound =  audio.loadSound("buttonclick.mp3")
			audio.play(buttonsound)
		end
		if(e.phase == "ended") then
			settings.loadlevel = e.target.levelval -- store level for loading
			director:changeScene(e.target.scene, "moveFromLeft");
		end
	end
	--SWITCH SCREEN TO HORIZONTAL
	--level select background
--	local background = display.newImage("background.jpg", true) -- flag overrides large image downscaling
--	background.x = display.contentWidth / 2
--	background.y = display.contentHeight / 2
	
	-- menu buttons	
	--local btn_to_menu = display.newText("Back", 0, 0, native.systemFontBold, 16);
	--	btn_to_menu:setReferencePoint(display.CenterReferencePoint);
	--	btn_to_menu.x = _w/2;
	--	btn_to_menu.y = _h/2-45;
	--	btn_to_menu.scene = "menu";
	--	btn_to_menu:addEventListener("touch", changeScene);
		
---------------------------------------------------------------
-- Start
---------------------------------------------------------------
 
for i=1,20 do
	if(settings.currentlevel < i) then
		--greyed out button, player has not unlocked this level yet
		buttons[i] = ui.newButton{
			id = "buttonid" .. i,
			default = "2x2_standard.png"
		}
	else
		buttons[i] = ui.newButton{
			id = "buttonid" .. i,
			default = "2x2_standard.png",
			over = "2x2_standard.png"
		}
		buttons[i].levelval = i
		buttons[i].scene = "levelloader";
		buttons[i]:addEventListener("touch", changeScene);
	end
	--Optimize this later
	if(i==1) then buttons[i].x = 42; buttons[i].y = 42; end
	if(i==2) then buttons[i].x = 138; buttons[i].y = 42;  end
	if(i==3) then buttons[i].x = 234; buttons[i].y = 42;  end
	if(i==4) then buttons[i].x = 330; buttons[i].y = 42;  end
	if(i==5) then buttons[i].x = 426; buttons[i].y = 42;  end
    if(i==6) then buttons[i].x = 42; buttons[i].y = 122;  end
	if(i==7)then buttons[i].x = 138; buttons[i].y = 122;  end
	if(i==8)then buttons[i].x = 234; buttons[i].y = 122;  end
	if(i==9)then buttons[i].x = 330; buttons[i].y = 122;  end
	if(i==10)then buttons[i].x = 426; buttons[i].y = 122;  end
    if(i==11)then buttons[i].x = 42; buttons[i].y = 202;  end
	if(i==12)then buttons[i].x = 138; buttons[i].y = 202;  end
	if(i==13)then buttons[i].x = 234; buttons[i].y = 202;  end
	if(i==14)then buttons[i].x = 330; buttons[i].y = 202;  end
	if(i==15) then buttons[i].x = 426; buttons[i].y = 202;  end
    if(i==16)then buttons[i].x = 42; buttons[i].y = 282;  end
	if(i==17)then buttons[i].x = 138; buttons[i].y = 282;  end
	if(i==18)then buttons[i].x = 234; buttons[i].y = 282;  end
	if(i==19)then buttons[i].x = 330; buttons[i].y = 282;  end
	if(i==20)then buttons[i].x = 426; buttons[i].y = 282;  end
	buttons[i]:setReferencePoint( display.CenterLeftReferencePoint )
	localGroup:insert(buttons[i])
end
		
		
	--- insert everything into the localGroup	
	--localGroup:insert(btn_to_menu)
	--localGroup:insert(background)	
		
	-- clean everything up
	clean = function ()
	
	end
	
	
	-- do not remove lest the sky shalt fall upon thine head
	return localGroup
	
end