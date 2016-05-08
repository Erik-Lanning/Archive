--globalfunc.lua
--Description:
--		This file holds all the resources for file management and other assorted functions
--
--
json = require("json") --bit redundant but just incase

settings = {}
settings.music = 1
settings.soundeffects = 1
saveTable(settings, "pdata.json")