local module = {}

module.qry_ambient = "ambient"
module.qry_requested = "requested"

module.API_v1 = "/api/v1/"
module.API_state = "state/"
module.API_v1_state_requested = module.API_v1..module.API_state..module.qry_requested

return module
