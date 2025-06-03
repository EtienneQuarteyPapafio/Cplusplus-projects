cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "C:/Users/Etienne Quartey-Papa/Downloads/vst-sdk_3.7.9_build-61_2023-10-09/VST_SDK/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(Filter
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "Filter VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(Filter
    source/version.h
    source/myplugincids.h
    source/mypluginprocessor.h
    source/mypluginprocessor.cpp
    source/myplugincontroller.h
    source/myplugincontroller.cpp
    source/mypluginentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ENABLE_VSTGUI_SUPPORT)
    target_sources(Filter
        PRIVATE
            resource/myplugineditor.uidesc
    )
    target_link_libraries(Filter
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(Filter
        RESOURCES
            "resource/myplugineditor.uidesc"
    )
endif(SMTG_ENABLE_VSTGUI_SUPPORT)
# -------------------

smtg_target_add_plugin_snapshots (Filter
    RESOURCES
        resource/D4E36DF89DB15ACAAF029CAB0E8D676E_snapshot.png
        resource/D4E36DF89DB15ACAAF029CAB0E8D676E_snapshot_2.0x.png
)

target_link_libraries(Filter
    PRIVATE
        sdk
)

smtg_target_configure_version_file(Filter)

if(SMTG_MAC)
    smtg_target_set_bundle(Filter
        BUNDLE_IDENTIFIER Ap2
        COMPANY_NAME "My Plug-in Company"
    )
    smtg_target_set_debug_executable(Filter
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(Filter PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Filter)

        smtg_target_set_debug_executable(Filter
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
