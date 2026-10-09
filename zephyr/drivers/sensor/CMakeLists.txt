# Es necesaria la condicion para que se filtre si no esta delcarado
# el sensor en el proyecto.
if(CONFIG_SI7021)
  zephyr_library()
  zephyr_library_sources(si7021.c)
endif()
