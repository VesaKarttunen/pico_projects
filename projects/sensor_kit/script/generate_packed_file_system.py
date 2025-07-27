import sys

# When executed as a script, call as follows:
# $ python generate_packed_file_system.py <web-page-source-file-dir> <generated-packed-file-system-cpp-file>

web_page_source_dir = sys.argv[1]
generated_packed_file_system_cpp_file = sys.argv[2]

template_packed_file_system = web_page_source_dir + "/web_page_packed_file_system.tpp"
template_file = open(template_packed_file_system, "r")
template_content = template_file.read()
template_file.close()

web_page_source_file_names = ["/index.html", "/main.js", "/style.css"]

for file_name in web_page_source_file_names:
    source_file = open(web_page_source_dir + file_name, "r")
    source_content = source_file.read()
    source_file.close()

    unicode_content = ""
    for index, character in enumerate(source_content):
        unicode_content += str(ord(character)) + ", "
        if index % 20 == 0 and index != 0:
            unicode_content += "\n"
    unicode_content += "0"

    if file_name == "/index.html":
        template_content = template_content.replace("@<index_html_unicode_character_content>", unicode_content)
    elif file_name == "/main.js":
        template_content = template_content.replace("@<main_js_unicode_character_content>", unicode_content)
    elif file_name == "/style.css":
        template_content = template_content.replace("@<style_css_unicode_character_content>", unicode_content)

generated_file = open(generated_packed_file_system_cpp_file, "w")
generated_file.write(template_content)
generated_file.close()
