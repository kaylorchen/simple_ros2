ARCH = $(shell arch)

all:
	cd ../.. && colcon build \
	--build-base build_${ARCH} \
	--install-base install_${ARCH} \
	--packages-select simple_ros2

clean:
	cd ../.. && rm -rf build_${ARCH} install_${ARCH} log*
