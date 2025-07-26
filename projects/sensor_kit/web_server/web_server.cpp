//---------------------------------------------------------------------------------------------------------------------
// HTTP Web Server
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "web_server.hpp"

// Mongoose
#include "mongoose/mongoose.h"

// STD
#include <cstdio>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE VARIABLE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static mg_mgr f_event_manager;

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static void HttpEventHandler(mg_connection* connection,
                             int event_type,
                             void* data)
{
    if (event_type == MG_EV_HTTP_MSG)
    {
        auto* request = reinterpret_cast<mg_http_message*>(data);

        if (mg_match(request->uri, mg_str("/api/toggle_led"), nullptr))
        {
            std::printf("Test API call\n");
            mg_http_reply(connection, 200, "", "OK\n");
        }
        else
        {
            mg_http_serve_opts opts = {};
            opts.root_dir           = "/";
            opts.fs                 = &mg_fs_packed;

            mg_http_serve_dir(connection, request, &opts);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------
void WebServer::Init()
{
    mg_log_set(MG_LL_DEBUG);
    mg_mgr_init(&f_event_manager);

    // Desired web server URL (http://ip_address:port) is given as command line argument
    // in cmake configuration step using the following format: "-D HTTP_SERVER_URL=<url>"
    mg_http_listen(&f_event_manager,
                   HTTP_SERVER_URL,
                   HttpEventHandler,
                   nullptr);
}

void WebServer::Task(void* p)
{
    (void)p;

    while (true)
    {
        int timeout_ms = 2000;
        mg_mgr_poll(&f_event_manager, timeout_ms);
    }
}
