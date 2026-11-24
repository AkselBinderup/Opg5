# The following variables contains the files used by the different stages of the build process.
set(opg5_default_default_XC8_FILE_TYPE_assemble)
set_source_files_properties(${opg5_default_default_XC8_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${opg5_default_default_XC8_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(opg5_default_default_XC8_FILE_TYPE_assemblePreprocess)
set_source_files_properties(${opg5_default_default_XC8_FILE_TYPE_assemblePreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${opg5_default_default_XC8_FILE_TYPE_assemblePreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(opg5_default_default_XC8_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../ExtInt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../RingBuffer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Timer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../Uart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../driver/ssd1306.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../driver/twi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c")
set_source_files_properties(${opg5_default_default_XC8_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(opg5_default_default_XC8_FILE_TYPE_link)
set(opg5_default_default_XC8_FILE_TYPE_objcopy_avr)
set(opg5_default_image_name "default.elf")
set(opg5_default_image_base_name "default")

# The output directory of the final image.
set(opg5_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/opg5")

# The full path to the final image.
set(opg5_default_full_path_to_image ${opg5_default_output_dir}/${opg5_default_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .hxl
    .mum
    .o
    .sdb
    .sym
    .cmf)
list(TRANSFORM output_extensions PREPEND "${opg5_default_output_dir}/${opg5_default_image_base_name}")
