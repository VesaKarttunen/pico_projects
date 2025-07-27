#include "mongoose/mongoose.h"

// clang-format off
static const unsigned char index_html[] = {
@<index_html_unicode_character_content>
};

static const unsigned char main_js[] = {
@<main_js_unicode_character_content>
};

static const unsigned char style_css[] = {
@<style_css_unicode_character_content>
};
// clang-format on

static const struct packed_file
{
    const char* name;
    const unsigned char* data;
    size_t size;
    time_t mtime;
} packed_files[] = {
    {.name = "/index.html", .data = index_html, .size = sizeof(index_html), .mtime = 1'753'533'813},
    {.name = "/main.js",    .data = main_js,    .size = sizeof(main_js),    .mtime = 1'753'534'790},
    {.name = "/style.css",  .data = style_css,  .size = sizeof(style_css),  .mtime = 1'753'534'006},
    {.name = nullptr,       .data = nullptr,    .size = 0,                  .mtime = 0            }
};

static int scmp(const char* a, const char* b)
{
    while (*a && (*a == *b))
    {
        a++;
        b++;
    }

    return *reinterpret_cast<const unsigned char*>(a) - *reinterpret_cast<const unsigned char*>(b);
}

const char* mg_unlist(size_t no)
{
    return packed_files[no].name;
}

const char* mg_unpack(const char* name, size_t* size, time_t* mtime)
{
    const packed_file* p;
    for (p = packed_files; p->name != nullptr; p++)
    {
        if (scmp(p->name, name) != 0)
        {
            continue;
        }
        if (size != nullptr)
        {
            *size = p->size - 1;
        }
        if (mtime != nullptr)
        {
            *mtime = p->mtime;
        }
        return reinterpret_cast<const char*>(p->data);
    }
    return nullptr;
}
