test:
	xcodebuild \
		-project proj.ios_mac/Animation.xcodeproj \
		-scheme Animation \
		-sdk iphonesimulator \
		-configuration Debug \
		-destination "platform=iOS Simulator,name=iPhone Retina(4-inch),OS=7.0" \
		clean build test
