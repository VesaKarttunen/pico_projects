import os
import sys

def GenerateSourceFileList(seach_root_directory,
                           excluded_subdirectories,
                           included_file_extension):
    source_files = []
    for parent_path, _, file_names in os.walk(seach_root_directory):
        for excluded_dir in excluded_subdirectories:
            if excluded_dir in parent_path:
                break
        else:
            for file_name in file_names:
                if file_name.endswith(included_file_extension):
                    file_path = os.path.join(parent_path, file_name + "\n")
                    source_files.append(file_path)

    return source_files


# When executed as a script, call as follows:
# $ python generate_source_file_list.py <source-root-dir> <result-file-name>

if __name__ == "__main__":
    search_root_directory = sys.argv[1]
    result_file_name      = sys.argv[2]

    excluded_subdirectories = ("build", "FreeRTOS-Kernel", "pico-sdk","toolchain")
    included_file_extension = (".cpp", ".hpp", ".h")

    source_files = GenerateSourceFileList(search_root_directory,
                                           excluded_subdirectories,
                                           included_file_extension)

    result_file = open(result_file_name, "w")
    result_file.writelines(source_files)
    result_file.close()
