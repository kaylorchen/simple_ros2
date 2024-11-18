ARCH = $(shell arch)
VERSION = $(shell git describe --tags)
MSG = $(shell git log -n 1 --pretty=format:"%s")

all:
	colcon build \
	--build-base build_${ARCH} \
	--install-base install_${ARCH} \
	--packages-select simple_ros2

clean:
	rm -rf build_${ARCH} install_${ARCH} log*

deb:
	rm -rf debian/changelog
	dch --create --package=ros-humble-stardust-clean-robot-base -v ${VERSION} ${MSG}
	fakeroot debian/rules clean
	fakeroot debian/rules binary

extract:
	rm deb_raw -rf && cd .. && dpkg-deb --raw-extract ./ros-foxy-simple-ros2*.deb ./simple_ros2/deb_raw
