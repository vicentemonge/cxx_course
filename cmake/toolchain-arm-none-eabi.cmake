# Toolchain para Cortex-M4F (STM32F4 y similares). Ajustar -mcpu/-mfpu al target.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(ARCH_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS_INIT
  "${ARCH_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS_INIT
  "${ARCH_FLAGS} -specs=nano.specs -specs=nosys.specs -Wl,--gc-sections -Wl,-Map=output.map")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
