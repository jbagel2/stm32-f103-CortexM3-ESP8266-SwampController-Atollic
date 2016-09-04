local module = {}

function module.listen()
 bCastSrv=net.createServer(net.UDP, 10)
 bCastSrv:on("receive", function(client, request) 
     print(request)
     local _, _, method, path, reqvars = string.find(request, "([A-Z]+) (.+)?(.+) CONTROL");
     print(method)
     print(path)
     print(reqvars)
     if request == "reset" then
      --Reset Node     
     else
     ip, nm, gw=wifi.sta.getip()
     client:send("{\"autoNode\":\""..config.NickName.."\", \"addr\":\""..ip.."\"}")
     end
 end)
 bCastSrv:listen(4444)
end

return module
