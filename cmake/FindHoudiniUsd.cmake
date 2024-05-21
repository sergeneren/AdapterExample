#  Copyright 2021 Tangent Animation
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
#  including without limitation, as related to merchantability and fitness
#  for a particular purpose.
#
#  In no event shall any copyright holder be liable for any damages of any kind
#  arising from the use of this software, whether in contract, tort or otherwise.
#  See the License for the specific language governing permissions and
#  limitations under the License.

if(NOT DEFINED HOUDINI_BASE)
    message(FATAL_ERROR "HOUDINI_BASE not defined")
endif()

# DSO
target_compile_definitions(UsdInterface
    INTERFACE
    USE_HBOOST
    BOOST_NS=hboost
)

set(_houdini_libs
    OpenImageIO_sidefx;
    hboost_filesystem-mt-x64;
    hboost_iostreams-mt-x64;
    hboost_system-mt-x64;
    hboost_regex-mt-x64;
    )

# optional boost_program_options
if(${USE_IMAGING_ENGINE})
    list(APPEND _houdini_libs hboost_program_options-mt-x64)
endif()

foreach(_houdini_lib ${_houdini_libs})
    find_library(${_houdini_lib}_path
            NAMES
            ${_houdini_lib}
            PATHS
            ${HOUDINI_BASE}/dsolib
            ${HOUDINI_BASE}/custom/houdini/dsolib/
            REQUIRED
            )

    message(STATUS "Found ${_houdini_lib}: ${${_houdini_lib}_path}")

    target_link_libraries(UsdInterface
            INTERFACE
            ${${_houdini_lib}_path}
            )

endforeach()

# Python
find_library(_houdini_python_lib
    NAMES
    python39
    python310
    python3.9
    python
    PATHS
    ${HOUDINI_BASE}/python39/libs
    ${HOUDINI_BASE}/python310/libs
    ${HOUDINI_BASE}/python/libs
    ${HOUDINI_BASE}/python/lib
    REQUIRED
    )

find_library(_houdini_hboost_python
        NAMES
        hboost_python39-mt-x64
        hboost_python310-mt-x64
        hboost_python-mt-x64
        PATHS
        ${HOUDINI_BASE}/dsolib
        ${HOUDINI_BASE}/custom/houdini/dsolib/
        REQUIRED
        )

target_link_libraries(UsdInterface INTERFACE ${_houdini_python_lib} ${_houdini_hboost_python})

# Usd
list(APPEND CMAKE_FIND_LIBRARY_PREFIXES lib) # append lib prefix to have same behaviour on win and lin
set(_houdini_pxr_libs pxr_ar;pxr_arch;pxr_cameraUtil;pxr_garch;pxr_gf;pxr_glf;pxr_hd;pxr_hdSt;pxr_hdx;pxr_hf;pxr_hgi;pxr_hgiGL;pxr_hio;pxr_js;pxr_kind;pxr_ndr;pxr_pcp;pxr_plug;pxr_pxOsd;pxr_sdf;pxr_sdr;pxr_tf;pxr_trace;pxr_usd;pxr_usdHydra;pxr_usdImaging;pxr_usdImagingGL;pxr_usdLux;pxr_usdRender;pxr_usdShade;pxr_usdSkel;pxr_usdUtils;pxr_usdVol;pxr_vt;pxr_work;pxr_usdGeom)
foreach(_pxr_lib ${_houdini_pxr_libs})
    find_library(${_pxr_lib}_path
            NAMES
            ${_pxr_lib}
            PATHS
            ${HOUDINI_BASE}/dsolib
            ${HOUDINI_BASE}/custom/houdini/dsolib/
            REQUIRED
            )

    target_link_libraries(UsdInterface
            INTERFACE
            ${${_pxr_lib}_path}
            )

endforeach()

