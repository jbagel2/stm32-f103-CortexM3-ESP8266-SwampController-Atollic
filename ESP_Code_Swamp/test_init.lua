config = require("config")
time = require("time")
--vars = require("string_vars")
app = require("connect")
app.start()
app.StartRestService(80)
time.GetTime()
tmr.alarm(0, 1000, 1, function() 
    if rtctime.get()==0 then
       --Nothing
    else
      local epoch, _=rtctime.get()  
      app.initTime=epoch    
      tmr.stop(0)      
    end
end)
