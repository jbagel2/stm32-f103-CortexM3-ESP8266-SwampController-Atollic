local module = {}

-- data format for STM32 (SEND) : "1:PUMP:FAN:HASH"
function module.MCUSetNewState()
    local lvars = require("str_proj_strings")
    if requestStates[lvars.pump] == nil then
        requestStates[lvars.pump] = 999
    end
    if requestStates[lvars.fan] == nil then
        requestStates[lvars.fan] = 999
    end
    local cmd_toSend = "::1234:<1:"..requestStates[lvars.pump]..":"..requestStates[lvars.fan]
    local cmd_hash = crypto.hash("sha1",cmd_toSend)
    print(cmd_toSend..":"..crypto.toHex(cmd_hash)..":")
end


function module.MCUReboot()
    local cmd_toSend = "::1234:<23:75"
    local cmd_hash = crypto.hash("sha1",cmd_toSend)
    print(cmd_toSend..":"..crypto.toHex(cmd_hash)..":")
end

function serverHEX_IP(HexValue)
    local oct1, oct2, oct3, oct4 = 0
    oct1 = string.format("%d", (HexValue:sub(1,2)))
    print(oct1)
end

function module.MCUSetConfig(vars)
    local lvars = require("str_proj_strings")
    if vars[lvars.dhtInt] == nil then
        vars[lvars.dhtInt] = 999
    end
    if vars[lvars.heartbeat] == nil then
        vars[lvars.heartbeat] = 999
    end
    if vars[lvars.server] == nil then
        vars[lvars.server] = 999
    end
    if vars[lvars.server] ~= 999 then
        serverHEX_IP(vars[lvars.server])
        config.HubServer = vars[lvars.server]
    end
    local cmd_toSend = "::1234:<4:"..vars[lvars.dhtInt]..":"..vars[lvars.heartbeat]..":"..vars[lvars.server]
    local cmd_hash = crypto.hash("sha1",cmd_toSend)
    print(cmd_toSend..":"..crypto.toHex(cmd_hash)..":")
end

return module