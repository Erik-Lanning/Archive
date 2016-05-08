module(..., package.seeall)

-- Main function - MUST return a display.newGroup()
function new()
	local localGroup = display.newGroup()
	
	local theTimer
	

		local goToLevel = function()
			director:changeScene( "levelloader" )
		end
		
		theTimer = timer.performWithDelay( 0.01, goToLevel, 1 )
	
	clean = function()

	end
	
	-- MUST return a display.newGroup()
	return localGroup
end
