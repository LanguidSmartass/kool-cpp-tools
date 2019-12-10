if(MSVC)
    set_property(
        TARGET ${gtests-exec-name}
        PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL$<$<CONFIG:Debug>:Debug>"
    )
endif()
