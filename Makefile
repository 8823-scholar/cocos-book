PROJECT=proj.ios_mac/Animation.xcodeproj
TARGET="Animation iOS Tests"
DESTINATION="platform=iOS Simulator,name=iPhone Retina(4-inch),OS=7.0"

test:
	xcodebuild \
		-project $(PROJECT) \
		-target $(TARGET) \
		-sdk iphonesimulator \
		-configuration Debug \
		-destination $(DESTINATION) \
		clean build test
