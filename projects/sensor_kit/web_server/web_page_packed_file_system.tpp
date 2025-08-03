#include "mongoose/mongoose.h"

// Read-only file system is emulated with embedding the content of the files into firmware binary
// as unicode character values served from build time generated const arrays
@<array_defs>

static struct packed_file
{
    const char* name;
    const unsigned char* data;
    size_t size;
    time_t mtime;
} packed_files[] = {
@<info_row_defs>
{.name = nullptr, .data = nullptr, .size = 0, .mtime = 0}
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
