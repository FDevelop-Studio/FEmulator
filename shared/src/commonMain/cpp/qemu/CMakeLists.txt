cmake_minimum_required(VERSION 3.25)
project(QEMU_CORE C)

if(MSVC)
		add_compile_options(/W0 /D_CRT_SECURE_NO_WARNINGS)
else()
		add_compile_options(-w)
endif()

add_compile_definitions(CONFIG_BLOCK=1 CONFIG_EVENT_LOOP=1)

if(ANDROID)
		add_compile_definitions(CONFIG_KVM=1)
		set(KVM_PLATFORM_SOURCES
			"accel/kvm/kvm-all.c"
			"accel/kvm/kvm-cpus.c"
		)
endif()

add_library(qemu STATIC
	block.c
	blockdev.c
	blockdev-nbd.c
	blockjob.c
	cpu-common.c
	cpu-target.c
	job.c
	job-qmp.c
	lothread.c
	event-loop-base.c
	replication.c
	target-info.c
	${KVM_PLATFORM_SOURCES}
)

target_include_directories(qemu PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(qemu PRIVATE -Os)
