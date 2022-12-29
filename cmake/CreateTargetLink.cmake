function(CreateTargetLink target)

  get_target_property(binarydirectory ${target} BINARY_DIR)
  get_target_property(sourcedirectory ${target} SOURCE_DIR)
  get_target_property(binarysuffix ${target} SUFFIX)

  if(binarysuffix_FOUND)
    set(executablename ${target}${binarysuffix})
  else()
    set(executablename ${target})
  endif()

  set (binaryname "${binarydirectory}/${executablename}")
  set (linkname "${sourcedirectory}/${executablename}")

  file(CREATE_LINK ${binaryname} ${linkname} SYMBOLIC)

  message(
    "created executable name ${binaryname} with a link ${linkname}")

endfunction()
