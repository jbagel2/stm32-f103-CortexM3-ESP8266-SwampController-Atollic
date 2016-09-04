local module = {}

module.return_newline = "\r\n"

module.Resp_301 = "HTTP/1.1 301 Moved Permanently"..module.return_newline
module.Resp_200 = "HTTP/1.1 200 OK"..module.return_newline
module.Resp_404 = "HTTP/1.1 404 Not Found"..module.return_newline
module.Resp_500 = "HTTP/1.1 500 Internal Server Error"..module.return_newline

module.qry_ambient = "ambient"
module.qry_requested = "requested"

local headers = require("str_resp_headers")

module.RespOK_needLength = module.Resp_200..headers.H_con_NO_cache..headers.H_con_close..headers.H_con_len
module.RespRedirect = module.Resp_301..headers.H_con_NO_cache.."Location: http://172.20.112.15/\r\n"
module.RespOK_Body = "{\"OK\"}"
module.RespError_Body = "{\"Server Error\"}"
module.RespError = module.Resp_500..headers.H_con_close..headers.H_con_len..string.len(module.RespError_Body)..module.return_newline..module.return_newline..module.RespError_Body
module.RespNotFound_Body = "{\"Not Found\"}"
module.RespNotFound_API_Body = "{\"message\":\"Not Found: Missing API and version in path!\"}"
module.RespNotFound = module.Resp_404..headers.H_con_close..headers.H_con_len..string.len(module.RespNotFound_Body)..module.return_newline..module.return_newline..module.RespNotFound_Body
module.RespNotFound_API = module.Resp_404..headers.H_con_close..headers.H_con_len..string.len(module.RespNotFound_API_Body).."\r\n\r\n"..module.RespNotFound_API_Body

function module.OK_response(message)
    if message == nil then
        return module.OK_response(module.RespOK_Body)
    else
        local temp_headers = module.RespOK_needLength..(string.len(message) + 2).."\r\n"..headers.H_con_json  
        local response = temp_headers.."\r\n\r\n"..message
        return response
    end
end

function module.NotFound_response()
    return module.RespNotFound
end

function module.NotFound_API_response()
    return module.RespNotFound_API
end

function module.Error_response()
    return module.RespError
end

function module.Help_response()
    local help = require("str_help_contents")
    return help.RespHelp
end

return module
