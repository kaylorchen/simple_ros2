ARCH = $(shell arch)

all:
	cd ../.. && colcon build \
	--build-base build_${ARCH} \
	--install-base install_${ARCH} \
	--packages-select simple_ros2

clean:
	cd ../.. && rm -rf build_${ARCH} install_${ARCH} log*

deb:
	fakeroot debian/rules clean
	gbp dch -S -a --snapshot-number='os.popen("git log --pretty=oneline | wc -l").readlines()[0]' 
	fakeroot debian/rules binary

extract:
	rm deb_raw -rf && cd .. && dpkg-deb --raw-extract ./ros-foxy-simple-ros2*.deb ./simple_ros2/deb_raw