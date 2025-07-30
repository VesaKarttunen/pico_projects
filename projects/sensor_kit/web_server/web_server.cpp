//---------------------------------------------------------------------------------------------------------------------
// HTTP Web Server
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE INCLUDE DIRECTIVES
//---------------------------------------------------------------------------------------------------------------------

// Own
#include "web_server.hpp"

// Local project
#include "app_command/app_command.hpp"

// Mongoose
#include "mongoose/mongoose.h"

// STD
#include <cstdio>
#include <string_view>

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE VARIABLE DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static mg_mgr f_event_manager;
static mg_http_serve_opts f_options_serve_files;

//---------------------------------------------------------------------------------------------------------------------
// PRIVATE FUNCTION DEFINITIONS
//---------------------------------------------------------------------------------------------------------------------

static constexpr std::string_view AsStrView(mg_str text)
{
    return {text.buf, text.len};
}

static void HttpEventHandler(mg_connection* connection,
                             int event_type,
                             void* data)
{
    if (event_type == MG_EV_HTTP_MSG)
    {
        auto* request = reinterpret_cast<mg_http_message*>(data);
        auto uri      = AsStrView(request->uri);
        auto query    = AsStrView(request->query);

        if (uri.starts_with("/api"))
        {
            bool is_success = false;

            if (query.starts_with("arg="))
            {
                // Remove "/api/" prefix from the uri string to get the name of the requested command
                uri.remove_prefix(5);
                // Remove "arg=" prefix from the query string to get the argument value
                query.remove_prefix(4);

                is_success = AppCommand::ProcessCommand({.name = uri,
                                                         .arg  = query});
            }

            if (is_success)
            {
                mg_http_reply(connection, 200, "", "OK\n");
            }
            else
            {
                std::printf("Invalid web API call\n");
                mg_http_reply(connection, 404, "", "Invalid web API call\n");
            }
        }
        else
        {
            mg_http_serve_dir(connection, request, &f_options_serve_files);
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

    // Define options for serving HTTP requests for files.
    // Note that embedded packed file system is used for web page files.
    f_options_serve_files.root_dir = "/";
    f_options_serve_files.fs       = &mg_fs_packed;

    // Desired web server URL (<url> = http://<ip_address>:<port>) is given as command line argument
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
