local module = {}

module.Help_Temp = {}
module.Help_Temp["temp"] = "{\"temp\" : [ { \"GET\" : [{\"ambient\" : [\"all\", \"current\"]}] } ] }"
module.Help_Temp["config"] = "{\"config\" : [] }"
module.Help_Temp["state"] = "{\"state\" : [ { \"GET\" : [\"requested\"] } ] }"
module.Help_Temp["health"] = "{\"health\" : [] }"
module.Help_Temp["help"] = "\"help\" : "

local headers = require("str_resp_headers")
local response = require("string_vars")

module.RespHelp_Body = "{"..module.Help_Temp["help"].."[".."\r\n"..module.Help_Temp["temp"]..",".."\r\n"..module.Help_Temp["config"]..",".."\r\n"..module.Help_Temp["state"]..",".."\r\n"..module.Help_Temp["health"].."".."\r\n".."]}"
module.RespHelp = response.RespOK_needLength..string.len(module.RespHelp_Body).."\r\n"..headers.H_con_json.."\r\n"..module.RespHelp_Body

return module