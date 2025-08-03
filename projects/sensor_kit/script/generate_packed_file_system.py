import os
import sys

# When executed as a script, call as follows:
# $ python generate_packed_file_system.py <web-page-source-file-dir> <generated-packed-file-system-cpp-file>

web_page_source_dir = sys.argv[1]
generated_packed_file_system_cpp_file = sys.argv[2]

# Note that the script assumes that the template file for generating the packed files system Cpp file is:
# -Named:   web_page_packed_file_system.tpp
# -Located: direct parent directory of the web page source directory
# TODO: Fix these hard coded assumptions
template_packed_file_system = web_page_source_dir + "/../web_page_packed_file_system.tpp"
template_file = open(template_packed_file_system, "r")
template_content = template_file.read()
template_file.close()

source_file_names = os.listdir(web_page_source_dir)

# Cpp code snippet templates to generate packed files system source file content
array_def_template = "static const unsigned char {array_name}[] = {{{unicode_content}}};\n\n"
info_row_def_template = "{{.name = \"/{file_name}\", .data = {array_name}, .size = sizeof({array_name}), .mtime = 1700000000}},\n"

# These strings will hold the final substituted content replacing the placeholders in the template file
array_defs_subst = ""
info_row_defs_subst = ""

for file_name in source_file_names:
    source_file = open(web_page_source_dir + "/" + file_name, "r")
    source_content = source_file.read()
    source_file.close()

    unicode_content = ""
    for character in source_content:
        unicode_content += str(ord(character)) + ", "
    unicode_content += "0"

    array_name = file_name.replace(".","_")
    array_defs_subst += array_def_template.format(array_name=array_name, unicode_content=unicode_content)
    info_row_defs_subst += info_row_def_template.format(file_name=file_name, array_name=array_name)

# Replace the placeholders in the template file with the generated substitution content
template_content = template_content.replace("@<array_defs>", array_defs_subst)
template_content = template_content.replace("@<info_row_defs>", info_row_defs_subst)

generated_file = open(generated_packed_file_system_cpp_file, "w")
generated_file.write(template_content)
generated_file.close()
