# Find if a Python module is installed
# Found at http://www.cmake.org/pipermail/cmake/2011-January/041666.html
# To use do: find_python_module(PyQt4 REQUIRED)
function(find_python_module module)
	string(TOUPPER ${module} module_upper)
	if(NOT PY_${module_upper})
		if(ARGC GREATER 1 AND ARGV1 STREQUAL "REQUIRED")
			set(${module}_FIND_REQUIRED TRUE)
		endif()
		if(ARGC GREATER 1 AND ARGV1 STREQUAL "QUIET")
			set(${module}_FIND_QUIETLY TRUE)
		endif()
		# A module's location is usually a directory, but for binary modules
		# it's a .so file.
		execute_process(COMMAND "${PYTHON_EXECUTABLE}" "-c"
			"import warnings; warnings.catch_warnings(); warnings.simplefilter('ignore'); import re, ${module}; print(re.compile('/__init__.py.*').sub('',${module}.__file__))"
			RESULT_VARIABLE _${module}_status 
			OUTPUT_VARIABLE _${module}_location
			ERROR_QUIET 
			OUTPUT_STRIP_TRAILING_WHITESPACE)
		#message(STATUS "${PYTHON_EXECUTABLE} -c	import re, ${module}; print(re.compile('/__init__.py.*').sub('',${module}.__file__))")

		if(NOT _${module}_status)
			set(PY_${module_upper} ${_${module}_location}
			  CACHE STRING "Location of Python module ${module}")
			#message(STATUS "PY_${module_upper} ${PY_${module_upper}}")
			mark_as_advanced(PY_${module_upper})
		endif(NOT _${module}_status)
	endif(NOT PY_${module_upper})
        if (NOT ${module}_FIND_QUIETLY)
	        find_package_handle_standard_args(PY_${module} DEFAULT_MSG PY_${module_upper})
	endif()
endfunction(find_python_module)
