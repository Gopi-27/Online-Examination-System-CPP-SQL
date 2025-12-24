@echo off
cl /EHsc ^
/IG:\instantclient_23_9\sdk\include ^
main.cpp DBConnection.cpp Login.cpp Admin.cpp Instructor.cpp Hod.cpp Student.cpp ^
/link ^
/LIBPATH:G:\instantclient_23_9\sdk\lib\msvc ^
oci.lib oraocci23.lib
pause
