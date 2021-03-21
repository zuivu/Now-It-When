TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
	Game \
        UnitTests \

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
UnitTests.depends = CourseLib Game
