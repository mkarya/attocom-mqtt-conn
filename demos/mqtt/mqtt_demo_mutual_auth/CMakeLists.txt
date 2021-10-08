set( DEMO_NAME "mqtt_demo_mutual_auth" )

# Include MQTT library's source and header path variables.
include( ${CMAKE_SOURCE_DIR}/libraries/standard/coreMQTT/mqttFilePaths.cmake )

# Include backoffAlgorithm library file path configuration.
include( ${CMAKE_SOURCE_DIR}/libraries/standard/backoffAlgorithm/backoffAlgorithmFilePaths.cmake )

# CPP files are searched for supporting CI build checks that verify C++ linkage of the coreMQTT library
file( GLOB DEMO_FILE "*.c" )

# Demo target.
add_executable(
    ${DEMO_NAME}
        "${DEMO_FILE}"
        ${MQTT_SOURCES}
        ${MQTT_SERIALIZER_SOURCES}
        ${BACKOFF_ALGORITHM_SOURCES}
)

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
target_link_directories(
    ${DEMO_NAME}
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/sdk/mercury/lib"
    )

target_link_libraries(
    ${DEMO_NAME}
    PRIVATE
        clock_posix
        openssl_posix
        -pthread
        mercuryapi
        ltkc
        ltkctm
)


target_include_directories(
    ${DEMO_NAME}
    PUBLIC
        ${MQTT_INCLUDE_PUBLIC_DIRS}
        ${BACKOFF_ALGORITHM_INCLUDE_PUBLIC_DIRS}
        ${CMAKE_CURRENT_LIST_DIR}
        ${LOGGING_INCLUDE_DIRS}
	    "${CMAKE_CURRENT_LIST_DIR}/sdk/mercury/include"
)

set_macro_definitions(TARGETS ${DEMO_NAME}
                      REQUIRED
                        "AWS_IOT_ENDPOINT"
                        "ROOT_CA_CERT_PATH"
                        "CLIENT_CERT_PATH"
                        "CLIENT_PRIVATE_KEY_PATH"
                        "CLIENT_IDENTIFIER"
                      OPTIONAL
                        "CLIENT_USERNAME"
                        "CLIENT_PASSWORD"
                        "OS_NAME"
                        "OS_VERSION"
                        "HARDWARE_PLATFORM_NAME")
