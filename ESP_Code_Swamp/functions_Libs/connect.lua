
-- data format for STM32 (SEND) : "1:PUMP:ZONE:ROOM:AUTOTEMP:HASH"
-- data format from STM32 (RECEIVE) : "2:PUMP:ACTIVEZONES:ACTIVEROOMS:LINETEMPS:AMBIENTTEMP:AMBIENTHUMID:HASH"
-- data format from STM32 (DIAG RECEIVE) : ""



local module = {}

initTime= 0
if httpSrv==nil then
    httpSrv=net.createServer(net.TCP, 10)
end

-- State Vaiables
temp_humids = {}
pump_cur = 0
fan_cur = 0

requestValid = false
headers = ""
body = ""

-- incoming requested state variables
requestStates = {}

local function ConnectToAP(ssid, pass)
wifi.setmode(wifi.STATION)
wifi.sta.config(ssid,pass)
status = wifi.sta.status()
tmr.alarm(0, 1000, 1, function() 
    if wifi.sta.getip()==nil then
      print("...") 
    else
      ip, nm, gw=wifi.sta.getip()
      print('::1234:<3:'..ip)
      tmr.stop(0)      
    end
end)
end

function listap(t)
    for k,v in pairs(t) do
    print(k.." : "..v)
    end
end

function SaveNewTempHumid(temp, humid)
if ((table.getn(temp_humids)) >= 5) then    
    table.remove(temp_humids, (table.getn(temp_humids)))
end
local epoch = rtctime.get()
table.insert(temp_humids, 1, {temp, humid, time.gmtime(epoch)})
end

function ClearAllSavedTempHumid()
    index = (table.getn(temp_humids))
    while (temp_humids[index] ~= nil) do
        table.remove(temp_humids, index )        
        index = index - 1
    end
end

function clearRequestVars()
    local lcvars = require("str_proj_strings")
    requestStates[lcvars.pump]=nil
    requestStates[lcvars.fan]=nil
end

function module.StartRestService(port)
    net.dns.setdnsserver(gw, 0)
    local varsFound = false
    clearRequestVars()
    httpSrv:listen(port, function(conn)        
        conn:on("receive", function(client, request)
            qryVars = {}            
            reqheaders = {}
            local _, _, method, path, reqvars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
            if reqvars ~= nil then
                if (reqvars ~= nil)then 
                for k, v in string.gmatch(reqvars, "(%w+)=(%w+)&*") do
                    qryVars[k] = v 
                end                
        end
            end
            if(method == nil)then 
                _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP");                
            end            
            if method == "GET" then
                client:send(parseGET(path, qryVars))              
                if reqvars == nil then   
                    local lovars = require("string_vars")                 
                    client:send(lovars.RespRedirect)
                end
            elseif method == "POST" then
                client:send(parsePOST(path, qryVars))            
            elseif method == "DELETE" then       
                client:send(parseDELETE(path, qryVars))             
            else 
                local lovars = require("string_vars")              
                client:send(lovars.NotFound_response())
            end             
            client:close();
            requestValid=false
        end)
    end)
end

function setRequestStates(requestV)
    local lovars = require("str_proj_strings")
    requestStates[lovars.pump]=requestV[lovars.pump]
    requestStates[lovars.fan]=requestV[lovars.fan]
end

function getHealthStatus()
    local current_health= {}
    current_health["heap"] = node.heap()
    current_health["time"] = time.gmtime((rtctime.get()))
    return current_health
end

function parseGET(path_to_parse, reqvars)
  local lcvars = require("string_vars")
  local api = require("rest_calls")
    if string.find(path_to_parse, api.API_v1) == nil then
        return lcvars.NotFound_API_response()
    end    
    if string.find(path_to_parse, api.API_v1.."temp") then -- Get ambient temp and humid
     if reqvars[api.qry_ambient] == "all" then         
      local ok, json = pcall(cjson.encode, temp_humids)
        if ok then
            return lcvars.OK_response(json)
        else
            return lcvars.Error_response()
        end   
     elseif reqvars[api.qry_ambient] == "current" then      
      local ok, json = pcall(cjson.encode, temp_humids[1])
        if ok then
            return lcvars.OK_response(json)
        else
            return lcvars.Error_response()
        end
     else
      return lcvars.NotFound_response()
     end
    elseif string.find(path_to_parse, api.API_v1.."config") then -- get the requested state of pump and valves and line temps
     th_buff = "{\"message\" : \"got config request\"}"
    elseif string.find(path_to_parse, api.API_v1.."state") then -- Get the current state of pump and valves and line temps
     if string.find(path_to_parse, api.API_v1.."state/"..api.qry_requested) then
        local ok, json = pcall(cjson.encode, requestStates)
        if ok then
            return lcvars.OK_response(json)
        else
            return lcvars.Error_response()
        end
     end     
    elseif string.find(path_to_parse, api.API_v1.."health") then -- Get memory and other ESP stats
     local ok, json = pcall(cjson.encode, getHealthStatus())
        if ok then
            return lcvars.OK_response(json)
        else
            return lcvars.Error_response()
        end
    elseif string.find(path_to_parse, api.API_v1.."help") then
        return lcvars.Help_response()
    end
    return lcvars.NotFound_response()       
