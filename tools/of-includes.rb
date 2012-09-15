def of_includes of_dir
	return  %w[
	openFrameworks/3d
	openFrameworks/app
	openFrameworks/communication
	openFrameworks/events
	openFrameworks/gl
	openFrameworks/graphics
	openFrameworks/math
	openFrameworks/sound
	openFrameworks/types
	openFrameworks/utils
	openFrameworks/video
	openFrameworks/
	assimp/include/
	assimp/include/Compiler/
	cairo/include/
	cairo/include/cairo/
	cairo/include/libpng15/
	cairo/include/pixman-1/
	fmodex/include/
	FreeImage/include/
	freetype/include/
	freetype/include/freetype2/
	freetype/include/freetype2/freetype/
	freetype/include/freetype2/freetype/config/
	freetype/include/freetype2/freetype/internal/
	freetype/include/freetype2/freetype/internal/services/
	glew/include/
	glew/include/GL/
	glut/include/
	poco/include/
	poco/include/CppUnit/
	poco/include/Poco/
	poco/include/Poco/DOM/
	poco/include/Poco/Dynamic/
	poco/include/Poco/Net/
	poco/include/Poco/SAX/
	poco/include/Poco/Util/
	poco/include/Poco/XML/
	rtAudio/include/
	].map { |lib|
		"-idirafter #{of_dir}/libs/#{lib}"
	}.join(" ") + " -I #{of_dir}/libs/tess2/include/"
end