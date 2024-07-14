%module LibraryT 

%{
#include <libraryT/utiles.h>
#include <libraryT/capi.h>
%}

%include std_vector.i
%template(IntVector) std::vector<int>;

// 方法一
// %include carrays.i
// %array_functions(int, IntArray);
// 方法二
%include arrays_java.i
%typemap(jni) (int *arr, int size) "jintArray";
%typemap(jtype) (int *arr, int size) "int[]";
%typemap(jstype) (int *arr, int size) "int[]";
%typemap(javain) (int *arr, int size) "$javainput";
%typemap(in) (int *arr, int size) {
    $1 = (int *) JCALL2(GetIntArrayElements, jenv, $input, NULL);
    $2 = JCALL1(GetArrayLength, jenv, $input);
};
%typemap(freearg) (int *arr, int size) {
    JCALL3(ReleaseIntArrayElements, jenv, $input, (jint*)$1, 0);
}

%include <libraryT/utiles.h>
%include <libraryT/capi.h>