end

function parseDELETE(path_to_parse, requestVars)
 local responses = require("string_vars")
 local str_rest = require("rest_calls") 
    if string.find(path_to_parse, str_rest.API_v1.."temp") then
     if requestVars[str_rest.qry_ambient] == "all" then 
      ClearAllSavedTempHumid()
      print(table.getn(temp_humids))
      if (table.getn(temp_humids)) == 0 then
        return responses.OK_response("{ \"true\" }")
      else
        return responses.Error_response()
      end
     else
      return responses.NotFound_response()
     end     
    end
 return responses.Error_response()
end

function parsePOST(path_to_parse, requestVars)
    local str_rest = require("rest_calls")
    local str_proj = require("str_proj_strings")
    local lvars = require("string_vars")
    print(requestVars)
    if string.find(path_to_parse, str_rest.API_v1_state_requested) then
      if requestVars[str_proj.pump] == nil and requestVars[str_proj.fan] == nil then 
        requestValid=false
      else
        local mcu = require("mcu_functions")
        setRequestStates(requestVars)        
        mcu.MCUSetNewState()
        requestValid=true
        return lvars.OK_response()
      end
    elseif string.find(path_to_parse, str_rest.API_v1.."config") then      
      if requestVars[str_proj.dhtInt] == nil and requestVars[str_proj.heartbeat] == nil and requestVars[str_proj.server] == nil then
        requestValid=false
      else        
        local mcu = require("mcu_functions")
        -- TODO: Validate server address
        mcu.MCUSetConfig(requestVars)
        -- TODO: Parse DHT interval,heartbeat,interval,address
      end
    elseif string.find(path_to_parse, str_rest.API_v1.."reboot") then
      if requestVars[str_proj.token] == str_proj.temp_token then
        local mcu = require("mcu_functions")
        mcu.MCUReboot()
        return lvars.OK_response()
      end
    end
    return lvars.NotFound_response()
end

function SetNodeStatus(pump, fan)
    pump_cur = pump
    fan_cur = fan
end

--function SetConfig(vars)
--    local lvars = require("str_proj_strings")
--    if vars[lvars.dhtInt] == nil then
--        vars[lvars.dhtInt] = 999
--    end
--    if vars[lvars.heartbeat] == nil then
--        vars[lvars.heartbeat] = 999
--    end
--    if vars[lvars.server] == nil then
--        vars[lvars.server] = 999
--    end
--    if vars[lvars.server] ~= 999 then
--        serverHEX_IP(vars[lvars.server])
--        config.HubServer = vars[lvars.server]
--    end
--    local cmd_toSend = "::1234:<4:"..vars[lvars.dhtInt]..":"..vars[lvars.heartbeat]..":"..vars[lvars.server]
--    local cmd_hash = crypto.hash("sha1",cmd_toSend)
--    print(cmd_toSend..":"..crypto.toHex(cmd_hash)..":")
--end
--
--function serverHEX_IP(HexValue)
--    local oct1, oct2, oct3, oct4 = 0
--    oct1 = string.format("%d", (HexValue:sub(1,2)))
--    print(oct1)
--end
--
---- data format for STM32 (SEND) : "1:PUMP:FAN:HASH"
--function MCUSetNewState()
--    local lvars = require("str_proj_strings")
--    if requestStates[lvars.pump] == nil then
--        requestStates[lvars.pump] = 999
--    end
--    if requestStates[lvars.fan] == nil then
--        requestStates[lvars.fan] = 999
--    end
--    local cmd_toSend = "::1234:<1:"..requestStates[lvars.pump]..":"..requestStates[lvars.fan]
--    local cmd_hash = crypto.hash("sha1",cmd_toSend)
--    print(cmd_toSend..":"..crypto.toHex(cmd_hash)..":")
--end
--
--function MCUReboot()
--    local cmd_toSend = "::1234:<23:75"
--    local cmd_hash = crypto.hash("sha1",cmd_toSend)
--    print(cmd_toSend..":"..crypto.toHex(cmd_hash)..":")
--end


-- data format from STM32 (RECEIVE) : "2:PUMP:ACTIVEZONES:ACTIVEROOMS:LINETEMPS:AMBIENTTEMP:AMBIENTHUMID:HASH"
function RequestMCUStatus()
    print('getSTAT')    
    for token in string.gmatch(MCUReturn, "([^,]+),%s*") do
        objPropo[i] = token
        i = i + 1
    end
end

function module.start()
 ip, nm, gw=wifi.sta.getip()
 if ip == nil then
     ConnectToAP(config.SSID["mySSID"], "porsche911")
 else
    print('::1234:<3:'..ip)
 end 
end

return module
