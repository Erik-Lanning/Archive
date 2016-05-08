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
	
		
	--LOAD BACKGROUND IMAGE
--	local background = display.newImage("img/Menu/background.jpg", true) -- flag overrides large image downscaling
--	background.x = display.contentWidth / 2
--	background.y = display.contentHeight / 2
	--Title
	local credits_Title = display.newText("Credits", 0, 0, "Comic Book", 24);
	credits_Title.x = 398; credits_Title.y = 24
	-- menu buttons	
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
--TO ADD:
--Sound Scientists album cover- 159x, 107y w:303, h:182
--Sound Scientist's debut album "Instrumentally Sound" - 158x, 211y - size font:12
--2x2 standard block: 382x, 284y
local block1 = display.newImage("2x2_magnet.png", 355, 250, true )
local albumcover = display.newImage("ssalbum.png", 6, 10, true)
localGroup:insert(block1)
localGroup:insert(albumcover)
--

	local text1 = display.newText("Sound Scientist's debut album \"Instrumentally Sound\"", 0, 0, "Comic Book", 10);
	text1.x = 158; text1.y = 242
	local text3 = display.newText("Programmer - Erik Lanning", 0, 0, "Comic Book", 10);
	text3.x = 397; text3.y = 52
	local text4 = display.newText("Sprite Artist - Devil Evil", 0, 0, "Comic Book", 10);
	text4.x = 392; text4.y = 75
	local text5 = display.newText("Music - Sound Scientists", 0, 0, "Comic Book", 10);
	text5.x = 391; text5.y = 97
	local text6 = display.newText("Fonts - dafont.com", 0, 0, "Comic Book", 10);
	text6.x = 380; text6.y = 121
	local text7 = display.newText("Special Thanks", 0, 0, "Comic Book", 16);
	text7.x = 388; text7.y = 154
	local text8 = display.newText("Angela Shapow", 0, 0, "Comic Book", 12);
	text8.x = 387; text8.y = 174
	local text9 = display.newText("Tyler J. Johnson", 0, 0, "Comic Book", 12);
	text9.x = 389; text9.y = 193
	local text10 = display.newText("Yonghyun Kim", 0, 0, "Comic Book", 12);
	text10.x = 387; text10.y = 215
	local text11 = display.newText("Meghan Dibble", 0, 0, "Comic Book", 12);
	text11.x = 387; text11.y = 235		
--
	--- insert everything into the localGroup	
	localGroup:insert(btn_back)	
	--localGroup:insert(background)
	localGroup:insert(credits_Title)
	localGroup:insert(text1)
	localGroup:insert(text3)
	localGroup:insert(text4)
	localGroup:insert(text5)
	localGroup:insert(text6)
	localGroup:insert(text7)
	localGroup:insert(text8)
	localGroup:insert(text9)
	localGroup:insert(text10)	
	localGroup:insert(text11)	
	-- clean everything up
	clean = function ()
	
	end
	
	
	-- do not remove lest the sky shalt fall upon thine head
	return localGroup
	
end