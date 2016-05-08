module(..., package.seeall)

function new()	
	
	-- we store everything inside this group at the end
	local localGroup = display.newGroup()

	-- change scene function
	function changeScene(e)
		if(settings.soundeffects==1) then
			--play button click sound effect
			local buttonsound =  audio.loadSound("buttonclick.mp3")
			audio.play( buttonsound )
		end
		if(e.phase == "ended") then
			director:changeScene(e.target.scene, "moveFromLeft");
		end
	end
	
	--LOAD BACKGROUND	
--	local background = display.newImage("img/Menu/background.jpg", true) -- flag overrides large image downscaling
--	background.x = display.contentWidth / 2
--	background.y = display.contentHeight / 2
	--TODO

--1x1 magnet block- 435x, 83y
local block1 = display.newImage("1x1_magnet.png", 435, 83, true )
--1x1 standard block-435x 118y
local block2 = display.newImage("1x1_standard.png", 435, 118, true )
--1x1 movable block-435x 158y
local block3 = display.newImage("1x1_draggable.png", 435, 158, true )
--1x1 explosive block-435x 200y
local block4 = display.newImage("1x1_bomb.png", 435, 200, true )
--1x1 indestructable blocks- 435x 243y
local block5 = display.newImage("1x1_combo.png", 435, 243, true )
localGroup:insert(block1)
localGroup:insert(block2)
localGroup:insert(block3)
localGroup:insert(block4)
localGroup:insert(block5)
	--back button	
	local btn_back = ui.newButton{
			default = "buttonRed.png",
			over = "buttonRedOver.png",
			x = 150,
			y = 288,
			text = "Back",
			font = "comic andy",
			size = 40,
			emboss = true,
			id = "btn_back"
		}
		btn_back.scene = "menu";
		btn_back:addEventListener("touch", changeScene);	
		
	local tutorial_Title = display.newText("Totem Story", 0, 0, "Yikes!", 36);
	tutorial_Title.x = 240; tutorial_Title.y = 22
	--IMAGE = IMAGES OF BLOCKS SO THEY CAN SEE WHAT IT LOOKS LIKE (make them interactive too)
	local text1 = display.newText("Remove blocks and don't let the totem hit the ground, good luck.", 0, 0, "Comic Book", 14);
	text1.x = 239; text1.y = 51
	local text2 = display.newText("Magnet blocks pull other magnet blocks together, the closer they are.", 0, 0, "Comic Book", 11);
	text2.x = 199; text2.y = 85
	local text3 = display.newText("Standard blocks are boring and do nothing, but can be removed.", 0, 0, "Comic Book", 11);
	text3.x = 186; text3.y = 119
	local text4 = display.newText("Draggable blocks can be moved around with tap and hold.", 0, 0, "Comic Book", 11);
	text4.x = 169; text4.y = 154
	local text5 = display.newText("Bomb blocks let out a blast that pushes nearby blocks.", 0, 0, "Comic Book", 11);
	text5.x = 157; text5.y = 202
	local text6 = display.newText("Indestructable blocks cannot be removed.", 0, 0, "Comic Book", 11);
	text6.x = 122; text6.y = 246	
		
		
	--- insert everything into the localGroup	
	localGroup:insert(btn_back)
	localGroup:insert(tutorial_Title)
	--localGroup:insert(background)
	localGroup:insert(text1)
	localGroup:insert(text2)
	localGroup:insert(text3)
	localGroup:insert(text4)
	localGroup:insert(text5)
	localGroup:insert(text6)
	-- clean everything up
	clean = function ()
	
	end
	
	
	-- do not remove lest the sky shalt fall upon thine head
	return localGroup
	
end