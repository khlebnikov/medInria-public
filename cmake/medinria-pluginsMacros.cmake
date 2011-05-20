###############################################################################
#
# Macros used by medinria-plugins
#
# Author: Benoît Bleuzé
#
###############################################################################

MACRO(MACRO_ADD_PLUGIN  P_NAME DEFAULT_BUILD_VALUE)

string(TOUPPER ${P_NAME} UPPER_CASE_NAME)
# set(MEDINRIA_BUILD_${UPPER_CASE_NAME}_PLUGIN ${DEFAULT_BUILD_VALUE})
option(MEDINRIA_BUILD_${UPPER_CASE_NAME}_PLUGIN "Build ${P_NAME} plugin" "${DEFAULT_BUILD_VALUE}")

if (MEDINRIA_BUILD_ALL_PLUGINS)
# Force to update the cache
    set(MEDINRIA_BUILD_${UPPER_CASE_NAME}_PLUGIN "ON" CACHE BOOL "Build ${P_NAME} plugin" FORCE)
endif()

if (MEDINRIA_BUILD_ALL_PLUGINS OR
    MEDINRIA_BUILD_${UPPER_CASE_NAME}_PLUGIN )
  #message("adding "${P_NAME})
  add_subdirectory(${P_NAME})
endif()


ENDMACRO(MACRO_ADD_PLUGIN)


# # argument LIST is a list with plugin names at odd indices followed by
# # the respective default build values (ON/OFF) at even indices
MACRO(MACRO_ADD_PLUGIN_LIST P_LIST)
message("plugin list: " ${P_LIST})  
list(LENGTH P_LIST N)
message("list length:" ${N})
set (INDEX 0)
#message(${PLUGIN_LIST})
while(INDEX LESS N)
  MATH( EXPR INDEX_BOOL "${INDEX} + 1" )
  MESSAGE ("index:" ${INDEX})
  MESSAGE ("index_bool:" ${INDEX_BOOL})

  list(GET P_LIST ${INDEX} PLUGIN_ITEM)
  list(GET P_LIST ${INDEX_BOOL} BUILD_VALUE)

  message("Item: " ${PLUGIN_ITEM} "; value: " ${BUILD_VALUE})

  MACRO_ADD_PLUGIN (${PLUGIN_ITEM} ${BUILD_VALUE})
  MATH( EXPR INDEX "${INDEX} + 2" )
endwhile()


ENDMACRO(MACRO_ADD_PLUGIN_LIST)
