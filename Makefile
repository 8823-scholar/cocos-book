PROJECT=proj.ios_mac/Animation.xcodeproj
SCHEME="Animation iOS"
DESTINATION="platform=iOS Simulator,name=iPhone Retina (4-inch),OS=7.1"

test:
	xcodebuild \
		-project $(PROJECT) \
		-scheme $(SCHEME) \
		-sdk iphonesimulator \
		-configuration Debug \
		-destination $(DESTINATION) \
		clean build test
