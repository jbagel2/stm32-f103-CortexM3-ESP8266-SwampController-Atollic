local module = {}

module.SSID = {}
module.SSID["mySSID"] = "Nonya"

module.REPORT_SERVER = ""
module.REPORT_PORT = 80
module.ID = node.chipid()
module.NickName = "Swamp Cooler"
module.EncStartVal = node.chipid() * node.flashid()
module.FirmV = "0.1.12"

module.HubServer = "172.20.112.144" -- MediaServer for now. Will be a Pi or custom linux box.

return module
