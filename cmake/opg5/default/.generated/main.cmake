include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(opg5_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(opg5_default_default_XC8_FILE_TYPE_assemble)
add_library(opg5_default_default_XC8_assemble OBJECT ${opg5_default_default_XC8_FILE_TYPE_assemble})
    opg5_default_default_XC8_assemble_rule(opg5_default_default_XC8_assemble)
    list(APPEND opg5_default_library_list "$<TARGET_OBJECTS:opg5_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(opg5_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(opg5_default_default_XC8_assemblePreprocess OBJECT ${opg5_default_default_XC8_FILE_TYPE_assemblePreprocess})
    opg5_default_default_XC8_assemblePreprocess_rule(opg5_default_default_XC8_assemblePreprocess)
    list(APPEND opg5_default_library_list "$<TARGET_OBJECTS:opg5_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(opg5_default_default_XC8_FILE_TYPE_compile)
add_library(opg5_default_default_XC8_compile OBJECT ${opg5_default_default_XC8_FILE_TYPE_compile})
    opg5_default_default_XC8_compile_rule(opg5_default_default_XC8_compile)
    list(APPEND opg5_default_library_list "$<TARGET_OBJECTS:opg5_default_default_XC8_compile>")

endif()

# Handle files with suffix elf, for group default-XC8
if(opg5_default_default_XC8_FILE_TYPE_objcopy_avr)
add_library(opg5_default_default_XC8_objcopy_avr OBJECT ${opg5_default_default_XC8_FILE_TYPE_objcopy_avr})
    opg5_default_default_XC8_objcopy_avr_rule(opg5_default_default_XC8_objcopy_avr)
    list(APPEND opg5_default_library_list "$<TARGET_OBJECTS:opg5_default_default_XC8_objcopy_avr>")

endif()


# Main target for this project
add_executable(opg5_default_image_aAN3X2ZZ ${opg5_default_library_list})

set_target_properties(opg5_default_image_aAN3X2ZZ PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${opg5_default_output_dir}")
target_link_libraries(opg5_default_image_aAN3X2ZZ PRIVATE ${opg5_default_default_XC8_FILE_TYPE_link})
# Add the link options from the rule file.
opg5_default_link_rule( opg5_default_image_aAN3X2ZZ)


#Add objcopy steps
opg5_default_objcopy_avr_rule(opg5_default_image_aAN3X2ZZ)

