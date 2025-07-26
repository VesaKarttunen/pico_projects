#include "mongoose/mongoose.h"

// clang-format off
static const unsigned char index_html[] = {
  60,  33,  68,  79,  67,  84,  89,  80,  69,  32, 104, 116,
 109, 108,  62,  13,  10,  60, 104, 116, 109, 108,  62,  13,
  10,  60, 104, 101,  97, 100,  62,  13,  10,  32,  32,  60,
 108, 105, 110, 107,  32, 104, 114, 101, 102,  61,  34, 115,
 116, 121, 108, 101,  46,  99, 115, 115,  34,  32, 114, 101,
 108,  61,  34, 115, 116, 121, 108, 101, 115, 104, 101, 101,
 116,  34,  32,  47,  62,  13,  10,  60,  47, 104, 101,  97,
 100,  62,  13,  10,  60,  98, 111, 100, 121,  62,  13,  10,
  32,  32,  60, 100, 105, 118,  32,  99, 108,  97, 115, 115,
  61,  34, 109,  97, 105, 110,  34,  62,  13,  10,  32,  32,
  32,  32,  60, 104,  49,  62,  83, 101, 110, 115, 111, 114,
  32,  75, 105, 116,  32,  85,  73,  60,  47, 104,  49,  62,
  13,  10,  32,  32,  32,  32,  60,  98, 117, 116, 116, 111,
 110,  32, 105, 100,  61,  34,  98, 117, 116, 116, 111, 110,
  95, 116, 111, 103, 103, 108, 101,  95, 108, 101, 100,  34,
  62,  84, 111, 103, 103, 108, 101,  32,  76,  69,  68,  60,
  47,  98, 117, 116, 116, 111, 110,  62,  13,  10,  32,  32,
  60,  47, 100, 105, 118,  62,  13,  10,  32,  32,  60, 115,
  99, 114, 105, 112, 116,  32, 115, 114,  99,  61,  34, 109,
  97, 105, 110,  46, 106, 115,  34,  62,  60,  47, 115,  99,
 114, 105, 112, 116,  62,  13,  10,  60,  47,  98, 111, 100,
 121,  62,  13,  10,  60,  47, 104, 116, 109, 108,  62, 0
};

static const unsigned char main_js[] = {
  99, 111, 110, 115, 116,  32, 116, 111, 103, 103, 108, 101,
  32,  61,  32,  40,  41,  32,  61,  62,  32, 102, 101, 116,
  99, 104,  40,  39,  97, 112, 105,  47, 116, 111, 103, 103,
 108, 101,  95, 108, 101, 100,  39,  41,  59,  13,  10,  13,
  10, 100, 111,  99, 117, 109, 101, 110, 116,  46, 103, 101,
 116,  69, 108, 101, 109, 101, 110, 116,  66, 121,  73, 100,
  40,  39,  98, 117, 116, 116, 111, 110,  95, 116, 111, 103,
 103, 108, 101,  95, 108, 101, 100,  39,  41,  46, 111, 110,
  99, 108, 105,  99, 107,  32,  61,  32, 116, 111, 103, 103,
 108, 101,  59,  13,  10, 0
};

static const unsigned char style_css[] = {
  46, 109,  97, 105, 110,  32,  32, 123,  32, 109,  97, 114,
 103, 105, 110,  58,  32,  49, 101, 109,  59,  32, 125, 0
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
