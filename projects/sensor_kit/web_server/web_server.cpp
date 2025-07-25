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

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE VARIABLE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static mg_mgr f_mg_event_manager;

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

        if (mg_match(request->uri, mg_str("/api/hello"), nullptr))
        {
            mg_http_reply(connection, 200, "", "Hello World!\n");
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------
void WebServer::Init()
{
    mg_log_set(MG_LL_DEBUG);
    mg_mgr_init(&f_mg_event_manager);

    // Desired web server URL (http://ip_address:port) is given as command line argument
    // in cmake configuration step using the following format: "-D HTTP_SERVER_URL=<url>"
    mg_http_listen(&f_mg_event_manager,
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
        mg_mgr_poll(&f_mg_event_manager, timeout_ms);
    }
}
